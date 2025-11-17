/*
 * ChaeburatorIT_Proc.h
 *
 *  Created on: Aug 15, 2025
 *      Author: dima
 */

#ifndef CHAEBURATORIT_PROC_H_
#define CHAEBURATORIT_PROC_H_

#include "main.h"

#define ACCELER 		0 // ускорение
#define STEER_TURN 		1 // поворот руля
#define CAM_HORIZONT  	3 // камера по горизонтали
#define CAM_VERTICAL	2 // камера вертикаль
#define STEER_TRIM		4 // триммер руля.
#define CAM_TRIM_HORIZ	5 // тример камеры по горизонтали
#define CAM_TRIM_VERT	6 // тример камеры вертикаль
#define HEADLIGHTS		7 // фары
#define LOAD1			8 // нагрузка1
#define	LOAD2			9 // нагрузка2
#define SOUND_SIG		10

#define WARNING_BAT_VOLTAGE 	6.15f //corresponds to a battery voltage of 6.1V
#define SHUTDOWN_BAT_VOLTAGE	5.7f //corresponds to a voltage of 5.65V

#define VOLT_OK			0
#define VOLT_CAUTION 	1
#define VOLT_SHUTDOWN	2

#define BATTERY_OK 		0
#define BATTERY_DISC	1

extern int8_t Acceleration;
extern int8_t SteerTurn;
extern int8_t CamHorizont;
extern int8_t CamVertical;
extern int8_t HeadLights;
extern int8_t Load1;
extern int8_t Load2;
extern int8_t CamHome;

extern uint32_t PayLoadCRCError;
extern uint32_t NumSuccessPack;
extern uint8_t BatteryStatus;

extern int8_t OutputNumSuccessPack;

//extern uint8_t BatteryStatus;

void CalcRxCommands();
void CheckRange(int32_t *BufComArr1, int8_t *Command);
void ZeroCommArr();
uint8_t CheckBatVolt(float U);

void Caution();

void EmergMode();

#endif /* CHAEBURATORIT_PROC_H_ */
