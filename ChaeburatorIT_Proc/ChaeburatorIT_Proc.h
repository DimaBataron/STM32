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

#define WARNING_BAT_VOLTAGE 	2.07f //������������� ���������� �� ���������� � 6.2�
#define SHUTDOWN_BAT_VOLTAGE	1.93f //������������� ���������� 5.8�

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
