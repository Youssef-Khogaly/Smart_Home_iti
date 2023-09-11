/*
 * EXT_INT_Interface.h
 *
 *  Created on: Aug 16, 2023
 *      Author: yosse
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_EXT_INT_INTERFACE_H_
#define MCAL_EXTERNAL_INTERRUPT_EXT_INT_INTERFACE_H_


/*************ISC***************/
#define  EX_INT_SC_LOW_LEVEL	0x00
#define  EX_INT_SC_ANYCHANGE	0x01
#define  EX_INT_SC_FALING_EDGE	0x02
#define  EX_INT_SC_RISING_EDGE	0x03
#define  EX_INT_DISABLE			0x04

#define EXT_INT0	0
#define EXT_INT1	1
#define EXT_INT2	2


typedef struct
{
	/**
	 * options:
	 * 		enable:
	 * 			EX_INT_SC_LOW_LEVEL
	 * 			EX_INT_SC_ANYCHANGE
	 *			EX_INT_SC_FALING_EDGE
	 *			EX_INT_SC_RISING_EDGE
	 *		Disable:
	 *			EX_INT_DISABLE
	 *
	 */

	u8 EXT_INT0_SC : 3;
	u8 EXT_INT1_SC : 3;

	/**
	 * options:
	 * 		enable:
	 *			EX_INT_SC_FALING_EDGE
	 *			EX_INT_SC_RISING_EDGE
	 *		Disable:
	 *			EX_INT_DISABLE
	 *
	 */

	u8 EXT_INT2_SC : 3;

	ISR_FuncPtr_t ExtInt0_CBF;
	ISR_FuncPtr_t ExtInt1_CBF;
	ISR_FuncPtr_t ExtInt2_CBF;
}ExtInt_stCfg;


void ExtINT_VoidInit(ExtInt_stCfg* copy_pExtInt_stCfg);
void ExtINT_VoidDeInit(ExtInt_stCfg* copy_pExtInt_stCfg);
void ExtINT_changeSense(u8 copy_u8Ext_INT , u8 copy_u8NewSens);
#endif /* MCAL_EXTERNAL_INTERRUPT_EXT_INT_INTERFACE_H_ */
