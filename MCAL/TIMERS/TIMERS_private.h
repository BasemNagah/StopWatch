/*
 * TIMERS_private.h
 *
 *  Created on: Aug 15, 2023
 *      Author: one
 */

#ifndef MCAL_TIMERS_TIMERS_PRIVATE_H_
#define MCAL_TIMERS_TIMERS_PRIVATE_H_

/*Timer 0*/
/*
 * Timer Control Register
 * [FOC0,WGM00,COM01,COM00,WGM01,CS02,CS01,CS00]
 *
 * */
#define TIMERS_TCCR0_REG 	*((volatile u8 *)0x53)
#define TIMERS_TCNT0_REG 	*((volatile u8 *)0x52)
#define TIMERS_OCR0_REG 	*((volatile u8 *)0x5C)

#define TIMERS_TIFR_REG 	*((volatile u8 *)0x58)
#define TIMERS_TIMSK_REG 	*((volatile u8 *)0x59)
#define TIMERS_SFIOR_REG 	*((volatile u8 *)0x50)

#define FOC0_BIT 	7
#define WGM00_BIT 	6
#define WGM01_BIT 	3
#define COM00_BIT   4
#define COM01_BIT   5

// TMSK reg : TIMER Interrupt enable bits for OVF and CTC modes
#define TOIE0_BIT 	0
#define OCIE0_BIT 	1
//TIFR reg : flags
#define TOV0_BIT 	0
#define OCF0_BIT 	1
//SFIOR REG : PRESCALER RESET
#define PSR10_BIT	0

/*Timer 1*/
#define TIMERS_TCCR1A_REG 	*((volatile u8 *)0x4F)
#define TIMERS_TCCR1B_REG 	*((volatile u8 *)0x4E)
#define TCNT1_REG 	*((volatile u16 *)0x4C)
#define OCR1A_REG 	*((volatile u16 *)0x4A)
#define OCR1B_REG	*((volatile u16 *)0x48)
#define ICR1_REG	*((volatile u16 *)0x46)






#endif /* MCAL_TIMERS_TIMERS_PRIVATE_H_ */
