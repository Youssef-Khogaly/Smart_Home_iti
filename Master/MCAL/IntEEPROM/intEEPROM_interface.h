/*
 * intEEPROM_interface.h
 *
 *  Created on: Aug 31, 2023
 *      Author: yosse
 */

#ifndef MCAL_INTEEPROM_INTEEPROM_INTERFACE_H_
#define MCAL_INTEEPROM_INTEEPROM_INTERFACE_H_

void INT_EEPROM_VoidWriteByte(u8 copy_u8Data ,  u16 copy_u16Address);
void INT_EEPROM_VoidReadByte(u8* copy_pu8Data , u16 copy_u16Address);


void INT_EEPROM_VoidWrite_Num_Bytes(u32 copy_u8Data ,  u16 copy_u16StartAddress , u8 copy_u8NumberOFbytes);
void INT_EEPROM_VoidReadByte_Num_Bytes(u32* copy_pu8Data , u16 copy_u16StartAddress,u8 copy_u8NumberOFbytes);
#endif /* MCAL_INTEEPROM_INTEEPROM_INTERFACE_H_ */
