/*
 * LM35_program.c
 *
 *  Created on: Aug 18, 2023
 *      Author: yosse
 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/ADC/ADC_private.h"
#include "../../MCAL/ADC/ADC_Config.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"

#include "LM35_config.h"
#include "LM35_private.h"
#include "LM35_interface.h"





void LM35_voidInit(ISR_FuncPtr_t Copy_ISR_FuncPtr_tAdcIsR)
{
	DIO_VoidSetPinDirection(DIO_PORTA_IDX ,LM35_ADC_CHANNEL_SELECT, DIO_PIN_DIR_INPUT);
#if ADC_INTERRUPT_CFG == ADC_INTERRUPT_DISABLE_CFG
	ADC_VoidInit();
#endif
#if ADC_INTERRUPT_ENABLE_CFG == ADC_INTERRUPT_CFG
	ADC_VoidInit_interrupt(Copy_ISR_FuncPtr_tAdcIsR);
#endif
}



void LM35_voidStartConv(void)
{
	AD_CHANNEL_SELECT(LM35_ADC_CHANNEL_SELECT);
	AD_STARTCONV();
}


void LM35_voidReadDegree(u8 copy_u8LM35_Channel,u16* copy_pu16Tempcelsius)
{
	u16 adcVal = 0;
#if ADC_INTERRUPT_CFG == ADC_INTERRUPT_DISABLE_CFG
	// wait till adc finsh conversion
	AD_CHANNEL_SELECT(copy_u8LM35_Channel);
	AD_STARTCONV();
	// wait till adc finsh conversion
	while( AD_READ_CONVSTAT() == ADC_CONV_INPROGRESS_CFG )
		;
	ADC_voidReadResult(&adcVal);
	*copy_pu16Tempcelsius = (adcVal/LM35_AdcVal_Per_degree);
#endif

#if ADC_INTERRUPT_ENABLE_CFG == ADC_INTERRUPT_CFG
	ADC_voidReadResult(&adcVal);
	*copy_pu16Tempcelsius = (adcVal/LM35_AdcVal_Per_degree);
#endif


}
