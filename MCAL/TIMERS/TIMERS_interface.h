/*
 * TIMERS_interface.h
 *
 *  Created on: Aug 15, 2023
 *      Author: one
 */

#ifndef MCAL_TIMERS_TIMERS_INTERFACE_H_
#define MCAL_TIMERS_TIMERS_INTERFACE_H_

/*
 * Explanation
 * OVF mode
 * Prescaler 8
 * Tick time = 1 / 8 MHz = 1 micro sec
 * Time OF = 1 micro sec * 256 = 256 micro sec
 * desired time = 1 sec
 *
 *
 * */

typedef enum{
	TIMER0_ID, TIMER1_ID, TIMER2_ID,
}TIMER_ID;

//Timer Mode
typedef enum{
	Normal_mode_OVF,
	PWM_phase_corr,
	Compare_mode,
	Fast_PWM
}TIMER_mode_t;

typedef enum{
	DISCONNECT_OCX, TOGGLE_OCX, CLEAR_OCX, SET_OCX
}TIMER_CompareOutput;

typedef enum{
	Polling, Interrupt
}TIMER_Technique;

// Prescaler to set the ( Timer Freq =  F_CPU / Prescaler )
typedef enum{
	T0_NoCLK_SRC,
	T0_FCPU,
	T0_FCPU_8,
	T0_FCPU_64,
	T0_FCPU_256,
	T0_FCPU_1024,
	T0_EXTERNAL_FALLING,
	T0_EXTERNAL_RISING
}TIMERS_TIM0_PreScaler_t;






typedef struct{
	TIMER_ID T_ID;
	TIMER_mode_t T_Mode;
	TIMER_CompareOutput T_CompareOutput;
	TIMERS_TIM0_PreScaler_t T_Prescaler;
	TIMER_Technique			Tech;

	u8 						PreloadValue;
	u8						CompareValue;





}TIMER_Config_t;





void TIMERS_voidInit( TIMER_Config_t* Timer_conf);
void TIMERS_voidTIM0Start(TIMER_Config_t * Timer_conf);
void TIMERS_voidTIM0SetPreloadVal(u8 Copy_u8Preload);
void TIMERS_voidTIM0GetTimerVal(u8 * PreLoadVal);

void TIMERS_voidTIM0SetCompareVal(u8 Copy_u8Compare);
void TIMERS_voidTIM0_Enable_OVF_Interrupt();
void TIMERS_voidTIM0_Disable_OVF_Interrupt();
void TIMERS_voidTIM0_Enable_CTC_Interrupt();
void TIMERS_voidTIM0_Disable_CTC_Interrupt();

void TIMERS_voidDeInit(TIMER_ID T_ID);


void TIMERS_voidTIM0_TIM1_PrescalerRESET();
void TIMERS_voidTIM0SetCallBackFunction(void (*ptrToFun) (void));
#endif /* MCAL_TIMERS_TIMERS_INTERFACE_H_ */
