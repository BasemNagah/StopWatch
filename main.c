/*
 * main.c
 *
 *  Created on: Aug 24, 2023
 *      Author: hp
 */
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/KPD/KPAD_interface.h"
#include "HAL/CLCD/CLCD_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "MCAL/TIMERS/TIMERS_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	KPAD_voidInit();
	CLCD_voidInit();
	TIMER_Config_t TimerInit = { TIMER0_ID , Normal_mode_OVF , DISCONNECT_OCX , T0_FCPU_1024 , Polling   };
	TIMERS_voidInit(&TimerInit);


	s8 i ;
	s8 j ;


	while(1)
	{
		s8 mintus  = 0 ;
		s8 seconds = 0 ;
		u8 getpressed = 0 ;
		CLCD_voidSendCommand(0x01);
		CLCD_voidSetPositoion(1,1);
		//position of zeros 10 , 11 , 13 , 14
		CLCD_voidSendString((u8*)"SET TIME 00:00",15);
		getpressed = KPAD_u8GetPressed() ;
		while(getpressed != '=')
		{
			for(u8 i = 0 ; i<5 ; i++)
			{
				if(i == 2)continue;
				getpressed = KPAD_u8GetPressed() ;
				while(getpressed == 0xff || getpressed == '=' )
				{
					getpressed = KPAD_u8GetPressed() ;
				}
				CLCD_voidSetPositoion(1,10+i);
				CLCD_voidSendNumber(getpressed-'0');
				if( i == 0 ) mintus  += ((getpressed-'0')*10);
				if( i == 1 ) mintus  += (getpressed-'0');
				if( i == 3 ) seconds += ((getpressed-'0')*10);
				if( i == 4 ) seconds += (getpressed-'0');
			}
			getpressed = KPAD_u8GetPressed() ;
			while(getpressed == 0xff)
			{
				getpressed = KPAD_u8GetPressed() ;
			}
		}
		CLCD_voidSendCommand(0x01);

		for(i = mintus ; i>=0 ; i-- )
		{
			//mintus
			if(i > 9)
			{
				CLCD_voidSetPositoion(1,6);
			}
			else
			{
				CLCD_voidSetPositoion(1,6);
				CLCD_voidSendNumber(0);
				CLCD_voidSetPositoion(1,7);
			}
			CLCD_voidSendNumber(i);
			CLCD_voidSetPositoion(1,8);
			CLCD_voidSendString((u8*)":",2);
			//second
			for(j = seconds ; j>=0 ; j-- )
			{
				if(j > 9)
				{
					CLCD_voidSetPositoion(1,9);
				}
				else
				{
					CLCD_voidSetPositoion(1,9);
					CLCD_voidSendNumber(0);
					CLCD_voidSetPositoion(1,10);
				}
				CLCD_voidSendNumber(j);
				for(u8 k = 0 ; k <31 ; k++)
				{
					TIMERS_voidTIM0Start(&TimerInit);
				}

			}

			seconds = 59 ;
		}
		CLCD_voidSendCommand(0x01);
		CLCD_voidSetPositoion(1,6);
		CLCD_voidSendString((u8*)"Time out",9);
		_delay_ms(1000);
	}




	return 0 ;
}



