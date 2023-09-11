/*
 * room.c
 *
 *  Created on: Sep 2, 2023
 *      Author: yosse
 */
#define F_CPU 8000000UL

#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../HAL/Led/Led_interface.h"
#include "../HAL/Stepper_Motor/StepperMotor_interface.h"
#include "../HAL/DCMOTOR/DCMOTOR_interface.h"
#include "../HAL/LM35/LM35_interface.h"
#include "room_private.h"
#include "room.h"



StepMotor_st Window_A =  {
		.Motor_BluePort = StepMotor_U8PORTB,
		.Motor_PinkPort = StepMotor_U8PORTB,
		.Motor_OrangePort = StepMotor_U8PORTB,
		.Motor_YellowPort =StepMotor_U8PORTB,

		.Motor_BluePin = StepMotor_U8PIN0,
		.Motor_PinkPin = StepMotor_U8PIN1,
		.Motor_OrangePin = StepMotor_U8PIN2,
		.Motor_YellowPin = StepMotor_U8PIN3,
};

StepMotor_st DOOR_A =  {
		.Motor_BluePort = StepMotor_U8PORTB,
		.Motor_PinkPort = StepMotor_U8PORTB,
		.Motor_OrangePort = StepMotor_U8PORTB,
		.Motor_YellowPort =StepMotor_U8PORTB,

		.Motor_BluePin = StepMotor_U8PIN4,
		.Motor_PinkPin = StepMotor_U8PIN5,
		.Motor_OrangePin = StepMotor_U8PIN6,
		.Motor_YellowPin = StepMotor_U8PIN7,
};

DC_MOTOR_stConfig AIR_A = {
		.MOTOR_Port = DCMOTOR_U8PORTD,
		.MOTOR_IN1_Pin = DCMOTOR_U8PIN2,
		.MOTOR_PWN_Pin = MOTOR_PWM_DISABLE

};
LED_t light_A = {
		.Port = LED_U8PORTA,
		.Pin = LED_U8PIN4,
		.ConType = LED_Con_Source
};

LED_t TV_A = {
		.Port = LED_U8PORTA,
		.Pin = LED_U8PIN5,
		.ConType = LED_Con_Source
};
/*** ROOM B ****/
StepMotor_st Window_B =  {
		.Motor_BluePort = StepMotor_U8PORTC,
		.Motor_PinkPort = StepMotor_U8PORTC,
		.Motor_OrangePort = StepMotor_U8PORTC,
		.Motor_YellowPort =StepMotor_U8PORTC,

		.Motor_BluePin = StepMotor_U8PIN0,
		.Motor_PinkPin = StepMotor_U8PIN1,
		.Motor_OrangePin = StepMotor_U8PIN2,
		.Motor_YellowPin = StepMotor_U8PIN3,
};

StepMotor_st DOOR_B =  {
		.Motor_BluePort = StepMotor_U8PORTC,
		.Motor_PinkPort = StepMotor_U8PORTC,
		.Motor_OrangePort = StepMotor_U8PORTC,
		.Motor_YellowPort =StepMotor_U8PORTC,

		.Motor_BluePin = StepMotor_U8PIN4,
		.Motor_PinkPin = StepMotor_U8PIN5,
		.Motor_OrangePin = StepMotor_U8PIN6,
		.Motor_YellowPin = StepMotor_U8PIN7,
};

DC_MOTOR_stConfig AIR_B = {
		.MOTOR_Port = DCMOTOR_U8PORTD,
		.MOTOR_IN1_Pin = DCMOTOR_U8PIN3,
		.MOTOR_PWN_Pin = MOTOR_PWM_DISABLE

};
LED_t light_B = {
		.Port = LED_U8PORTA,
		.Pin = LED_U8PIN6,
		.ConType = LED_Con_Source
};

LED_t TV_B = {
		.Port = LED_U8PORTA,
		.Pin = LED_U8PIN7,
		.ConType = LED_Con_Source
};

/*****************/
LED_t FireSignal = {
		.Port = LED_U8PORTD,
		.Pin = LED_U8PIN6,
		.ConType = LED_Con_Sink
};


// command that send by master unit
static u8 G_u8Command = 0;

// user temperature
u8 airA_usertemp = 0;
u8 airB_usertemp = 0;

// doors stat so if door is open and user want to open the door motor will not move
u8 doorA_stat = DOOR_STAT_CLOSE;
u8 doorB_stat = DOOR_STAT_CLOSE;

// windows stat so if door is open and user want to open the door motor will not move
u8 WindA_stat = Wind_STAT_CLOSE;
u8 WindB_stat = Wind_STAT_CLOSE;

// lm35 sensors values
u16 RoomA_temp = 0;
u16 RoomB_temp = 0;
u16 Kitchen_temp = 0;

// air conditions state
u8 AirA_stat = Air_Stat_off;
u8 AirB_stat = Air_Stat_off;
void main()
{
	SYSTEM_INIT();
	while(1)
	{
		/**
		 * start adc converstion and update result for room a , room b , kitchen
		 */
		Sensors();

		/**
		 * if air condition is on and room temperature more than or equal  to user temperature turn on air condition
		 * if air condition is on and room temperature less than user temperature turn off air condition
		 *
		 */
		Air_automate();
		MasterCommandHanler();

	}
}


void SYSTEM_INIT(void)
{
	// firesignal init
	LED_u8Init(&FireSignal);
	//uart init
	UART_VoidInit();
	UART_VoidSetRxCBF(UART_RXISR);
	// init adc pins as input
	DIO_VoidSetPinDirection(DIO_PORTA_IDX , DIO_PIN0 , DIO_PIN_DIR_INPUT);
	DIO_VoidSetPinDirection(DIO_PORTA_IDX , DIO_PIN1 , DIO_PIN_DIR_INPUT);
	DIO_VoidSetPinDirection(DIO_PORTA_IDX , DIO_PIN2 , DIO_PIN_DIR_INPUT);
	// sensors init
	LM35_voidInit(NULL);

	/*ROOM A*/
	DCMOTOR_voidInit(&AIR_A);

	StepperMotor_VoidInit(&DOOR_A);
	StepperMotor_VoidInit(&Window_A);
	LED_u8Init(&light_A);
	LED_u8Init(&TV_A);
	/****/
	/*ROOM B*/
	DCMOTOR_voidInit(&AIR_B);

	StepperMotor_VoidInit(&DOOR_B);
	StepperMotor_VoidInit(&Window_B);
	LED_u8Init(&light_B);
	LED_u8Init(&TV_B);
	/****/

}
void UART_RXISR(void)
{
	static u8 counter = 0;
	if(counter == 0)
	{
		UART_Receive_interrupt(&G_u8Command);
		if(G_u8Command == ROOMA_AIR_OPEN)
		{
			counter = 1;
		}
		else if (G_u8Command == ROOMB_AIR_OPEN )
		{
			counter = 2;
		}
	}
	else if (counter == 1)
	{
		UART_Receive_interrupt(&airA_usertemp);

		counter = 0;
	}
	else if (counter == 2)
	{
		UART_Receive_interrupt(&airB_usertemp);
		counter = 0;
	}
}
void Sensors(void)
{

	LM35_voidReadDegree(LM35_ROOMA , &RoomA_temp);
	LM35_voidReadDegree(LM35_ROOMB , &RoomB_temp);
	LM35_voidReadDegree(LM35_KITCHEN , &Kitchen_temp);

	/**
	 * if any room temperature is more than or equal 100
	 * send a fire allarm signal to the master
	 * and open all doors and windows
	 * and disconnect any electrical device
	 */
	if(RoomA_temp >= 100 || RoomB_temp >= 100 || Kitchen_temp >= 100 )
	{
		LED_u8TurnOn(&FireSignal);

		Air_Close(ROOM_A);
		Air_Close(ROOM_B);

		DOOR_OPEN(ROOM_A);
		DOOR_OPEN(ROOM_B);

		Wind_OPEN(ROOM_A);
		Wind_OPEN(ROOM_B);

		LED_u8TurnOff(&light_A);
		LED_u8TurnOff(&light_B);

		LED_u8TurnOff(&TV_A);
		LED_u8TurnOff(&TV_B);
	}
	else {}
}
void DOOR_OPEN(u8 copy_u8Room)
{
	if(copy_u8Room == ROOM_A && doorA_stat == DOOR_STAT_CLOSE)
	{
		StepperMotor_VoidSteps_ClockWise(&DOOR_A,11);
		doorA_stat = DOOR_STAT_OPEN;
	}
	else if(copy_u8Room == ROOM_B && doorB_stat == DOOR_STAT_CLOSE)
	{
		StepperMotor_VoidSteps_ClockWise(&DOOR_B,11);
		doorB_stat = DOOR_STAT_OPEN;
	}
}
void DOOR_Close(u8 copy_u8Room)
{
	if(copy_u8Room == ROOM_A && doorA_stat == DOOR_STAT_OPEN)
	{
		StepperMotor_VoidSteps_AntiClockWise(&DOOR_A,11);
		doorA_stat = DOOR_STAT_CLOSE;
	}
	else if(copy_u8Room == ROOM_B && doorB_stat == DOOR_STAT_OPEN)
	{
		StepperMotor_VoidSteps_AntiClockWise(&DOOR_B,11);
		doorB_stat = DOOR_STAT_CLOSE;
	}
}

void Wind_OPEN(u8 copy_u8Room)
{
	if(copy_u8Room == ROOM_A && WindA_stat == Wind_STAT_CLOSE)
	{
		StepperMotor_VoidSteps_ClockWise(&Window_A,11);
		WindA_stat = Wind_STAT_OPEN;
	}
	else if(copy_u8Room == ROOM_B && WindB_stat == Wind_STAT_CLOSE)
	{
		StepperMotor_VoidSteps_ClockWise(&Window_B,11);
		WindB_stat = Wind_STAT_OPEN;
	}
}
void Wind_Close(u8 copy_u8Room)
{
	if(copy_u8Room == ROOM_A && WindA_stat == Wind_STAT_OPEN)
	{
		StepperMotor_VoidSteps_AntiClockWise(&Window_A,11);
		WindA_stat = DOOR_STAT_CLOSE;
	}
	else if(copy_u8Room == ROOM_B && WindB_stat == Wind_STAT_OPEN)
	{
		StepperMotor_VoidSteps_AntiClockWise(&Window_B,11);
		WindB_stat = DOOR_STAT_CLOSE;
	}
}

void Air_open(u8 copy_u8Room)
{
	if(copy_u8Room == ROOM_A)
	{
		AirA_stat = Air_Stat_ON;
	}
	else if(copy_u8Room == ROOM_B)
	{
		AirB_stat = Air_Stat_ON;
	}

}
void Air_Close(u8 copy_u8Room)
{
	if(copy_u8Room == ROOM_A)
	{

		DCMOTOR_voidStop(&AIR_A);
		AirA_stat = Air_Stat_off;
	}
	else if(copy_u8Room == ROOM_B)
	{
		DCMOTOR_voidStop(&AIR_B);
		AirB_stat = Air_Stat_off;
	}
}

void MasterCommandHanler(void)
{
	switch(G_u8Command)
		{
			/*ROOM A*/
			case ROOMA_LIGHT_ON:
				LED_u8TurnOn(&light_A);
				G_u8Command = 0;
				break;
			case ROOMA_LIGHT_OFF:
				LED_u8TurnOff(&light_A);
				G_u8Command = 0;
				break;

			case ROOMA_Tv_ON:
				LED_u8TurnOn(&TV_A);
				G_u8Command = 0;
				break;
			case ROOMA_Tv_OFF:
				LED_u8TurnOff(&TV_A);
				G_u8Command = 0;
				break;
			case ROOMA_WINDOW_OPEN:
				Wind_OPEN(ROOM_A);
				G_u8Command = 0;
				break;
			case ROOMA_WINDOW_CLOSE:
				Wind_Close(ROOM_A);
				G_u8Command = 0;
				break;
			case ROOMA_DOOR_OPEN:
				DOOR_OPEN(ROOM_A);
				G_u8Command = 0;
				break;
			case ROOMA_DOOR_CLOSE:
				DOOR_Close(ROOM_A);
				G_u8Command = 0;
				break;

			case ROOMA_AIR_OPEN:
				Air_open(ROOM_A);
				G_u8Command = 0;
				break;

			case ROOMA_AIR_CLOSE:
				Air_Close(ROOM_A);
				G_u8Command = 0;
				break;
			/********ROOM B***********/
			case ROOMB_LIGHT_ON:
				LED_u8TurnOn(&light_B);
				G_u8Command = 0;
				break;
			case ROOMB_LIGHT_OFF:
				LED_u8TurnOff(&light_B);
				G_u8Command = 0;
				break;

			case ROOMB_Tv_ON:
				LED_u8TurnOn(&TV_B);
				G_u8Command = 0;
				break;
			case ROOMB_Tv_OFF:
				LED_u8TurnOff(&TV_B);
				G_u8Command = 0;
				break;
			case ROOMB_WINDOW_OPEN:
				Wind_OPEN(ROOM_B);
				G_u8Command = 0;
				break;
			case ROOMB_WINDOW_CLOSE:
				Wind_Close(ROOM_B);
				G_u8Command = 0;
				break;
			case ROOMB_DOOR_OPEN:
				DOOR_OPEN(ROOM_B);
				G_u8Command = 0;
				break;
			case ROOMB_DOOR_CLOSE:
				DOOR_Close(ROOM_B);
				G_u8Command = 0;
				break;

			case ROOMB_AIR_OPEN:
				Air_open(ROOM_B);
				G_u8Command = 0;
				break;

			case ROOMB_AIR_CLOSE:
				Air_Close(ROOM_B);
				G_u8Command = 0;
				break;
		}

}

void Air_automate(void)
{
	// if air condition is on
	if(AirA_stat == Air_Stat_ON)
	{
		// if room temperature  more than or equal to user temperature open the air condition
		if(RoomA_temp >= airA_usertemp)
		{
				DCMOTOR_voidStartClockWise(&AIR_A);
		}
		// if room temperature less than user temperature close the air condition
		else if(RoomA_temp < airA_usertemp)
		{
				DCMOTOR_voidStop(&AIR_A);
		}
	}
	// if air condition is on
	if (AirB_stat == Air_Stat_ON)
	{
		// if room temperature  more than or equal to user temperature open the air condition
		if(RoomB_temp >= airB_usertemp)
		{
				DCMOTOR_voidStartClockWise(&AIR_B);
		}
		// if room temperature less than user temperature close the air condition
		else if(RoomA_temp < airA_usertemp)
		{
				DCMOTOR_voidStop(&AIR_B);
		}
	}
}




