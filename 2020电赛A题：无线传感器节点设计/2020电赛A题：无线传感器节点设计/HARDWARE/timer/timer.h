#ifndef __TIMER_H
#define __TIMER_H

#define BOOL   bool 

#define SYS_EA_EN()					( __enable_irq() )			//�����ж�
#define SYS_EA_DIS()				( __disable_irq() )			//�����ж�
#define SYS_EXTI0_NVIC_SUBPRI		0							//�ж������ȼ�
#define SYS_UART1_NVIC_SUBPRI		1							//�ж������ȼ�
#define SYS_UART2_NVIC_SUBPRI		2							//�ж������ȼ�
#define SYS_TIM_NVIC_SUBPRI			4							//�ж������ȼ�
#define DebugStr					printf						//�������

//------------------------------------------------------------------------------
#endif
