/*
 * StepperMotor_interface.h
 *
 *  Created on: Aug 16, 2023
 *      Author: yosse
 */

#ifndef HAL_STEPPER_MOTOR_STEPPERMOTOR_INTERFACE_H_
#define HAL_STEPPER_MOTOR_STEPPERMOTOR_INTERFACE_H_


/* StepMotor PORT */
#define StepMotor_U8PORTA		0
#define StepMotor_U8PORTB		1
#define StepMotor_U8PORTC		2
#define StepMotor_U8PORTD		3
/* LCD PINS */
#define StepMotor_U8PIN0		0
#define StepMotor_U8PIN1		1
#define StepMotor_U8PIN2		2
#define StepMotor_U8PIN3		3
#define StepMotor_U8PIN4		4
#define StepMotor_U8PIN5		5
#define StepMotor_U8PIN6		6
#define StepMotor_U8PIN7		7







/* user data types*/

typedef struct{

	f32 Motor_stepAngle;
	u8 Motor_BluePin:3;
	u8 Motor_PinkPin:3;
	u8 Motor_BluePort:2;

	u8 Motor_OrangePin:3;
	u8 Motor_YellowPin:3;
	u8 Motor_PinkPort:2;

	u8 Motor_OrangePort:2;
	u8 Motor_YellowPort:2;
}StepMotor_st;
/*******************/

/**interfaces**/

void StepperMotor_VoidInit(const StepMotor_st* Copy_pStepMotor_st_Config);

void StepperMotor_VoidStepClockWise(const StepMotor_st* Copy_pStepMotor_st_Config);

void StepperMotor_VoidSteps_ClockWise(const StepMotor_st* Copy_pStepMotor_st_Config , u32 copy_u8Numsteps);

void StepperMotor_VoidStepAntiClockWise(const StepMotor_st* Copy_pStepMotor_st_Config);

void StepperMotor_VoidSteps_AntiClockWise(const StepMotor_st* Copy_pStepMotor_st_Config , u32 copy_u8Numsteps);

#endif /* HAL_STEPPER_MOTOR_STEPPERMOTOR_INTERFACE_H_ */
