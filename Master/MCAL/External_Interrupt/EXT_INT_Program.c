/*
 * EXT_INT_Program.c
 *
 *  Created on: Aug 16, 2023
 *      Author: yossef
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Bit_Math.h"
#include "../Global_interrupt/GloableINT_Private.h"
#include "EXT_INT_Private.h"
#include "EXT_INT_Config.h"
#include "EXT_INT_Interface.h"
#include "../DIO/DIO_Interface.h"

static ISR_FuncPtr_t ptrFunc_Int0CallBack = NULL;
static ISR_FuncPtr_t ptrFunc_Int1CallBack = NULL;
static ISR_FuncPtr_t ptrFunc_Int2CallBack = NULL;

void __vector_1(void) __attribute__ ((signal, used));
void __vector_2(void) __attribute__ ((signal , used));
void __vector_3(void) __attribute__ ((signal , used));

void ExtINT_VoidInit(ExtInt_stCfg* copy_pExtInt_stCfg)
{
	if(NULL != copy_pExtInt_stCfg && ( copy_pExtInt_stCfg->EXT_INT0_SC != EX_INT_DISABLE || copy_pExtInt_stCfg->EXT_INT1_SC != EX_INT_DISABLE || copy_pExtInt_stCfg->EXT_INT2_SC != EX_INT_DISABLE  ) )
	{
		/*Enable Global Interrupt*/
		GIE_ENABLE();

		if(copy_pExtInt_stCfg->EXT_INT0_SC != EX_INT_DISABLE)
		{
			/*
			 * IMPORTANT NOTE FOR ME!! when i back to study:
			 * 		if u enable int0~int2 interrupt microcontroller auto configure the pin as input
			 * 		but he dont change the logic on the pin:
			 * 		so if pin  output logic was high -> its automatic set the pin as input with logic high aka 'internal pull up resistance'
			 *		and if pin output logic low -> its automatic set the pin as input with logic low 'no internal pull up resistance'
			 *		same if pin was input
			 *		ext_int_config.h handle this cases to check if the user want internal pullup resistance or not
			 *
			 * */
#if	EXT_INT0_INTERNAL_PULLUP == EXT_INT_INT_PULLUP_ENABLE
			DIO_VoidSetPinValue(DIO_PORTD_IDX , DIO_PIN2 , DIO_PIN_LOGIC_HIGH);
#elif EXT_INT0_INTERNAL_PULLUP == EXT_INT_INT_PULLUP_DISABLE
			DIO_VoidSetPinValue(DIO_PORTD_IDX , DIO_PIN2,DIO_PIN_LOGIC_LOW);
#else
#warning "Check EXT_INT_Config.h please"
#endif
			/*configure sense control*/
			EXT_INT0_ISC_SET(copy_pExtInt_stCfg->EXT_INT0_SC);
			/*set ISR Function*/
			ptrFunc_Int0CallBack = copy_pExtInt_stCfg->ExtInt0_CBF;
			/*enable INT0 interrupt*/
			EXT_INT0_ENABLE();

		}
		else{/*Nothing*/}
		if(copy_pExtInt_stCfg->EXT_INT1_SC != EX_INT_DISABLE)
		{
#if	EXT_INT1_INTERNAL_PULLUP == EXT_INT_INT_PULLUP_ENABLE
			DIO_VoidSetPinValue(DIO_PORTD_IDX , DIO_PIN3 , DIO_PIN_LOGIC_HIGH);
#elif EXT_INT1_INTERNAL_PULLUP == EXT_INT_INT_PULLUP_DISABLE
			DIO_VoidSetPinValue(DIO_PORTD_IDX , DIO_PIN3,DIO_PIN_LOGIC_LOW);
#else
#warning "Check EXT_INT_Config.h please"
#endif
			/*configure sense control*/
			EXT_INT1_ISC_SET(copy_pExtInt_stCfg->EXT_INT1_SC);
			/*set ISR Function*/
			ptrFunc_Int1CallBack = copy_pExtInt_stCfg->ExtInt1_CBF;
			/*enable INT1 interrupt*/
			EXT_INT1_ENABLE();
		}
		else{/*Nothing*/}
		if(copy_pExtInt_stCfg->EXT_INT2_SC != EX_INT_DISABLE)
		{
#if	EXT_INT2_INTERNAL_PULLUP == EXT_INT_INT_PULLUP_ENABLE
			DIO_VoidSetPinValue(DIO_PORTB_IDX , DIO_PIN2 , DIO_PIN_LOGIC_HIGH);
#elif EXT_INT2_INTERNAL_PULLUP == EXT_INT_INT_PULLUP_DISABLE
			DIO_VoidSetPinValue(DIO_PORTB_IDX , DIO_PIN2,DIO_PIN_LOGIC_LOW);
#else
#warning "Check EXT_INT_Config.h please"
#endif
			/*configure sense control*/
			EXT_INT2_ISC_SET(copy_pExtInt_stCfg->EXT_INT2_SC);
			/*set ISR Function*/
			ptrFunc_Int2CallBack = copy_pExtInt_stCfg->ExtInt2_CBF;
			/*enable INT2 interrupt*/
			EXT_INT2_ENABLE();
		}
		else{/*Nothing*/}
	}
	else
	{

	}
	return;
}

void ExtINT_VoidDeInit(ExtInt_stCfg* copy_pExtInt_stCfg)
{
	EXT_INT0_DISABLE();
	EXT_INT1_DISABLE();
	EXT_INT2_DISABLE();
}
void ExtINT_changeSense(u8 copy_u8Ext_INT , u8 copy_u8NewSens)
{
	switch(copy_u8Ext_INT)
	{
	case EXT_INT0:
		EXT_INT0_ISC_SET(copy_u8NewSens);
		break;
	case EXT_INT1:
		EXT_INT1_ISC_SET(copy_u8NewSens);
		break;
	case EXT_INT2:
		EXT_INT2_ISC_SET(copy_u8NewSens);
		break;
	}

}



void __vector_1(void)
{
	if(NULL != ptrFunc_Int0CallBack)
		ptrFunc_Int0CallBack();
}

void __vector_2(void)
{
	if(NULL != ptrFunc_Int1CallBack)
		ptrFunc_Int1CallBack();
}

void __vector_3(void)
{
	if(NULL != ptrFunc_Int2CallBack)
		ptrFunc_Int2CallBack();
}
