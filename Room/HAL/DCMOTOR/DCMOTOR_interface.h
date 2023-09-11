/*
 * DCMOTOR_interface.h
 *
 *  Created on: Sep 1, 2023
 *      Author: yosse
 */

#ifndef HAL_DCMOTOR_DCMOTOR_INTERFACE_H_
#define HAL_DCMOTOR_DCMOTOR_INTERFACE_H_



#ifndef F_CPU
#define F_CPU	8000000UL
#endif


typedef enum {
	MOTOR_PWM_OCR1A ,MOTOR_PWM_OCR1B , MOTOR_PWM_DISABLE
}DC_MOTOR_enPWM_PIN;



/* DCMOTOR PORTS */
#define DCMOTOR_U8PORTA		0
#define DCMOTOR_U8PORTB		1
#define DCMOTOR_U8PORTC		2
#define DCMOTOR_U8PORTD		3
/* DCMOTOR PINS */
#define DCMOTOR_U8PIN0		0
#define DCMOTOR_U8PIN1		1
#define DCMOTOR_U8PIN2		2
#define DCMOTOR_U8PIN3		3
#define DCMOTOR_U8PIN4		4
#define DCMOTOR_U8PIN5		5
#define DCMOTOR_U8PIN6		6
#define DCMOTOR_U8PIN7		7

typedef struct {
	u8 MOTOR_Port : 2;
	u8 MOTOR_IN1_Pin : 3;
	u8 MOTOR_IN2_Pin : 3;
	DC_MOTOR_enPWM_PIN MOTOR_PWN_Pin;
	/*ignore next variables if u chose to not  controll with pwm */
	u16 MOTOR_PWM_Freq;
	u8 MOTOR_dutyCycle : 7;
}DC_MOTOR_stConfig;

void DCMOTOR_voidInit(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig);
void DCMOTOR_voidStop(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig);

void DCMOTOR_voidStartClockWise(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig);
void DCMOTOR_voidStartAntiClockWise(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig);
void DCMOTOR_voidSetSpeed(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig, u8 copy_u8DutyCycle);

void DCMOTOR_voidStartClockWise_withSpeed(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig,u8 copy_u8DutyCycle);
void DCMOTOR_voidStartAntiClockWise_withSpeed(DC_MOTOR_stConfig* Copy_pDC_MOTOR_stConfig,u8 copy_u8DutyCycle);
#endif /* HAL_DCMOTOR_DCMOTOR_INTERFACE_H_ */
