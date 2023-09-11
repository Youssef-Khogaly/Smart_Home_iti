/*
 * SPT_interface.h
 *
 *  Created on: Aug 21, 2023
 *      Author: yosse
 */

#ifndef MCAL_SPT_SPT_INTERFACE_H_
#define MCAL_SPT_SPT_INTERFACE_H_




typedef enum {
	PWM_timer0_select,PWM_timer1_select,PWM_timer2_select
}PWM_enTimers;


typedef enum {
	PWM_PhaseCorrectMode = 0 ,PWM_FastPwmMode
}PWM_enGenMode;

typedef enum {
	PWM_Disconnected, PWM_Toggle, PWM_NonInverting ,PWM_Inverting
}PWM_enCompareMode;
typedef enum {
	PWM_Disconnect,PWM_Prescaler_1 ,PWM_Prescaler_8 ,PWM_Prescaler_64
	,PWM_Prescaler_256 ,PWM_Prescaler_1024 ,
	PWM_ExtClock_faling,PWM_ExtClock_rising
}PWM_enPrescaler;

typedef enum {
	PWM_OCR1A ,PWM_OCR1B
}PWM_enOCR_SELECt;

typedef struct {
	PWM_enTimers PWM_timer;
	PWM_enGenMode PWM_mode;
	PWM_enCompareMode PWM_compareMode;
	PWM_enPrescaler PWM_prescaler;
	PWM_enOCR_SELECt PWM_OCR;
	u16 PWM_OCR1A_val; // if you use timer 0 or timer2 write a u8 cmp value
	u16 PWM_OCR1B_val; /*if u use timer0 or timer2 ignore PWM_OCR1B_VAL*/
	u16 PWM_topVal; // ignore if u use timer 0 or timer 2
}PWM_stConfig;

void PWM_voidInit(PWM_stConfig* copy_pst_config);
void PWM_VoidSetDuty(PWM_stConfig* copy_pst_config , u8 copy_u8DutyCycle);

#endif /* MCAL_SPT_SPT_INTERFACE_H_ */
