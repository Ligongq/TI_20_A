#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	
#define BEEP PBout(8)	// BEEP,蜂鸣器接口		   

void BEEP_Init(void);	//初始化
		
void LED_Init(void);//初始化

		 				    
#endif
