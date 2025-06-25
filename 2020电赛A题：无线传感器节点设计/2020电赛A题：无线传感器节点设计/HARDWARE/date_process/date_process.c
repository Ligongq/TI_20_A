#include "date_process.h"
#include "stdio.h"
#include "stm32f10x.h"
#include "timer.h"


u32 MedianFilter(u32* pData,u8 nSize)//中指滤波
{
	u8  i;
	u32 sum=0,max=pData[0],min=pData[0];

	for(i = 0; i < nSize; i++)
	{
		sum += pData[i];            
		if(pData[i] > max) max = pData[i];  
		if(pData[i] < min) min = pData[i];
	}

	sum = sum-max-min;      
	return (sum/(nSize-2));          
}
//u32 Now_Date=0;
//u16 Last_Max=0,Previous_Max=0,Last_Min=1000,Previous_Min=1000,All_Max=0,All_Min=1000;
//u16 start=0,stop=0;
//u16 cha1=0,he1=0;
//float hecha=0.0;
//u8 mode=0;
//u8 moshi=0;
//u32 shijian=0,jishu=0;
//#define yuchuli 2000
//#define chuli 6000
//void Selsct_Max_Min(void)
//{
//    if(Now_Date>Last_Max&&Last_Max>Previous_Max)//判断波形开始上升
//		{
//            if(mode!=1)
//				{
//           	start = Previous_Max;
//          }
//      mode = 1;
//			Last_Max= Now_Date;
//			if(Last_Max>All_Max)
//			{
//				All_Max = Last_Max;//历史最大值点
//			}
//		}
//		else if(Now_Date<Last_Min&&Last_Min<Previous_Min)
//		{
//			Last_Min = Now_Date;
//			if(Last_Min<All_Min)
//			{
//				All_Min = Last_Min;//历史最小值点
//			}
//		}
//		Previous_Max = Last_Max;
//		Previous_Min = Last_Min;
//		Last_Max = Now_Date;
//		Last_Min = Now_Date;
//		cha1 =All_Max-All_Min;
//}
//void GuiYiHua_Init(void)
//{
//	Last_Max=0;
//	Previous_Max=0;
//	Last_Min=1000;
//	Previous_Min=1000;
//	All_Max=0;
//	All_Min=1000;
//	max1=-100000;
//	min1=-1000;
//	max2=-100000;
//	min2=-1000;
//	max0=-100000;
//	min0 = -1000;
//}
//void Start_Mode(void)//整个过程需要十秒
//{
//	if ( moshi == 1 )//自适应阶段
//	{
//		shijian++;//1秒=500shijian
//		guiyihua();
//	}
//	if ( shijian == yuchuli && moshi == 1)//适应结束开始计数
//	{
//		moshi = 2;
//		jishu ++;
//		if ( jishu <= chuli)
//		{
//						//计数处理
//		
//			if ( jishu == chuli)
//			{
//				jishu = 0;
//				shijian = 0;
//				moshi =0;
//			}
//		}
//	}

//}




