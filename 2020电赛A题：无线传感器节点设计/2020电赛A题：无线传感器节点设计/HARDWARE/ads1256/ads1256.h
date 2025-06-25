/*
*********************************************************************************************************
*                                                康威科技
*	模块名称 : ADS1256 驱动模块(8通道带PGA的24位ADC)
*	文件名称 : bsp_ads1256.h
*
*********************************************************************************************************
*/
/*
    ADS1256模块    STM32开发板
      +5V   <------  5.0V      5V供电
      GND   -------  GND       地

      DRDY  ------>  PC3       准备就绪
      CS    <------  PC12      SPI_CS
      DIN   <------  PC10      SPI_MOSI
      DOUT  ------>  PC9       SPI_MISO
      SCLK  <------  PC11      SPI时钟
      GND   -------  GND       地
      PDWN  <------  PC8       掉电控制 常高
      RST   <------  PC13      复位信号 常高
      NC   空脚
      NC   空脚
*/
#ifndef _ADS1256_H
#define _ADS1256_H
#include "sys.h"

	#define RCC_SCK 	RCC_APB2Periph_GPIOC
	#define PORT_SCK	GPIOC
	#define PIN_SCK		GPIO_Pin_11

	#define RCC_DIN 	RCC_APB2Periph_GPIOC
	#define PORT_DIN	GPIOC
	#define PIN_DIN		GPIO_Pin_10

	#define RCC_CS 		RCC_APB2Periph_GPIOC
	#define PORT_CS		GPIOC
	#define PIN_CS		GPIO_Pin_12

	#define RCC_DRDY 	RCC_APB2Periph_GPIOC
	#define PORT_DRDY	GPIOC
	#define PIN_DRDY	GPIO_Pin_3

	#define RCC_DOUT 	RCC_APB2Periph_GPIOC
	#define PORT_DOUT	GPIOC
	#define PIN_DOUT	GPIO_Pin_9

	#define RCC_SYNC 	RCC_APB2Periph_GPIOC
	#define PORT_SYNC	GPIOC
	#define PIN_SYNC	GPIO_Pin_8
	
	#define RCC_RST 	RCC_APB2Periph_GPIOC
	#define PORT_RST	GPIOC
	#define PIN_RST	GPIO_Pin_13
//RST->HIGH	PC13
//SYNC->HIGH PC8
	/* 定义口线置0和置1的宏 */
	#define CS_0()		GPIO_ResetBits(PORT_CS, PIN_CS)
	#define CS_1()		GPIO_SetBits(PORT_CS, PIN_CS)

	#define SCK_0()		GPIO_ResetBits(PORT_SCK, PIN_SCK)
	#define SCK_1()		GPIO_SetBits(PORT_SCK, PIN_SCK)

	#define DI_0()		GPIO_ResetBits(PORT_DIN, PIN_DIN)
	#define DI_1()		GPIO_SetBits(PORT_DIN, PIN_DIN)
	
	#define SYNC_0()		GPIO_ResetBits(PORT_SYNC, PIN_SYNC)
	#define SYNC_1()		GPIO_SetBits(PORT_SYNC, PIN_SYNC)
	
	#define RST_0()		GPIO_ResetBits(PORT_RST, PIN_RST)
	#define RST_1()		GPIO_SetBits(PORT_RST, PIN_RST)

	#define DO_IS_HIGH()	(GPIO_ReadInputDataBit(PORT_DOUT, PIN_DOUT) == Bit_SET)

	#define DRDY_IS_LOW()	(GPIO_ReadInputDataBit(PORT_DRDY, PIN_DRDY) == Bit_RESET)

/* 增益选项 */
typedef enum
{
	ADS1256_GAIN_1			= (0),	/* 增益1（缺省） */
	ADS1256_GAIN_2			= (1),	/* 增益2 */
	ADS1256_GAIN_4			= (2),	/* 增益4 */
	ADS1256_GAIN_8			= (3),	/* 增益8 */
	ADS1256_GAIN_16			= (4),	/* 增益16 */
	ADS1256_GAIN_32			= (5),	/* 增益32 */
	ADS1256_GAIN_64			= (6),	/* 增益64 */
}ADS1256_GAIN_E;

/* 采样速率选项 */
/* 数据转换率选择
	11110000 = 30,000SPS (default)
	11100000 = 15,000SPS
	11010000 = 7,500SPS
	11000000 = 3,750SPS
	10110000 = 2,000SPS
	10100001 = 1,000SPS
	10010010 = 500SPS
	10000010 = 100SPS
	01110010 = 60SPS
	01100011 = 50SPS
	01010011 = 30SPS
	01000011 = 25SPS
	00110011 = 15SPS
	00100011 = 10SPS
	00010011 = 5SPS
	00000011 = 2.5SPS
*/
typedef enum
{
	ADS1256_30000SPS = 0,
	ADS1256_15000SPS,
	ADS1256_7500SPS,
	ADS1256_3750SPS,
	ADS1256_2000SPS,
	ADS1256_1000SPS,
	ADS1256_500SPS,
	ADS1256_100SPS,
	ADS1256_60SPS,
	ADS1256_50SPS,
	ADS1256_30SPS,
	ADS1256_25SPS,
	ADS1256_15SPS,
	ADS1256_10SPS,
	ADS1256_5SPS,
	ADS1256_2d5SPS,

	ADS1256_DRATE_MAX
}ADS1256_DRATE_E;

#define ADS1256_DRAE_COUNT = 15;

typedef struct
{
	ADS1256_GAIN_E Gain;		/* 增益 */
	ADS1256_DRATE_E DataRate;	/* 数据输出速率 */
	int32_t AdcNow[8];			/* 8路ADC采集结果（实时）有符号数 */
	uint8_t Channel;			/* 当前通道 */
	uint8_t ScanMode;			/* 扫描模式，0表示单端8路， 1表示差分4路 */
}ADS1256_VAR_T;

void bsp_InitADS1256(void);
void ADS1256_CfgADC(ADS1256_GAIN_E _gain, ADS1256_DRATE_E _drate);

uint8_t ADS1256_ReadChipID(void);
void ADS1256_StartScan(uint8_t _ucScanMode);
void ADS1256_StopScan(void);
int32_t ADS1256_GetAdc(uint8_t _ch);

extern ADS1256_VAR_T g_tADS1256;

#endif

