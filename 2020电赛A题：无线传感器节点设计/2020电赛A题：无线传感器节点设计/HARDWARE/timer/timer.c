#include "timer.h"
#include "ADS1292.h"
//typedef struct		//�����ṹ��
//{	
//	u8  sta;		//״̬
//	u8  cnt;		//����
//	u8  time;		//��ʱ
//	u8  buff[32];	//����
//}strModPc;
//static strModPc sModPc = {0};

//strDrvSysTime gDrvSysTime = {0};	//ϵͳʱ�ӱ���

//void DrvSys_Time4Init(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

//	//-------------------------------------------------------------------
//	//NVIC �ж�����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SYS_TIM_NVIC_SUBPRI;//�����ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);								//����ָ���Ĳ�����ʼ��VIC�Ĵ���

//	/* ---------------------------------------------------------------
//	=> TIMxCLK ( TIM_CKD_DIV1 ) = SystemCoreClock = 72 MHz
//	Period / (72M / (Prescaler+1) )=____ ��
//	100��/ ( 72M / ( 7199 + 1 ) ) = 0.001 S
//	--------------------------------------------------------------- */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//	TIM_TimeBaseStructure.TIM_Period = 100;						//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseStructure.TIM_Prescaler =(720-1);				//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM���ϼ���ģʽ
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);				//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
//	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);					//ʹ�ܸ����ж�Դ	
//	TIM_Cmd(TIM4, ENABLE);										//ʹ���ж�
//}
////------------------------------------------------------------------------------
//void TIM4_IRQHandler(void)  
//{
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	//���ָ����TIM�жϷ������:TIM �ж�Դ 
//	{
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);		//���TIMx���жϴ�����λ:TIM �ж�Դ 

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

