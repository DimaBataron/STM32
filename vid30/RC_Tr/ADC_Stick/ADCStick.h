/*
 * ADCStick.h
 *
 *  Created on: Apr 20, 2024
 *      Author: dima
 */

#ifndef ADC_STICK_ADCSTICK_H_
#define ADC_STICK_ADCSTICK_H_
#include "main.h"

extern uint32_t Adc1Value[5];
extern uint32_t Adc1Null[4];
extern int8_t Adc1Calc[4];

// Начальная настройка ADC на работу.
void InitADCStick(ADC_HandleTypeDef* hadc);

//Стартовая калибровка стиков
void StickCal(uint32_t* Adc1Value,ADC_HandleTypeDef* hadc, uint32_t* Adc1Null);

//вычисление текущего положения стика
void StickCalc(uint32_t* Adc1Value,ADC_HandleTypeDef* hadc, uint32_t* Adc1Null);

// returns the calculated battery percentage
float BattCharge(uint32_t Adc1Value);

// frame buffer formation
void BufFormCharge();

//frame buffer stick formation
void BufFormStick();

void BufFormNumbConv();

#endif /* ADC_STICK_ADCSTICK_H_ */
