#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_


#define ADC_ADMUX_REG          *((volatile u8 *)0x27)
#define ADC_ADCSRA_REG         *((volatile u8 *)0x26)
#define ADC_ADCH_REG           *((volatile u8 *)0x25)
#define ADC_ADCL_REG           *((volatile u8 *)0x24)

#define ADC_ADC_REG            *((volatile u16 *)0x24)

#define ADC_SFIOR_REG          *((volatile u8 *)0x50)

#define ADC_ADEN_BIT    7
#define ADC_ADATE_BIT	5
#define ADC_ADIE_BIT    3
#define ADC_ADSC_BIT    6
#define ADC_ADIF_BIT    4

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
