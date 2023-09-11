/*
 * room.h
 *
 *  Created on: Sep 2, 2023
 *      Author: yosse
 */

#ifndef APP_ROOM_H_
#define APP_ROOM_H_

#define LM35_ROOMA			LM35_CHANNEL_0
#define LM35_ROOMB			LM35_CHANNEL_1
#define LM35_KITCHEN		LM35_CHANNEL_2



void SYSTEM_INIT(void);
void UART_RXISR(void);
void DOOR_OPEN(u8 copy_u8Room);
void DOOR_Close(u8 copy_u8Room);
void Sensors(void);
void Wind_OPEN(u8 copy_u8Room);
void Wind_Close(u8 copy_u8Room);

void Air_open(u8 copy_u8Room);
void Air_Close(u8 copy_u8Room);
void Air_automate(void);
void MasterCommandHanler(void);
#endif /* APP_ROOM_H_ */
