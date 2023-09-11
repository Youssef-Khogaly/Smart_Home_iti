/*
 * LDR_program.c
 *
 *  Created on: Aug 18, 2023
 *      Author: yosse
 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/ADC/ADC_private.h"
#include "../../MCAL/ADC/ADC_Config.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "LDR_private.h"
#include "LDR_config.h"
#include "LDR_interface.h"
#include "../../MCAL/DIO/DIO_Config.h"
#include "../../MCAL/DIO/DIO_Interface.h"


void LDR_VoidInit(ISR_FuncPtr_t Copy_ISR_FuncPtr_tAdcIsR)
{
	DIO_VoidSetPinDirection(DIO_PORTA_IDX ,LDR_ADC_CHANNEL_CFG, DIO_PIN_DIR_INPUT);
#if ADC_INTERRUPT_CFG == ADC_INTERRUPT_DISABLE_CFG
	ADC_VoidInit();
#endif
#if ADC_INTERRUPT_ENABLE_CFG == ADC_INTERRUPT_CFG
	ADC_VoidInit_interrupt(Copy_ISR_FuncPtr_tAdcIsR);
#endif
}

void LDR_VoidStartConv(void)
{
	AD_CHANNEL_SELECT(LDR_ADC_CHANNEL_CFG);
	AD_STARTCONV();
}


void LDR_VoidGetTime(u8* copy_pu8RetTime)
{
	u16 adcVal = 0;
	f32 ldrVolt = 0;
#if ADC_INTERRUPT_CFG == ADC_INTERRUPT_DISABLE_CFG
	AD_CHANNEL_SELECT(LDR_ADC_CHANNEL_CFG);
	AD_STARTCONV();
	while( AD_READ_CONVSTAT() == ADC_CONV_INPROGRESS_CFG )
		;
	ADC_voidReadResult(&adcVal);
	ldrVolt = (adcVal/LDR_adcVal_PER_Volt);
	*copy_pu8RetTime = (ldrVolt >= LDR_NIGHT_VOLT) ? LDR_NIGHT_TIME : LDR_SUN_TIME;
#endif


#if ADC_INTERRUPT_ENABLE_CFG == ADC_INTERRUPT_CFG
	ADC_voidReadResult(&adcVal);
	ldrVolt = (adcVal/LDR_adcVal_PER_Volt);
	*copy_pu8RetTime = (ldrVolt >= LDR_NIGHT_VOLT) ? LDR_NIGHT_TIME : LDR_SUN_TIME;
#endif
}
