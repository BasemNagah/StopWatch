/*
 * GIE_program.c
 *
 *  Created on: Aug 12, 2023
 *      Author: Obiid
 */



#include "GIE_interface.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


/* Because you are in the mcal so you can't now use the DIO*/

void GIE_voidEnable		(void){

	SET_BIT(SREG_REG,7);

}
void GIE_voidDisable	(void){
	CLR_BIT(SREG_REG,7);
}
