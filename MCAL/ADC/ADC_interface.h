/*
 * ADC_interface.h
 *
 *  Created on: Aug 13, 2023
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_


typedef enum{
	ADC_AREF,			/*Internal Vref turned off*/
	ADC_AVCC,			/* With external Cap on Aref pin */
	ADC_INTERNAL = 3	/* Internal 2.56 voltage with external Cap on Aref pin*/
}ADC_RefSelect_t;

typedef enum{
	ADC_FCPU_2 = 1,
	ADC_FCPU_4,
	ADC_FCPU_8,
	ADC_FCPU_16,
	ADC_FCPU_32,
	ADC_FCPU_64,
	ADC_FCPU_128
}ADC_Prescaler_t;

//typedef enum{
//	ADC_CHANNEL0,
//	ADC_CHANNEL1,
//	ADC_CHANNEL2,
//	ADC_CHANNEL3,
//	ADC_CHANNEL4,
//	ADC_CHANNEL5,
//	ADC_CHANNEL6,
//	ADC_CHANNEL7
//}ADC_Channel_t;


typedef enum{

	/*For single Channel (ADC_SINGLE_ENDED_5) it means channel 5*/
	ADC_SINGLE_ENDED_0,
	ADC_SINGLE_ENDED_1,
	ADC_SINGLE_ENDED_2,
	ADC_SINGLE_ENDED_3,
	ADC_SINGLE_ENDED_4,
	ADC_SINGLE_ENDED_5,
	ADC_SINGLE_ENDED_6,
	ADC_SINGLE_ENDED_7,

	/*For differential (ADC_DIFF_0_1_10) it means channel 0 on positive and 1 on negative and 10x gain*/
	ADC_DIFF_0_0_10x,
	ADC_DIFF_1_0_10x,
	ADC_DIFF_0_0_200x,
	ADC_DIFF_1_0_200x,
	ADC_DIFF_2_2_10x,
	ADC_DIFF_3_2_10x,
	ADC_DIFF_2_2_200x,
	ADC_DIFF_3_2_200x,


	ADC_DIFF_0_1_1x,
	ADC_DIFF_1_1_1x,
	ADC_DIFF_2_1_1x,
	ADC_DIFF_3_1_1x,
	ADC_DIFF_4_1_1x,
	ADC_DIFF_5_1_1x,
	ADC_DIFF_6_1_1x,
	ADC_DIFF_7_1_1x,

	ADC_DIFF_0_2_1x,
	ADC_DIFF_1_2_1x,
	ADC_DIFF_2_2_1x,
	ADC_DIFF_3_2_1x,
	ADC_DIFF_4_2_1x,
	ADC_DIFF_5_2_1x,

}ADC_InputChWithGain_t;

typedef enum{
	ADC_FREE_RUNNING_MODE,
	ADC_ANALOG_COMPARATOR,
	ADC_EXT_INT0,
	ADC_TIMER0_COMPARE_MATCH,
	ADC_TIMER0_OVERFLOW,
	ADC_TIMER1_COMPARE_MATCH_B,
	ADC_TIMER1_OVERFLOW,
	ADC_TIMER1_CAPTURE_EVENT,


}ADC_trigger_source_t;

typedef struct{
	ADC_RefSelect_t   		ADC_vref;
	ADC_Prescaler_t   		ADC_prescaler;

}ADC_Conf_t;





void ADC_voidInit(ADC_Conf_t * ADC_ptr);
u16	 ADC_u16SynchReadChannel(ADC_InputChWithGain_t ADC_InputChWithGain);
void ADC_voidInterruptEnable(void);
void ADC_voidInterruptDisable(void);
void ADC_voidChooseTrigSrc(ADC_trigger_source_t Copy_enumTriggerSource);
void ADC_voidSetCallBackNotification(void (*Pf) (void) );
void ADC_voidAsynchReadChannel(u16 * Data);
void ADC_voidAsynchChooseChannel(ADC_InputChWithGain_t ADC_InputChWithGain);


#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
