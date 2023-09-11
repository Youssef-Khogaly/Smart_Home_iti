/*
 * master.h
 *
 *  Created on: Sep 2, 2023
 *      Author: yosse
 */

#ifndef APP_MASTER_H_
#define APP_MASTER_H_





void SYSTEM_VoidINIT(void);

void LCD_welcomeMessage(void);
void LCD_NewPasswordMessage(void);
void LCD_PasswordMessage(void);
void LCD_passWordRemaining(u8 copy_u8remainingcount);
void LCD_Menu(void);
void LCD_EntranceMenu_1(void);
void ROOM_Control(u8 copy_u8Room);
void MainDoor_voidopen(void);
void MainDoor_voidClose(void);
void LCD_WrongInputMessage(void);
void ROOM_DOOR_CONTROL(u8 copy_u8Room);
void ROOM_AIR_CONTROL(u8 copy_u8Room);
void Air_voidgetTemp(u8* copy_pu8temp);
void Fire_allarm(void);
void LDR_ISR_Read(void);
void FireAllarm_ISR(void);
#endif /* APP_MASTER_H_ */
