/*
 * ADC_private.h
 *
 *  Created on: Aug 17, 2023
 *      Author: yosse
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_


#define ADC_CONV_FINSHED_CFG				0
#define ADC_CONV_INPROGRESS_CFG				1


#define ADC_INTERRUPT_DISABLE_CFG			0

#define ADC_INTERRUPT_ENABLE_CFG			1

#define ADC_AUTO_TRIGGER_DISABLE_CFG		0
#define ADC_AUTO_TRIGGER_ENABLE_CFG			1


/****AUTO TRIGGER SOURCES****/

#define AD_FREE_RUNNING_CFG					0
#define AD_ANALOG_COMPARTOR_CFG				1
#define AD_EXT_INT0_CFG						2

#define AD_TIMER0_CM_CFG					3
#define AD_TIMER0_OF_CFG					4

#define AD_TIMER1_CM_CFG					5
#define AD_TIMER1_OF_CFG					6
#define AD_TIMER1_CAPTURE_CFG				7

/****ADC_voltageRef*****/
#define AD_VREF_AREF_CFG					0
#define AD_VREF_AVCC_CFG					1
#define AD_VREF_IVF_2_56_V_CFG				3



/***ADC PRESCALER****/

#define AD_PRESCALER_2_CFG				0
#define AD_PRESCALER_4_CFG				2
#define AD_PRESCALER_8_CFG				3
#define AD_PRESCALER_16_CFG				4
#define AD_PRESCALER_32_CFG				5
#define AD_PRESCALER_64_CFG				6
#define AD_PRESCALER_128_CFG			7

/**ADMUX_BITS**/
#define AD_ADMUX_MUX0_BIT		0
#define AD_ADMUX_MUX1_BIT		1
#define AD_ADMUX_MUX2_BIT		2
#define AD_ADMUX_MUX3_BIT		3
#define AD_ADMUX_MUX4_BIT		4

#define AD_ADMUX_ADLAR_BIT		5

#define AD_ADMUX_REFS0_BIT		6
#define AD_ADMUX_REFS1_BIT		7

/**ADCSRA_BITS**/
#define AD_ADCSRA_ADPS0_BIT		0
#define AD_ADCSRA_ADPS1_BIT		1
#define AD_ADCSRA_ADPS2_BIT		2

#define AD_ADCSRA_ADIE_BIT		3

#define AD_ADCSRA_ADIF_BIT		4

#define AD_ADCSRA_ADATE_BIT		5

#define AD_ADCSRA_ADSC_BIT		6

#define AD_ADCSRA_ADEN_BIT		7

/**** SFIOR BITS ***/

#define AD_SFIOR_ADST0_BIT		5
#define AD_SFIOR_ADST1_BIT		6
#define AD_SFIOR_ADST2_BIT		7






/***Registers**********/
#define AD_ADMUX_REG	(*(volatile u8*)0x27)

#define AD_ADCSRA_REG	(*(volatile u8*)0x26)

#define AD_ADCH_REG		(*(volatile u8*)0x25)

#define AD_ADCL_REG		(*(volatile u8*)0x24)

#define AD_SFIOR_REG	(*(volatile u8*)0x50)


/*****************MACRO FUNCTIONS*************/

#define AD_DISABLE()			(	AD_ADCSRA_REG &= ~(0x01 << AD_ADCSRA_ADEN_BIT) )
#define AD_ENABLE()				(	AD_ADCSRA_REG |= (0x01 << AD_ADCSRA_ADEN_BIT) )


#define AD_CHANNEL_SELECT(_CH)	(	AD_ADMUX_REG = (AD_ADMUX_REG & 0xE0) | _CH	)

#define AD_VREF_SELECT(_Vref)	(	AD_ADMUX_REG = (AD_ADMUX_REG & 0x3F) | (_Vref << AD_ADMUX_REFS0_BIT ) )

/*
 * return
* 		:	AD_CONV_FINSHED
* 			AD_CONV_INPROGRESS
 * */
#define AD_READ_CONVSTAT()		(	 (AD_ADCSRA_REG>>AD_ADCSRA_ADSC_BIT) &0x01 )
#define AD_STARTCONV()			( AD_ADCSRA_REG |= (0x01 << AD_ADCSRA_ADSC_BIT) )

#define AD_READ_RESULT()		( ((u16)AD_ADCL_REG) | (AD_ADCH_REG << 8)	)

#define AD_PRESCALER_SELECT(_PRE)		( AD_ADCSRA_REG |= _PRE  )


#define AD_INTERRUPT_DISABLE()		( AD_ADCSRA_REG &= ~(0x01 << AD_ADCSRA_ADIE_BIT) )
#define AD_INTERRUPT_ENABLE()		( AD_ADCSRA_REG |= (0x01 << AD_ADCSRA_ADIE_BIT) )


#define AD_AUTO_TRIGGER_DISABLE()	(AD_ADCSRA_REG &= ~(0x01 << AD_ADCSRA_ADATE_BIT))
#define AD_AUTO_TRIGGER_ENABLE()	(AD_ADCSRA_REG |= (0x01 << AD_ADCSRA_ADATE_BIT))


#define AD_ATRIGGER_SOURCE_SELECT(_SRC)	( AD_SFIOR_REG = (AD_SFIOR_REG & 0x1F) |( _SRC << AD_SFIOR_ADST0_BIT) )

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
