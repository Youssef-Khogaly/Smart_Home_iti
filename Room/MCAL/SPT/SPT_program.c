/*
 * SPT_program.c
 *
 *  Created on: Aug 21, 2023
 *      Author: yosse
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Bit_Math.h"
#include "SPT_private.h"
#include "SPT_interface.h"

void PWM_voidInit(PWM_stConfig* copy_pst_config)
{
	if(copy_pst_config->PWM_timer == PWM_timer1_select)
	{
		if(copy_pst_config->PWM_mode == PWM_FastPwmMode)
		{
				// select fast pwm mode
				Clr_Bit(PWM_TCCR1A_REG,PWM_TCCR1A_WMG10_BIT);
				Set_Bit(PWM_TCCR1A_REG,PWM_TCCR1A_WMG11_BIT);
				Set_Bit(PWM_TCCR1B_REG , PWM_TCCR1B_WGM12_BIT);
				Set_Bit(PWM_TCCR1B_REG , PWM_TCCR1B_WGM13_BIT);
				// select compare mode
				PWM_TCCR1A_REG |= (copy_pst_config->PWM_compareMode << PWM_TCCR1A_COM1A0_BIT);
				PWM_TCCR1A_REG |= (copy_pst_config->PWM_compareMode << PWM_TCCR1A_COM1B0_BIT);
				//select prescaler

				PWM_TCCR1B_REG |= copy_pst_config->PWM_prescaler;
				// select top value
				PWM_ICR1_REG  = copy_pst_config->PWM_topVal;
				//cmp match value
				if(copy_pst_config->PWM_OCR == PWM_OCR1A)
					PWM_OCR1A_REG = copy_pst_config->PWM_OCR1A_val;
				else if(copy_pst_config->PWM_OCR == PWM_OCR1B)
					PWM_OCR1B_REG = copy_pst_config->PWM_OCR1B_val;
		}
		else if(copy_pst_config->PWM_mode == PWM_PhaseCorrectMode)
		{
				// select fast pwm mode
				Clr_Bit(PWM_TCCR1A_REG,PWM_TCCR1A_WMG10_BIT);
				Set_Bit(PWM_TCCR1A_REG,PWM_TCCR1A_WMG11_BIT);
				Clr_Bit(PWM_TCCR1B_REG , PWM_TCCR1B_WGM12_BIT);
				Set_Bit(PWM_TCCR1B_REG , PWM_TCCR1B_WGM13_BIT);
				// select compare mode
				PWM_TCCR1A_REG |= (copy_pst_config->PWM_compareMode << PWM_TCCR1A_COM1A0_BIT);
				PWM_TCCR1A_REG |= (copy_pst_config->PWM_compareMode << PWM_TCCR1A_COM1B0_BIT);
				//select prescaler

				PWM_TCCR1B_REG |= copy_pst_config->PWM_prescaler;
				// select top value
				PWM_ICR1_REG  = copy_pst_config->PWM_topVal;
				//cmp match value
				PWM_OCR1A_REG = copy_pst_config->PWM_OCR1A_val;
				PWM_OCR1B_REG = copy_pst_config->PWM_OCR1B_val;
		}

	}

	else if (copy_pst_config->PWM_timer == PWM_timer0_select)
	{
		if(copy_pst_config->PWM_mode == PWM_FastPwmMode)
		{
			/*select prescaler*/
			PWM_TCCR0_REG |= copy_pst_config->PWM_prescaler;
			// select fast pwm mode
			Set_Bit(PWM_TCCR0_REG , PWM_TCCR0_WGM00_BIT);
			Set_Bit(PWM_TCCR0_REG , PWM_TCCR0_WGM01_BIT);
			// select Compare Mode
			PWM_TCCR0_REG |= (copy_pst_config->PWM_compareMode << PWM_TCCR0_COM00_BIT);
			// write cmp value
			PWM_OCR0_REG = (u8)copy_pst_config->PWM_OCR1A_val;
		}
		else if(copy_pst_config->PWM_mode == PWM_PhaseCorrectMode)
		{
			/*select prescaler*/
			PWM_TCCR0_REG |= copy_pst_config->PWM_prescaler;
			// select phase correct pwm mode
			Set_Bit(PWM_TCCR0_REG , PWM_TCCR0_WGM00_BIT);
			Clr_Bit(PWM_TCCR0_REG , PWM_TCCR0_WGM01_BIT);
			// select Compare Mode
			PWM_TCCR0_REG |= (copy_pst_config->PWM_compareMode << PWM_TCCR0_COM00_BIT);
			// write cmp value
			PWM_OCR0_REG = (u8)copy_pst_config->PWM_OCR1A_val;
		}
	}
}

void PWM_VoidSetDuty(PWM_stConfig* copy_pst_config , u8 copy_u8DutyCycle)
{
	if(copy_pst_config && copy_pst_config->PWM_timer == PWM_timer1_select && copy_u8DutyCycle <= 100 )
	{
		if(copy_pst_config->PWM_OCR == PWM_OCR1A)
		{
			PWM_OCR1A_REG = (u16)((copy_u8DutyCycle/(f32)100.0) * copy_pst_config->PWM_topVal);
		}
		else if(copy_pst_config->PWM_OCR == PWM_OCR1B)
		{
			PWM_OCR1B_REG = (u16)((copy_u8DutyCycle/(f32)100.0) * copy_pst_config->PWM_topVal);
		}
	}
	else
	{
		// nothing
	}

}




