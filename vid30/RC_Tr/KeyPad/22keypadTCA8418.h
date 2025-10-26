/*
 * 22keypadTCA8418.h
 *
 *  Created on: Aug 5, 2024
 *      Author: dima
 */
#include "main.h"
#ifndef KEYPAD_22KEYPADTCA8418_H_
#define KEYPAD_22KEYPADTCA8418_H_

extern uint8_t FlagPress;
extern uint8_t MassPressKey[10];
extern uint32_t ConditionEncoder;
//Адрес
#define AddrTCA8418 0b01101000  // сдвинул вправо

//Регистры
#define REG_KP_GPIO1 0x1D
#define REG_KP_GPIO2 0x1E
#define REG_KP_GPIO3 0x1F

#define REG_CFG 		0x01
#define REG_INT_STAT 	0x02

#define REG_KEY_EVENT_A 0x04
//Использованы ROW0-ROW2 и COL0-COL7
#define ROW0 0x01
#define ROW1 0x02
#define ROW2 0x04

#define COL0 0x0001
#define COL1 0x0002
#define COL2 0x0004
#define COL3 0x0008
#define COL4 0x0010
#define COL5 0x0020
#define COL6 0x0040
#define COL7 0x0080

//Биты настройки регистра CFG
#define CFG_AI 				0x80
#define CFG_GPI_E_CFG 		0x40
#define CFG_OVR_FLOW_M 		0x20
#define CFG_INT_CFG 		0x10
#define CFG_OVR_FLOW_IEN 	0x08
#define CFG_K_LCK_IEN 		0x04
#define CFG_GPI_IEN 		0x02
#define CFG_KE_IEN 			0x01

//Биты регистра INT_STAT

#define K_INT				0x01
#define Timeout_I2C_Tr		500


/*Процедура передает команды инициализации на устройство TCA8418
Принимает:
- указатель на структуру заголовочного файла i2c
*/
HAL_StatusTypeDef MatrixConfig8418(I2C_HandleTypeDef *hi2c);

HAL_StatusTypeDef ReadFIFO(I2C_HandleTypeDef *hi2c);

//form buffer press key
void BufFormKey(uint8_t X);
//processing press key menu
void MenuEventPress(uint8_t ReadData);

void PrintSymbASCII(uint8_t *MassPressKey);
#endif /* KEYPAD_22KEYPADTCA8418_H_ */
