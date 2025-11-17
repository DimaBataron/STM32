/*
 * BrushedDC.h
 *
 *  Created on: Aug 10, 2025
 *      Author: dima
 */

#ifndef BRUSHEDDC_BRUSHEDDC_H_
#define BRUSHEDDC_BRUSHEDDC_H_

#include "main.h"
// Направление вращения по часовой стрелке
#define DirectRotCW 1

// Направление вращения против часовой стрелки
#define	DirectRotCCW 2

// Мертвая зона
#define DeadZone 3

// 7199/127 = 56.68 на единицу (процентов?) 127 максимальное число которое можно приянть
// с пульта
#define MotorStep 56.68

// Структура описания двигателя.
typedef struct {
	uint16_t PinIn1; //  пин направления вращения 1
	uint16_t PinIn2; // пин направления вращения 2
	uint16_t StbyPin;

	GPIO_TypeDef * PortIn1;
	GPIO_TypeDef * PortIn2;
	GPIO_TypeDef * StbyPort;
	volatile uint32_t *pwm_register_ptr; // адрес регистра шим этого двигателя

} DC_Motor;

/*
 * Функция управляет одновременно двумя двигателями.
 * Функция управляет контроллером щеточных двигателей
 * TB6612FNG в зависимости от принятых команд
 * устанавливает коэффициент заполнения ШИМ.
 * На вход принимает направление вращения,
 * число принятое с пульта, указывающее на желаемую
 * скорость, указатель на структутуру таймера.
 *
 * */

void Brushed2DC_Control(TIM_HandleTypeDef *htim1,uint32_t Channnel1, \
		uint32_t Channel2, int8_t acceleration, uint32_t DirectRot1, \
		uint32_t DirectRot2);
/*
 * Управление одним двигателем.
 *
 * */
void Brushed1DC_Control(TIM_HandleTypeDef *htim1,uint32_t Channel, int8_t acceleration);


void DC_Control(DC_Motor *Motor, int8_t acceleration);

// тормоз двигателем
void EngineBrake(uint32_t Channel);

void Engine_Control(int8_t acceleration, DC_Motor *Motor1, DC_Motor *Motor2);

int8_t AccelerationIncr(int16_t tmp);

void Engine1_Control(int8_t acceleration, DC_Motor *Motor1);


#endif /* BRUSHEDDC_BRUSHEDDC_H_ */
