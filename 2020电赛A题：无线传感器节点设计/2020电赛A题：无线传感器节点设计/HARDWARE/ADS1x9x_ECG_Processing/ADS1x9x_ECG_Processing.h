#ifndef ADS1x9x_ECG_PROCESSING_H_
#define ADS1x9x_ECG_PROCESSING_H_

//! \brief MAX_PEAK_TO_SEARCH
//!
#define MAX_PEAK_TO_SEARCH 				5

//! \brief MAXIMA_SEARCH_WINDOW
//!
#define MAXIMA_SEARCH_WINDOW			40

//! \brief MINIMUM_SKIP_WINDOW
//!
#define MINIMUM_SKIP_WINDOW				50

//! \brief SAMPLING_RATE
//!
#define SAMPLING_RATE					250//500

//! \brief TWO_SEC_SAMPLES
//!
#define TWO_SEC_SAMPLES  				2 * SAMPLING_RATE

/*threshold = maxima * N / 10   */
#define QRS_THRESHOLD_FRACTION			5//0.7					
	
//! \brief MAXCHAN
//!
#define MAXCHAN							2

//! \brief FILTERORDER
//!
#define FILTERORDER 					161

#define TRUE							1
#define FALSE							0

//! \brief MUSCLE_ARTIFACT_FILTER
//!
#define MUSCLE_ARTIFACT_FILTER			1

//! \brief NOTCHFILTERSEL
//!
#define NOTCHFILTERSEL					1		// 0 - 50 Hz Notch filter
											// 1 - 60 Hz Notch filter

//! \brief DC Removal Numerator Coeff
//!
#define NRCOEFF							(0.992)

enum emADS1x9x
{
	ADS1191_16BIT = 0,
	ADS1192_16BIT,
	ADS1291_24BIT,
	ADS1292_24BIT
};

//-------------------------------------------------
extern unsigned short QRS_Heart_Rate;
extern short ECGFilteredData[4];

//*****************************************************************************
//
//! \此函数由主采集线程在

//!样本读取。在调用进程_buffer（）之前，请执行以下检查

//!必须这么做。i、 我们以前一直收到2个样品

//!开始处理每个样本。这个功能基本上

//!检查当前和以前的ECG样本之间的差异

//!使用第一和第二微分计算。
//
//! \param Lead     II sample CurrSample
//
//! \return  None
//
//*****************************************************************************
void QRS_Algorithm_Interface(short CurrSample);

//*****************************************************************************
//
//! \简述161阶FIR单采样滤波的功能过程

//!多波段滤波器0.5 t0 150 Hz和50/60Hz线鼻子。这个

//!函数支持编译时50/60赫兹选项

//
//! \输入样本缓冲区中的参数WorkingBuff

//! \FIR滤波器参数系数。

//! \param FilterOut Out-过滤输出
//
//! \return  None
//
//*****************************************************************************
void ECG_FilterProcess(short * WorkingBuff, short * CoeffBuf, short* FilterOut);

//*****************************************************************************
//
//! \这个函数叫做呼吸检测和

//!心率检测功能。在调用每个函数之前，函数

//!确保ECG IC支持该模式。例如不是全部

//!ADS1x9x支持呼吸速率计算.
//
//! \param none     none
//
//! \return  None
//
//*****************************************************************************
void ADS1x9x_Filtered_ECG(unsigned char IDreg, long*ptECGdata);
void ADS1x9x_Filtered_ECG_Task4(unsigned char IDreg, long *ptECGdata);

//*****************************************************************************
//
//! \简要说明函数过程一次一个数据样本和存储

//!Leadinfobuff中筛选出的样本。函数执行

//!跟随。

//!-直流移除电流样本

//!-多波段161 Tab FIR滤波器，带50 Hz/60Hz的陷波。

//

//! \参数ECG\U WorkingBuff In-ECG。输入样本缓冲区

//! \param FilterOut Out-过滤输出
//
//! \return  None
//
//*****************************************************************************
//void ECG_ProcessCurrSample(short *CurrAqsSample, short *FilteredOut);

//*****************************************************************************
//
//! \简要说明函数过程一次一个数据样本和存储

//!Leadinfobuff中筛选出的样本。函数执行

//!跟随。

//!-直流移除电流样本

//!-多波段161 Tab FIR滤波器，带50 Hz/60Hz的陷波。

//

//! \参数ECG\U WorkingBuff In-ECG。输入样本缓冲区

//! \param FilterOut Out-过滤输出
//
//! \return  None
//
//*****************************************************************************
//void ECG_ProcessCurrSample_ch0(short *CurrAqsSample, short *FilteredOut);

//*****************************************************************************
//
//! \此函数使用顺序计算QRS峰值的持续时间

//!差分输入样本并计算QRS U电流样本。

//!在我们处理数据之后，我们可以测量心率。它使计算机静音

//!以防导线断开。

//

//! \参数缩放结果

//! \参数QRS_心率和心率标志
//
//! \return  None
//
//*****************************************************************************
//static void QRS_check_sample_crossing_threshold( unsigned short scaled_result );

//*****************************************************************************
//
//! \这个函数将做一阶和二阶微分

//!对于输入样本，QRS U电流_样品。之后我们可以处理数据

//! 填充QRS_Proc_Data_Buffer，它是HR计算的输入

//!算法。此函数针对每个n调用样本。一次我们有

//!在B4缓冲器中接收到6s的处理数据（即采样率*6）

//!我们将首次开始计算心率，稍后

//!一旦我们收到规定的数字，我们会计算心率

//!预期刷新秒数的样本数。
//
//! \param none     none
//
//! \return  None
//
//*****************************************************************************
//static void QRS_process_buffer( void );

#endif /*ADS1x9x_ECG_PROCESSING_H_*/
