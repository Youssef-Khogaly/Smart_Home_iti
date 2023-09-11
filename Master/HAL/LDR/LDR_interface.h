/*
 * LDR_interface.h
 *
 *  Created on: Aug 18, 2023
 *      Author: yossef
 */

#ifndef HAL_LDR_LDR_INTERFACE_H_
#define HAL_LDR_LDR_INTERFACE_H_



#define LDR_NIGHT_TIME	0
#define LDR_SUN_TIME	1




void LDR_VoidInit(ISR_FuncPtr_t Copy_ISR_FuncPtr_tAdcIsR);

void LDR_VoidStartConv(void);

/**
 * name: LDR_VoidGetTime
 *
 * inputs:
 * 			@u8* copy_pu8RetTime : pointer to u8 to return time
 * 								return: 	LDR_DARK_TIME if its dark
 * 								return : 	LDR_SUN_TIME if its sun
 *
 *	@note!! :
 *			if u use interrupt with adc u have to call startConvInterrupt function first then try to read status
 *			if u dont user interrupt with adc u dont need to call start conv adc function function will call it and return result
 *
 *
 *return Void
 */
void LDR_VoidGetTime(u8* copy_pu8RetTime);

#endif /* HAL_LDR_LDR_INTERFACE_H_ */
