/*
 * ADC_interface.h
 *
 *  Created on: Aug 17, 2023
 *      Author: yosse
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_


/***ADC CHANNELS****/

#define ADC_CHANNEL0			0
#define ADC_CHANNEL1			1
#define ADC_CHANNEL2			2
#define ADC_CHANNEL3			3
#define ADC_CHANNEL4			4
#define ADC_CHANNEL5			5
#define ADC_CHANNEL6			6
#define ADC_CHANNEL7			7





/******Interrupt Disable Functions*******/


void ADC_VoidInit(void);

/**
 * Name: ADC_VoidStartConv_Blocking
 * des: function start adc conversion in selected channel and blocking the code till conversion end
 * inputs:
 * 			@u8 copy_u8ADChannel:
 * 									options:
 * 												ADC_CHANNEL0
 * 												ADC_CHANNEL1
 * 												ADC_CHANNEL2
 * 												ADC_CHANNEL3
 * 												ADC_CHANNEL4
 * 												ADC_CHANNEL5
 * 												ADC_CHANNEL6
 * 												ADC_CHANNEL7
 * 			@u16* copy_pu16ReadVal:
 * 									Pointer to u16 to return ADC result
 *
 *
 *		return: void
 */
void ADC_VoidStartConv_Blocking(u8 copy_u8ADChannel,u16* copy_pu16ReadVal);


/******Interrupt ENABLE  Functions*******/




/**
 * name:	ADC_VoidInit
 *
 * 	inputs:
 * 			@ISR_FuncPtr_t copy_ISR_FuncPtr_t : pointer to isr function
 *
 * 	return void
 */
void ADC_VoidInit_interrupt(ISR_FuncPtr_t copy_ISR_FuncPtr_t);

/**
 * Name: ADC_VoidStartConv_interrupt
 * des : function start conversion on selected channel and when conversion end call isr function
 * inputs:
 * 			@u8 copy_u8ADChannel:
 * 									options:
 * 												ADC_CHANNEL0
 * 												ADC_CHANNEL1
 * 												ADC_CHANNEL2
 * 												ADC_CHANNEL3
 * 												ADC_CHANNEL4
 * 												ADC_CHANNEL5
 * 												ADC_CHANNEL6
 * 												ADC_CHANNEL7
 * 			@u16* copy_pu16ReadVal:
 * 									Pointer to u16 to return ADC result
 *
 *
 *		return: void
 */
void ADC_VoidStartConv_interrupt(u8 copy_u8ADChannel);


void ADC_voidGetCurrChannel(u8* copy_pu8CurrAdcChannel);
/************************************/
void ADC_VoidRefresh_freeRunning(void);
void ADC_VoidSelectChannel(u8 copy_u8Channel);
void ADC_voidReadResult(u16* copy_pu16AdcResult);


#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
