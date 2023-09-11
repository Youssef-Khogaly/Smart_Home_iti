/*
 * GloableINT_Private.h
 *
 *  Created on: Aug 16, 2023
 *      Author: yosse
 */

#ifndef MCAL_GLOBAL_INTERRUPT_GLOABLEINT_PRIVATE_H_
#define MCAL_GLOBAL_INTERRUPT_GLOABLEINT_PRIVATE_H_


#define GINT_GIE_BIT	0x07

#define GINT_SREG_REG	( *((volatile u8*)0x5F ) )



/*********MacroFunc************/

/* Disable Global interrupt*/
#define GIE_DISABLE()		(GINT_SREG_REG &= ~(0x01<<GINT_GIE_BIT))

/*Enable Global interrupt*/
#define GIE_ENABLE()		(GINT_SREG_REG |= (0x01<<GINT_GIE_BIT))

/****************************/






#endif /* MCAL_GLOBAL_INTERRUPT_GLOABLEINT_PRIVATE_H_ */
