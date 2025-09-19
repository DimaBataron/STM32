/*
 * ADC_LoadCell.c
 *
 *  Created on: Aug 22, 2025
 *      Author: dima
 */

#include "ADC_LoadCell.h"




// массив содержащий преобразования
uint16_t AdcConvBuf[ADC_BUFFER_SIZE];


// переменная содержащая итоговый результат служащая для вывода в UART?


// процедура запускает преобразования используя DMA.
void StartMeasure(){
	// 1. Запускаем АЦП в режиме DMA для сбора ADC_BUFFER_SIZE? значений.
	    // Функция HAL_ADC_Start_DMA() запускает непрерывное преобразование,
	    // и DMA начинает заполнять буфер.
	    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)AdcConvBuf, ADC_BUFFER_SIZE);

}

// вычисление полученного напряжения
//U =  (result/4096)*3,3 = result * 0.0008057
// На входе АЦП напряжение вычисляет точно.
float VoltageCalc(){
	uint32_t SumMas = 0;
	float U = 0;
	for(uint32_t i = 0; i < ADC_BUFFER_SIZE; i++){
		SumMas += AdcConvBuf[i];
	}
	U = ((float)SumMas)/((float)ADC_BUFFER_SIZE);
	U *= 0.0008057f;
	return U;
}

// Функция проверки вычисленных значений, на то не вышли ли они за пределы


// функция обратного вызова разблокирует задачу
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	BaseType_t xHigherPriorityTaskWoken;
  if(hadc->Instance == ADC1)
  {
    // ВАЖНО: Останавливаем АЦП и DMA, чтобы они не начали
    // перезаписывать наш буфер со следующей порцией данных.
    // Мы запустим их снова в основном цикле, когда будем готовы.
    HAL_ADC_Stop_DMA(&hadc1); // надо ли это?

    // даю семафор задаче.
    xSemaphoreGiveFromISR(SemDMA_VoltMeasHandle,&xHigherPriorityTaskWoken);
  }
}
