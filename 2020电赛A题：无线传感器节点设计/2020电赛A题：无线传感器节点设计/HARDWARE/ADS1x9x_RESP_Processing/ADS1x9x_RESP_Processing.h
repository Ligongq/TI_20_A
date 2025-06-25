
#ifndef ADS1x9x_RESP_PROCESSING_H_
#define ADS1x9x_RESP_PROCESSING_H_

#define RESP_MAX_PEAK_TO_SEARCH 			5
#define RESP_MAXIMA_SEARCH_WINDOW			8
#define RESP_MINIMUM_SKIP_WINDOW			80

#define RESP_SAMPLING_RATE					100
#define RESP_TWO_SEC_SAMPLES  				2 * RESP_SAMPLING_RATE

/*threshold = 0.7 * maxima*/
//#define QRS_THRESHOLD_FRACTION				0.7				

#define MAXCHAN								2
#define FILTERORDER 						161

#define TRUE								1
#define FALSE								0

/* DC Removal Numerator Coeff*/
//#define NRCOEFF								(0.992)

//-------------------------------------------------
extern unsigned short Respiration_Rate;


void Resp_ProcessCurrSample(short *CurrAqsSample, short *FilteredOut);

//*****************************************************************************
//
//! \brief   This function is called by the main acquisition thread at every
//!			 samples read. Before calling the process_buffer() the below check
//!	  		 has to be done. i.e. We have always received +2 samples before
//!			 starting the processing  for each samples. This function basically
//!			 checks the difference between the current  and  previous ECG Samples
//!			 using 1st & 2nd differentiation calculations.
//!			 	- DC Removal of the current sample
//!				- Multi band FIR LPF with Notch at 50Hz filtering
//
//! \param Respiration CurrSample
//
//! \return  None
//
//*****************************************************************************
void Resp_Algorithm_Interface(short CurrSample);

//*****************************************************************************
//
//! \brief   The function process one sample filtering with 161 ORDER FIR low
//!			 pass filter with 2Hz .
//
//! \param RESP_WorkingBuff In - input sample buffer
//! \param CoeffBuf  In - Co-eficients for FIR filter.
//! \param FilterOut Out - Filtered output
//
//! \return  None
//
//*****************************************************************************
//void Resp_FilterProcess(short * RESP_WorkingBuff, short * CoeffBuf, short* FilterOut);


//*****************************************************************************
//
//! \brief   The function detects the respiration rate.
//
//! \param Resp_wave ECG samples
//
//! \return  None
//
//*****************************************************************************
//void Respiration_Rate_Detection(short Resp_wave);

#endif /*ADS1x9x_RESP_PROCESSING_H_*/
