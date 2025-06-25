/*******************************************************************************
 * copyright Copyright (C) 2019 SYQ Electronic Co., LTD.
 *
 * Module: MODULE
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      LYQ	      2020/09/14 10:06          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     ModTemper.c
 * \brief    �¶ȴ���
 * \author   LYQ
 * \version  V1.0
 * \date  	 2020/09/14 10:06 
 *******************************************************************************/
#ifndef _MODTEMPER_C_
#define _MODTEMPER_C_	 
#include "ModTemper.h"	
//------------------------------------------------------------------------------
u16 gModTemperDat = 0;
s16 gModTemperErv = 0;

/*!*****************************************************************************
\brief  	��ʼ��

\param[in]	none
\param[out]	none

\return     none
\retval		none

\ingroup	none

\note
	\li		

\author		LYQ 2020/09/14 10:06
*******************************************************************************/
void ModTemper_Init(void)
{
	gModTemperErv = gDrvParamSave[DRVPARAM_ADDR_LMT70_X];
}

/*!*****************************************************************************
\brief  	��ʼ��

\param[in]	none
\param[out]	none

\return     none
\retval		none

\ingroup	none

\note
	\li		

\author		LYQ 2020/09/14 10:06
*******************************************************************************/
void ModTemper_Run100ms(void)
{
	u32 tdat;
	float tvol,temp;

	tdat = DrvAD7799_GetVol();				//��ȡADCֵ
	tvol = (float)tdat * 2500 / 16777216L;	//ת����ѹmV
	temp = (-0.0000078579)*tvol*tvol + (-0.1777501)*tvol + 204.6398;
	gModTemperDat = temp*100 + gModTemperErv;
	//DebugStr("Lmt70,vol=%.4f,temp=%.1f\r\n",tvol,temp);
}

/*!*****************************************************************************
\brief  	����ƫ��ֵ

\param[in]	indat��ƫ��ֵ
\param[out]	none

\return     none
\retval		none

\ingroup	none

\note
	\li		

\author		LYQ 2020/09/14 10:06
*******************************************************************************/
void ModTemper_SetErv(s16 indat)
{
	gModTemperErv = indat;
	gDrvParamSave[DRVPARAM_ADDR_LMT70_X] = indat;
	DrvParam_FlashWr(DRVPARAM_FLASH_ADDR, gDrvParamSave, DRVPARAM_ADDR_MAX);
}


//------------------------------------------------------------------------------
#endif	//END
//------------------------------------------------------------------------------
