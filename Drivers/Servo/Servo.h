/*
 * Servo.h
 *
 *  Created on: Apr 17, 2025
 *      Author: dima
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "main.h"

/*
 * ��� ������� �� ����� �������������� ������ �� ��������.
 */
//#define SERV_ZERO 		4909 // ������� ��������� �����
//#define SERV_PLUS_90 	6545 // +90 ��������
//#define SERV_MINUS_90 	3273 // -90 ��������.
//
//#define SERV_PITCH		13 // �������� �� ������� ����.


#define SERV_ZERO 		4350 // ������� ��������� �����
#define SERV_PLUS_90 	7500 // +90 ��������
#define SERV_MINUS_90 	1200 // -90 ��������.

#define SERV_PITCH		25 // �������� �� ������� ����.

void ServoStartInit(TIM_HandleTypeDef *htim, uint32_t Channel);

void SteeringWheel(TIM_HandleTypeDef *htim, uint32_t Channel, float angle);

#endif /* SERVO_H_ */
