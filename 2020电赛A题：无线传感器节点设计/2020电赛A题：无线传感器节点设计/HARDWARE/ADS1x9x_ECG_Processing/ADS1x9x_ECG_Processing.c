#include "ADS1x9x_ECG_Processing.h"
#include "ADS1x9x_Resp_Processing.h"
#include <math.h>
#include <stdlib.h>

static unsigned short QRS_B4_Buffer_ptr = 0 ;


unsigned short QRS_Heart_Rate = 0 ;
unsigned char HR_flag;

/* 	Variable which holds the threshold value to calculate the maxima */
short QRS_Threshold_Old = 0;
short QRS_Threshold_New = 0;


/* Variables to hold the sample data for calculating the 1st and 2nd */
/* differentiation                                                   */
int QRS_Second_Prev_Sample = 0 ;
int QRS_Prev_Sample = 0 ;
int QRS_Current_Sample = 0 ;
int QRS_Next_Sample = 0 ;
int QRS_Second_Next_Sample = 0 ;

/* Flag which identifies the duration for which sample count has to be incremented */
unsigned char Start_Sample_Count_Flag = 0;
unsigned char first_peak_detect = FALSE ;
unsigned int sample_count = 0 ;
unsigned int sample_index[MAX_PEAK_TO_SEARCH+2]={0};
short ECG_ch0_WorkingBuff[2 * FILTERORDER]={0};
short ECG_WorkingBuff[2 * FILTERORDER]={0};
short ECGRawData[4]={0},ECGFilteredData[4]={0};

extern unsigned short Respiration_Rate;
//extern unsigned char LeadStatus;

unsigned char Filter_Option = 0;//0=40hz,2=50hz,3=60hz

#if (FILTERORDER == 161)
short CoeffBuf_40Hz_LowPass[FILTERORDER] = {

      -33,     19,     48,     44,      9,    -49,   -118,   -179,   -217,
     -222,   -191,   -131,    -57,     13,     61,     74,     48,    -12,
      -92,   -173,   -233,   -257,   -237,   -178,    -92,     -1,     73,
      110,     99,     40,    -52,   -156,   -246,   -299,   -299,   -244,
     -145,    -26,     83,    155,    170,    119,     14,   -123,   -257,
     -355,   -389,   -347,   -234,    -75,     91,    224,    286,    256,
      135,    -53,   -266,   -449,   -555,   -547,   -417,   -186,     97,
      365,    547,    584,    447,    145,   -271,   -711,  -1067,  -1230,
    -1111,   -664,    100,   1114,   2259,   3386,   4334,   4967,   5189,
     4967,   4334,   3386,   2259,   1114,    100,   -664,  -1111,  -1230,
    -1067,   -711,   -271,    145,    447,    584,    547,    365,     97,
     -186,   -417,   -547,   -555,   -449,   -266,    -53,    135,    256,
      286,    224,     91,    -75,   -234,   -347,   -389,   -355,   -257,
     -123,     14,    119,    170,    155,     83,    -26,   -145,   -244,
     -299,   -299,   -246,   -156,    -52,     40,     99,    110,     73,
       -1,    -92,   -178,   -237,   -257,   -233,   -173,    -92,    -12,
       48,     74,     61,     13,    -57,   -131,   -191,   -222,   -217,
     -179,   -118,    -49,      9,     44,     48,     19,    -33
};

short CoeffBuf_50Hz_Notch[FILTERORDER] = {
	/* Coeff for Notch @ 50Hz @ 500 SPS*/
	-47,   -210,    -25,    144,     17,     84,    249,     24,   -177,
	-58,   -144,   -312,    -44,    191,     78,    185,    357,     42,
	-226,   -118,   -248,   -426,    -61,    243,    134,    290,    476,
	56,   -282,   -169,   -352,   -549,    -70,    301,    177,    392,
	604,     60,   -344,   -200,   -450,   -684,    -66,    369,    191,
	484,    749,     44,   -420,   -189,   -535,   -843,    -32,    458,
	146,    560,    934,    -16,   -532,    -89,   -600,  -1079,     72,
	613,    -50,    614,   1275,   -208,   -781,    308,   -642,  -1694,
	488,   1141,  -1062,    642,   3070,  -1775,  -3344,   9315,  19005,
	9315,  -3344,  -1775,   3070,    642,  -1062,   1141,    488,  -1694,
	-642,    308,   -781,   -208,   1275,    614,    -50,    613,     72,
	-1079,   -600,    -89,   -532,    -16,    934,    560,    146,    458,
	-32,   -843,   -535,   -189,   -420,     44,    749,    484,    191,
	369,    -66,   -684,   -450,   -200,   -344,     60,    604,    392,
	177,    301,    -70,   -549,   -352,   -169,   -282,     56,    476,
	290,    134,    243,    -61,   -426,   -248,   -118,   -226,     42,
	357,    185,     78,    191,    -44,   -312,   -144,    -58,   -177,
	24,    249,     84,     17,    144,    -25,   -210,    -47
};

short CoeffBuf_60Hz_Notch[FILTERORDER] = {
/* Coeff for Notch @ 60Hz for 500SPS/60Hz Notch coeff13102008*/
      131,    -16,     85,     97,   -192,   -210,      9,    -37,    -11,
      277,    213,   -105,    -94,   -100,   -324,   -142,    257,    211,
      121,    242,    -38,   -447,   -275,    -39,    -79,    221,    543,
      181,   -187,   -138,   -351,   -515,     34,    446,    260,    303,
      312,   -344,   -667,   -234,    -98,    -46,    585,    702,    -17,
     -241,   -197,   -683,   -552,    394,    540,    239,    543,    230,
     -811,   -700,    -44,   -254,     81,   1089,    594,   -416,    -81,
     -249,  -1195,   -282,   1012,    223,     80,   1170,   -156,  -1742,
       21,    543,  -1503,    505,   3202,  -1539,  -3169,   9372,  19006,
     9372,  -3169,  -1539,   3202,    505,  -1503,    543,     21,  -1742,
     -156,   1170,     80,    223,   1012,   -282,  -1195,   -249,    -81,
     -416,    594,   1089,     81,   -254,    -44,   -700,   -811,    230,
      543,    239,    540,    394,   -552,   -683,   -197,   -241,    -17,
      702,    585,    -46,    -98,   -234,   -667,   -344,    312,    303,
      260,    446,     34,   -515,   -351,   -138,   -187,    181,    543,
      221,    -79,    -39,   -275,   -447,    -38,    242,    121,    211,
      257,   -142,   -324,   -100,    -94,   -105,    213,    277,    -11,
      -37,      9,   -210,   -192,     97,     85,    -16,    131
};
#endif


void ECG_FilterProcess(short * WorkingBuff, short * CoeffBuf, short* FilterOut)
{
	int  mpys=0; 
	short i,macs,op2;
	
	for ( i = 0; i < FILTERORDER; i++)
	{
		macs = *WorkingBuff--;	
		op2  = *CoeffBuf++;			
		mpys+= (int)(macs) * op2;
	}
	*FilterOut = mpys>>8;		//去掉低8位，保存为16位数据
// 	macs = mpys>>16;
// 	macs = macs<<1;		
// 	op2  = (mpys>>15)&0x01;
// 	*FilterOut = macs | op2;	
}

void ECG_IIR_50Notch(short *CurrDat, short *FilteredOut)
{
	//50hz 噪声滤波，要求输入采样率250SPS
	float x0,y0;
	static float w0[3];
	static float IIR_50Notch_A[3] = {1,-0.55771247730967288,0.80479548847391036};
	static float IIR_50Notch_B[3] = {0.90239774423695518,-0.55771247730967288,0.90239774423695518};

	x0    = (float)CurrDat[0];  
	w0[0] = IIR_50Notch_A[0]*x0 -    IIR_50Notch_A[1]*w0[1] - IIR_50Notch_A[2]*w0[2];
	y0    = IIR_50Notch_B[0]*w0[0] + IIR_50Notch_B[1]*w0[1] + IIR_50Notch_B[2]*w0[2];
	w0[2] = w0[1];
	w0[1] = w0[0];
	FilteredOut[0] = (short)y0;
}

void ECG_ProcessCurrSample(short *CurrAqsSample, short *FilteredOut)
{
	static unsigned short ECG_bufStart=0, ECG_bufCur = FILTERORDER-1, ECGFirstFlag = 1;
 	static short ECG_Pvev_DC_Sample, ECG_Pvev_Sample;/* Working Buffer Used for Filtering*/
//	static short ECG_WorkingBuff[2 * FILTERORDER];
 	short *CoeffBuf;
 	short temp1, temp2, ECGData;
	/* Count variable*/
	unsigned short Cur_Chan;
	short FiltOut;
//	short FilterOut[2];
	CoeffBuf = CoeffBuf_40Hz_LowPass;					// Default filter option is 40Hz LowPass
	if ( Filter_Option == 2)
	{
		CoeffBuf = CoeffBuf_50Hz_Notch;					// filter option is 50Hz Notch & 0.5-150 Hz Band
	}
	else if ( Filter_Option == 3)
	{
		CoeffBuf = CoeffBuf_60Hz_Notch;					// filter option is 60Hz Notch & 0.5-150 Hz Band
	}
	if  ( ECGFirstFlag )								// First Time initialize static variables.
	{
		for ( Cur_Chan =0 ; Cur_Chan < FILTERORDER; Cur_Chan++)
		{
			ECG_WorkingBuff[Cur_Chan] = 0;
		} 
		ECG_Pvev_DC_Sample = 0;
		ECG_Pvev_Sample = 0;
		ECGFirstFlag = 0;
	}
	temp1 = NRCOEFF * ECG_Pvev_DC_Sample;				//First order IIR
	ECG_Pvev_DC_Sample = (CurrAqsSample[0]  - ECG_Pvev_Sample) + temp1;
	ECG_Pvev_Sample = CurrAqsSample[0];
	temp2 = ECG_Pvev_DC_Sample >> 2;
	ECGData = temp2;
	/* Store the DC removed value in Working buffer in millivolts range*/
	ECG_WorkingBuff[ECG_bufCur] = ECGData;
	ECG_FilterProcess(&ECG_WorkingBuff[ECG_bufCur],CoeffBuf,&FiltOut);
	/* Store the DC removed value in ECG_WorkingBuff buffer in millivolts range*/
	ECG_WorkingBuff[ECG_bufStart] = ECGData;
	//FiltOut = ECGData[Cur_Chan];
	/* Store the filtered out sample to the LeadInfo buffer*/
	FilteredOut[0] = FiltOut ;//(CurrOut);
	ECG_bufCur++;
	ECG_bufStart++;
	if ( ECG_bufStart  == (FILTERORDER-1))
	{
		ECG_bufStart=0; 
		ECG_bufCur = FILTERORDER-1;
	}
	return ;
}
void ECG_ProcessCurrSample_ch0(short *CurrAqsSample, short *FilteredOut)
{
 	static unsigned short ECG_ch0_bufStart=0, ECG_ch0_bufCur = FILTERORDER-1, ECG_ch0FirstFlag = 1;
 	static short ECG_ch0_Pvev_DC_Sample, ECG_ch0_Pvev_Sample;
 	//static short ECG_ch0_WorkingBuff[2 * FILTERORDER];
 	short *CoeffBuf;
 	
 	short temp1_ch0, temp2_ch0, ECGData_ch0;
 	
	/* Count variable*/
	unsigned short Cur_Chan_ch0;
	short FiltOut_ch0;

	CoeffBuf = CoeffBuf_40Hz_LowPass;					// Default filter option is 40Hz LowPass
	if ( Filter_Option == 2)
	{
		CoeffBuf = CoeffBuf_50Hz_Notch;					// filter option is 50Hz Notch & 0.5-150 Hz Band
	}
	else if ( Filter_Option == 3)
	{
		CoeffBuf = CoeffBuf_60Hz_Notch;					// filter option is 60Hz Notch & 0.5-150 Hz Band
	}
	if  ( ECG_ch0FirstFlag )							// First time initialize static variables
	{
		for ( Cur_Chan_ch0 =0 ; Cur_Chan_ch0 < FILTERORDER; Cur_Chan_ch0++)
		{
			ECG_ch0_WorkingBuff[Cur_Chan_ch0] = 0;
		} 
		ECG_ch0_Pvev_DC_Sample = 0;
		ECG_ch0_Pvev_Sample = 0;
		ECG_ch0FirstFlag = 0;
	}
	temp1_ch0 = NRCOEFF * ECG_ch0_Pvev_DC_Sample;			// First order IIR
	ECG_ch0_Pvev_DC_Sample = (CurrAqsSample[0]  - ECG_ch0_Pvev_Sample) + temp1_ch0;
	ECG_ch0_Pvev_Sample = CurrAqsSample[0];
	temp2_ch0 = ECG_ch0_Pvev_DC_Sample >> 2;
	ECGData_ch0 = (short) temp2_ch0;

	/* Store the DC removed value in Working buffer in millivolts range*/
	ECG_ch0_WorkingBuff[ECG_ch0_bufCur] = ECGData_ch0;
	/* */
	ECG_FilterProcess(&ECG_ch0_WorkingBuff[ECG_ch0_bufCur],CoeffBuf,(short*)&FiltOut_ch0);
	/* Store the DC removed value in ECG_WorkingBuff buffer in millivolts range*/
	ECG_ch0_WorkingBuff[ECG_ch0_bufStart] = ECGData_ch0;

	//FiltOut = ECGData[Cur_Chan];

	/* Store the filtered out sample to the LeadInfo buffer*/
	FilteredOut[0] = FiltOut_ch0 ;//(CurrOut);

	ECG_ch0_bufCur++;
	ECG_ch0_bufStart++;
	if ( ECG_ch0_bufStart  == (FILTERORDER-1))
	{
		ECG_ch0_bufStart=0; 
		ECG_ch0_bufCur = FILTERORDER-1;
	}

	return ;
}

static void QRS_check_sample_crossing_threshold( unsigned short scaled_result )
{
	/* array to hold the sample indexes S1,S2,S3 etc */
	
	static unsigned short s_array_index = 0 ;
	static unsigned short m_array_index = 0 ;
	
	static unsigned char threshold_crossed = FALSE ;
	static unsigned short maxima_search = 0 ;
	static unsigned char peak_detected = FALSE ;
	static unsigned short skip_window = 0 ;
	static long maxima_sum = 0 ;
	static unsigned int peak = 0;
	static unsigned int sample_sum = 0;
	static unsigned int nopeak=0;
	unsigned short max = 0 ;
	unsigned short HRAvg;

	
	if( TRUE == threshold_crossed  )
	{
		/*
		Once the sample value crosses the threshold check for the
		maxima value till MAXIMA_SEARCH_WINDOW samples are received
		*/
		sample_count ++ ;
		maxima_search ++ ;

		if( scaled_result > peak )
		{
			peak = scaled_result ;
		}

		if( maxima_search >= MAXIMA_SEARCH_WINDOW )
		{
			// Store the maxima values for each peak
			maxima_sum += peak ;
			maxima_search = 0 ;

			threshold_crossed = FALSE ;
			peak_detected = TRUE ;
		}

	}
	else if( TRUE == peak_detected )
	{
		/*
		Once the sample value goes below the threshold
		skip the samples untill the SKIP WINDOW criteria is meet
		*/
		sample_count ++ ;
		skip_window ++ ;

		if( skip_window >= MINIMUM_SKIP_WINDOW )
		{
			skip_window = 0 ;
			peak_detected = FALSE ;
		}

		if( m_array_index == MAX_PEAK_TO_SEARCH )
		{
			sample_sum = sample_sum / (MAX_PEAK_TO_SEARCH - 1);
			HRAvg =  (unsigned short) sample_sum  ;
#if 0
			if((LeadStatus & 0x0005)== 0x0000)
			{
				
			QRS_Heart_Rate = (unsigned short) 60 *  SAMPLING_RATE;
			QRS_Heart_Rate =  QRS_Heart_Rate/ HRAvg ;
				if(QRS_Heart_Rate > 250)
					QRS_Heart_Rate = 250 ;
			}
			else
			{
				QRS_Heart_Rate = 0;
			}
#else
			// Compute HR without checking LeadOffStatus
			QRS_Heart_Rate = (unsigned short) 60 *  SAMPLING_RATE;
			QRS_Heart_Rate =  QRS_Heart_Rate/ HRAvg ;
			if(QRS_Heart_Rate > 250)
				QRS_Heart_Rate = 250 ;
#endif

			/* Setting the Current HR value in the ECG_Info structure*/

			HR_flag = 1;

			maxima_sum =  maxima_sum / MAX_PEAK_TO_SEARCH;
			max = (short) maxima_sum ;
			/*  calculating the new QRS_Threshold based on the maxima obtained in 4 peaks */
			maxima_sum = max * 7;
			maxima_sum = maxima_sum/10;
			QRS_Threshold_New = (short)maxima_sum;

			/* Limiting the QRS Threshold to be in the permissible range*/
			if(QRS_Threshold_New > (4 * QRS_Threshold_Old))
			{
				QRS_Threshold_New = QRS_Threshold_Old;
	 		}

	 		sample_count = 0 ;
	 		s_array_index = 0 ;
	 		m_array_index = 0 ;
	 		maxima_sum = 0 ;
			sample_index[0] = 0 ;
			sample_index[1] = 0 ;
			sample_index[2] = 0 ;
			sample_index[3] = 0 ;
			Start_Sample_Count_Flag = 0;

			sample_sum = 0;
		}
	}
	else if( scaled_result > QRS_Threshold_New )
	{
		/*
			If the sample value crosses the threshold then store the sample index
		*/
		Start_Sample_Count_Flag = 1;
		sample_count ++ ;
		m_array_index++;
		threshold_crossed = TRUE ;
		peak = scaled_result ;
		nopeak = 0;

		/*	storing sample index*/
	   	sample_index[ s_array_index ] = sample_count ;
		if( s_array_index >= 1 )
		{
			sample_sum += sample_index[ s_array_index ] - sample_index[ s_array_index - 1 ] ;
		}
		s_array_index ++ ;
	}

	else if(( scaled_result < QRS_Threshold_New ) && (Start_Sample_Count_Flag == 1))
	{
		sample_count ++ ;
        nopeak++;	
        if (nopeak > (3 * SAMPLING_RATE))
        { 
        	sample_count = 0 ;
	 		s_array_index = 0 ;
	 		m_array_index = 0 ;
	 		maxima_sum = 0 ;
			sample_index[0] = 0 ;
			sample_index[1] = 0 ;
			sample_index[2] = 0 ;
			sample_index[3] = 0 ;
			Start_Sample_Count_Flag = 0;
			peak_detected = FALSE ;
			sample_sum = 0;
        	    	
        	first_peak_detect = FALSE;
	      	nopeak=0;

			QRS_Heart_Rate = 0;
			HR_flag = 1;
        }
	}
   else
   {
    nopeak++;	
   	if (nopeak > (3 * SAMPLING_RATE))
     { 
		/* Reset heart rate computation sate variable in case of no peak found in 3 seconds */
 		sample_count = 0 ;
 		s_array_index = 0 ;
 		m_array_index = 0 ;
 		maxima_sum = 0 ;
		sample_index[0] = 0 ;
		sample_index[1] = 0 ;
		sample_index[2] = 0 ;
		sample_index[3] = 0 ;
		Start_Sample_Count_Flag = 0;
		peak_detected = FALSE ;
		sample_sum = 0;
     	first_peak_detect = FALSE;
	 	nopeak = 0;
		QRS_Heart_Rate = 0;
		HR_flag = 1;

     }
   }

}

static void QRS_process_buffer( void )
{

	short first_derivative = 0 ;
	short scaled_result = 0 ;
	static short max = 0 ;
	first_derivative = QRS_Next_Sample - QRS_Prev_Sample  ;
	if(first_derivative < 0)
	{
		first_derivative = -(first_derivative);
	}
	scaled_result = first_derivative;
	if( scaled_result > max )
	{
		max = scaled_result ;
	}
	QRS_B4_Buffer_ptr++;
	if (QRS_B4_Buffer_ptr ==  TWO_SEC_SAMPLES)
	{
		//QRS_Threshold_Old = ((max *7) /10 ) ;
		QRS_Threshold_Old = ((max * QRS_THRESHOLD_FRACTION) /10 ) ; 
		QRS_Threshold_New = QRS_Threshold_Old ;
		if(max > 70)
		first_peak_detect = TRUE ;
		max = 0;
		QRS_B4_Buffer_ptr = 0;
	}


	if( TRUE == first_peak_detect )
	{
		QRS_check_sample_crossing_threshold( scaled_result ) ;//QRS检查超过阈值
	}
}

void QRS_Algorithm_Interface(short CurrSample)//QRS算法接口
{
	static short prev_data[32] ={0};
	short i;
	long Mac=0;
	prev_data[0] = CurrSample;
	for ( i=31; i > 0; i--)
	{
		Mac += prev_data[i];
		prev_data[i] = prev_data[i-1];
	}
	Mac += CurrSample;
	Mac = Mac >> 2;
	CurrSample = (short) Mac;
	QRS_Second_Prev_Sample = QRS_Prev_Sample ;
	QRS_Prev_Sample = QRS_Current_Sample ;
	QRS_Current_Sample = QRS_Next_Sample ;
	QRS_Next_Sample = QRS_Second_Next_Sample ;
	QRS_Second_Next_Sample = CurrSample ;
	QRS_process_buffer();//QRS U过程缓冲区
}
void ADS1x9x_Filtered_ECG_Task4(unsigned char IDreg, long *ptECGdata)
{
//	short tmp;
			//if ((IDreg&0x20) == 0x20) //ADS1292R
			//{

				//24位数据转为16位数据
				ptECGdata[1]  = ptECGdata[1];		//3 bytes CH0 data
				ptECGdata[2]  = ptECGdata[2] >> 4;	//3 bytes CH1 data
				ptECGdata[1] &= 0xFFFF;				
				ptECGdata[2] &= 0xFFFF;				
				ECGRawData[0] = (short)ptECGdata[1];	//3 bytes CH0 data
				ECGRawData[1] = (short)ptECGdata[2];	//3 bytes ch1 data
				//ECGFilteredData[0] = ECGRawData[1];//滤波测试对比用

 				//滤波计算处理
 				//Resp_ProcessCurrSample(&ECGRawData[0],&ECGFilteredData[0]);
				ECG_IIR_50Notch(&ECGRawData[1],&ECGFilteredData[1]);//50HZ
 				//ECG_ProcessCurrSample(&ECGRawData[1],&ECGFilteredData[1]);
 				//Resp_Algorithm_Interface(ECGFilteredData[0]);//呼吸算法
 				QRS_Algorithm_Interface(ECGFilteredData[1]);//QRS算法
		//	}	
}
void ADS1x9x_Filtered_ECG(unsigned char IDreg, long *ptECGdata)
{
//	short tmp;
			//if ((IDreg&0x20) == 0x20) //ADS1292R
			//{

				//24位数据转为16位数据
				ptECGdata[1]  = ptECGdata[1];		//3 bytes CH0 data
				ptECGdata[2]  = ptECGdata[2] >> 4;	//3 bytes CH1 data
				ptECGdata[1] &= 0xFFFF;				
				ptECGdata[2] &= 0xFFFF;				
				ECGRawData[0] = (short)ptECGdata[1];	//3 bytes CH0 data
				ECGRawData[1] = (short)ptECGdata[2];	//3 bytes ch1 data
				//ECGFilteredData[0] = ECGRawData[1];//滤波测试对比用

 				//滤波计算处理
				Resp_ProcessCurrSample(&ECGRawData[0],&ECGFilteredData[0]);
				ECG_IIR_50Notch(&ECGRawData[1],&ECGFilteredData[1]);//50HZ
 				//ECG_ProcessCurrSample(&ECGRawData[1],&ECGFilteredData[1]);
 			//	Resp_Algorithm_Interface(ECGFilteredData[0]);//呼吸算法
 				QRS_Algorithm_Interface(ECGFilteredData[1]);//QRS算法
		//	}	
}
// End of File

