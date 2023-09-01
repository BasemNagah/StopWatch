/*
 * TIMERS_program.c
 *
 *  Created on: Aug 15, 2023
 *      Author: Islam Shaaban
 */


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "TIMERS_private.h"
#include "TIMERS_config.h"
#include "TIMERS_interface.h"

#include <avr/interrupt.h>

void TIMERS_voidInit(TIMER_Config_t* Timer_conf){

	switch(Timer_conf->T_ID){
	case TIMER0_ID:

		switch(Timer_conf->T_Mode){
		case Normal_mode_OVF:
			/* only active in (NOT PWM MODE)
			 * When it set, immediate compare match is forced on the
			 * waveform generation unit.
			 * The OC0 output is changed according to COM01:00 setting.
			 * so we will make these 2 bit to zero.
			 * It always read as zero.
			 */
			SET_BIT(TIMERS_TCCR0_REG,FOC0_BIT);

			/* To Set the source of maximum counter value TOP = 0xFF.
			 * It as OVF Mode  */
			CLR_BIT(TIMERS_TCCR0_REG,WGM00_BIT);
			CLR_BIT(TIMERS_TCCR0_REG,WGM01_BIT);

			switch(Timer_conf->Tech){
			case Polling:
				break;
			case Interrupt:
				//Enable OFlow PIE
				SET_BIT(TIMERS_TIMSK_REG,TOIE0_BIT);
				break;
			}
			break;
			case Compare_mode:
				SET_BIT(TIMERS_TCCR0_REG,FOC0_BIT);
				/* To Set it as CTC MODE
				 * Top is OCR0
				 */
				CLR_BIT(TIMERS_TCCR0_REG,WGM00_BIT);
				SET_BIT(TIMERS_TCCR0_REG,WGM01_BIT);

				if(Timer_conf->Tech== Interrupt){
					//Enable CTC PIE
					SET_BIT(TIMERS_TIMSK_REG,OCIE0_BIT);
				}
				else{
					//Do Nothing
				}
				break;
			case PWM_phase_corr:
				CLR_BIT(TIMERS_TCCR0_REG,FOC0_BIT);
				SET_BIT(TIMERS_TCCR0_REG , WGM00_BIT);
				CLR_BIT(TIMERS_TCCR0_REG , WGM01_BIT);

				break;

			case Fast_PWM:
				CLR_BIT(TIMERS_TCCR0_REG,FOC0_BIT);
				SET_BIT(TIMERS_TCCR0_REG , WGM00_BIT);
				SET_BIT(TIMERS_TCCR0_REG , WGM01_BIT);

				break;
			default:
				break;
		}

		/* Configure the Compare output option.
		 * [COM00,COM01]
		 * [  0	 ,	0  ] >>0>> Normal operation, OCX is disconeccted.
		 * [  0	 ,	1  ] >>1>> Toggle OCX in OVF,CTC & Reserved in PWM Mode.
		 * [  1	 ,	0  ] >>2>> Clear OCX on compare match, [Set OC0 at bottom = Non inverting].
		 * [  1	 ,	1  ] >>3>> Set OCX on compare match,   [Clear OC0 at bottom = Inverting].
		 * */
		TIMERS_TCCR0_REG &= 0xCF; // 0x11001111 clearing [COM00,COM01]
		if( ( Timer_conf->T_CompareOutput ) == TOGGLE_OCX ){
			if( ( (Timer_conf->T_Mode) == Fast_PWM ) ||( (Timer_conf->T_Mode) == PWM_phase_corr ) ){
				//#warning ("Unavailable Copmare Output mode [RESERVED].");
			}
			else{
				TIMERS_TCCR0_REG |= ((Timer_conf->T_CompareOutput) << 4);
			}
		}
		else{
			TIMERS_TCCR0_REG |= ((Timer_conf->T_CompareOutput) << 4);
		}

		/* Configure THE REQUIRED Clock select
		 * [CS02,CS01,CS00]
		 * [ 0	,  0  , 0 ] >>0>> TIMER/COUNTER STOPPED.
		 * [ 0	,  0  , 1 ] >>1>> THE TIMER CLOCK = CPU CLOCK.
		 * [ 0	,  1 ,  0 ] >>2>> THE TIMER CLOCK = CPU CLOCK / 8.
		 *
		 * [ 1	,  1  , 1 ] >>7>> EXTERNAL CLOCK SRC ON T0 PIN, RISING EDGE.
		 */
		TIMERS_TCCR0_REG &= 0xF8;	// 0x11111000 (CLEAR LS 3 BITS [CS02,CS01,CS00])
		TIMERS_TCCR0_REG |= ((Timer_conf->T_Prescaler) & 0x07 );

		/* Reset the Timer/Counter Register 8bit */
		TIMERS_TCNT0_REG = 0;


		break;
		case TIMER1_ID:
			break;
		case TIMER2_ID:
			break;
		default:
			break;
	}



}

void TIMERS_voidTIM0Start(TIMER_Config_t * Timer_conf){
	switch(Timer_conf->T_Mode){
	case Normal_mode_OVF:
		TIMERS_TCNT0_REG = Timer_conf->PreloadValue;
		// Configure the flag
		switch(Timer_conf->Tech){
		case Polling:
			//WAITing until timer finish counting
			while(GET_BIT(TIMERS_TIFR_REG,TOV0_BIT)==0);
			// set it to clear the flag
			SET_BIT(TIMERS_TIFR_REG,TOV0_BIT);
			break;
		case Interrupt:
			//It cleared by HW when executing the corresponding ISR
			break;
		default:
			break;

		}
		break;
		case Compare_mode:
			TIMERS_TCNT0_REG = Timer_conf->PreloadValue;
			TIMERS_OCR0_REG =Timer_conf->CompareValue;
			switch(Timer_conf->Tech){
			case Polling:
				//WAITing until timer finish counting
				while(GET_BIT(TIMERS_TIFR_REG,OCF0_BIT) == 0);
				SET_BIT(TIMERS_TIFR_REG,OCF0_BIT);
				break;
			case Interrupt:
				break;
			default:
				break;
			}
			break;
			case Fast_PWM:
				// SET ICR0 (TOP) and it's default by zero
				//SET OCR
				TIMERS_OCR0_REG =Timer_conf->CompareValue;
				break;

			default:
				break;

	}
}

void TIMERS_voidTIM0SetPreloadVal(u8 Copy_u8Preload){
	TIMERS_TCNT0_REG = Copy_u8Preload;
}
void TIMERS_voidTIM0GetTimerVal(u8 * PreLoadVal){
	*PreLoadVal = TIMERS_TCNT0_REG;
}

void TIMERS_voidTIM0SetCompareVal(u8 Copy_u8Compare){
	TIMERS_OCR0_REG = Copy_u8Compare;
}

void TIMERS_voidTIM0_Enable_OVF_Interrupt(){
	SET_BIT(TIMERS_TIMSK_REG,TOIE0_BIT);
}
void TIMERS_voidTIM0_Disable_OVF_Interrupt(){
	CLR_BIT(TIMERS_TIMSK_REG,TOIE0_BIT);
}
void TIMERS_voidTIM0_Enable_CTC_Interrupt(){
	SET_BIT(TIMERS_TIMSK_REG,OCIE0_BIT);
}
void TIMERS_voidTIM0_Disable_CTC_Interrupt(){
	CLR_BIT(TIMERS_TIMSK_REG,OCIE0_BIT);
}

void TIMERS_voidTIM0DeInit(void){
	TIMERS_TCCR0_REG =0;
	TIMERS_TCNT0_REG=0;
	TIMERS_OCR0_REG =0;
	TIMERS_TIMSK_REG&= 0xFC;
}

void TIMERS_voidTIM0_TIM1_PrescalerRESET(){
	SET_BIT(TIMERS_SFIOR_REG,PSR10_BIT);
}



static void (*Global_PtrToFun)(void) = NULL_PTR;
//REGISTERING FUNCTION
void TIMERS_voidTIM0SetCallBackFunction(void (*ptrToFun) (void)){
	Global_PtrToFun = ptrToFun;
}

ISR(TIMER0_OVF_vect){
	if(Global_PtrToFun!= NULL_PTR){
		(*Global_PtrToFun)();
	}
	//	(*Global_PtrToFun)();
}

ISR(TIMER0_COMP_vect){
	if(Global_PtrToFun!= NULL_PTR){
		Global_PtrToFun();
	}

}
