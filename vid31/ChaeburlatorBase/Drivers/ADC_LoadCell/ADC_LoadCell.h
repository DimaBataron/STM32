/*
 * ADC_LoadCell.h
 *
 *  Created on: Aug 22, 2025
 *      Author: dima
 */

#ifndef ADC_LOADCELL_H_
#define ADC_LOADCELL_H_

#include "main.h"

//количество элементов в массиве.
#define ADC_BUFFER_SIZE 40

//количество преобразований т.к. думаю что они будут осуществятся по двое.
#define ADC_NUMBER_DIMENSIONS 20

// проверка. Если задам это количество массив будет заполнен наполовину 20 элементов
#define ADC_TEST_NUMBER_DIMENSIONS 10

void StartMeasure();

float VoltageCalc();

#endif /* ADC_LOADCELL_H_ */
