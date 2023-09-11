/*
 * EXT_INT_Private.h
 *
 *  Created on: Aug 16, 2023
 *      Author: yosse
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_EXT_INT_PRIVATE_H_
#define MCAL_EXTERNAL_INTERRUPT_EXT_INT_PRIVATE_H_

#define EXT_INT_INT_PULLUP_DISABLE	0x00
#define EXT_INT_INT_PULLUP_ENABLE	0x01


/**********************************/

/*******BITS Locations**********/

#define EX_INT_MCUCR_ISC00_BIT		0x00
#define EX_INT_MCUCR_ISC01_BIT		0x01
#define EX_INT_MCUCR_ISC10_BIT		0x02
#define EX_INT_MCUCR_ISC11_BIT		0x03

#define EX_INT_MCUCSR_ISC2_BIT		0x06

#define EX_INT_GICR_EINT0_BIT		0x06
#define EX_INT_GICR_EINT1_BIT		0x07
#define EX_INT_GICR_EINT2_BIT		0x05




/******************************/

/************hardware registers*****/
#define HW_REG(_REGADD)			( * ( (volatile u8*) _REGADD ) )

#define EX_INT_MCUCR_REG		(HW_REG(0x55))

#define EX_INT_MCUCSR_REG		(HW_REG(0x54))

#define EX_INT_GICR_REG			(HW_REG(0x5B))

#define EX_INT_GIFR_REG			(HW_REG(0x5A))



/*************************************/


/********MacroFunc*********/
/* Disable int0 interrupt*/
#define EXT_INT0_DISABLE()		( EX_INT_GICR_REG &= ~(0x01 << EX_INT_GICR_EINT0_BIT)  )

/* Enable int0 interrupt*/
#define EXT_INT0_ENABLE()		( EX_INT_GICR_REG |= (0x01 << EX_INT_GICR_EINT0_BIT) )

/* Disable int1 interrupt*/
#define EXT_INT1_DISABLE()		( EX_INT_GICR_REG &= ~(0x01 << EX_INT_GICR_EINT1_BIT)  )

/* Enable int1 interrupt*/
#define EXT_INT1_ENABLE()		( EX_INT_GICR_REG |= (0x01 << EX_INT_GICR_EINT1_BIT) )

/* Disable int2 interrupt*/
#define EXT_INT2_DISABLE()		( EX_INT_GICR_REG &= ~(0x01 << EX_INT_GICR_EINT2_BIT)  )

/* Enable int2 interrupt*/
#define EXT_INT2_ENABLE()		( EX_INT_GICR_REG |= (0x01 << EX_INT_GICR_EINT2_BIT) )

/*set Int0 sense control*/
#define EXT_INT0_ISC_SET(_ISC)	(EX_INT_MCUCR_REG = (EX_INT_MCUCR_REG & 0xFC)|  _ISC )

/*set Int1 sense control*/
#define EXT_INT1_ISC_SET(_ISC)	(EX_INT_MCUCR_REG =  (EX_INT_MCUCR_REG & 0xF3)| (_ISC << EX_INT_MCUCR_ISC10_BIT ) )

/*set Int2 sense control*/
#define EXT_INT2_ISC_SET(_ISC)	(EX_INT_MCUCSR_REG |=  ( (_ISC &0x01) << EX_INT_MCUCSR_ISC2_BIT ) )




#endif /* MCAL_EXTERNAL_INTERRUPT_EXT_INT_PRIVATE_H_ */
