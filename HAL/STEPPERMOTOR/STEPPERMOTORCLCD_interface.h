/*
 * CLCD_interface.h
 *
 *  Created on: Aug 5, 2023
 *      Author: Abdelrahman
 */
#ifndef HAL_STEPPERMOTOR_INTERFACE_H_
#define HAL_STEPPERMOTOR_INTERFACE_H_


#include "../../LIB/STD_TYPES.h"



void STEPPERMOTOR_voidInit(void);

void STEPPERMOTOR_voidRotCW(u16 degrees);

void STEPPERMOTOR_voidRotCCW(u16 degrees);





#endif /* HAL_CLCD_CLCD_INTERFACE_H_ */
