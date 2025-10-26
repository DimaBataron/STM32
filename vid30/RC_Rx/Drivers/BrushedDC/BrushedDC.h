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

// 7199/127 = 56.68 �� ������� (���������?) 127 ������������ ����� ������� ����� �������
// � ������
#define MotorStep 56.68

// ��������� �������� ���������.
typedef struct {
	uint16_t PinIn1; //  ��� ����������� �������� 1
	uint16_t PinIn2; // ��� ����������� �������� 2
	uint16_t StbyPin;

	GPIO_TypeDef * PortIn1;
	GPIO_TypeDef * PortIn2;
	GPIO_TypeDef * StbyPort;
	volatile uint32_t *pwm_register_ptr; // ����� �������� ��� ����� ���������

} DC_Motor;

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


void DC_Control(DC_Motor *Motor, int8_t acceleration);

// ������ ����������
void EngineBrake(uint32_t Channel);

void Engine_Control(int8_t acceleration, DC_Motor *Motor1, DC_Motor *Motor2);

int8_t AccelerationIncr(int16_t tmp);


#endif /* BRUSHEDDC_BRUSHEDDC_H_ */
