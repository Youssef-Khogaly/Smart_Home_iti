w/*
 * master.c
 *
 *  Created on: Sep 2, 2023
 *      Author: yosse
 */

#define F_CPU	8000000UL

#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/Bit_Math.h"
#include "master_private.h"
#include "master.h"
#include "../HAL/LCD/LCD_interfacec.h"
#include "../HAL/Keypad/KPD_config.h"
#include "../HAL/Keypad/KPD_interface.h"
#include "../HAL/LDR/LDR_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../HAL/Led/Led_interface.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../HAL/Stepper_Motor/StepperMotor_interface.h"
#include "../MCAL/GPT/GPT_interface.h"
#include "../MCAL/External_Interrupt/EXT_INT_Interface.h"
LCD_stConfig lcd = {
		.LCD_u8DataPort = LCD_U8PORTC,

		.LCD_u8EnablePort = LCD_U8PORTD,
		.LCD_u8RsPort = LCD_U8PORTD,
		.LCD_u8RwPort = LCD_U8PORTD,

		.LCD_u8RsPin = LCD_U8PIN5,
		.LCD_u8RwPin = LCD_U8PIN6,
		.LCD_u8EnablePin = LCD_U8PIN7
};

LED_t entranceLed = {
		.Port = LED_U8PORTA,
		.Pin = LED_U8PIN2,
		.ConType = LED_Con_Source
};

LED_t buzzer = {
		.Port = LED_U8PORTA,
		.Pin = LED_U8PIN3,
		.ConType = LED_Con_Source
};
StepMotor_st MainDoor =  {
		.Motor_BluePort = StepMotor_U8PORTA,
		.Motor_PinkPort = StepMotor_U8PORTA,
		.Motor_OrangePort = StepMotor_U8PORTA,
		.Motor_YellowPort =StepMotor_U8PORTA,

		.Motor_BluePin = StepMotor_U8PIN4,
		.Motor_PinkPin = StepMotor_U8PIN5,
		.Motor_OrangePin = StepMotor_U8PIN6,
		.Motor_YellowPin = StepMotor_U8PIN7,
};
GPT_stConfig adcDelay = {
		.GPT_Mode = GPT_CTCMode,
		.GPT_Preloaded = 0,
		.GPT_timer = GPT_Timer1,
		.GPT_Prescaler = GPT_TIMER_PRESCALER_256,
		.GPT_u8CmpMatchVal = 31250,
		.GPT_Timer_CBF = LDR_ISR_Read,
};
ExtInt_stCfg fireAllarm = {
	.EXT_INT0_SC = EX_INT_SC_FALING_EDGE,
	.ExtInt0_CBF = FireAllarm_ISR
};
u8 MainDoorStat = MAINDOOR_CLOSE;
u8 LDR_stat = 0;
void main()
{

	u8 kpd_userinput = KEYPAD_U8NOTPRESSED;


	SYSTEM_VoidINIT();
	LCD_welcomeMessage();
	Master_private();
	while(1)
	{
			LCD_Menu();
			kpd_userinput = KEYPAD_U8NOTPRESSED;
			while(kpd_userinput == KEYPAD_U8NOTPRESSED)
			{
				kpd_userinput = KPD_U8GetKey();
			}

			switch(kpd_userinput)
			{
				case 1:
					LCD_EntranceMenu_1();
					kpd_userinput = KEYPAD_U8NOTPRESSED;
					break;
				case 2:
					ROOM_Control(ROOM_A);
					kpd_userinput = KEYPAD_U8NOTPRESSED;
					break;
				case 3:
					ROOM_Control(ROOM_B);
					kpd_userinput = KEYPAD_U8NOTPRESSED;
					break;
				default:
					LCD_WrongInputMessage();
					kpd_userinput = KEYPAD_U8NOTPRESSED;
					break;
			}

	}


}


void LDR_ISR_Read(void)
{
	LDR_VoidGetTime(&LDR_stat);
	if(LDR_stat == LDR_NIGHT_TIME)
	{
		LED_u8TurnOn(&entranceLed);
	}
	else if (LDR_stat == LDR_SUN_TIME)
	{
		LED_u8TurnOff(&entranceLed);
	}
}

void SYSTEM_VoidINIT(void)
{
	/**
	 *
	 */

	DIO_VoidSetPinDirection(DIO_PORTD_IDX,DIO_PIN0,DIO_PIN_DIR_OUTPUT);
	DIO_VoidSetPinDirection(DIO_PORTD_IDX,DIO_PIN1,DIO_PIN_DIR_OUTPUT);
	//
	UART_VoidInit();
	GPT_VoidInit(&adcDelay);
	StepperMotor_VoidInit(&MainDoor);
	KPD_VoidInit();
	LDR_VoidInit(NULL);
	LED_u8Init(&entranceLed);
	LED_u8Init(&buzzer);
	LCD_voidInit(&lcd);
	ExtINT_VoidInit(&fireAllarm);
}
void LCD_Menu(void)
{
	LCD_voidClearDisplay(&lcd);
	LCD_voidSendString(&lcd,"Select Room Num");
	_delay_ms(500);
	LCD_voidClearDisplay(&lcd);
	LCD_voidSendString(&lcd,"1-Entrance Room");
	LCD_voidSendString_Postion(&lcd,"2-RoomA 3-RoomB" , LCD_U8ROW2 , LCD_U8COL1);

}
void LCD_WrongInputMessage(void)
{
	LCD_voidClearDisplay(&lcd);
	LCD_voidSendString(&lcd,"Wrong Input");
	_delay_ms(500);
}
void LCD_welcomeMessage(void)
{
	LCD_voidSendString_Postion(&lcd , "Smart Home" , LCD_U8ROW1 , LCD_U8COL4);
	_delay_ms(500);
	LCD_voidClearDisplay(&lcd);
	LCD_voidSendString_Postion(&lcd , "Welcome" , LCD_U8ROW1 , LCD_U8COL4);
	_delay_ms(500);
	LCD_voidClearDisplay(&lcd);
}




void LCD_EntranceMenu_1(void)
{
	LCD_voidClearDisplay(&lcd);
	LCD_voidSendString(&lcd , "1-CloseMainDoor");
	LCD_voidSendString_Postion(&lcd , "2-OpenMainDoor" , LCD_U8ROW2 , LCD_U8COL1);
	u8 kpd_input = KEYPAD_U8NOTPRESSED;
	while(kpd_input == KEYPAD_U8NOTPRESSED)
		kpd_input = KPD_U8GetKey();
	switch(kpd_input)
	{
	// close the door
	case 1:
		MainDoor_voidClose();
		break;
	case 2:
		MainDoor_voidopen();
		break;
	default:
		kpd_input = KEYPAD_U8NOTPRESSED;
		LCD_WrongInputMessage();
		break;
	}
}
void MainDoor_voidopen(void)
{
	if(MainDoorStat ==MAINDOOR_CLOSE)
	{
		MainDoorStat = MAINDOOR_OPEN;
		StepperMotor_VoidSteps_ClockWise(&MainDoor,11);
	}
}
void ROOM_Control(u8 copy_u8Room)
{
	LCD_voidClearDisplay(&lcd);
	LCD_voidSendString(&lcd , "1-LightON  3-TvOn 5-WindowOpen 7-Door");
	LCD_voidSendString_Postion(&lcd , "2-LightOff 4-TvOFF 6-WindowClose 8-Air",LCD_U8ROW2 , LCD_U8COL1);
	u8 kpd_input = KEYPAD_U8NOTPRESSED;
	while(kpd_input == KEYPAD_U8NOTPRESSED || kpd_input == '+' ||  kpd_input == '-')
	{
		kpd_input = KPD_U8GetKey();
		switch(kpd_input)
		{
		// turn on light
		//ROOM_LIGHT_ON+copy_u8Room
		case 1:
			UART_Send(ROOM_LIGHT_ON+copy_u8Room);
		break;
		// turn off light
		case 2:
			UART_Send(ROOM_LIGHT_OFF+copy_u8Room);
		break;
		// turn on tv
		case 3:
			UART_Send(ROOM_Tv_ON+copy_u8Room);
		break;
		//turn off tv
		case 4:
			UART_Send(ROOM_Tv_OFF+copy_u8Room);
		break;
		//window open
		case 5:
			UART_Send(ROOM_WINDOW_OPEN+copy_u8Room);
		break;
		// window close
		case 6:
			UART_Send(ROOM_WINDOW_CLOSE+copy_u8Room);
		break;
		// DOOR
		case 7:
			ROOM_DOOR_CONTROL(copy_u8Room);
		break;
		// AIR
		case 8:
			ROOM_AIR_CONTROL(copy_u8Room);
		break;
		//
		case '-':
			LCD_voidShiftScreenLeft(&lcd);
			LCD_voidShiftScreenLeft(&lcd);
			break;
		case '+':
			LCD_voidShiftScreenRight(&lcd);
			LCD_voidShiftScreenRight(&lcd);
			break;
		case KEYPAD_U8NOTPRESSED:
			break;
		default:
			LCD_WrongInputMessage();
			LCD_voidClearDisplay(&lcd);
			LCD_voidSendString(&lcd , "1-LightON  3-TvOn 5-WindowOpen 7-Door");
			LCD_voidSendString_Postion(&lcd , "2-LightOff 4-TvOFF 6-WindowClose 8-Air",LCD_U8ROW2 , LCD_U8COL1);
			kpd_input = KEYPAD_U8NOTPRESSED;
			break;
		}
	}

}
void ROOM_DOOR_CONTROL(u8 copy_u8Room)
{
	LCD_voidClearDisplay(&lcd);
	LCD_voidSendString(&lcd , "1-Open Door");
	LCD_voidSendString_Postion(&lcd , "2-Close Door",LCD_U8ROW2 , LCD_U8COL1);
	u8 kpd_input = KEYPAD_U8NOTPRESSED;
	while(kpd_input == KEYPAD_U8NOTPRESSED || kpd_input >2 || kpd_input == 0)
	{
		kpd_input = KPD_U8GetKey();
		switch(kpd_input)
		{

			case 1:
				UART_Send(ROOM_DOOR_OPEN+copy_u8Room);
			break;

			case 2:
				UART_Send(ROOM_DOOR_CLOSE+copy_u8Room);
			break;
		}
	}
}
void ROOM_AIR_CONTROL(u8 copy_u8Room)
{
	LCD_voidClearDisplay(&lcd);
	LCD_voidSendString(&lcd , "1-Air On");
	LCD_voidSendString_Postion(&lcd , "2-Air Off",LCD_U8ROW2 , LCD_U8COL1);
	u8 kpd_input = KEYPAD_U8NOTPRESSED;
	u8 temp = 0;
	while(kpd_input == KEYPAD_U8NOTPRESSED || kpd_input >2 || kpd_input == 0)
	{
		kpd_input = KPD_U8GetKey();
		switch(kpd_input)
		{

			case 1:
				LCD_voidClearDisplay(&lcd);
				LCD_voidSendString(&lcd , "Set Temperature");
				LCD_voidSetCursor(&lcd,LCD_U8ROW2 , LCD_U8COL1);
				Air_voidgetTemp(&temp);
				UART_Send(ROOM_AIR_OPEN+copy_u8Room);
				_delay_ms(50);
				UART_Send(temp);
			break;

			case 2:
				UART_Send(ROOM_AIR_CLOSE+copy_u8Room);
			break;
		}
	}
}
void Air_voidgetTemp(u8* copy_pu8temp)
{
	u8 kpd_input = KEYPAD_U8NOTPRESSED;
	u8 temperature = 0;
	u8 counter = 0;
	while(counter <2)
	{
		kpd_input = KPD_U8GetKey();
		if(kpd_input != KEYPAD_U8NOTPRESSED && kpd_input <=9)
		{
			temperature = (temperature*10)+kpd_input;
			counter++;
			LCD_voidSendU32Digit(&lcd,kpd_input);
		}
	}
	*copy_pu8temp = temperature;
	_delay_ms(500);
}
void MainDoor_voidClose(void)
{
	if(MainDoorStat == MAINDOOR_OPEN)
	{
		MainDoorStat = MAINDOOR_CLOSE;
		StepperMotor_VoidSteps_AntiClockWise(&MainDoor,11);
	}

}
void Fire_allarm(void)
{
		LCD_voidSendString_Postion(&lcd , "ALERT!! ALERT!!", LCD_U8ROW1 , LCD_U8COL1);
		LCD_voidSendString_Postion(&lcd , "FIRE ALLARM" , LCD_U8ROW2 , LCD_U8COL1);
		_delay_ms(2000);
}

void FireAllarm_ISR(void)
{
	MainDoor_voidopen();
	LED_u8TurnOn(&buzzer);
	LCD_voidClearDisplay(&lcd);
		while(1)
			Fire_allarm();

}
