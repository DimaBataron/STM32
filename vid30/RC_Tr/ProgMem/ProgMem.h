/*
 * ProgMem.h
 *
 *  Created on: Oct 9, 2025
 *      Author: dima
 */

#ifndef PROGMEM_H_
#define PROGMEM_H_

#include "main.h"

// ����� ��������� �������� F103C8T6
#define EndPage 0x0801FC00
// ���� Key ��������� ������������� �������� ����������� �� ������
#define Key 12345

// ������ ��������� � ������������ �������
typedef struct {
	uint32_t KeySt;
	CalibrStruct CalibrValues;
} ProgMemStruct;

void read_config_from_flash(ProgMemStruct* config);

HAL_StatusTypeDef write_config_to_flash(ProgMemStruct* config);

void StartInitCalValues(CalibrStruct *CalibrValues);

HAL_StatusTypeDef ClearProgMem();


#endif /* PROGMEM_H_ */
