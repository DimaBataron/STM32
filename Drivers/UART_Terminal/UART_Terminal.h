/*
 * UART_Terminal.h
 *
 *  Created on: Sep 21, 2025
 *      Author: dima
 */

#ifndef UART_TERMINAL_UART_TERMINAL_H_
#define UART_TERMINAL_UART_TERMINAL_H_

#include "main.h"
#include "Console.h"

void StartUartRX();
void console_write_function(const char* str);
void MyConsole_Setup(void);
uint32_t USART1_Receive(uint8_t chr, uint8_t *Buffer, uint32_t Length, TickType_t TimesUp);

#endif /* UART_TERMINAL_UART_TERMINAL_H_ */
