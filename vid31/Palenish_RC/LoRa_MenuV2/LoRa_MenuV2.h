/*
 * LoRa_MenuV2.h
 *
 *  Created on: Mar 29, 2025
 *      Author: dima
 */

#ifndef LORA_MENUV2_H_
#define LORA_MENUV2_H_
#define DIGIT_LEN 6 		//максимальное количество изменяемых цифровых значений

#include "main.h"


void printFreqMenu(struct PositionMenuStruct *MenuStructOld);
void printPowerMenu(struct PositionMenuStruct *MenuStructOld);
void printSignalBw(struct PositionMenuStruct *MenuStructOld);
void printSfMenu(struct PositionMenuStruct *MenuStructOld);

void printErrCod(struct PositionMenuStruct *MenuStructOld);

void LoRaMenuInit();

uint32_t checkParamRf();
void LoRaParamCalc();

#endif /* LORA_MENUV2_H_ */
