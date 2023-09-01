
#include "../../MCAL/DIO/DIO_interface.h"

#include "SSD_config.h"
#include "SSD_private.h"
#include "SSD_interface.h"


void SSD_voidInit			(SSD_t * Copy_pstructSSD){

    DIO_voidSetPortDirection(Copy_pstructSSD->Port , DIO_OUTPUT);
    switch(Copy_pstructSSD->CommonState){
        case SSD_COMMON_ANODE:
        DIO_voidSetPortValue(Copy_pstructSSD->Port , 0xff );
        break;
       
        case SSD_COMMON_CATHODE:
        DIO_voidSetPortValue(Copy_pstructSSD->Port , 0x00 );
        break;
       
       default:
       break;

    }

}
void SSD_voidEnable			(SSD_t * Copy_pstructSSD ,u8 Copy_u8Number ){

    switch(Copy_pstructSSD->CommonState){
          case SSD_COMMON_CATHODE:
        DIO_voidSetPortValue(Copy_pstructSSD->Port , ArrayNumbers[Copy_u8Number] );
        break;
       
        case SSD_COMMON_ANODE:
        DIO_voidSetPortValue(Copy_pstructSSD->Port , ~ArrayNumbers[Copy_u8Number] );
        break;
       
       default:
       break;
        
    }
}
void SSD_voidDisable		(SSD_t * Copy_pstructSSD){
       
        switch(Copy_pstructSSD->CommonState){
        case SSD_COMMON_ANODE:
        DIO_voidSetPortValue(Copy_pstructSSD->Port , 0xff );
        break;
       
        case SSD_COMMON_CATHODE:
        DIO_voidSetPortValue(Copy_pstructSSD->Port , 0x00 );
        break;
       
       default:
       break;

    }
}


