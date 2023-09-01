

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"



static void (*Glo_ApfNotification [3] ) ( void ) = { NULL_PTR , NULL_PTR , NULL_PTR } ;

void EXTI_voidChangeSenseControl(u8 Copy_u8IntId	,	u8 Copy_u8SenseControl	){

	switch(Copy_u8IntId){

	case EXTI_INT0:

		switch(Copy_u8SenseControl){
		case EXTI_RISING_EDGE:
			SET_BIT(EXTI_MCUCR_REG,1);
			SET_BIT(EXTI_MCUCR_REG,0);

			break;
		case EXTI_FAILING_EDGE:
			SET_BIT(EXTI_MCUCR_REG,1);
			CLR_BIT(EXTI_MCUCR_REG,0);


			break;
		case EXTI_ON_CHANGE_LEVEL:
			SET_BIT(EXTI_MCUCR_REG,0);
			CLR_BIT(EXTI_MCUCR_REG,1);

			break;
		case EXTI_LOW_LEVEL:
			CLR_BIT(EXTI_MCUCR_REG,1);
			CLR_BIT(EXTI_MCUCR_REG,0);
			break;

		}

		break;

		case EXTI_INT1:
			switch(Copy_u8SenseControl){
			case EXTI_RISING_EDGE:
				SET_BIT(EXTI_MCUCR_REG,3);
				SET_BIT(EXTI_MCUCR_REG,2);

				break;
			case EXTI_FAILING_EDGE:
				SET_BIT(EXTI_MCUCR_REG,3);
				CLR_BIT(EXTI_MCUCR_REG,2);


				break;
			case EXTI_ON_CHANGE_LEVEL:
				CLR_BIT(EXTI_MCUCR_REG,3);
				SET_BIT(EXTI_MCUCR_REG,2);


				break;
			case EXTI_LOW_LEVEL:
				CLR_BIT(EXTI_MCUCR_REG,3);
				CLR_BIT(EXTI_MCUCR_REG,2);
				break;
			}
			break;
			case EXTI_INT2:
				switch(Copy_u8SenseControl){
				case EXTI_RISING_EDGE:
					SET_BIT(EXTI_MCUCSR_REG,6);


					break;
				case EXTI_FAILING_EDGE:

					CLR_BIT(EXTI_MCUCSR_REG,6);
					break;
				}
				break;

	}

}

void EXTI_voidEnable	(u8 Copy_u8IntId){

	switch(Copy_u8IntId){

	case EXTI_INT0:

		SET_BIT(EXTI_GICR_REG,EXTI_INT0_BIT);
		break;
	case EXTI_INT1:
		SET_BIT(EXTI_GICR_REG,EXTI_INT1_BIT);
		break;

	case EXTI_INT2:
		SET_BIT(EXTI_GICR_REG,EXTI_INT2_BIT);
		break;

	}
}
void EXTI_voidDisable	(u8 Copy_u8IntId){
	switch(Copy_u8IntId){

	case EXTI_INT0:

		CLR_BIT(EXTI_GICR_REG,EXTI_INT0_BIT);
		break;
	case EXTI_INT1:
		CLR_BIT(EXTI_GICR_REG,EXTI_INT1_BIT);
		break;

	case EXTI_INT2:
		CLR_BIT(EXTI_GICR_REG,EXTI_INT2_BIT);
		break;

	}
}

void EXTI_voidSetCallBack	(u8 Copy_u8IntId , void (*Pf) (void)	){


	/*Options of Copy_u8IntId
	 * EXTI_INT0 = 0
	 * EXTI_INT1 = 1
	 * EXTI_INT2 = 2
	 * */
	Glo_ApfNotification[Copy_u8IntId] = Pf;
}


/* ISR for INT0 */
//void __vector_1	(void)	__attribute__((signal));
//void __vector_1	(void)
//{
//	if (Glo_ApfNotification[0] != NULL_PTR)
//	{
//		Glo_ApfNotification[0]();
//	}
//
//
//}
/* ISR for INT1 */
void __vector_2	(void)	__attribute__((signal));
void __vector_2	(void)
{
	if (Glo_ApfNotification[1] != NULL_PTR)
	{
		Glo_ApfNotification[1]();
	}


}
/* ISR for INT2 */
void __vector_3	(void)	__attribute__((signal));
void __vector_3	(void)
{
	if (Glo_ApfNotification[2] != NULL_PTR)
	{
		Glo_ApfNotification[2]();
	}

}


