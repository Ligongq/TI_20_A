#include "timer.h"
#include "ADS1292.h"
//typedef struct		//变量结构体
//{	
//	u8  sta;		//状态
//	u8  cnt;		//计数
//	u8  time;		//超时
//	u8  buff[32];	//缓存
//}strModPc;
//static strModPc sModPc = {0};

//strDrvSysTime gDrvSysTime = {0};	//系统时钟变量

//void DrvSys_Time4Init(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

//	//-------------------------------------------------------------------
//	//NVIC 中断配置
//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SYS_TIM_NVIC_SUBPRI;//子优先级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);								//根据指定的参数初始化VIC寄存器

//	/* ---------------------------------------------------------------
//	=> TIMxCLK ( TIM_CKD_DIV1 ) = SystemCoreClock = 72 MHz
//	Period / (72M / (Prescaler+1) )=____ 秒
//	100　/ ( 72M / ( 7199 + 1 ) ) = 0.001 S
//	--------------------------------------------------------------- */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//	TIM_TimeBaseStructure.TIM_Period = 100;						//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
//	TIM_TimeBaseStructure.TIM_Prescaler =(720-1);				//设置用来作为TIMx时钟频率除数的预分频值 
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);				//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
//	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);					//使能更新中断源	
//	TIM_Cmd(TIM4, ENABLE);										//使能中断
//}
////------------------------------------------------------------------------------
//void TIM4_IRQHandler(void)  
//{
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	//检查指定的TIM中断发生与否:TIM 中断源 
//	{
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);		//清除TIMx的中断待处理位:TIM 中断源 

//		gDrvSysTime.flg1ms = TRUE;

//		gDrvSysTime.cnt10ms++;
//		if (gDrvSysTime.cnt10ms == 10)
//		{
//			gDrvSysTime.cnt10ms = 0;
//			gDrvSysTime.flg10ms = TRUE;
//		}

//		gDrvSysTime.cnt100ms++;
//		if (gDrvSysTime.cnt100ms == 100)
//		{
//			gDrvSysTime.cnt100ms = 0;
//			gDrvSysTime.flg100ms = TRUE;
//		}
//	}
//}

