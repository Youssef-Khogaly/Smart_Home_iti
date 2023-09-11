/*
 * intEEPROM_private.h
 *
 *  Created on: Aug 31, 2023
 *      Author: yosse
 */

#ifndef MCAL_INTEEPROM_INTEEPROM_PRIVATE_H_
#define MCAL_INTEEPROM_INTEEPROM_PRIVATE_H_


#define EEPROM_MAXADDRESS	0x3FF

#define INTEEPROM_EEAR_REG	(*(volatile u16*)0x3E)
#define INTEEPROM_EEDR_REG	(*(volatile u8*)0x3D)

#define INTEEPROM_EECR_REG	(*(volatile u8*)0x3C)

#define INTEEPROM_EECR_EERE_BIT	 	    0
#define INTEEPROM_EECR_EEWE_BIT		    1
#define INTEEPROM_EECR_EEMWE_BIT		2
#define INTEEPROM_EECR_EERIE_BIT		3

#endif /* MCAL_INTEEPROM_INTEEPROM_PRIVATE_H_ */
