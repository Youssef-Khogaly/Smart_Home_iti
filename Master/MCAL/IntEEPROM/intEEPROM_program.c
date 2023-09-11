/*
 * intEEPROM_program.c
 *
 *  Created on: Aug 31, 2023
 *      Author: yosse
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Bit_Math.h"
#include "intEEPROM_private.h"
#include "intEEPROM_interface.h"
void INT_EEPROM_VoidWriteByte(u8 copy_u8Data ,  u16 copy_u16Address)
{
	// busy wait untill prev write operation finish
	while( Get_Bit(INTEEPROM_EECR_REG,INTEEPROM_EECR_EEWE_BIT) == 1 )
		;
	// setup address
	INTEEPROM_EEAR_REG = copy_u16Address;
	// setup data in data reg
	INTEEPROM_EEDR_REG = copy_u8Data;
	// set EEMWE within 4 cycles

	__asm__( 	" sbi 0x1c , 2 "	);


	// set EEME within 4 cycles


	__asm__( 	" sbi 0x1c,1 "	);


}
void INT_EEPROM_VoidReadByte(u8* copy_pu8Data , u16 copy_u16Address)
{
	if(copy_pu8Data)
	{
		// busy wait untill prev write operation finish
		while( Get_Bit(INTEEPROM_EECR_REG,INTEEPROM_EECR_EEWE_BIT) == 1 )
			;
		// setup address
		INTEEPROM_EEAR_REG = copy_u16Address;
		// set EERE within 4 cycles
		__asm__( 	" sbi 0x1c,0 "	);
		*copy_pu8Data = INTEEPROM_EEDR_REG;
	}
	else
	{
		// nothing
	}

}

void INT_EEPROM_VoidWrite_Num_Bytes(u32 copy_u8Data ,  u16 copy_u16StartAddress , u8 copy_u8NumberOFbytes)
{
	if(copy_u8NumberOFbytes <= 4 && copy_u16StartAddress <= (EEPROM_MAXADDRESS-copy_u8NumberOFbytes+1))
	{
		u32 l_temp = copy_u8Data;
		u8 l_counter = 0;
		for(; l_counter < copy_u8NumberOFbytes ; ++l_counter)
			INT_EEPROM_VoidWriteByte(	(l_temp >> (l_counter* 8)) & 0xFF	,  (copy_u16StartAddress+l_counter) );
	}

}
void INT_EEPROM_VoidReadByte_Num_Bytes(u32* copy_pu8Data , u16 copy_u16StartAddress,u8 copy_u8NumberOFbytes)
{
	if(copy_pu8Data &&copy_u8NumberOFbytes <= 4 && copy_u16StartAddress <= (EEPROM_MAXADDRESS-copy_u8NumberOFbytes+1))
	{
		u8 l_temp_read = 0;
		u32 l_result_temp = 0;
		u8 l_counter = 0;
		for(; l_counter < copy_u8NumberOFbytes ; ++l_counter)
		{
			INT_EEPROM_VoidReadByte(&l_temp_read , (copy_u16StartAddress+l_counter) );
			l_result_temp |= (l_temp_read << (l_counter* 8) );
		}
		*copy_pu8Data = l_result_temp;
	}
}





