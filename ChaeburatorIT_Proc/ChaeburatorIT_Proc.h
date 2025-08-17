/*
 * ChaeburatorIT_Proc.h
 *
 *  Created on: Aug 15, 2025
 *      Author: dima
 */

#ifndef CHAEBURATORIT_PROC_H_
#define CHAEBURATORIT_PROC_H_

#include "main.h"

#define ACCELER 		0 // ���������
#define STEER_TURN 		1 // ������� ����
#define CAM_HORIZONT  	2 // ������ �� �����������
#define CAM_VERTICAL	3 // ������ ���������
#define STEER_TRIM		4 // ������� ����.
#define CAM_TRIM_HORIZ	5 // ������ ������ �� �����������
#define CAM_TRIM_VERT	6 // ������ ������ ���������
#define HEADLIGHTS		7 // ����
#define LOAD1			8 // ��������1
#define	LOAD2			9 // ��������2
#define CAM_HOME		10 // ������� ������ � ������� ���������

void CalcRxCommands();
void CheckRange(int32_t *BufComArr1, int8_t *Command);

#endif /* CHAEBURATORIT_PROC_H_ */
