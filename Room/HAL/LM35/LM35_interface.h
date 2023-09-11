/*
 * LM35_interface.h
 *
 *  Created on: Aug 18, 2023
 *      Author: yosse
 */

#ifndef HAL_LM35_LM35_INTERFACE_H_
#define HAL_LM35_LM35_INTERFACE_H_


#define LM35_CHANNEL_0		0
#define LM35_CHANNEL_1		1
#define LM35_CHANNEL_2		2
#define LM35_CHANNEL_3		3
#define LM35_CHANNEL_4		4
#define LM35_CHANNEL_5		5
#define LM35_CHANNEL_6		6
#define LM35_CHANNEL_7		7


/**
 * 	@ISR_FuncPtr_t Copy_ISR_FuncPtr_tAdcIsR : pointer to adc isr function if u dont use interrupt pass NULL
 *
 */
void LM35_voidInit(ISR_FuncPtr_t Copy_ISR_FuncPtr_tAdcIsR);





/**
 *
 * function select adc channel and start conversion ONLY!!
 */
void LM35_voidStartConv(void);

/**
 * NAME : LM35_voidReadDegree
 *
 *	IMPORTANT NOTE:
 *					U have to use LM35_voidStartConv before trying to call LM35_voidReadDegree
 *					even if u use interrupt!!
 * 	inputs:
 * 			@u16* copy_pu16TempDegre : pointer to return lm35 read in celsius
 *
 *
 * return void
 */
void LM35_voidReadDegree(u8 copy_u8LM35_Channel,u16* copy_pu16Tempcelsius);

#endif /* HAL_LM35_LM35_INTERFACE_H_ */
