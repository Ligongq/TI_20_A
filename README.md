# 无线运动传感器节点设计项目

## 🎯 功能概述


- ✅ **心电图(ECG)实时分析**：500Hz采样率，±2bpm临床级精度
- ✅ **呼吸频率检测**：100Hz采样率，±2rpm精度
- ✅ **体表温度测量**：LMT70传感器 + 三阶曲线拟合，±0.05℃精度
- ✅ **运动识别**：MPU6050加速度计，步数统计误差<1.6%
- ✅ **无线传输**：2.4GHz透传模块，100米传输距离
- ✅ **嵌入式显示**：1.3寸LCD实时波形显示


## 📂 项目结构

├── Core/                   // 主控制逻辑与初始化

├── Drivers/                // 外设驱动，如ADC、MPU6050、ADS1292等

├── Display/                // 显示控制模块

├── Wireless/               // 无线透传模块管理

├── Sensors/                // 各传感器模块接口

├── date\_process.c          // 数据预处理与滤波逻辑

├── date\_process.h

├── README.md

---

## 🧠 心电算法核心实现

### ⚙️ QRS波检测流程
```mermaid
graph LR
A[原始ECG信号] --> B[硬件滤波]
B --> C[数字滤波]
C --> D[特征增强]
D --> E[自适应峰值检测]
E --> F[RR间期分析]
F --> G[心率输出]
```

### 🔍 关键技术实现

#### 1. 信号预处理（双重滤波）

- **硬件级滤波**：
  - 150Hz低通滤波（消除肌电干扰）
  - 0.05Hz高通滤波（抑制基线漂移）
- **数字滤波**：
  ```c
  // 50Hz工频陷波滤波器
  void ECG_NotchFilter(int16_t input) {
    static int16_t buffer[3] = {0};
    // 双二阶IIR滤波器实现
    output = b0*input + b1*buffer[0] + b2*buffer[1] 
             - a1*buffer[2] - a2*buffer[3];
    // 更新状态寄存器
    buffer[1] = buffer[0];
    buffer[0] = input;
  }
  ```

#### 2. 特征增强（斜率放大）

```c
// QRS斜率增强处理
int16_t enhance_QRS_slope(int16_t sample) {
    static int16_t prev = 0;
    int16_t slope = abs(sample - prev) * 4; // 斜率放大4倍
    prev = sample;
    return slope;
}
```

#### 3. 自适应峰值检测（核心创新）

```c
// 动态阈值算法
void update_threshold(int16_t peak_value) {
    // 双阈值系统
    peak_threshold = 0.7*peak_threshold + 0.3*peak_value;
    noise_threshold = 0.7*noise_threshold + 0.3*(peak_value/3);
    
    // 保护逻辑
    if (peak_threshold < noise_threshold*2) {
        peak_threshold = noise_threshold*2;
    }
}
```

#### 4. 心率计算（RR间期分析）

```c
// 精准心率计算
void calculate_heart_rate(uint32_t interval) {
    static uint32_t rr_buffer[8] = {0};
    static uint8_t idx = 0;
    
    // 更新缓冲区
    rr_buffer[idx++] = interval;
    idx %= 8;
    
    // 计算平均心率
    uint32_t total = 0;
    for(int i=0; i<8; i++) total += rr_buffer[i];
    heart_rate = (60 * 500 * 8) / total; // 500Hz采样率
}
```

### ⚡ 实时性能优化

1. **处理架构**：
   
   - 中断驱动设计（每2ms处理一个样本）
   - 单样本处理时间<50μs @72MHz
2. **抗干扰机制**：
   
   - **绝对不应期**：200ms内屏蔽二次检测（防T波误判）
   - **信号丢失保护**：>3秒无QRS波自动重置系统
   - **运动伪影抑制**：加速度数据辅助判别
     

## 💡 我的设计思路与实现亮点

1. ​**模块化设计**​：各硬件模块（ECG、温度、运动、无线）独立建构，统一由 STM32 管理，便于移植与调试。
2. ​**自适应心率检测**​：采用 CFAR 思路估计波峰门限，自适应性强，适应不同用户体质差异。
3. ​**三阶温度拟合优化**​：基于 LMT70 曲线特性，引入三阶拟合函数提升温度采样精度。
4. ​**高性能 ADC 设计**​：采用 ADS1256 实现 24bit 精度的模拟数据采样，满足高精度信号还原要求。
5. ​**无线串口透传​**​：便于上位机串口调试和数据分析，同时具有良好的可视化展示潜力。
6. ​**结构创新**​：体温传感器模块采用导热硅脂封装设计，避免空气热阻，提高数据准确性

# 更详细内容见上传的比赛报告
