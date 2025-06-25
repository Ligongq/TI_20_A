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
#ifndef _DRVPARAM_H_
#define _DRVPARAM_H_
#include "Sys.h"	
//------------------------------------------------------------------------------
//���ݺ궨��
#define DRVPARAM_FLASH_ADDR		0x800FC00  
#define DRVPARAM_FLASH_FLAG		0x55AA

//------------------------------------------------------------------------------
typedef enum //�Ĵ�����ַ
{
	DRVPARAM_ADDR_ECG_MOD,		//0 ͼ����ʾ����ģʽ sModECG_Mode
	DRVPARAM_ADDR_LMT70_X,		//1 LMT70ƫ����ֵ
	DRVPARAM_ADDR_FLAG,			//������־
	DRVPARAM_ADDR_MAX
}emDRVPARAM_ADDR;
extern u16 gDrvParamSave[DRVPARAM_ADDR_MAX];


//------------------------------------------------------------------------------
//��������
void DrvParam_Init(void);
void DrvParam_FlashRd(u32 addr,u16 *pbuff,u16 len);
void DrvParam_FlashWr(u32 addr,u16 *pbuff,u16 len);




//------------------------------------------------------------------------------
#endif	//END
//------------------------------------------------------------------------------
