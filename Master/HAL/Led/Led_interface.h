/*
 * Led_interface.h
 *
 *  Created on: Aug 11, 2023
 *      Author: yosse
 */

#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_

/*************Macros*************/

// connection type
/*logic 1 to turn on logic 0 to turn off*/
#define LED_Con_Source		1
/*logic 0 to turn on logic 1 to turn off*/
#define LED_Con_Sink		0


/* LED PORTS */
#define LED_U8PORTA		0
#define LED_U8PORTB		1
#define LED_U8PORTC		2
#define LED_U8PORTD		3
/* LED PINS */
#define LED_U8PIN0		0
#define LED_U8PIN1		1
#define LED_U8PIN2		2
#define LED_U8PIN3		3
#define LED_U8PIN4		4
#define LED_U8PIN5		5
#define LED_U8PIN6		6
#define LED_U8PIN7		7

/*******************************/



/***********User Data Types*******/

typedef struct{
	u8 Port : 4; /* ex DIO_PORTA_IDX*/
	u8 Pin : 3; /* ex DIO_PIN2*/
	u8 ConType : 1; /* LED_Con_Source or LED_Con_Sink*/
}LED_t;

/*********************************/

/*****Prototypes***********/

/**
 * Name: LED_u8Init
 * Dec: Inistalize led pin direction as output  and  turn off led as default stat
 *  @Important Note You must use it before using any another function that turn on or turn off the led etc
 * Parameter:
 * 			@LED_t* Copy_pled_tConfig : pointer to @LED_t
 * Return:
 * 			1 - > done successfuly
 * 			0 -> error
 */

u8 LED_u8Init(const LED_t* Copy_pled_tConfig);

/**
 * Name: LED_u8TurnOn
 * Dec: Turn Led On
 * Parameter:
 * 			@LED_t* Copy_pled_tConfig : pointer to @LED_t
 * Return:
 * 			1 - > done successfuly
 * 			0 -> error
 */

u8 LED_u8TurnOn(const LED_t* Copy_pled_tConfig);

/**
 * Name: LED_u8TurnOff
 * Dec: Turn Led OFF
 * Parameter:
 * 			@LED_t* Copy_pled_tConfig : pointer to @LED_t
 * Return:
 * 			1 - > done successfuly
 * 			0 -> error
 */

u8 LED_u8TurnOff(const LED_t* Copy_pled_tConfig);

/**
 * Name: LED_u8Toggle
 * Dec: Toggle LED
 * Parameter:
 * 			@LED_t* Copy_pled_tConfig : pointer to @LED_t
 * Return:
 * 			1 - > done successfuly
 * 			0 -> error
 */

u8 LED_u8Toggle(const LED_t* Copy_pled_tConfig);

/**
 *
 * @param Copy_pled_tConfig
 * @return LED_LOGIC
 */
u8 LED_u8Stat(const LED_t* Copy_pled_tConfig);

/************************/
#endif /* HAL_LED_LED_INTERFACE_H_ */
