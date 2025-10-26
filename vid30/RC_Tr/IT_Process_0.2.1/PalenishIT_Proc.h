/*
 * PalenishIT_Proc.h
 *
 *  Created on: Mar 27, 2025
 *      Author: dima
 */

#ifndef PALENISHIT_PROC_H_
#define PALENISHIT_PROC_H_

#include "main.h"

//Assign symbolic names to all commands in the array
//They will be stored in ComArr1 (the command array) using these numbers.
// This is obsolete. Replace
#define ROLL 		0 // КРЕН
#define PITCH 		1 // ТАНГАЖ
#define YAW			2 // РЫСКАНЬЕ
#define THROTTLE 	3 // РУД
//Остальные пока не использую.
#define ACCELER 		0 // acceleration
#define STEER_TURN 		1 // steering wheel turn
#define CAM_HORIZONT  	2 // camera horizontally
#define CAM_VERTICAL	3 // vertical camera
#define STEER_TRIM		4 // steering wheel trimmer.
#define CAM_TRIM_HORIZ	5 // horizontal camera trimmer
#define CAM_TRIM_VERT	6 // vertical camera trimmer
#define HEADLIGHTS		7 // headlights
#define LOAD1			8 // load1
#define	LOAD2			9 // load2
#define CAM_HOME		10 // return the camera to the zero position

//Here are the keypad key codes
#define KEY_STEER_TRIM_P 		129
#define KEY_STEER_TRIM_N		139
#define KEY_CAM_TRIM_HORIZ_P	130
#define KEY_CAM_TRIM_HORIZ_N	140
#define KEY_CAM_TRIM_VERT_P		131
#define KEY_CAM_TRIM_VERT_N		141
#define KEY_HEADLIGHTS			149
#define KEY_LOAD1				135
#define KEY_LOAD2				145
#define KEY_CAM_HOME			154

// Calibration values
typedef enum
{
  START_CAL = 0u,
  CAL_WRITE
} StatCalibr;

/* В структуре:
 * 	- страница
 *  - положение на странице,
 * 	- нажатая клавиша.
 *	- пункт подменю ( сама функция вычисляет надо ли ей такое)
 *	- клавиша выход.
 */
typedef struct PositionMenuStruct{
	uint32_t Page; 				// currently selected page.
	uint32_t PositionMarker; 	// position of the pointer on the page.
	uint32_t PressKey;			// whether there was a press.
	uint32_t NestMenuItem;   	// nested menu item.
	uint32_t ExitPressed;    	// the exit button was pressed.
	uint32_t NestPressUP;    	// in the nested menu up.
	uint32_t NestPressDown;	 	// in the nested menu down.
	uint32_t PressStart;	 	// the start button is pressed.
	uint32_t PressSelectLoraInit; // Selecting LoRa initialization settings.
	uint32_t CalibrStartStop; 	// Start stop calibration.

} PositionMenuStruct;

typedef struct CalibrStruct{
	float CalibrValMax[4];
	float CalibrValMin[4];
	uint32_t Adc1NULL[4];
}CalibrStruct;

typedef struct MaxMinCalStruct{
	int8_t MaxADC1Calc[4];
	int8_t MinADC1Calc[4];
}MaxMinCalStruct;


extern PositionMenuStruct MenuStructOld ;
extern uint8_t ComArr1[];
extern CalibrStruct CalibrValues;

HAL_StatusTypeDef IT_GPIO_Handl(uint16_t GPIO_Pin);
HAL_StatusTypeDef PressHandl(uint8_t *MassPressKey, PositionMenuStruct *MenuStructOld);
void NewPressState(uint8_t MassPressKey, PositionMenuStruct *MenuStructOld);
HAL_StatusTypeDef MenuHandl(PositionMenuStruct *MenuStructOld);

HAL_StatusTypeDef LoRaInitTx(PositionMenuStruct *MenuStructOld);

void NumPacSec();

void DMA_EndTransmitToFiFo();

void FormArrComm();

void PressContrKeys(uint8_t MassPressKey);

void CalibrStartInit(CalibrStruct *Calib);

MaxMinCalStruct *CalcCalVal(StatCalibr Mode,CalibrStruct *Calib );

void PrintCalibMaxMin(MaxMinCalStruct *CalStruct);

void ClearCalValues();



#endif /* PALENISHIT_PROC_H_ */
