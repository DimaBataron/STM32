/*
 * BrushedDC.c
 *
 *  Created on: Aug 10, 2025
 *      Author: dima
 */


#include "BrushedDC.h"

void Brushed2DC_Control(TIM_HandleTypeDef *htim1,uint32_t Channel1, \
		uint32_t Channel2, int8_t acceleration, uint32_t DirectRot1, \
		uint32_t DirectRot2){

	static float accelStep = MotorStep;
	int32_t accelPWM = 0;

	// �������� ������� ����
	if((acceleration > DeadZone) || (acceleration < -DeadZone)){
		accelPWM = (int32_t)(accelStep*(float)acceleration);
	}
	else accelPWM = 0;

//	����������� ������. ������������ 1_2 ��� 2_3 �����?
	if(Channel1 == TIM_CHANNEL_1){
		HAL_GPIO_WritePin(STBY_M1_M2_GPIO_Port, STBY_M1_M2_Pin, GPIO_PIN_SET);
		//�������� �� ������� �������.
		if(DirectRot1 == DirectRotCW){ // ����� DirectRot2 == DirectRotCCW
			//������ ���
			if(accelPWM<0){
				HAL_GPIO_WritePin(M1_IN1_GPIO_Port, M1_IN1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(M1_IN2_GPIO_Port, M1_IN2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(M2_IN1_GPIO_Port, M2_IN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(M2_IN2_GPIO_Port, M2_IN2_Pin, GPIO_PIN_RESET);
				htim1->Instance->CCR1 = -accelPWM;
				htim1->Instance->CCR2 = -accelPWM;
			}
			// ������ ���
			else {
				HAL_GPIO_WritePin(M1_IN1_GPIO_Port, M1_IN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(M1_IN2_GPIO_Port, M1_IN2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(M2_IN1_GPIO_Port, M2_IN1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(M2_IN2_GPIO_Port, M2_IN2_Pin, GPIO_PIN_SET);
				htim1->Instance->CCR1 = accelPWM;
				htim1->Instance->CCR2 = accelPWM;
			}
		}
		// �������� ������ �������
		else{
			//������ ���
			if(accelPWM<0){
				HAL_GPIO_WritePin(M1_IN1_GPIO_Port, M1_IN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(M1_IN2_GPIO_Port, M1_IN2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(M2_IN1_GPIO_Port, M2_IN1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(M2_IN2_GPIO_Port, M2_IN2_Pin, GPIO_PIN_SET);
				htim1->Instance->CCR1 = -accelPWM;
				htim1->Instance->CCR2 = -accelPWM;
			}
			// ������ ���
			else {
				HAL_GPIO_WritePin(M1_IN1_GPIO_Port, M1_IN1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(M1_IN2_GPIO_Port, M1_IN2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(M2_IN1_GPIO_Port, M2_IN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(M2_IN2_GPIO_Port, M2_IN2_Pin, GPIO_PIN_RESET);
				htim1->Instance->CCR1 = accelPWM;
				htim1->Instance->CCR2 = accelPWM;
			}

		}
	}
}

// ���������� ����� ����������
void Brushed1DC_Control(TIM_HandleTypeDef *htim1,uint32_t Channel, int8_t acceleration){
	HAL_GPIO_WritePin(STBY_M3_M4_GPIO_Port, STBY_M3_M4_Pin, GPIO_PIN_SET);
	static float accelStep =  MotorStep;
	int32_t accelPWM = 0;
	accelPWM = (int32_t)(accelStep*(float)acceleration);
// ������ ���
	if(accelPWM<0){
		HAL_GPIO_WritePin(M3_IN1_GPIO_Port, M3_IN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(M3_IN2_GPIO_Port, M3_IN2_Pin, GPIO_PIN_SET);
		htim1->Instance->CCR3 = -accelPWM;
	}
	// ������
	else {
		HAL_GPIO_WritePin(M3_IN1_GPIO_Port, M3_IN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(M3_IN2_GPIO_Port, M3_IN2_Pin, GPIO_PIN_RESET);
		htim1->Instance->CCR3 = accelPWM;
	}
}


// ������� ��� ���������� ����� ����������. �� ���� ��������� ���������
// �������� ����������� ����������, � ���������.
// ��������� �� ���� +-100%
void DC_Control(DC_Motor *Motor, int8_t acceleration){
	HAL_GPIO_WritePin(Motor->StbyPort, Motor->StbyPin, GPIO_PIN_SET);

	static float accelStep =  MotorStep;
	int32_t accelPWM = (int32_t)(accelStep*(float)acceleration);
	// ������ ���
		if(accelPWM<0){
			HAL_GPIO_WritePin(Motor->PortIn1, Motor->PinIn1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Motor->PortIn2, Motor->PinIn2, GPIO_PIN_SET);
			*(Motor->pwm_register_ptr) = -accelPWM;
		}
		// ������
		else {
			HAL_GPIO_WritePin(Motor->PortIn1, Motor->PinIn1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Motor->PortIn2, Motor->PinIn2, GPIO_PIN_RESET);
			*(Motor->pwm_register_ptr) = accelPWM;
		}
}

// ������ ����������
void EngineBrake(uint32_t Channel){
	if((Channel == TIM_CHANNEL_1) || (Channel == TIM_CHANNEL_2) ){
		HAL_GPIO_WritePin(STBY_M1_M2_GPIO_Port, STBY_M1_M2_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(STBY_M3_M4_GPIO_Port, STBY_M3_M4_Pin, GPIO_PIN_SET);
	}
	switch (Channel){
			case TIM_CHANNEL_1 : {
				HAL_GPIO_WritePin(M1_IN1_GPIO_Port, M1_IN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(M1_IN2_GPIO_Port, M1_IN2_Pin, GPIO_PIN_SET);
				break;
			}
			case TIM_CHANNEL_2 : {
				HAL_GPIO_WritePin(M2_IN1_GPIO_Port, M2_IN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(M2_IN2_GPIO_Port, M2_IN2_Pin, GPIO_PIN_SET);
				break;
			}
			case TIM_CHANNEL_3 : {
				HAL_GPIO_WritePin(M3_IN1_GPIO_Port, M3_IN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(M3_IN2_GPIO_Port, M3_IN2_Pin, GPIO_PIN_SET);
				break;
			}
			case TIM_CHANNEL_4 : {
				HAL_GPIO_WritePin(M4_IN1_GPIO_Port, M3_IN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(M4_IN2_GPIO_Port, M3_IN2_Pin, GPIO_PIN_SET);
				break;
			}
		}
}
