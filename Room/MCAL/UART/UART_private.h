/*
 * UART_private.h
 *
 *  Created on: Aug 23, 2023
 *      Author: yosse
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_


#define UART_UDR_REG	(*(volatile u8*)0x2C )


#define UART_UCSRA_REG  (*(volatile u8*)0x2B)
#define UART_UCSRA_RXC_BIT		7
#define UART_UCSRA_TXC_BIT		6
#define UART_UCSRA_UDRE_BIT		5
#define UART_UCSRA_FE_BIT		4
#define UART_UCSRA_DOR_BIT		3
#define UART_UCSRA_PE_BIT		2
#define UART_UCSRA_U2X_BIT		1
#define UART_UCSRA_MPCM_BIT		0


#define UART_UCSRB_REG  (*(volatile u8*)0x2A)

#define UART_UCSRB_RXCIE_BIT	7
#define UART_UCSRB_TXCIE_BIT	6
#define UART_UCSRB_UDRIE_BIT	5
#define UART_UCSRB_RXEN_BIT		4
#define UART_UCSRB_TXEN_BIT		3
#define UART_UCSRB_UCSZ2_BIT	2
#define UART_UCSRB_RXB8_BIT		1
#define UART_UCSRB_TXB8_BIT		0

#define UART_UCSRC_REG	(*(volatile u8*)0x40)

#define UART_UCSRC_URSEL_BIT		7
#define UART_UCSRC_UMSEL_BIT		6
#define UART_UCSRC_UPM1_BIT			5
#define UART_UCSRC_UPM0_BIT			4
#define UART_UCSRC_USBS_BIT			3
#define UART_UCSRC_UCSZ1_BIT		2
#define UART_UCSRC_UCSZ0_BIT		1
#define UART_UCSRC_UCPOL_BIT		0



#define UART_UBRRH_REG	(*(volatile u8*)0x40)
#define UART_UBRRL_REG  (*(volatile u8*)0x29)



#endif /* MCAL_UART_UART_PRIVATE_H_ */
