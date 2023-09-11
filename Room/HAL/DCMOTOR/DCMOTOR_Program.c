/*
 * DCMOTOR_Program.c
 *
 *  Created on: Sep 1, 2023
 *      Author: yosse
 */



#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Bit_Math.h"
#include "DCMOTOR_interface.h"
#include "DCMOTOR_Config.h"
#include "../../MCAL/SPT/SPT_interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"

// index is prescaler value that u write it in reg
static const u16 PrescalerArr[5] = {1,8,64,256,1024};
static u8 PrescalerCalculation(u16 Copy_u16Freq);

static PWM_stConfig G_PWM_OCR1A = {
		.PWM_mode = PWM_FastPwmMode,
		.PWM_timer = PWM_timer1_select,
		.PWM_compareMode = PWM_NonInverting,
		.PWM_OCR = PWM_OCR1A
};

static PWM_stConfig G_PWM_OCR1B = {
	.PWM_mode = PWM_FastPwmMode,
	.PWM_timer = PWM_timer1_select,
	.PWM_compareMode = PWM_NonInverting,
	.PWM_OCR = PWM_OCR1B
};


void DCMOTOR_voidInit(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig)
{
	u8 l_Prescaler = 0;
	u16 l_topValue = 0;
	u32 temp = 0;
	if(Copy_pDC_MOTOR_stConfig)
	{
		DIO_voidPinInit(Copy_pDC_MOTOR_stConfig->MOTOR_Port,Copy_pDC_MOTOR_stConfig->MOTOR_IN1_Pin,DIO_PIN_DIR_OUTPUT , DIO_PIN_LOGIC_LOW);
		DIO_voidPinInit(Copy_pDC_MOTOR_stConfig->MOTOR_Port,Copy_pDC_MOTOR_stConfig->MOTOR_IN2_Pin,DIO_PIN_DIR_OUTPUT , DIO_PIN_LOGIC_LOW);
		if(Copy_pDC_MOTOR_stConfig->MOTOR_PWN_Pin != MOTOR_PWM_DISABLE)
		{
			DIO_VoidSetPinDirection(DIO_PORTD_IDX, 5-Copy_pDC_MOTOR_stConfig->MOTOR_PWN_Pin,DIO_PIN_DIR_OUTPUT);
			l_Prescaler = PrescalerCalculation(Copy_pDC_MOTOR_stConfig->MOTOR_PWM_Freq);
			temp = ((f32)1.0/Copy_pDC_MOTOR_stConfig->MOTOR_PWM_Freq) * F_CPU;
			l_topValue = (u16)((f32)temp / PrescalerArr[l_Prescaler-1]);

			if(Copy_pDC_MOTOR_stConfig->MOTOR_PWN_Pin == MOTOR_PWM_OCR1A)
			{
				G_PWM_OCR1A.PWM_topVal = l_topValue;
				G_PWM_OCR1A.PWM_prescaler = l_Prescaler;
				G_PWM_OCR1A.PWM_OCR1A_val = 0;
				PWM_voidInit(&G_PWM_OCR1A);
				PWM_VoidSetDuty(&G_PWM_OCR1A , Copy_pDC_MOTOR_stConfig->MOTOR_dutyCycle);
			}
			else if (Copy_pDC_MOTOR_stConfig->MOTOR_PWN_Pin == MOTOR_PWM_OCR1B)
			{
				G_PWM_OCR1B.PWM_topVal = l_topValue;
				G_PWM_OCR1B.PWM_prescaler = l_Prescaler;
				G_PWM_OCR1B.PWM_OCR1A_val = 0;
				PWM_voidInit(&G_PWM_OCR1B);
				PWM_VoidSetDuty(&G_PWM_OCR1B , Copy_pDC_MOTOR_stConfig->MOTOR_dutyCycle);
			}
		}
	}
	else
	{
		// nothing
	}
}


void DCMOTOR_voidStartClockWise(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig)
{
	if(Copy_pDC_MOTOR_stConfig)
	{
		DIO_VoidSetPinValue(Copy_pDC_MOTOR_stConfig->MOTOR_Port,Copy_pDC_MOTOR_stConfig->MOTOR_IN1_Pin, DIO_PIN_LOGIC_HIGH);
		//DIO_VoidSetPinValue(Copy_pDC_MOTOR_stConfig->MOTOR_Port,Copy_pDC_MOTOR_stConfig->MOTOR_IN2_Pin, DIO_PIN_LOGIC_LOW);
	}
	else
	{

	}
}
void DCMOTOR_voidStop(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig)
{
	if(Copy_pDC_MOTOR_stConfig)
	{
		DIO_VoidSetPinValue(Copy_pDC_MOTOR_stConfig->MOTOR_Port,Copy_pDC_MOTOR_stConfig->MOTOR_IN1_Pin, DIO_PIN_LOGIC_LOW);
		//DIO_VoidSetPinValue(Copy_pDC_MOTOR_stConfig->MOTOR_Port,Copy_pDC_MOTOR_stConfig->MOTOR_IN2_Pin, DIO_PIN_LOGIC_LOW);
	}
	else
	{

	}
}
void DCMOTOR_voidStartAntiClockWise(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig)
{
	if(Copy_pDC_MOTOR_stConfig)
	{
		DIO_VoidSetPinValue(Copy_pDC_MOTOR_stConfig->MOTOR_Port,Copy_pDC_MOTOR_stConfig->MOTOR_IN1_Pin, DIO_PIN_LOGIC_LOW);
		DIO_VoidSetPinValue(Copy_pDC_MOTOR_stConfig->MOTOR_Port,Copy_pDC_MOTOR_stConfig->MOTOR_IN2_Pin, DIO_PIN_LOGIC_HIGH);
	}
	else
	{

	}
}
void DCMOTOR_voidSetSpeed(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig, u8 copy_u8DutyCycle)
{
	if(Copy_pDC_MOTOR_stConfig->MOTOR_PWN_Pin == MOTOR_PWM_OCR1A)
	{
		PWM_VoidSetDuty(&G_PWM_OCR1A , Copy_pDC_MOTOR_stConfig->MOTOR_dutyCycle);
	}
	else if (Copy_pDC_MOTOR_stConfig->MOTOR_PWN_Pin == MOTOR_PWM_OCR1B)
	{
		PWM_VoidSetDuty(&G_PWM_OCR1B , Copy_pDC_MOTOR_stConfig->MOTOR_dutyCycle);
	}
}

void DCMOTOR_voidStartClockWise_withSpeed(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig,u8 copy_u8DutyCycle)
{
	DCMOTOR_voidStartClockWise(Copy_pDC_MOTOR_stConfig);
	DCMOTOR_voidSetSpeed(Copy_pDC_MOTOR_stConfig,copy_u8DutyCycle);

}
void DCMOTOR_voidStartAntiClockWise_withSpeed(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig,u8 copy_u8DutyCycle)
{
	DCMOTOR_voidStartAntiClockWise(Copy_pDC_MOTOR_stConfig);
	DCMOTOR_voidSetSpeed(Copy_pDC_MOTOR_stConfig,copy_u8DutyCycle);
}


static u8 PrescalerCalculation(u16 Copy_u16Freq)
{
	s8 local_counter = 4;
	u16 local_min = 65535;
	u8 local_min_idx = 0;
	// top = period*F_CPU/n - > n prescaler
	u32 temp =	((f32)1.0/Copy_u16Freq) * F_CPU;
	for(;local_counter >= 0 ; local_counter--)
	{
		if( (temp%PrescalerArr[local_counter]) < local_min )
		{
			local_min = temp%PrescalerArr[local_counter];
			local_min_idx = local_counter+1;
		}
	}
	return local_min_idx;
}
