/*
 * UART_interface.h
 *
 *  Created on: Aug 23, 2023
 *      Author: yosse
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_




void UART_VoidInit(void);
void UART_VoidSetRxCBF(ISR_FuncPtr_t copy_ISR_FuncPtr_t);
void UART_Receive_interrupt(u8* Copy_pu8GetData);
void UART_Send(u8 Copy_u8Data);
void UART_Receive(u8* Copy_pu8GetData);
void UART_SendString(u8* Copy_pu8Data);

#endif /* MCAL_UART_UART_INTERFACE_H_ */
