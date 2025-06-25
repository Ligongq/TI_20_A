#ifndef ADS1x9x_ECG_PROCESSING_H_
#define ADS1x9x_ECG_PROCESSING_H_

//! \brief MAX_PEAK_TO_SEARCH
//!
#define MAX_PEAK_TO_SEARCH 				5

//! \brief MAXIMA_SEARCH_WINDOW
//!
#define MAXIMA_SEARCH_WINDOW			40

//! \brief MINIMUM_SKIP_WINDOW
//!
#define MINIMUM_SKIP_WINDOW				50

//! \brief SAMPLING_RATE
//!
#define SAMPLING_RATE					250//500

//! \brief TWO_SEC_SAMPLES
//!
#define TWO_SEC_SAMPLES  				2 * SAMPLING_RATE

/*threshold = maxima * N / 10   */
#define QRS_THRESHOLD_FRACTION			5//0.7					
	
//! \brief MAXCHAN
//!
#define MAXCHAN							2

//! \brief FILTERORDER
//!
#define FILTERORDER 					161

#define TRUE							1
#define FALSE							0

//! \brief MUSCLE_ARTIFACT_FILTER
//!
#define MUSCLE_ARTIFACT_FILTER			1

//! \brief NOTCHFILTERSEL
//!
#define NOTCHFILTERSEL					1		// 0 - 50 Hz Notch filter
											// 1 - 60 Hz Notch filter

//! \brief DC Removal Numerator Coeff
//!
#define NRCOEFF							(0.992)

enum emADS1x9x
{
	ADS1191_16BIT = 0,
	ADS1192_16BIT,
	ADS1291_24BIT,
	ADS1292_24BIT
};

//-------------------------------------------------
extern unsigned short QRS_Heart_Rate;
extern short ECGFilteredData[4];

//*****************************************************************************
//
//! \�˺��������ɼ��߳���

//!������ȡ���ڵ��ý���_buffer����֮ǰ����ִ�����¼��

//!������ô����i�� ������ǰһֱ�յ�2����Ʒ

//!��ʼ����ÿ��������������ܻ�����

//!��鵱ǰ����ǰ��ECG����֮��Ĳ���

//!ʹ�õ�һ�͵ڶ�΢�ּ��㡣
//
//! \param Lead     II sample CurrSample
//
//! \return  None
//
//*****************************************************************************
void QRS_Algorithm_Interface(short CurrSample);

//*****************************************************************************
//
//! \����161��FIR�������˲��Ĺ��ܹ���

//!�ನ���˲���0.5 t0 150 Hz��50/60Hz�߱��ӡ����

//!����֧�ֱ���ʱ50/60����ѡ��

//
//! \���������������еĲ���WorkingBuff

//! \FIR�˲�������ϵ����

//! \param FilterOut Out-�������
//
//! \return  None
//
//*****************************************************************************
void ECG_FilterProcess(short * WorkingBuff, short * CoeffBuf, short* FilterOut);

//*****************************************************************************
//
//! \�������������������

//!���ʼ�⹦�ܡ��ڵ���ÿ������֮ǰ������

//!ȷ��ECG IC֧�ָ�ģʽ�����粻��ȫ��

//!ADS1x9x֧�ֺ������ʼ���.
//
//! \param none     none
//
//! \return  None
//
//*****************************************************************************
void ADS1x9x_Filtered_ECG(unsigned char IDreg, long*ptECGdata);
void ADS1x9x_Filtered_ECG_Task4(unsigned char IDreg, long *ptECGdata);

//*****************************************************************************
//
//! \��Ҫ˵����������һ��һ�����������ʹ洢

//!Leadinfobuff��ɸѡ��������������ִ��

//!���档

//!-ֱ���Ƴ���������

//!-�ನ��161 Tab FIR�˲�������50 Hz/60Hz���ݲ���

//

//! \����ECG\U WorkingBuff In-ECG����������������

//! \param FilterOut Out-�������
//
//! \return  None
//
//*****************************************************************************
//void ECG_ProcessCurrSample(short *CurrAqsSample, short *FilteredOut);

//*****************************************************************************
//
//! \��Ҫ˵����������һ��һ�����������ʹ洢

//!Leadinfobuff��ɸѡ��������������ִ��

//!���档

//!-ֱ���Ƴ���������

//!-�ನ��161 Tab FIR�˲�������50 Hz/60Hz���ݲ���

//

//! \����ECG\U WorkingBuff In-ECG����������������

//! \param FilterOut Out-�������
//
//! \return  None
//
//*****************************************************************************
//void ECG_ProcessCurrSample_ch0(short *CurrAqsSample, short *FilteredOut);

//*****************************************************************************
//
//! \�˺���ʹ��˳�����QRS��ֵ�ĳ���ʱ��

//!�����������������QRS U����������

//!�����Ǵ�������֮�����ǿ��Բ������ʡ���ʹ���������

//!�Է����߶Ͽ���

//

//! \�������Ž��

//! \����QRS_���ʺ����ʱ�־
//
//! \return  None
//
//*****************************************************************************
//static void QRS_check_sample_crossing_threshold( unsigned short scaled_result );

//*****************************************************************************
//
//! \�����������һ�׺Ͷ���΢��

//!��������������QRS U����_��Ʒ��֮�����ǿ��Դ�������

//! ���QRS_Proc_Data_Buffer������HR���������

//!�㷨���˺������ÿ��n����������һ��������

//!��B4�������н��յ�6s�Ĵ������ݣ���������*6��

//!���ǽ��״ο�ʼ�������ʣ��Ժ�

//!һ�������յ��涨�����֣����ǻ��������

//!Ԥ��ˢ����������������
//
//! \param none     none
//
//! \return  None
//
//*****************************************************************************
//static void QRS_process_buffer( void );

#endif /*ADS1x9x_ECG_PROCESSING_H_*/
