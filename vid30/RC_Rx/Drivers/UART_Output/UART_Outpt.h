/*
 * UART_Outpt.h
 *
 *  Created on: Aug 17, 2025
 *      Author: dima
 */

#ifndef UART_OUTPT_H_
#define UART_OUTPT_H_

#include "main.h"
#include <string.h>
#include "stdio.h"

// Необходимые дополнительные символы


// знак 							+1
// 3 цифры числа 					+3
// нулевой символ 					+1
// -6 символы которые уже есть в строке
// 12

#define ADDIT_SYMB_REQUIR 5

// Структура содержащая указатель на выделенную память и количество элементов.
typedef struct {
	char 	*StrSymb;
	int16_t  Quantity;
}MemAllocData;

MemAllocData TransArrayLayout();

MemAllocData MemReqString(const char *Str, int8_t DataOutput);

uint16_t MemCpyStr(char *Purpose, char *Source, uint16_t Len);

void OutDataRxLoRa(UART_HandleTypeDef *huart);

void OutStringTask();

#endif /* UART_OUTPT_H_ */
