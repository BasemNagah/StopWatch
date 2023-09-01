/*
 * CLCD_interface.h
 *
 *  Created on: Aug 5, 2023
 */
#ifndef HAL_CLCD_CLCD_INTERFACE_H_
#define HAL_CLCD_CLCD_INTERFACE_H_


#include "../../LIB/STD_TYPES.h"

#define CLCD_ROW_1		1
#define CLCD_ROW_2		2

#define CLCD_COL_1		1
#define CLCD_COL_2		2
#define CLCD_COL_3      3
#define CLCD_COL_4      4
#define CLCD_COL_5      5
#define CLCD_COL_6      6
#define CLCD_COL_7      7
#define CLCD_COL_8      8
#define CLCD_COL_9      9
#define CLCD_COL_10     10
#define CLCD_COL_11     11
#define CLCD_COL_12     12
#define CLCD_COL_13     13
#define CLCD_COL_14     14
#define CLCD_COL_15     15
#define CLCD_COL_16     16

void CLCD_voidInit(void);
void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidSetPositoion(u8 Copy_u8Row,u8 Copy_u8Col);

//Extra Character

void CLCD_voidCreateNewChar(u8 Copy_u8PatternLocation, u8 * Copy_u8PtrToCharacters);

void CLCD_voidCreateAndDispNew(u8 Copy_u8PatternLocation, u8 * Copy_pu8ExtraChar, u8 Copy_u8Row,u8 Copy_u8Col);
void CLCD_voidSendString(u8 * Copy_u8PtrToChar, u8 Copy_u8LengthOfStr);
//Send Sabri (Sine wave)

void CLCD_voidSendNumber(s16 Copy_s16Num);


//3.Hamoksha


#endif /* HAL_CLCD_CLCD_INTERFACE_H_ */
