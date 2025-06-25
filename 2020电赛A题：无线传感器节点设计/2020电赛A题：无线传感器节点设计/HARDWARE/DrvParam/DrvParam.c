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
 * \brief    ��������
 * \author   LYQ
 * \version  V1.0
 * \date  	 2020/09/14 10:06 
 *******************************************************************************/
#ifndef _DRVPARAM_C_
#define _DRVPARAM_C_	
#include "DrvParam.h"	
//------------------------------------------------------------------------------
u16 gDrvParamSave[DRVPARAM_ADDR_MAX] = {0};		//Ҫ����Ĳ���

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
void DrvParam_Init(void)
{
	//��������ʼ��
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
\brief  	��ȡָ��FLASH��ַ������

\param[in]	addr  :��ַ
\param[in]	pbuff :����ָ��
\param[in]	len   :���ݳ���
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
		pbuff[i] = *(vu16*)addr;		//��ȡ2���ֽ�.
		addr += 2;						//ƫ��2���ֽ�.	
	}
}

/*!*****************************************************************************
\brief  	��ָ��FLASH��ַд���ݣ���ҳΪ��λ,������������������2KB������1KB��

\param[in]	addr  :ҳ�׵�ַ
\param[in]	pbuff :����ָ��
\param[in]	len   :���ݳ���
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

	FLASH_Unlock();					//����
	FLASH_ErasePage(addr);			//�����������
	for(i=0; i < len; i++)
	{
		FLASH_ProgramHalfWord(addr,pbuff[i]);
		addr += 2;					//��ַ����2.
	}  
	FLASH_Lock();					//����
}






//------------------------------------------------------------------------------
#endif	//END
//------------------------------------------------------------------------------
