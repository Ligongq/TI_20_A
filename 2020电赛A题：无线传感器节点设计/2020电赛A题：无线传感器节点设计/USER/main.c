#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "ads1256.h"
#include "ADS1292.h"
#include "stdio.h"
#include "dma.h"
#include "date_process.h"
#include "ADS1x9x_Resp_Processing.h"
#include "ADS1x9x_ECG_Processing.h"
#include "mpu6050.h"  
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "math.h"
#include "timer2.h"
/********************************************************
 *************************Define************************
********************************************************/
#define Key_delay  0
#define Key_close  1
#define Key_last_delay 3
/********************************************************
 *************************KEY����************************
********************************************************/
volatile u8 taskID = 0;
u8 count = 0;
u8 Key_state = Key_close;
u8 General_status = 1; //��ʼϵͳ״̬����Ϊ1
/********************************************************
 *************************ECG����************************
********************************************************/
u8 LeadStatus=0;
s32 cannle[4];	//�洢����ͨ��������
s32	p_Temp[4];	//���ݻ���
u8 data_to_send[40]={0},s_cnt=0;//���ڷ��ͻ���
u8 Task5_Date_Send[10]={0};
/*********************************************************
 * **********************LMT70����*************************
 * *******************************************************/
u32 viol=0;//ads1256ת���������ź�
u32 volt=0;//����֮��ĵ�ѹֵ
float Task2_temp=0.0,Last_Task2_Temp=0.0;//ʵ���¶�ֵ	
u16 int_Last_Task2_Temp=0;//for TASK5
u16 int_Last_Task4_Temp=0;//for TASK5
u16 float_Last_Task2_temp=0;
u16 temp_i =0;//ʵ���¶�
u32 tempsum = 0;//�˲����
/********************************************************
 *************************SPRORT����*********************
********************************************************/
short A_Total=0;
float mpu6050_a=0.0;
u16 time1=0;
uint16_t time_global = 0; 
float pitch,roll,yaw; 		//ŷ����
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;	//������ԭʼ����
short temp;					//�¶�
u8 record_steps = 0;//�Ʋ�
u32 steps_length =0 ;//����
u32 integer = 0;//��������λ
u32 decimal = 0;//����С��
/********************************************************
 **********************LAST����**************************
********************************************************/
u16 tempt =0;//����4
u16 Sum_Task1 = 0,Sum_Task4=0;//���
u8 Task1_i =0,Task4_i=0,Task2_i=0;//����i
/********************************************************
 * *********************�����궨��***********************
 * ******************************************************/
s32 get_volt(u32 num);//�Ѳɵ���3���ֽڲ���ת���з���32λ��
void wangge(void);//������
void ModECG_Task_1(void);
void ModECG_Task_2(void);
void ModECG_Task_3(void);
void ModECG_Task_4(void);
void ModECG_Task_1_For_4(void);
void ModECG_Tsk_3_for_4(void);
void ALL_INIT_SHOW(void);
void ALL_INIT(void);
void ModECG_Tsk_2_for_4(void);
void ModECG_Task_5(void);
/********************************************************
 * ************************Main����**********************
 * *****************************************************/
int main(void)
{ 
	ALL_INIT();
	while(1)
	{
		 switch(General_status)
		 	{
		 		case 1:
		 			taskID = 1; //ModECG_Task_1();
		 			break;
		 		case 2:
		 			taskID = 2;//LMT70
		 			break;
		 		case 3:
		 			taskID = 3;//�Ʋ�+����
		 			break;
		 		case 4:
		 			taskID = 4;
		 			break;
				case 5:
					taskID = 5;
				  break;
		 		default:
		 			break;
		 }
		LCD_ShowNum(100,150,(u32)taskID,1,12);
	}
}
void ALL_INIT(void)
{
	  u8 id=0;
		SystemInit();
		delay_init();	    	 
		delay_ms(100);	
		uart_init(115200);	
		LED_Init();		  	
		BEEP_Init(); 	//��ʼ��LCD
		uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
		POINT_COLOR=RED;//��������Ϊ��ɫ
		delay_ms(100);		
		delay_ms(100);
		bsp_InitADS1256();
		delay_ms(100);
		ADS1292_Init();	
		MPU_Init();					//��ʼ��MPU6050
		delay_ms(100);
		TIM2_Int_Init(71999, 0);//1ms
		TIM3_Int_Init(99,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  ������100Ϊ10ms
		KEY_Init();				//������ʼ��
		id = ADS1256_ReadChipID();	
		while(Set_ADS1292_Collect(0))//0 �����ɼ�  //1 1mV1Hz�ڲ������ź� //2 �ڲ��̽���������
		{
			printf("1292�Ĵ�������ʧ��\r\n");
			LCD_ShowString_N(15,56,240,24,24,"ADS1292 init: error");
			delay_ms(1000);		
		}	
		while(id!=3)
		{
			printf("error");
			printf("Id is %d" ,id);
			LCD_ShowString_N(50,56,240,24,24,"ADS1256 init: error");
			delay_ms(1000);
		}
		while(mpu_dmp_init())
 		{
			delay_ms(10);
			LCD_ShowString_N(70,130,200,16,16,"MPU6050 Error");
			delay_ms(200);
			LCD_Fill(30,130,239,130+16,BLACK);
		}	
		DMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)data_to_send);//����1DMA����
		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //DMA	
		EXTI->IMR |= EXTI_Line8;//��DRDY�ж�	 
		ADS1256_CfgADC(ADS1256_GAIN_1, ADS1256_100SPS);	/* ����ADC������ ����1:1, ����������� 15Hz */
		ADS1256_StartScan(0);	/* �����ж�ɨ��ģʽ. 0��ʾ����8·��1��ʾ���4· */		
		ALL_INIT_SHOW();

		delay_ms(100);
}
void ALL_INIT_SHOW(void)
{
	LCD_Clear(BLACK);
	showhz32str(20,0,"�����˶��������ڵ�",RED,BLACK);
	LCD_ShowString_N(15,33,400,24,24,"Heart rate:        bpm");
	LCD_ShowString_N(15,60,600,24,24,"Temperature:   .   C");
	LCD_ShowString_N(15,84,200,24,24,"Step number:");
	LCD_ShowString_N(15,108,400,24,24,"Distance:          CM");
	LCD_ShowString_N(15,150,400,24,24,"Task:");
}
 s32 get_volt(u32 num)
{
			s32 temp;			
			temp = num;
			temp <<= 8;
			temp >>= 8;
			return temp;
}
void ModECG_Task_1(void)
{
	Sum_Task1=0;
	s_cnt=0;
	//if(ads1292_recive_flag)//
	//{
		cannle[0]=ads1292_Cache[0]<<16 | ads1292_Cache[1]<<8 | ads1292_Cache[2];	
		cannle[1]=ads1292_Cache[3]<<16 | ads1292_Cache[4]<<8 | ads1292_Cache[5];	
		cannle[2]=ads1292_Cache[6]<<16 | ads1292_Cache[7]<<8 | ads1292_Cache[8];
		ADS1x9x_Filtered_ECG_Task4(ADS1292_DEVICE, cannle);
		cannle[0] = cannle[0] & 0x0F8000;
		cannle[0] = cannle[0] >> 15;
		LeadStatus = cannle[0]&0x00FF;
		data_to_send[s_cnt++] = 0xAA;							
		data_to_send[s_cnt++] = 0xAA;							
		data_to_send[s_cnt++] = 0xF1;	 
		data_to_send[s_cnt++] = 10;							
		data_to_send[s_cnt++] = 0;				//Heart Rate
		data_to_send[s_cnt++] = 0;				//Respiration
		data_to_send[s_cnt++] = 0;					//����
		data_to_send[s_cnt++] = 0;					//����
		data_to_send[s_cnt++] = 0;				//�ߵľ���	
		data_to_send[s_cnt++] = 0;				//Heart Rate
		data_to_send[s_cnt++] = 0;				//Respiration Rate
		data_to_send[s_cnt++] = 0;					//����		
		data_to_send[s_cnt++] = ECGFilteredData[1] >> 8;		//CH2		
		data_to_send[s_cnt++] = ECGFilteredData[1];	
		for(Task1_i=0;Task1_i<s_cnt;Task1_i++)
		Sum_Task1 += data_to_send[Task1_i];							
	 	data_to_send[s_cnt] = Sum_Task1;	//У���																		
	 	DMA_Enable(DMA1_Channel4,s_cnt);//����1DMA
		ads1292_recive_flag=0;
	LCD_ShowNum(190,33,QRS_Heart_Rate,3,16);//ADS1292������ʾ
}

void ModECG_Task_1_For_4(void)
{
	//if(ads1292_recive_flag)
	//{
		cannle[0]=ads1292_Cache[0]<<16 | ads1292_Cache[1]<<8 | ads1292_Cache[2];	
		cannle[1]=ads1292_Cache[3]<<16 | ads1292_Cache[4]<<8 | ads1292_Cache[5];	
		cannle[2]=ads1292_Cache[6]<<16 | ads1292_Cache[7]<<8 | ads1292_Cache[8];
		ADS1x9x_Filtered_ECG(ADS1292_DEVICE, cannle);
		cannle[0] = cannle[0] & 0x0F8000;
		cannle[0] = cannle[0] >> 15;
		LeadStatus = cannle[0]&0x00FF;
		ads1292_recive_flag=0;
	//}
}
void ModECG_Task_2(void)//LMT70
{
		float Task2_viol_Exchange=0.0;
		u16 Task2_x=0,Task2_y=0;
	//	if(DRDY_IS_LOW())
	//{
		u32 tdat=0;
		viol = ADS1256_GetAdc(1);
		tempsum += viol;
		Task2_i++;
		if(Task2_i==20)
		{
		volt = tempsum/20;
		Task2_i = 0;
		Task2_viol_Exchange = ((float)volt * 2500) / 4165270L ;//4165300
		Task2_temp =(-0.0000078579)*Task2_viol_Exchange*Task2_viol_Exchange + (-0.1777501)*Task2_viol_Exchange + 204.6398;
		Last_Task2_Temp = (Task2_temp+1.30);
		//Task2_y =tempsum - (Task2_x*100);
		tempsum=0;
		LCD_ShowxNum(169,60,(u32)Last_Task2_Temp,2,24,0);//ǰ��λLMT70�¶���ʾ
//		((u32)((Last_Task2_Temp-((u32)Last_Task2_Temp))*100))
		LCD_ShowxNum(205,60,((u32)((Last_Task2_Temp-((u32)Last_Task2_Temp))*100)),2,24,0);//����λLMT70�¶���ʾ
	}
}
void ModECG_Tsk_2_for_4(void)//LMT70
{
		float Task2_viol_Exchange=0.0;
	//if(DRDY_IS_LOW())
	//{
		u32 tdat=0;
		viol = ADS1256_GetAdc(1);
		tempsum += viol;
		Task2_i++;
		if(Task2_i==20)
		{
		volt = tempsum/20;
		Task2_i = 0;
		Task2_viol_Exchange = ((float)volt * 2500) / 4165270L ;//4165300
		Task2_temp =(-0.0000078579)*Task2_viol_Exchange*Task2_viol_Exchange + (-0.1777501)*Task2_viol_Exchange + 204.6398;
		Last_Task2_Temp = (Task2_temp+1.30);
		int_Last_Task4_Temp = (u16)(Last_Task2_Temp * 100);
		int_Last_Task2_Temp = (u8)(Last_Task2_Temp);
		float_Last_Task2_temp = (u8)((Last_Task2_Temp - int_Last_Task2_Temp)*100);
		tempsum=0;
		}
	//}
}
void ModECG_Task_3(void)//�Ʋ�+����
{
		if(MPU_Get_Accelerometer(&aacx,&aacy,&aacz) == 0)
		{
			A_Total = (short)sqrt(aacx * aacx + aacy * aacy + aacz * aacz);//������ά�ռ�ļ��ٶ��ܺ� 
			mpu6050_a = (float)A_Total / 16384 * 10;
			if((mpu6050_a > 13.7) || (mpu6050_a < 6.8))//�Ʋ�
			{
				if(fabs(time_global - time1) > 3000)//10ms
				{
					time1 = time_global;
					record_steps++;
			//	LCD_ShowNum(30,300, (u32)record_steps,3,16);
					steps_length = record_steps*63;     // ��λ �� cm   69.1
					integer = (u32)steps_length;
					decimal = (u32)((steps_length-integer)*10);
					LCD_ShowxNum(180,84,(u32)record_steps,3,24,0);//������ʾ
					LCD_ShowxNum(180,108,steps_length,4,24,0);//4λ������ʾ�����ף�
				}
			}
		}	
//		if(TPAD_Scan(0))
//		{
//			record_steps--;
//			steps_length = steps_length-69;
//		}
}
void ModECG_Tsk_3_for_4(void)
{
		if(MPU_Get_Accelerometer(&aacx,&aacy,&aacz) == 0)
		{
			A_Total = (short)sqrt(aacx * aacx + aacy * aacy + aacz * aacz);//������ά�ռ�ļ��ٶ��ܺ� 
			mpu6050_a = (float)A_Total / 16384 * 10;
			if(mpu6050_a > 13.7 || mpu6050_a < 6.8)//�Ʋ�
			{
				if(fabs(time_global - time1) > 3000)//10ms
				{
					time1 = time_global;
					record_steps++;					
					steps_length = (u16)record_steps*63;     // ��λ �� cm   69.1
				}
			}
		}
}
void ModECG_Task_4(void)
{
		s_cnt=0;
		Sum_Task4=0;	
		ModECG_Task_1_For_4();
		ModECG_Tsk_2_for_4();
		ModECG_Tsk_3_for_4();
		data_to_send[s_cnt++] = 0xAA;							
		data_to_send[s_cnt++] = 0xAA;							
		data_to_send[s_cnt++] = 0xF1;	 
		data_to_send[s_cnt++] = 10;							
		data_to_send[s_cnt++] = QRS_Heart_Rate;				//Heart Rate
		data_to_send[s_cnt++] = int_Last_Task4_Temp>>8;				//Respiration Rate
		data_to_send[s_cnt++] = int_Last_Task4_Temp;				//Respiration Rate
		data_to_send[s_cnt++] = record_steps;					//����
		data_to_send[s_cnt++] = steps_length>>8;				//�ߵľ���
		data_to_send[s_cnt++] = steps_length;
		data_to_send[s_cnt++] = ECGFilteredData[0] >> 8;		//CH1
		data_to_send[s_cnt++] = ECGFilteredData[0];	
		data_to_send[s_cnt++] = ECGFilteredData[1] >> 8;		//CH2		
		data_to_send[s_cnt++] = ECGFilteredData[1];	
		for(Task4_i=0;Task4_i<s_cnt;Task4_i++)
		Sum_Task4 += data_to_send[Task4_i];							
	 	data_to_send[s_cnt] = Sum_Task4;	//У���																		
	 	DMA_Enable(DMA1_Channel4,s_cnt);//����1DMA
	//}
}
void ModECG_Task_5(void)
{
	u8 Task5_i=0;
	ModECG_Tsk_2_for_4();
	ModECG_Tsk_3_for_4();
	s_cnt=0;
	//if(ads1292_recive_flag)
	//{
		cannle[2]=ads1292_Cache[6]<<16 | ads1292_Cache[7]<<8 | ads1292_Cache[8];
		ADS1x9x_Filtered_ECG(ADS1292_DEVICE, cannle);
		data_to_send[s_cnt++] = QRS_Heart_Rate;
		data_to_send[s_cnt++] = int_Last_Task2_Temp;
		data_to_send[s_cnt++] = float_Last_Task2_temp;
		data_to_send[s_cnt++] = record_steps;
		data_to_send[s_cnt++] = steps_length>>8;
		data_to_send[s_cnt++] = steps_length;
		data_to_send[s_cnt++] = ECGFilteredData[1]>>8;
		data_to_send[s_cnt++] = ECGFilteredData[1];
		data_to_send[s_cnt++] = 0x0d;
	  data_to_send[s_cnt++] = 0x0a;
		DMA_Enable(DMA1_Channel4,s_cnt);
		ads1292_recive_flag=0;
	//}
}

