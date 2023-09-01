/*
 * WDT_interface.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Obiid
 */

#ifndef MCAL_WDT_WDT_INTERFACE_H_
#define MCAL_WDT_WDT_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

typedef enum{

	WDT_16_DOT_3_ms,
	WDT_32_DOT_5_ms,
	WDT_65_DOT_ms,
	WDT_0_DOT_13_sec,
	WDT_0_DOT_26_sec,
	WDT_0_DOT_52_sec,
	WDT_1_DOT_0_sec,
	WDT_2_DOT_1_sec

}WDT_prescalar_t;

void WDT_voidEnable(WDT_prescalar_t Copy_Choosen_Time);

void WDT_voidDisable(void);

#endif /* MCAL_WDT_WDT_INTERFACE_H_ */
