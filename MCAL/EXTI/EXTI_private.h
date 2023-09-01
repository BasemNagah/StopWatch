
#ifndef _H_EXTI_PRIVATE_H
#define _H_EXTI_PRIVATE_H


#define EXTI_MCUCR_REG		*(	(	volatile u8*	)	0x55	)
#define EXTI_MCUCSR_REG		*(	(	volatile u8*	)	0x54	)
#define EXTI_GICR_REG		*(	(	volatile u8*	)	0x5B	)
#define EXTI_GIFR_REG		*(	(	volatile u8*	)	0x5A	)

#define EXTI_INT2_BIT	5
#define EXTI_INT0_BIT	6
#define EXTI_INT1_BIT	7



#endif
