/*
 * SPT_private.h
 *
 *  Created on: Aug 21, 2023
 *      Author: yosse
 */

#ifndef MCAL_SPT_SPT_PRIVATE_H_
#define MCAL_SPT_SPT_PRIVATE_H_

/**timer0***/

#define PWM_TCCR0_REG		(*(volatile u8*)0x53)

#define PWM_TCCR0_CS00_BIT		0
#define PWM_TCCR0_CS01_BIT		1
#define PWM_TCCR0_CS02_BIT		2

#define PWM_TCCR0_WGM01_BIT		3

#define PWM_TCCR0_COM00_BIT		4
#define PWM_TCCR0_COM01_BIT		5

#define PWM_TCCR0_WGM00_BIT		6

#define PWM_TCCR0_FOC0_BIT		7


#define PWM_TCNT0_REG		(*(volatile u8*)0x52)


#define PWM_OCR0_REG		(*(volatile u8*)0x5C)



/******timer1 ****/
#define PWM_TCCR1A_REG		(*(volatile u8*)0x4F)

#define PWM_TCCR1A_WMG10_BIT	0
#define PWM_TCCR1A_WMG11_BIT	1

#define PWM_TCCR1A_COM1B0_BIT	4
#define PWM_TCCR1A_COM1B1_BIT	5

#define PWM_TCCR1A_COM1A0_BIT	6
#define PWM_TCCR1A_COM1A1_BIT	7



#define PWM_TCCR1B_REG		(*(volatile u8*)0x4E)

#define PWM_TCCR1B_CS10_BIT   0
#define PWM_TCCR1B_CS11_BIT   1
#define PWM_TCCR1B_CS12_BIT   2

#define PWM_TCCR1B_WGM12_BIT  3
#define PWM_TCCR1B_WGM13_BIT  4



#define PWM_TIMSK_REG	(*(volatile u8)0x59)

#define PWM_TIMSK_OCIE1A_BIT	4
#define PWM_TIMSK_OCIE1B_BIT	3

#define PWM_OCR1A_REG 		(*(volatile u16*)0x4A)
#define PWM_OCR1B_REG 		(*(volatile u16*)0x48)

#define PWM_ICR1_REG 		(*(volatile u16*)0x46)

#endif /* MCAL_SPT_SPT_PRIVATE_H_ */
