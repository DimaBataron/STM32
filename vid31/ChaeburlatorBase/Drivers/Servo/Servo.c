/*
 * Servo.c
 *
 *  Created on: Apr 17, 2025
 *      Author: dima
 */


#include "Servo.h"

/*
 * Каждый канал соответствует серве. Может испольовать символьные имена?
 */

/*
 * Функция стартовой инициализации таймера управляющего сервомашинкой
 * На вход адрес структуры используемого таймера и номер канала.
 * Остальные функции настраиваются автоматически функциями HAL.
 *
 * - устанавливает в 0 положение сервы.
 * - включает серву.
 */

void ServoStartInit(TIM_HandleTypeDef *htim, uint32_t Channel){
	switch (Channel){
		case TIM_CHANNEL_1 : {
			htim->Instance->CCR1 = SERV_ZERO;
		}
		case TIM_CHANNEL_2 : {
			htim->Instance->CCR2 = SERV_ZERO;
		}
		case TIM_CHANNEL_3 : {
			htim->Instance->CCR3 = SERV_ZERO;
		}
		case TIM_CHANNEL_4 : {
			htim->Instance->CCR4 = SERV_ZERO;
		}
	}
	HAL_TIM_PWM_Start(htim, Channel);
}

/*
 * Функция поворачивает сервомашинку. Принимает на вход :
 * 	- адрес структуры сервомашины
 * 	- номер канала.
 *  - угол поворота
 */

void SteeringWheel(TIM_HandleTypeDef *htim, uint32_t Channel, float angle){
	static 	float RotAngle = 1.4111;
	int8_t TurnNum;
	int32_t ServoNumber = SERV_ZERO;

	TurnNum = (int8_t)(angle * RotAngle);
	ServoNumber = SERV_ZERO+(TurnNum*SERV_PITCH);

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
* The function rotates the servo, accepting the +/-127 command as input without any transformations.
* Accepts as input:
* - servo structure address
* - channel number
* - control command.
 *
 */
void ServRot(TIM_HandleTypeDef *htim, uint32_t Channel, int8_t TurnNum){
	int32_t ServoNumber = SERV_ZERO;
	ServoNumber = SERV_ZERO+(TurnNum*SERV_PITCH);
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
 *  Функция возвращает значение на которое можно повернуть серву этим значением
 *  Принимает на вход управляющую команду
 *  Возвращает угол float
 *  127 =90%
 *  -127 = -90%
 */
float RotAngl(int8_t TurnNum){
	return (float)TurnNum / 1.4111f;
}


/*
 * Поворачивается только на 90 градусов 45 в одну сторону 45 во вторую. Сделать цифры как в видео.
 * Или умножить все коэффициенты на 2. В любом случае надо переписать функцию.
 */
