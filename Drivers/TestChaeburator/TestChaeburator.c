/*
 * TestChaeburator.c
 *
 *  Created on: Sep 19, 2025
 *      Author: dima
 *
 *     ����� ���������� ������� ������������. ������� ������������� ��� �������� ����������
 *     ��� ������ ���������.
 *
 *     ��� ��������� ���������� ��������������
 *     - ��������� �������.
 *     - ����������.
 *     - ������
 *     - �����������
 *     - ������� ���������
 *     - ������
 *     - wifi
 *     - ������������ ��������
 *     - ������ LoRa ( �����)
 *
 *     ������� ������������ ������������� ��� ���-�� ����� ������ �������� �� � ������,
 *     �������� ������ ������ � ���������� � ��� ����� ��������.
 *
 *	 ����� ������� 2 ���������(���������) ������������ �� 100% ���� ��������, ��� ���� ������� �������
 *	 ����� �� ��� ����� � ����� �������. �������� ���-�� �������.
 *	 ����� 2 ������ ����� �������� ���������� ��-�� �����, ���� ��������.
 *	 � ����� ��� ������� ��������.
 *	 ������ ��������� �� ����������. (��� ��������� ������� �������� ���)
 *
 *   ����� �������� ���-�� ���� ������������ �������.
 *   �� ������ ����� � ������� ��������� ��������.
 *   �� ������� ���������� ���� ����� ���, ��� �� ���������.
 *	 ��� ����������� ��������� ���� ������ �������� ��������� 0.046�
 *
 *    */


#include "TestChaeburator.h"

void TestFunction(){
	//��������� �������
	Power_ON();

	//��������� ���������� �����.
	Light1(GPIO_PIN_SET);
	Light2(GPIO_PIN_SET);
	HAL_Delay(2000);
	Light1(GPIO_PIN_RESET);
	Light2(GPIO_PIN_RESET);

////	������� ������ � ��������
	Boozer(GPIO_PIN_SET);
	HAL_Delay(500);
	Boozer(GPIO_PIN_RESET);

	ServoStartInit(&htim3, TIM_CHANNEL_1);
	ServoStartInit(&htim3, TIM_CHANNEL_2);

	SteeringWheel(&htim3, TIM_CHANNEL_1, 90.0f);
	SteeringWheel(&htim3, TIM_CHANNEL_2, 90.0f);
	HAL_Delay(2000);
	SteeringWheel(&htim3, TIM_CHANNEL_1, -90.0f);
	SteeringWheel(&htim3, TIM_CHANNEL_2, -90.0f);
	HAL_Delay(2000);
	SteeringWheel(&htim3, TIM_CHANNEL_1, 0.0f);
	SteeringWheel(&htim3, TIM_CHANNEL_2, 0.0f);

//	�� ������� Servo3 � Servo4
	DC_Motor Motor1 = {0};
	Motor1.PinIn1 = M1_IN1_Pin;
	Motor1.PinIn2 = M1_IN2_Pin;
	Motor1.PortIn1 = M1_IN1_GPIO_Port;
	Motor1.PortIn2 = M1_IN2_GPIO_Port;
	Motor1.StbyPin = STBY_M1_M2_Pin;
	Motor1.StbyPort = STBY_M1_M2_GPIO_Port;
	Motor1.pwm_register_ptr = &(htim2.Instance->CCR1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
//	TestMotor(&Motor1, acceleration);
//
////	���� ������� ������
	DC_Motor Motor2 = {0};
	Motor2.PinIn1 = M2_IN1_Pin;
	Motor2.PinIn2 = M2_IN2_Pin;
	Motor2.PortIn1 = M2_IN1_GPIO_Port;
	Motor2.PortIn2 = M2_IN2_GPIO_Port;
	Motor2.StbyPin = STBY_M1_M2_Pin;
	Motor2.StbyPort = STBY_M1_M2_GPIO_Port;
	Motor2.pwm_register_ptr = &(htim2.Instance->CCR2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
//	TestMotor(&Motor2, acceleration);
	Test2Motor(&Motor1, &Motor2, 120);

// ���� ������� ����
	DC_Motor Motor3 = {0};
	Motor3.PinIn1 = M3_IN1_Pin;
	Motor3.PinIn2 = M3_IN2_Pin;
	Motor3.PortIn1 = M3_IN1_GPIO_Port;
	Motor3.PortIn2 = M3_IN2_GPIO_Port;
	Motor3.StbyPin = STBY_M3_M4_Pin;
	Motor3.StbyPort = STBY_M3_M4_GPIO_Port;
	Motor3.pwm_register_ptr = &(htim2.Instance->CCR3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

	DC_Motor Motor4 = {0};
	Motor4.PinIn1 = M4_IN1_Pin;
	Motor4.PinIn2 = M4_IN2_Pin;
	Motor4.PortIn1 = M4_IN1_GPIO_Port;
	Motor4.PortIn2 = M4_IN2_GPIO_Port;
	Motor4.StbyPin = STBY_M3_M4_Pin;
	Motor4.StbyPort = STBY_M3_M4_GPIO_Port;
	Motor4.pwm_register_ptr = &(htim2.Instance->CCR4);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);

	Test2Motor(&Motor3, &Motor4, 120);
	TestMotor(&Motor3, 120);
	while(1){

	}
}

// �������� ������� ������ ���������
//������� ��������� �� ���� �������� �� ��������� ���������
// ��������� ��������� � ���� ������� �� � ���������
// ����� �� -� � �������� �������.
void TestMotor(DC_Motor *Motor, int8_t acceleration){
	for(int8_t i = 0; i< (acceleration+1); i+=1){
		DC_Control(Motor, i);
		HAL_Delay(5);
	}
	HAL_Delay(1000);
	for(int8_t i = (acceleration+1); i> -acceleration ; i-=1){
		DC_Control(Motor, i);
		HAL_Delay(5);
	}
	HAL_Delay(1000);
	for(int8_t i = -acceleration-1; i<0; i+=1){
		DC_Control(Motor, i);
		HAL_Delay(5);
	}
}

// ��������� ������ ���� ������� �����, ������ ���� �� ������ (���������)
void Test2Motor(DC_Motor *Motor1, DC_Motor *Motor2, int8_t acceleration){
	for(int8_t i = 0; i< (acceleration+1); i+=1){
		DC_Control(Motor1, i);
		DC_Control(Motor2, i);
		HAL_Delay(5);
	}
	HAL_Delay(1000);
	for(int8_t i = (acceleration+1); i> -acceleration ; i-=1){
		DC_Control(Motor1, i);
		DC_Control(Motor2, i);
		HAL_Delay(5);
	}
	HAL_Delay(1000);
	for(int8_t i = -acceleration-1; i<0; i+=1){
		DC_Control(Motor1, i);
		DC_Control(Motor2, i);
		HAL_Delay(5);
	}
}
