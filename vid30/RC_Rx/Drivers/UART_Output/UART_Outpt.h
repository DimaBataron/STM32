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

// ����������� �������������� �������


// ���� 							+1
// 3 ����� ����� 					+3
// ������� ������ 					+1
// -6 ������� ������� ��� ���� � ������
// 12

#define ADDIT_SYMB_REQUIR 5

// ��������� ���������� ��������� �� ���������� ������ � ���������� ���������.
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
