/*
 * GPT_program.c
 *
 *  Created on: Aug 20, 2023
 *      Author: yosse
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Bit_Math.h"
#include "GPT_private.h"
#include "GPT_interface.h"
#include "../Global_interrupt/GloableINT_Private.h"

void __vector_11(void) __attribute__ ((signal,used));
void __vector_10(void) __attribute__ ((signal,used));

void __vector_7(void) __attribute__ ((signal,used));


static ISR_FuncPtr_t G_TIMER0_OVF_CBF = NULL;
static ISR_FuncPtr_t G_TIMER0_CTC_CBF = NULL;

static ISR_FuncPtr_t G_TIMER1_CTCA_CBF = NULL;

void GPT_VoidInit(GPT_stConfig* copy_pGPT_stConfig) {
	if (copy_pGPT_stConfig) {
		if (copy_pGPT_stConfig->GPT_timer == GPT_Timer0)
		{
			if (copy_pGPT_stConfig->GPT_Mode == GPT_NormalMode)
			{

				// set call back func
				G_TIMER0_OVF_CBF = copy_pGPT_stConfig->GPT_Timer_CBF;
				/*select mode*/
				Clr_Bit(GPT_TCCR0_REG, GPT_TCCR0_WGM00_BIT);
				Clr_Bit(GPT_TCCR0_REG, GPT_TCCR0_WGM01_BIT);
				// select clock source
				GPT_TCCR0_REG |= copy_pGPT_stConfig->GPT_Prescaler;
				// set preloaded value
				GPT_TCNT0_REG = copy_pGPT_stConfig->GPT_Preloaded;
				//enable timer ovf interrupt
				GPT_TIMSK_REG |= 0x01;
				// enable gloable interrupt
				GIE_ENABLE();

			}
			else if (copy_pGPT_stConfig->GPT_Mode == GPT_CTCMode)
			{
				/* set call back func*/
				G_TIMER0_CTC_CBF = copy_pGPT_stConfig->GPT_Timer_CBF;
				/*select mode*/
				Clr_Bit(GPT_TCCR0_REG, GPT_TCCR0_WGM00_BIT);
				Set_Bit(GPT_TCCR0_REG, GPT_TCCR0_WGM01_BIT);
				// select clock source
				GPT_TCCR0_REG |= copy_pGPT_stConfig->GPT_Prescaler;
				/* set cmp value*/
				GPT_OCR0_REG = copy_pGPT_stConfig->GPT_u8CmpMatchVal;
				//enable timer0 compare match interrupt
				GPT_TIMSK_REG |= (0x01 << GPT_TIMSK_OCIE0_BIT);
				/*enable gloable interrupt*/
				GIE_ENABLE();

			}
		}
		else if (copy_pGPT_stConfig->GPT_timer == GPT_Timer1)
		{
			 if (copy_pGPT_stConfig->GPT_Mode == GPT_CTCMode)
			 {
				 // set call back func
				 G_TIMER1_CTCA_CBF = copy_pGPT_stConfig->GPT_Timer_CBF;
				 /*select mode*/
				 Clr_Bit(GPT_TCCR1A_REG , GPT_TCCR1A_WMG10_BIT);
				 Clr_Bit(GPT_TCCR1A_REG , GPT_TCCR1A_WMG11_BIT);
				 Set_Bit(GPT_TCCR1B_REG , GPT_TCCR1B_WGM12_BIT);
				 Clr_Bit(GPT_TCCR1B_REG , GPT_TCCR1B_WGM13_BIT);
				 // select prescaler
				 GPT_TCCR1B_REG |= copy_pGPT_stConfig->GPT_Prescaler;
				 // set cmp
				 GPT_OCR1A_REG = copy_pGPT_stConfig->GPT_u8CmpMatchVal;
				 //enable timer1 cmp interrupt
				 GPT_TIMSK_REG |= (0x01 << GPT_TIMSK_OCIE1A_BIT);
				/*enable gloable interrupt*/
				GIE_ENABLE();
			 }

		}
		else if (copy_pGPT_stConfig->GPT_timer == GPT_Timer2)
		{
			// to continue
		}
	} else {

	}
}

void GPT_voidReadTimer(GPT_stConfig* copy_pGPT_stConfig , u8* copy_pu8Timer_read)
{
	if(copy_pGPT_stConfig->GPT_timer == GPT_Timer0)
	{
		*copy_pu8Timer_read = GPT_TCNT0_REG;
	}
}
void GPT_VoidSetPreload(GPT_enTimer Copy_GPT_enTimer, u8 Copy_u8PreloadVal) {
	if (Copy_GPT_enTimer == GPT_Timer0) {
		GPT_TCNT0_REG = Copy_u8PreloadVal;
	}
}

void __vector_10(void)
{
	if(G_TIMER0_CTC_CBF)
		G_TIMER0_CTC_CBF();
}
void __vector_11(void) {
	if (G_TIMER0_OVF_CBF)
		G_TIMER0_OVF_CBF();
}

void __vector_7(void)
{
	if (G_TIMER1_CTCA_CBF)
		G_TIMER1_CTCA_CBF();
}
