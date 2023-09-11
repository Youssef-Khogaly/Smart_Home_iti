/*
 * room_private.h
 *
 *  Created on: Sep 3, 2023
 *      Author: yosse
 */

#ifndef APP_ROOM_PRIVATE_H_
#define APP_ROOM_PRIVATE_H_

#define ROOM_A			0
#define ROOM_B			2

/* instructions code*/
#define ROOMA_LIGHT_ON						10
#define ROOMA_LIGHT_OFF						9

#define ROOMA_Tv_ON							20
#define ROOMA_Tv_OFF						19


#define ROOMA_DOOR_OPEN						40
#define ROOMA_DOOR_CLOSE					39


#define ROOMA_WINDOW_OPEN					50
#define ROOMA_WINDOW_CLOSE					49

#define ROOMA_AIR_OPEN						60
#define ROOMA_AIR_CLOSE						59


#define ROOMB_LIGHT_ON						10+ROOM_B
#define ROOMB_LIGHT_OFF						9+ROOM_B

#define ROOMB_Tv_ON							20+ROOM_B
#define ROOMB_Tv_OFF						19+ROOM_B


#define ROOMB_DOOR_OPEN						40+ROOM_B
#define ROOMB_DOOR_CLOSE					39+ROOM_B


#define ROOMB_WINDOW_OPEN					50+ROOM_B
#define ROOMB_WINDOW_CLOSE					49+ROOM_B

#define ROOMB_AIR_OPEN						60+ROOM_B
#define ROOMB_AIR_CLOSE						59+ROOM_B



#define DOOR_STAT_CLOSE						0
#define DOOR_STAT_OPEN						1

#define Wind_STAT_CLOSE						0
#define Wind_STAT_OPEN						1

#define LIGHT_STAT_OFF						0
#define LIGHT_STAT_ON						1

#define Air_Stat_off						0
#define Air_Stat_ON							1

#endif /* APP_ROOM_PRIVATE_H_ */
