/*
 * CLCD_program.c
 *
 *  Created on: Aug 5, 2023
 *      Author: Obiid
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#define F_CPU 8000000UL
#include <util/delay.h>

#include "../../MCAL/DIO/DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"
#include "CLCD_interface.h"



void CLCD_voidInit(void){

	/* Directions of the pins*/
	DIO_voidSetPortDirection(CLCD_DATA_PORT,DIO_OUTPUT);
	DIO_voidSetPinDirection(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_OUTPUT);
	DIO_voidSetPinDirection(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_OUTPUT);
	DIO_voidSetPinDirection(CLCD_CTRL_PORT, CLCD_EN_PIN, DIO_OUTPUT);


	/* Power on sequence*/

	_delay_ms(40);

	//Function Set
	CLCD_voidSendCommand(0b00111000);
	_delay_us(50);

	//Display on/off
	CLCD_voidSendCommand(0b00001100);
	_delay_us(50);

	//DispalyClear
	CLCD_voidSendCommand(0x01);
	_delay_ms(2);

	//Entry Mode Set
	CLCD_voidSendCommand(0b00000110);

}

void CLCD_voidSendCommand(u8 Copy_u8Command){

	//Rs = 0 -> command
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_LOW);

	//RW = 0-> write
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_LOW);
	//Send command
	DIO_voidSetPortValue(CLCD_DATA_PORT, Copy_u8Command);
	//enable sequence
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, DIO_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, DIO_LOW);
	_delay_ms(2);

}

void CLCD_voidSendData(u8 Copy_u8Data){

	//Rs = 1 -> data
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_HIGH);

	//RW = 0-> write
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_LOW);
	//Send data
	DIO_voidSetPortValue(CLCD_DATA_PORT, Copy_u8Data);
	//enable sequence
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, DIO_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_EN_PIN, DIO_LOW);

}



void CLCD_voidCreateNewChar(u8 Copy_u8PatternLocation, u8 * Copy_pu8ExtraChar){

	u8 Local_u8PatternLocation = 64 + Copy_u8PatternLocation * 8;
	CLCD_voidSendCommand(Local_u8PatternLocation);

	for(u8 i = 0; i<8 ; i++){

		CLCD_voidSendData(Copy_pu8ExtraChar[i]);
	}

	CLCD_voidSendData(Copy_u8PatternLocation);
}

void CLCD_voidCreateAndDispNew(u8 Copy_u8PatternLocation, u8 * Copy_pu8ExtraChar, u8 Copy_u8Row,u8 Copy_u8Col){

	u8 Local_u8PatternLocation = 64 + Copy_u8PatternLocation * 8;
	CLCD_voidSendCommand(Local_u8PatternLocation);

	for(u8 i = 0; i<8 ; i++){

		CLCD_voidSendData(Copy_pu8ExtraChar[i]);
	}

	CLCD_voidSendData(Copy_u8PatternLocation);

	CLCD_voidSetPositoion(Copy_u8Row, Copy_u8Col);

	CLCD_voidSendData(Copy_u8PatternLocation);
}

// The first step is to write the value of the character in the memory then
// if you want to display it on the screen just call the function of send data with the location
// or pattern location to the function of CLCD_voidSendData(0); for example 0 here is the first location
void CLCD_voidSetPositoion(u8 Copy_u8Row,u8 Copy_u8Col){

	switch(Copy_u8Row){

	case CLCD_ROW_1:
		CLCD_voidSendCommand(0x80 + Copy_u8Col - 1 );
		break;

	case CLCD_ROW_2:
		CLCD_voidSendCommand(0xc0 + Copy_u8Col - 1);
		break;

	default:
		break;
	}


}

void CLCD_voidSendString(u8 * Copy_u8PtrToChar, u8 Copy_u8LengthOfStr){

	for(u8 i = 0; (i<Copy_u8LengthOfStr) && (Copy_u8PtrToChar[i] != '\0'); i++ ){

		CLCD_voidSendData(Copy_u8PtrToChar[i]);
	}

}

void CLCD_voidSendNumber(s16 Copy_s16Num){

	u16 Local_u16Num = 0;
	u16 Local_u16MulOf10 = 1;
	u8 Local_u16Temp = 0;

	if(Copy_s16Num == 0){

		CLCD_voidSendData('0');
	}

	else if(Copy_s16Num < 0){


		CLCD_voidSendData('-');
		Local_u16Num = -1 * Copy_s16Num;

		while(Local_u16Num != 0){

			Local_u16Num /= 10;
			Local_u16MulOf10 *= 10;
		}


		Local_u16Num = -1 * Copy_s16Num;
		Local_u16MulOf10 /= 10;

		while(Local_u16MulOf10 != 0){

			Local_u16Temp = Local_u16Num / (Local_u16MulOf10);
			CLCD_voidSendData(Local_u16Temp + 48);
			Local_u16Num = Local_u16Num - (Local_u16MulOf10 * Local_u16Temp);
			Local_u16MulOf10 /= 10;


		}
	}
	else {

		Local_u16Num = Copy_s16Num;

		while(Local_u16Num != 0){

			Local_u16Num /= 10;
			Local_u16MulOf10 *= 10;


		}



		Local_u16Num = Copy_s16Num;
		Local_u16MulOf10 /= 10;

		while(Local_u16MulOf10 != 0){

			Local_u16Temp = Local_u16Num / (Local_u16MulOf10);
			CLCD_voidSendData(Local_u16Temp + 48);
			Local_u16Num = Local_u16Num - (Local_u16MulOf10 * Local_u16Temp);
			Local_u16MulOf10 /= 10;


		}	}

}
