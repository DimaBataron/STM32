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

void CalcRxCommands();
void CheckRange(int32_t *BufComArr1, int8_t *Command);

#endif /* CHAEBURATORIT_PROC_H_ */
