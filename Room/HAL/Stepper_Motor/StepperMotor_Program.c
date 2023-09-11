/*
 * StepperMotor_Program.c
 *
 *  Created on: Aug 16, 2023
 *      Author: yosse
 */

#include <util/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "StepperMotor_Private.h"
#include "StepperMotor_config.h"
#include "StepperMotor_interface.h"


void StepperMotor_VoidInit(const StepMotor_st* Copy_pStepMotor_st_Config)
{
	if(Copy_pStepMotor_st_Config)
	{
		// init blue pin
		DIO_VoidSetPinDirection(Copy_pStepMotor_st_Config->Motor_BluePort, Copy_pStepMotor_st_Config->Motor_BluePin , DIO_PIN_DIR_OUTPUT);
		//pink
		DIO_VoidSetPinDirection(Copy_pStepMotor_st_Config->Motor_PinkPort, Copy_pStepMotor_st_Config->Motor_PinkPin , DIO_PIN_DIR_OUTPUT);
		//orange
		DIO_VoidSetPinDirection(Copy_pStepMotor_st_Config->Motor_OrangePort, Copy_pStepMotor_st_Config->Motor_OrangePin , DIO_PIN_DIR_OUTPUT);
		//yellow
		DIO_VoidSetPinDirection(Copy_pStepMotor_st_Config->Motor_YellowPort, Copy_pStepMotor_st_Config->Motor_YellowPin , DIO_PIN_DIR_OUTPUT);
	}
	else
	{

	}
	return;
}

void StepperMotor_VoidStepClockWise(const StepMotor_st* Copy_pStepMotor_st_Config)
{
	if(Copy_pStepMotor_st_Config)
	{
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_BluePort, Copy_pStepMotor_st_Config->Motor_BluePin , DIO_PIN_LOGIC_HIGH);
		_delay_ms(10);

		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_BluePort, Copy_pStepMotor_st_Config->Motor_BluePin , DIO_PIN_LOGIC_LOW);
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_PinkPort, Copy_pStepMotor_st_Config->Motor_PinkPin , DIO_PIN_LOGIC_HIGH);
		_delay_ms(10);

		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_PinkPort, Copy_pStepMotor_st_Config->Motor_PinkPin , DIO_PIN_LOGIC_LOW);
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_OrangePort, Copy_pStepMotor_st_Config->Motor_OrangePin , DIO_PIN_LOGIC_HIGH);
		_delay_ms(10);
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_OrangePort, Copy_pStepMotor_st_Config->Motor_OrangePin , DIO_PIN_LOGIC_LOW);
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_YellowPort, Copy_pStepMotor_st_Config->Motor_YellowPin , DIO_PIN_LOGIC_HIGH);
		_delay_ms(10);
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_YellowPort, Copy_pStepMotor_st_Config->Motor_YellowPin , DIO_PIN_LOGIC_LOW);
		_delay_ms(10);
	}
	else
	{

	}
	return;
}

void StepperMotor_VoidStepAntiClockWise(const StepMotor_st* Copy_pStepMotor_st_Config)
{
	if(Copy_pStepMotor_st_Config)
	{
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_OrangePort, Copy_pStepMotor_st_Config->Motor_OrangePin , DIO_PIN_LOGIC_HIGH);
		_delay_ms(5);

		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_OrangePort, Copy_pStepMotor_st_Config->Motor_OrangePin , DIO_PIN_LOGIC_LOW);
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_YellowPort, Copy_pStepMotor_st_Config->Motor_YellowPin , DIO_PIN_LOGIC_HIGH);
		_delay_ms(5);

		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_YellowPort , Copy_pStepMotor_st_Config->Motor_YellowPin , DIO_PIN_LOGIC_LOW);
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_PinkPort, Copy_pStepMotor_st_Config->Motor_PinkPin , DIO_PIN_LOGIC_HIGH);
		_delay_ms(5);
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_PinkPort, Copy_pStepMotor_st_Config->Motor_PinkPin , DIO_PIN_LOGIC_LOW);
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_BluePort, Copy_pStepMotor_st_Config->Motor_BluePin , DIO_PIN_LOGIC_HIGH);
		_delay_ms(5);
		DIO_VoidSetPinValue(Copy_pStepMotor_st_Config->Motor_BluePort, Copy_pStepMotor_st_Config->Motor_BluePin , DIO_PIN_LOGIC_LOW);
		_delay_ms(5);
	}
	else
	{

	}
	return;
}


void StepperMotor_VoidSteps_ClockWise(const StepMotor_st* Copy_pStepMotor_st_Config , u32 copy_u8Numsteps)
{
	u32 i = 0;
	for(; i <copy_u8Numsteps ; ++i)
		StepperMotor_VoidStepClockWise(Copy_pStepMotor_st_Config);
	return;
}
void StepperMotor_VoidSteps_AntiClockWise(const StepMotor_st* Copy_pStepMotor_st_Config , u32 copy_u8Numsteps)
{
	u32 i = 0;
	for(; i <copy_u8Numsteps ; ++i)
		StepperMotor_VoidStepAntiClockWise(Copy_pStepMotor_st_Config);
}

