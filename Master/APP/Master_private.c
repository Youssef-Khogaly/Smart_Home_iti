/*
 * Master_private.c
 *
 *  Created on: Sep 2, 2023
 *      Author: yosse
 */


#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "master_private.h"
#include "../HAL/LCD/LCD_interfacec.h"
#include "../HAL/Keypad/KPD_config.h"
#include "../HAL/Keypad/KPD_interface.h"
#include "../HAL/Led/Led_interface.h"
#include "../MCAL/IntEEPROM/intEEPROM_interface.h"

extern LCD_stConfig lcd;
extern LED_t buzzer;



void Master_private(void)
{
	u8 passwordFlag = 0;
	u8 PassWordStat = Password_notSet;
	u8 counter = 0 , remaining_counter = 3 ;
	u8 kpd_input = KEYPAD_U8NOTPRESSED;
	u32 Password = 0 ,userInput = 0;
	INT_EEPROM_VoidReadByte(&PassWordStat,PassWordstat_address);
		if(PassWordStat  == Password_notSet)
		{
				LCD_NewPasswordMessage();
				for(counter = 0 ; counter <4 ;)
				{
					kpd_input = KPD_U8GetKey();
					if(kpd_input != KEYPAD_U8NOTPRESSED && kpd_input <= 9)
					{
						Password = (Password*10)+kpd_input;
						LCD_voidSendU32Digit(&lcd ,kpd_input);
						_delay_ms(100);
						LCD_voidSendChar_Postion(&lcd,'*' , LCD_U8ROW2,LCD_U8COL9+counter);
						counter++;
					}
				}
				INT_EEPROM_VoidWrite_Num_Bytes(Password,PassWordAddress,PASSWORD_SizeBytes);
				INT_EEPROM_VoidWriteByte(Password_Set,PassWordstat_address);
				passwordFlag = PasswordMatch;
		}
		else if(PassWordStat  == Password_Set)
		{
			INT_EEPROM_VoidReadByte_Num_Bytes(&Password,PassWordAddress,PASSWORD_SizeBytes);
			while(remaining_counter>=1)
			{
				LCD_PasswordMessage();
				for(counter = 0 ; counter <4 ;)
				{
					kpd_input = KPD_U8GetKey();
					if(kpd_input != KEYPAD_U8NOTPRESSED && kpd_input <= 9)
					{
						userInput = (userInput*10)+kpd_input;
						LCD_voidSendU32Digit(&lcd ,kpd_input);
						_delay_ms(100);
						LCD_voidSendChar_Postion(&lcd,'*' , LCD_U8ROW2,LCD_U8COL1+counter);
						counter++;
					}
				}

				if(Password == userInput)
				{
					passwordFlag = PasswordMatch;
					break;
				}
				else if (Password != userInput)
				{
					passwordFlag = 0;
					userInput = 0;
					LCD_passWordRemaining(--remaining_counter);
				}
			}
		}
		else {}

		if(passwordFlag != PasswordMatch)
		{

			LED_u8TurnOn(&buzzer);

			while(1)
			{
				LCD_voidClearDisplay(&lcd);
				LCD_voidSendString(&lcd,"Alert Alert !!");
				LCD_voidSendString_Postion(&lcd,"SYSTEM DISABLE",LCD_U8ROW2,LCD_U8COL1);
				_delay_ms(500);
			}
		}
		else
		{
			//nothing
		}
		return;
}













void LCD_NewPasswordMessage(void)
{
	LCD_voidClearDisplay(&lcd);
	LCD_voidSendString(&lcd,"Set New PW");
	LCD_voidSendString_Postion(&lcd,"4Digits:",LCD_U8ROW2,LCD_U8COL1);

}


void LCD_PasswordMessage(void)
{
	LCD_voidClearDisplay(&lcd);
	LCD_voidSendString(&lcd,"Enter Password:");
	LCD_voidSetCursor(&lcd,LCD_U8ROW2,LCD_U8COL1);
}



void LCD_passWordRemaining(u8 copy_u8remainingcount)
{
	LCD_voidClearDisplay(&lcd);
	LCD_voidSendString(&lcd , "Wrong Password");
	LCD_voidSendString_Postion(&lcd , "Reaming Trails:" , LCD_U8ROW2 , LCD_U8COL1);
	LCD_voidSendU32Digit(&lcd,copy_u8remainingcount);
	_delay_ms(1000);
	LCD_voidClearDisplay(&lcd);
}
