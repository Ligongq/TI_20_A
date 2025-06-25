#ifndef __TIMER2_H
#define __TIMER2_H
#include "sys.h"

extern uint16_t time_global;

extern int key_count;
extern u8 General_status;
void TIM3_Int_Init(u16 arr,u16 psc);
 


void TIM2_Int_Init(uint32_t arr,uint32_t psc);
void TIM3_PWM_Init(uint32_t arr,uint32_t psc);
#endif
