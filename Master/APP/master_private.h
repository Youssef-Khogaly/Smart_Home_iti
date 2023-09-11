/*
 * master_private.h
 *
 *  Created on: Sep 2, 2023
 *      Author: yosse
 */

#ifndef APP_MASTER_PRIVATE_H_
#define APP_MASTER_PRIVATE_H_

#define ROOM_A			0
#define ROOM_B			2

/* instructions code*/
#define ROOM_LIGHT_ON					10
#define ROOM_LIGHT_OFF					9

#define ROOM_Tv_ON						20
#define ROOM_Tv_OFF						19


#define ROOM_DOOR_OPEN					40
#define ROOM_DOOR_CLOSE					39


#define ROOM_WINDOW_OPEN				50
#define ROOM_WINDOW_CLOSE				49

#define ROOM_AIR_OPEN					60
#define ROOM_AIR_CLOSE					59


/*EEPROM*/
#define Password_notSet					0xFF
#define Password_Set					0x01

#define PassWordstat_address			0x00
#define PassWordAddress					0x01

#define PASSWORD_SizeBytes				  2

#define PasswordMatch					0x3F

#define MAINDOOR_CLOSE			0
#define MAINDOOR_OPEN			1

void Master_private(void);
void LCD_passWordRemaining(u8 copy_u8remainingcount);
void LCD_PasswordMessage(void);
void LCD_NewPasswordMessage(void);

#endif /* APP_MASTER_PRIVATE_H_ */
