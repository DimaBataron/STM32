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
#define CAM_HORIZONT  	2 // камера по горизонтали
#define CAM_VERTICAL	3 // камера вертикаль
#define STEER_TRIM		4 // триммер руля.
#define CAM_TRIM_HORIZ	5 // тример камеры по горизонтали
#define CAM_TRIM_VERT	6 // тример камеры вертикаль
#define HEADLIGHTS		7 // фары
#define LOAD1			8 // нагрузка1
#define	LOAD2			9 // нагрузка2
#define CAM_HOME		10 // возврат камеры в нулевое положение

#define WARNING_BAT_VOLTAGE 	2.07f //соответствует напряжению на батарейках в 6.2В
#define SHUTDOWN_BAT_VOLTAGE	1.93f //соответствует напряжению 5.8В

#define VOLT_OK			0
#define VOLT_CAUTION 	1
#define VOLT_SHUTDOWN	2

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

extern int8_t OutputNumSuccessPack;

extern uint8_t BatteryStatus;

void CalcRxCommands();
void CheckRange(int32_t *BufComArr1, int8_t *Command);
void ZeroCommArr();
uint8_t CheckBatVolt(float U);

#endif /* CHAEBURATORIT_PROC_H_ */
