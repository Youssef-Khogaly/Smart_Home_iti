/*
 * Led_Program.c
 *
 *  Created on: Aug 11, 2023
 *      Author: yossef
 */
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include"Led_interface.h"
#include "Led_private.h"
#include "led_config.h"

u8 LED_u8Init(const LED_t* Copy_pled_tConfig)
{
	u8 ret = 0;
	if(Copy_pled_tConfig  && Copy_pled_tConfig->Port <= DIO_PORTD_IDX && Copy_pled_tConfig->Pin <= DIO_PIN7 )
	{
		switch(Copy_pled_tConfig->ConType)
		{
		case LED_Con_Source:
			DIO_voidPinInit(Copy_pled_tConfig->Port , Copy_pled_tConfig->Pin , DIO_PIN_DIR_OUTPUT , DIO_PIN_LOGIC_LOW);
			ret = 1;
			break;
		case LED_Con_Sink:
			DIO_voidPinInit(Copy_pled_tConfig->Port , Copy_pled_tConfig->Pin , DIO_PIN_DIR_OUTPUT , DIO_PIN_LOGIC_HIGH);
			ret = 1;
			break;
		default: ret = 0; break;
		}
	}
	else
	{
		ret = 0;
	}
	return ret;
}
u8 LED_u8TurnOff(const LED_t* Copy_pled_tConfig)
{
	u8 ret = 0;
	if(Copy_pled_tConfig  && Copy_pled_tConfig->Port <= DIO_PORTD_IDX && Copy_pled_tConfig->Pin <= DIO_PIN7 )
	{
		switch(Copy_pled_tConfig->ConType)
		{
			case LED_Con_Source:
				DIO_VoidSetPinValue(Copy_pled_tConfig->Port,Copy_pled_tConfig->Pin, DIO_PIN_LOGIC_LOW);
				ret = 1;
				break;
			case LED_Con_Sink:
				DIO_VoidSetPinValue(Copy_pled_tConfig->Port,Copy_pled_tConfig->Pin, DIO_PIN_LOGIC_HIGH);
				ret = 1;
				break;
			default: ret = 0; break;
		}
	}
	else
	{
		ret = 0;
	}
	return ret;
}

u8 LED_u8TurnOn(const LED_t* Copy_pled_tConfig)
{
	u8 ret = 0;
	if(Copy_pled_tConfig  && Copy_pled_tConfig->Port <= DIO_PORTD_IDX && Copy_pled_tConfig->Pin <= DIO_PIN7 )
	{
		switch(Copy_pled_tConfig->ConType)
		{
			case LED_Con_Source:
				DIO_VoidSetPinValue(Copy_pled_tConfig->Port,Copy_pled_tConfig->Pin, DIO_PIN_LOGIC_HIGH);
				ret = 1;
				break;
			case LED_Con_Sink:
				DIO_VoidSetPinValue(Copy_pled_tConfig->Port,Copy_pled_tConfig->Pin, DIO_PIN_LOGIC_LOW);
				ret = 1;
				break;
			default: ret = 0; break;
		}
	}
	else
	{
		ret = 0;
	}
	return ret;
}

u8 LED_u8Toggle(const LED_t* Copy_pled_tConfig)
{
	u8 ret = 0;
	if(Copy_pled_tConfig  && Copy_pled_tConfig->Port <= DIO_PORTD_IDX && Copy_pled_tConfig->Pin <= DIO_PIN7 )
	{
		DIO_VoidTogglePinValue(Copy_pled_tConfig->Port , Copy_pled_tConfig->Pin);
		ret = 1;
	}
	else
	{
		ret = 0;
	}
	return ret;
}

u8 LED_u8Stat(const LED_t* Copy_pled_tConfig)
{
	u8 ret = 0;
	if(Copy_pled_tConfig  && Copy_pled_tConfig->Port <= DIO_PORTD_IDX && Copy_pled_tConfig->Pin <= DIO_PIN7 )
	{
		DIO_VoidGetPinValue(Copy_pled_tConfig->Port , Copy_pled_tConfig->Pin , &ret);
	}
	else
	{
	}
	return ret;
}
