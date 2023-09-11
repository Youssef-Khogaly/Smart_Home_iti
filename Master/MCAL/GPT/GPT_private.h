/*
 * GPT_private.h
 *
 *  Created on: Aug 20, 2023
 *      Author: yosse
 */

#ifndef MCAL_GPT_GPT_PRIVATE_H_
#define MCAL_GPT_GPT_PRIVATE_H_


/******TCCR0 BITS********/

#define GPT_TCCR0_CS00_BIT		0
#define GPT_TCCR0_CS01_BIT		1
#define GPT_TCCR0_CS02_BIT		2

#define GPT_TCCR0_WGM01_BIT		3

#define GPT_TCCR0_COM00_BIT		4
#define GPT_TCCR0_COM01_BIT		5

#define GPT_TCCR0_WGM00_BIT		6

#define GPT_TCCR0_FOC0_BIT		7

/******TIMSK BITS********/

#define GPT_TIMSK_TOIE0_BIT		0
#define GPT_TIMSK_OCIE0_BIT		1


/********SFIOR BITS********/

#define GPT_SFIOR_PSR10_BIT		0


/******* Registers***********/

#define GPT_TCCR0_REG		(*(volatile u8*)0x53)

#define GPT_TCNT0_REG		(*(volatile u8*)0x52)

#define GPT_OCR0_REG		(*(volatile u8*)0x5C)

#define GPT_TIMSK_REG		(*(volatile u8*)0x59)

#define GPT_TIFR_REG		(*(volatile u8*)0x58)

#define GPT_SFIOR_REG		(*(volatile u8*)0x50)

/***************************/

/******Timer 1*************/

#define GPT_TCCR1A_REG		(*(volatile u8*)0x4F)

#define GPT_TCCR1A_WMG10_BIT	0
#define GPT_TCCR1A_WMG11_BIT	1

#define GPT_TCCR1A_COM1B0_BIT	4
#define GPT_TCCR1A_COM1B1_BIT	5

#define GPT_TCCR1A_COM1A0_BIT	6
#define GPT_TCCR1A_COM1A1_BIT	7

#define GPT_TCCR1B_REG		(*(volatile u8*)0x4E)

#define GPT_TCCR1B_CS10_BIT   0
#define GPT_TCCR1B_CS11_BIT   1
#define GPT_TCCR1B_CS12_BIT   2

#define GPT_TCCR1B_WGM12_BIT  3
#define GPT_TCCR1B_WGM13_BIT  4



#define GPT_TIMSK_OCIE1A_BIT	4
#define GPT_TIMSK_OCIE1B_BIT	3

#define GPT_OCR1A_REG 		(*(volatile u16*)0x4A)
#define GPT_OCR1B_REG 		(*(volatile u16*)0x48)

#define GPT_ICR1_REG 		(*(volatile u16*)0x46)


#endif /* MCAL_GPT_GPT_PRIVATE_H_ */
