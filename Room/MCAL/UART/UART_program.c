/*
 * UART_program.c
 *
 *  Created on: Aug 23, 2023
 *      Author: yossef
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Bit_Math.h"
#include "UART_config.h"
#include "UART_private.h"
#include "UART_interface.h"
#include "../Global_interrupt/GloableINT_Private.h"
#define UART_UCSRC_VAL_CFG	(( UART_STOPBIT_LEN_CFG << UART_UCSRC_USBS_BIT ) | (UART_STOPBIT_LEN_CFG << UART_UCSRC_USBS_BIT) |  ( (UART_DATA_LEN_CFG & 0x04) << UART_UCSRC_UCSZ0_BIT ) | (UART_PARITYMODE_CFG << UART_UCSRC_UPM0_BIT))


void __vector_13(void) __attribute__ ((signal,used));

ISR_FuncPtr_t ISR_UAST_RX_CBF = NULL;
void UART_VoidInit(void)
{
	// select double speed config
	UART_UCSRA_REG |= (UART_D_TXSPEED_CFG <<  UART_UCSRA_U2X_BIT );

	// enable write to UCSRC
	Set_Bit(UART_UCSRC_REG,UART_UCSRC_URSEL_BIT);

	//select data lenth
	UART_UCSRB_REG |=  ( (Get_Bit(UART_DATA_LEN_CFG , 2)) << UART_UCSRB_UCSZ2_BIT); //bit2 in data lenth

	// USCRC CONFIG
	UART_UCSRC_REG = UART_UCSRC_VAL_CFG ;

	// access  UBRRH
	Clr_Bit(UART_UCSRC_REG,UART_UCSRC_URSEL_BIT);

	// select Baud rate
	UART_UBRRL_REG = (u8)UART_BAUDRATE_CFG;
	UART_UBRRH_REG = (u8)(UART_BAUDRATE_CFG>>8);
#if UART_RX_INTERRUPT_CFG == UART_INTERRUPT_FEATUER_ENABLE
	GIE_ENABLE();
	// enable interrupt on data recived
	UART_UCSRB_REG |= (0x01 << UART_UCSRB_RXCIE_BIT);

#endif
	//rx enable
	UART_UCSRB_REG |= (0x01 << UART_UCSRB_RXEN_BIT);
	//tx enable
	UART_UCSRB_REG |= (0x01 << UART_UCSRB_TXEN_BIT);
}


void UART_VoidSetRxCBF(ISR_FuncPtr_t copy_ISR_FuncPtr_t)
{
	if(copy_ISR_FuncPtr_t)
		ISR_UAST_RX_CBF = copy_ISR_FuncPtr_t;
}
void UART_Send(u8 Copy_u8Data)
{
	while( Get_Bit(UART_UCSRA_REG,UART_UCSRA_UDRE_BIT) != 1)
		;
	UART_UDR_REG = Copy_u8Data;

}

void UART_Receive(u8* Copy_pu8GetData)
{

	while( Get_Bit(UART_UCSRA_REG,UART_UCSRA_RXC_BIT) != 1)
		;
	*Copy_pu8GetData = UART_UDR_REG;

}

void UART_Receive_interrupt(u8* Copy_pu8GetData)
{
	*Copy_pu8GetData = UART_UDR_REG;
}

void UART_SendString(u8* Copy_pu8Data)
{
	u8 i = 0;
	while( Get_Bit(UART_UCSRA_REG,UART_UCSRA_UDRE_BIT) != 1)
			;
	while(Copy_pu8Data[i])
	{
		UART_Send(Copy_pu8Data[i++]);
	}

}




void __vector_13(void)
{
	if(ISR_UAST_RX_CBF)
		ISR_UAST_RX_CBF();
}








