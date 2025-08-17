/*
 * Servo.c
 *
 *  Created on: Apr 17, 2025
 *      Author: dima
 */


#include "Servo.h"

/*
 * ������ ����� ������������� �����. ����� ����������� ���������� �����?
 */

/*
 * ������� ��������� ������������� ������� ������������ �������������
 * �� ���� ����� ��������� ������������� ������� � ����� ������.
 * ��������� ������� ������������� ������������� ��������� HAL.
 *
 * - ������������� � 0 ��������� �����.
 * - �������� �����.
 */

void ServoStartInit(TIM_HandleTypeDef *htim, uint32_t Channel){
	switch (Channel){
		case TIM_CHANNEL_1 : {
			htim->Instance->CCR1 = SERV_ZERO;
			break;
		}
		case TIM_CHANNEL_2 : {
			htim->Instance->CCR2 = SERV_ZERO;
			break;
		}
		case TIM_CHANNEL_3 : {
			htim->Instance->CCR3 = SERV_ZERO;
			break;
		}
		case TIM_CHANNEL_4 : {
			htim->Instance->CCR4 = SERV_ZERO;
			break;
		}
	}
	HAL_TIM_PWM_Start(htim, Channel);
}

/*
 * ������� ������������ ������������. ��������� �� ���� :
 * 	- ����� ��������� �����������
 * 	- ����� ������.
 *  - ����� ��������������� ��������.
 */

void SteeringWheel(TIM_HandleTypeDef *htim, uint32_t Channel, int8_t TurnNum){
	int32_t ServoNumber = SERV_ZERO;
	ServoNumber = SERV_ZERO+(TurnNum*SERV_PITCH);
//	if(TurnNum > 0){
//		ServoNumber += TurnNum * SERV_PITCH;
//		ServoNumber > SERV_PLUS_90 ? ServoNumber = SERV_PLUS_90 : ServoNumber;
//	}
//	else {
//		ServoNumber += TurnNum * SERV_PITCH;
//		ServoNumber < SERV_MINUS_90 ? ServoNumber = SERV_MINUS_90 : ServoNumber;
//	}

	switch (Channel){
			case TIM_CHANNEL_1 : {
				htim->Instance->CCR1 = ServoNumber;
				break;
			}
			case TIM_CHANNEL_2 : {
				htim->Instance->CCR2 = ServoNumber;
				break;
			}
			case TIM_CHANNEL_3 : {
				htim->Instance->CCR3 = ServoNumber;
				break;
			}
			case TIM_CHANNEL_4 : {
				htim->Instance->CCR4 = ServoNumber;
				break;
			}
		}
}

/*
 * �������������� ������ �� 90 �������� 45 � ���� ������� 45 �� ������. ������� ����� ��� � �����.
 * ��� �������� ��� ������������ �� 2. � ����� ������ ���� ���������� �������.
 */
