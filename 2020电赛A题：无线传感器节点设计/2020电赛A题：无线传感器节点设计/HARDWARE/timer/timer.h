#ifndef __TIMER_H
#define __TIMER_H

#define BOOL   bool 

#define SYS_EA_EN()					( __enable_irq() )			//开总中断
#define SYS_EA_DIS()				( __disable_irq() )			//关总中断
#define SYS_EXTI0_NVIC_SUBPRI		0							//中断子优先级
#define SYS_UART1_NVIC_SUBPRI		1							//中断子优先级
#define SYS_UART2_NVIC_SUBPRI		2							//中断子优先级
#define SYS_TIM_NVIC_SUBPRI			4							//中断子优先级
#define DebugStr					printf						//调试输出

//------------------------------------------------------------------------------
#endif
