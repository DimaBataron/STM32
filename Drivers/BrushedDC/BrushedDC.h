/*
 * BrushedDC.h
 *
 *  Created on: Aug 10, 2025
 *      Author: dima
 */

#ifndef BRUSHEDDC_BRUSHEDDC_H_
#define BRUSHEDDC_BRUSHEDDC_H_

#include "main.h"
// ����������� �������� �� ������� �������
#define DirectRotCW 1

// ����������� �������� ������ ������� �������
#define	DirectRotCCW 2

// ������� ����
#define DeadZone 3

// 7199/127 = 56.68 �� �������
#define MotorStep 56.68


/*
 * ������� ��������� ������������ ����� �����������.
 * ������� ��������� ������������ �������� ����������
 * TB6612FNG � ����������� �� �������� ������
 * ������������� ����������� ���������� ���.
 * �� ���� ��������� ����������� ��������,
 * ����� �������� � ������, ����������� �� ��������
 * ��������, ��������� �� ����������� �������.
 *
 * */

void Brushed2DC_Control(TIM_HandleTypeDef *htim1,uint32_t Channnel1, \
		uint32_t Channel2, int8_t acceleration, uint32_t DirectRot1, \
		uint32_t DirectRot2);
/*
 * ���������� ����� ����������.
 *
 * */
void Brushed1DC_Control(TIM_HandleTypeDef *htim1,uint32_t Channel, int8_t acceleration);

// ������ ����������
void EngineBrake(uint32_t Channel);


#endif /* BRUSHEDDC_BRUSHEDDC_H_ */
