/*
 * GPT_interface.h
 *
 *  Created on: Aug 20, 2023
 *      Author: yossef
 */

#ifndef MCAL_GPT_GPT_INTERFACE_H_
#define MCAL_GPT_GPT_INTERFACE_H_




typedef enum{
	GPT_Timer0,GPT_Timer1,GPT_Timer2
}GPT_enTimer;

typedef enum {
	GPT_NormalMode,
	GPT_CTCMode = 2
}GPT_enTimerMode;

typedef enum{
	GPT_TIMER_NOCLOCK,
	GPT_TIMER_PRESCALER_1,
	GPT_TIMER_PRESCALER_8,
	GPT_TIMER_PRESCALER_64,
	GPT_TIMER_PRESCALER_256,
	GPT_TIMER_PRESCALER_1024,
	GPT_TIMER_ExtClock_Faling,
	GPT_TIMER_ExtClock_Rising
}GPT_enPrescaler;

typedef struct{
	GPT_enTimer GPT_timer;
	GPT_enTimerMode GPT_Mode;
	GPT_enPrescaler GPT_Prescaler;
	u8 GPT_Preloaded;
	u16 GPT_u8CmpMatchVal;
	ISR_FuncPtr_t GPT_Timer_CBF;
}GPT_stConfig;

void GPT_VoidInit(GPT_stConfig* copy_pGPT_stConfig);
void GPT_voidReadTimer(GPT_stConfig* copy_pGPT_stConfig , u8* Timer_read);

void GPT_VoidSetPreload(GPT_enTimer Copy_GPT_enTimer , u8 Copy_u8PreloadVal);


#endif /* MCAL_GPT_GPT_INTERFACE_H_ */
