/*
 * ADC_program.c
 *
 *  Created on: Aug 17, 2023
 *      Author: yosse
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Bit_Math.h"
#include "ADC_private.h"
#include "ADC_Config.h"
#include "ADC_interface.h"
#include "../Global_interrupt/GloableINT_Private.h"



static ISR_FuncPtr_t Global_pADC_ISR = NULL;

volatile static u16 ADC_CHANNELS_RESULT[8];

volatile static const u8 ADC_CHANNEL_AT_ARR[3] = { ADC_CHANNEL0 , ADC_CHANNEL1 , ADC_CHANNEL2 };

volatile static u8 ADC_CURR_CHANNEL_IDX = 0 ;

void __vector_16(void) __attribute__ ((signal,used));


#if ADC_INTERRUPT_CFG == ADC_INTERRUPT_DISABLE_CFG

void ADC_VoidInit(void)
{
	/*Set ADC Voltage Ref*/
	AD_VREF_SELECT(ADC_VOLTAGE_REF_CFG);

	/*Set ADC PRESCALER*/
	AD_PRESCALER_SELECT(ADC_PRESCALER_CFG);

	/*set ADC Result read as right Adjust clear ADLAR*/
	AD_ADMUX_REG &=	~(0x01 << AD_ADMUX_ADLAR_BIT);

	/*Enable ADC*/
	AD_ENABLE();

	return;
}

void ADC_VoidStartConv_Blocking(u8 copy_u8ADChannel , u16* copy_pu16ReadVal )
{
	if(copy_pu16ReadVal && copy_u8ADChannel <= ADC_CHANNEL7)
	{
		// select adc channel before start adc conversion
		AD_CHANNEL_SELECT(copy_u8ADChannel);
		// start adc convertion
		AD_STARTCONV();
		// wait till adc finsh conversion
		while( AD_READ_CONVSTAT() == ADC_CONV_INPROGRESS_CFG )
			;
		// return adc result in pointer
		*copy_pu16ReadVal = AD_READ_RESULT();
	}
	else
	{
		/*nothing*/
	}
	return;
}

#endif

#if ADC_INTERRUPT_CFG == ADC_INTERRUPT_ENABLE_CFG

void ADC_VoidInit_interrupt(ISR_FuncPtr_t copy_ISR_FuncPtr_t)
{
	/*Set ADC Voltage Ref*/
	AD_VREF_SELECT(ADC_VOLTAGE_REF_CFG);

	/*Set ADC PRESCALER*/
	AD_PRESCALER_SELECT(ADC_PRESCALER_CFG);

	/*set ADC Result read as right Adjust clear ADLAR*/
	AD_ADMUX_REG &=	~(0x01 << AD_ADMUX_ADLAR_BIT);

#if ADC_AUTO_TRIGGER_CFG == ADC_AUTO_TRIGGER_ENABLE_CFG
	AD_ATRIGGER_SOURCE_SELECT(ADC_ATRIGGER_SOURCE_CFG);
	AD_AUTO_TRIGGER_ENABLE();
#endif
	/** set isr function**/
	Global_pADC_ISR = copy_ISR_FuncPtr_t;
	/*Enable Global Interrupt*/
	GIE_ENABLE();
	/*enable specific interrupt*/
	AD_INTERRUPT_ENABLE();
	/*Enable ADC*/
	AD_ENABLE();

	return;
}

void ADC_VoidStartConv_interrupt(u8 copy_u8ADChannel)
{
	if(copy_u8ADChannel <= ADC_CHANNEL7 && (AD_READ_CONVSTAT() == ADC_CONV_FINSHED_CFG))
	{
		// select adc channel before start adc conversion
		AD_CHANNEL_SELECT(copy_u8ADChannel);
		//Start conversion
		AD_STARTCONV();
	}
	else {/*nothing*/}
}



#endif

void ADC_voidReadResult(u16* copy_pu16AdcResult)
{
	if(copy_pu16AdcResult)
	{
		*copy_pu16AdcResult = AD_READ_RESULT();
	}
	else
	{
		/*nothing*/
	}
}

void ADC_voidGetCurrChannel(u8* copy_pu8CurrAdcChannel)
{
		*copy_pu8CurrAdcChannel = (AD_ADMUX_REG &0x1F);
}

void ADC_VoidSelectChannel(u8 copy_u8Channel)
{
	AD_CHANNEL_SELECT(copy_u8Channel);
}
void ADC_VoidRefresh_freeRunning(void)
{
	ADC_CURR_CHANNEL_IDX = 0;
	AD_CHANNEL_SELECT(ADC_CHANNEL_AT_ARR[ADC_CURR_CHANNEL_IDX]);
	AD_STARTCONV();
}

void __vector_16(void)
{

#if ADC_AUTO_TRIGGER_CFG == ADC_AUTO_TRIGGER_ENABLE_CFG && ADC_ATRIGGER_SOURCE_CFG == AD_FREE_RUNNING_CFG
	if(Global_pADC_ISR)
	{
		AD_DISABLE();
		ADC_CHANNELS_RESULT[ ADC_CHANNEL_AT_ARR[ADC_CURR_CHANNEL_IDX] ] = AD_READ_RESULT();
		++ADC_CURR_CHANNEL_IDX;
		if(ADC_CURR_CHANNEL_IDX == 3 )
		{
			ptr = ADC_CHANNELS_RESULT;
			ADC_CURR_CHANNEL_IDX = 0;
			Global_pADC_ISR();
			AD_ENABLE();
			//AD_CHANNEL_SELECT( ADC_CHANNEL_AT_ARR[ADC_CURR_CHANNEL_IDX] );

			//AD_STARTCONV();
		}
		else
		{

			AD_CHANNEL_SELECT( ADC_CHANNEL_AT_ARR[ADC_CURR_CHANNEL_IDX] );
			AD_ENABLE();
			AD_STARTCONV();
		}
	}

#else
	if(Global_pADC_ISR)
		Global_pADC_ISR();
#endif


}


