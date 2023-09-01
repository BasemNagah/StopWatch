
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"



void (*Glo_voidPtrTofn)(void) = NULL_PTR;

void ADC_voidInit(ADC_Conf_t * ADC_ptr)
{

	/*Clear the ref voltage to assign the new*/
	ADC_ADMUX_REG &= 0x3F;


	/* Assigning the ref voltage*/
	ADC_ADMUX_REG |= ((ADC_ptr->ADC_vref) << 6);

	/*CLEAR LEAST SIG 3 BITS*/
	ADC_ADCSRA_REG &= 0xF8;

	/*INSERT THE REQUIRED PRESCALER*/
	ADC_ADCSRA_REG |= (ADC_ptr->ADC_prescaler);

	/*ENABLING ADC*/
	SET_BIT(ADC_ADCSRA_REG, ADC_ADEN_BIT);

#if ADC_INTERRUPT_STATUS == ADC_INTERRUPT_DISABLE
	/*DISABLE INTERRUPT OF ADC*/
	CLR_BIT(ADC_ADCSRA_REG,ADC_ADIE_BIT);
#elif ADC_INTERRUPT_STATUS == ADC_INTERRUPT_ENABLE
	SET_BIT(ADC_ADCSRA_REG,ADC_ADIE_BIT);
#endif
}



u16 ADC_u16SynchReadChannel(ADC_InputChWithGain_t ADC_InputChWithGain)
{
	u16 Local_u16RetVal = 0;

	/*CLEARING LEAST SIG 5 BITS*/
	ADC_ADMUX_REG &= 0xE0;

	/*INSERT THE REQUIRED CHANNEL*/
	ADC_ADMUX_REG |= (ADC_InputChWithGain);

	/*START CONVERSION*/
	SET_BIT(ADC_ADCSRA_REG , ADC_ADSC_BIT);

	/*WAIT UNTIL FLAG IS HIGH*/
	while(GET_BIT(ADC_ADCSRA_REG, ADC_ADIF_BIT) == 0);

	/*CLEAR THE FLAG*/
	SET_BIT(ADC_ADCSRA_REG, ADC_ADIF_BIT);



	/*GET THE DIGITAL READING*/
	Local_u16RetVal = ADC_ADCL_REG ;
	Local_u16RetVal |= (((u16)ADC_ADCH_REG << 8) );

	return Local_u16RetVal;
}


void ADC_voidInterruptEnable(void){
	SET_BIT(ADC_ADCSRA_REG, ADC_ADIE_BIT);
}
void ADC_voidInterruptDisable(void){
	CLR_BIT(ADC_ADCSRA_REG, ADC_ADIE_BIT);
}


void ADC_voidChooseTrigSrc(ADC_trigger_source_t Copy_enumTriggerSource){

	/*Clearing 7,6,5 bits in SIFOR REG*/
	ADC_SFIOR_REG &= 0b00001111;

	/*Assigning the value of trigger Source*/
	ADC_SFIOR_REG |= (Copy_enumTriggerSource<< 5);

	/*Enable Tigger in ADCSRA REG*/
	SET_BIT(ADC_ADCSRA_REG, ADC_ADATE_BIT);


	/*ENABLING ADC*/
	SET_BIT(ADC_ADCSRA_REG, ADC_ADEN_BIT);

	/*START CONVERSION*/
	SET_BIT(ADC_ADCSRA_REG , ADC_ADSC_BIT);

}


void ADC_voidAsynchChooseChannel(ADC_InputChWithGain_t ADC_InputChWithGain){
	/*CLEARING LEAST SIG 5 BITS*/
	ADC_ADMUX_REG &= 0xE0;

	/*INSERT THE REQUIRED CHANNEL*/
	ADC_ADMUX_REG |= (ADC_InputChWithGain);

}

void ADC_voidAsynchReadChannel(u16 * Data){

	u16 Local_u16RetVal = 0;
	/*GET THE DIGITAL READING*/
	Local_u16RetVal = ADC_ADCL_REG ;
	Local_u16RetVal |= (((u16)ADC_ADCH_REG << 8) );

	*Data = Local_u16RetVal;
}

void ADC_voidSetCallBackNotification(void (*Pf) (void) ){

		Glo_voidPtrTofn = Pf;
}
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{

	if(Glo_voidPtrTofn != NULL_PTR){

		Glo_voidPtrTofn();
	}

}
