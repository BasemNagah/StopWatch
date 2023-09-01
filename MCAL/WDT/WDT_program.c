/*
 * WDT_program.c
 *
 *  Created on: Aug 19, 2023
 *      Author: Obiid
 */


#include "../../LIB/STD_TYPES.h"


#include "WDT_config.h"
#include "WDT_private.h"
#include "WDT_interface.h"


void WDT_voidEnable(WDT_prescalar_t Copy_Choosen_Time){

	/*Set the choosen time*/
	WDT_WDTCR_REG = Copy_Choosen_Time;
	/*Start using the watch dog timer*/
	WDT_WDTCR_REG |= (1<<3);

}
void WDT_voidDisable(void){

	/*Stop WDT*/
	WDT_WDTCR_REG |= (0x2<<3);
	/*Reset the value of WDT to use it again*/
	WDT_WDTCR_REG = 0x00;
}
