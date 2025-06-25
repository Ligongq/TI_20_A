/*******************************************************************************
 * copyright Copyright (C) 2019 SYQ Electronic Co., LTD.
 *
 * Module: Driver
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      LYQ	      2020/09/14 10:06          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     DrvParam.h
 * \brief    参数保存
 * \author   LYQ
 * \version  V1.0
 * \date  	 2020/09/14 10:06 
 *******************************************************************************/
#ifndef _DRVPARAM_C_
#define _DRVPARAM_C_	
#include "DrvParam.h"	
//------------------------------------------------------------------------------
u16 gDrvParamSave[DRVPARAM_ADDR_MAX] = {0};		//要保存的参数

/*!*****************************************************************************
\brief  	初始化

\param[in]	none
\param[out]	none

\return     none
\retval		none

\ingroup	none

\note
	\li		

\author		LYQ 2020/09/14 10:06
*******************************************************************************/
void DrvParam_Init(void)
{
	//检测参数初始化
	DrvParam_FlashRd(DRVPARAM_FLASH_ADDR,gDrvParamSave,DRVPARAM_ADDR_MAX);
	if (gDrvParamSave[DRVPARAM_ADDR_FLAG] != DRVPARAM_FLASH_FLAG)
	{
		gDrvParamSave[DRVPARAM_ADDR_ECG_MOD] = 3;//MODECG_MOD_APP_FIL
		gDrvParamSave[DRVPARAM_ADDR_LMT70_X] = 0;
		gDrvParamSave[DRVPARAM_ADDR_FLAG]    = DRVPARAM_FLASH_FLAG;
		DrvParam_FlashWr(DRVPARAM_FLASH_ADDR, gDrvParamSave, DRVPARAM_ADDR_MAX);
	}
} 

/*!*****************************************************************************
\brief  	读取指定FLASH地址的数据

\param[in]	addr  :地址
\param[in]	pbuff :数据指针
\param[in]	len   :数据长度
\param[out]	none

\return     none
\retval		none

\ingroup	none

\note
	\li		

\author		LYQ 2020/09/14 10:06
*******************************************************************************/
void DrvParam_FlashRd(u32 addr,u16 *pbuff,u16 len)
{
	u16 i;

	for(i=0; i < len; i++)
	{
		pbuff[i] = *(vu16*)addr;		//读取2个字节.
		addr += 2;						//偏移2个字节.	
	}
}

/*!*****************************************************************************
\brief  	在指定FLASH地址写数据，以页为单位,带扇区擦除（大容量2KB，其它1KB）

\param[in]	addr  :页首地址
\param[in]	pbuff :数据指针
\param[in]	len   :数据长度
\param[out]	none

\return     none
\retval		none

\ingroup	none

\note
	\li		

\author		LYQ 2020/09/14 10:06
*******************************************************************************/
void DrvParam_FlashWr(u32 addr,u16 *pbuff,u16 len)
{
	u16 i;

	FLASH_Unlock();					//解锁
	FLASH_ErasePage(addr);			//擦除这个扇区
	for(i=0; i < len; i++)
	{
		FLASH_ProgramHalfWord(addr,pbuff[i]);
		addr += 2;					//地址增加2.
	}  
	FLASH_Lock();					//上锁
}






//------------------------------------------------------------------------------
#endif	//END
//------------------------------------------------------------------------------
