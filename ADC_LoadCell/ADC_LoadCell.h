/*
 * ADC_LoadCell.h
 *
 *  Created on: Aug 22, 2025
 *      Author: dima
 */

#ifndef ADC_LOADCELL_H_
#define ADC_LOADCELL_H_

#include "main.h"

//���������� ��������� � �������.
#define ADC_BUFFER_SIZE 40

//���������� �������������� �.�. ����� ��� ��� ����� ������������ �� ����.
#define ADC_NUMBER_DIMENSIONS 20

// ��������. ���� ����� ��� ���������� ������ ����� �������� ���������� 20 ���������
#define ADC_TEST_NUMBER_DIMENSIONS 10

void StartMeasure();

float VoltageCalc();

#endif /* ADC_LOADCELL_H_ */
