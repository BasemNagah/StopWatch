
#ifndef _H_EXTI_INTERFACE_H
#define _H_EXTI_INTERFACE_H



#define EXTI_RISING_EDGE		0
#define EXTI_FAILING_EDGE		1
#define EXTI_LOW_LEVEL			2
#define EXTI_ON_CHANGE_LEVEL	3

#define EXTI_INT0				0
#define EXTI_INT1				1
#define EXTI_INT2				2


void EXTI_voidChangeSenseControl	(u8 Copy_u8IntId	,	u8 Copy_u8SenseControl	);

void EXTI_voidEnable	(u8 Copy_u8IntId);
void EXTI_voidDisable	(u8 Copy_u8IntId);

void EXTI_voidSetCallBack	(u8 Copy_u8IntId , void (*Pf) (void)	);


#endif
