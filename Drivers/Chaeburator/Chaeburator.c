/*
 * Chaeburator.c
 *
 *  Created on: Sep 20, 2025
 *      Author: dima
 */


#include "Chaeburator.h"


// включает все системы питания.
void Power_ON(){
	HAL_GPIO_WritePin(P_CONTROL_GPIO_Port, P_CONTROL_Pin, GPIO_PIN_SET);
}

// выключает питание
void Power_Off(){
	HAL_GPIO_WritePin(P_CONTROL_GPIO_Port, P_CONTROL_Pin, GPIO_PIN_RESET);
}

// включение выключение фар
void Light1(GPIO_PinState state){
	HAL_GPIO_WritePin(LIGHT1_GPIO_Port, LIGHT1_Pin, state);
}
void Light2(GPIO_PinState state){
	HAL_GPIO_WritePin(LIGHT2_GPIO_Port, LIGHT2_Pin, state);
}

// сигнал
void Boozer(GPIO_PinState state){
	HAL_GPIO_WritePin(BOOZER_GPIO_Port, BOOZER_Pin, state);
}

