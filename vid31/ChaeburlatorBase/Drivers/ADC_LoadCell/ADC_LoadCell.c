/*
 * ADC_LoadCell.c
 *
 *  Created on: Aug 22, 2025
 *      Author: dima
 */

#include "ADC_LoadCell.h"




// array containing ADC conversions
uint16_t AdcConvBuf[ADC_BUFFER_SIZE];


// переменная содержащая итоговый результат служащая для вывода в UART?

/*
* The procedure starts conversions using DMA.
* Starts the ADC in DMA mode to collect ADC_BUFFER_SIZE? values.
* The HAL_ADC_Start_DMA() function starts continuous conversion,
* and the DMA begins filling the buffer.
 */
//
void StartMeasure(ADC_HandleTypeDef* hadc1){

	    HAL_ADC_Start_DMA(hadc1, (uint32_t*)AdcConvBuf, ADC_BUFFER_SIZE);

}

// calculating the resulting voltage
//U =  (result/4096)*3,3 = result * 0.0008057
float VoltageCalc(){
	uint32_t SumMas = 0;
	float U = 0;
	for(uint32_t i = 0; i < ADC_BUFFER_SIZE; i++){
		SumMas += AdcConvBuf[i];
	}
	U = ((float)SumMas)/((float)ADC_BUFFER_SIZE);
	U *=  0.002417f;
	return U;
}



// функция обратного вызова разблокирует задачу
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc1)
{
	BaseType_t xHigherPriorityTaskWoken;
  if(hadc1->Instance == ADC1)
  {
    // ВАЖНО: Останавливаем АЦП и DMA, чтобы они не начали
    // перезаписывать наш буфер со следующей порцией данных.
    // Мы запустим их снова в основном цикле, когда будем готовы.
    HAL_ADC_Stop_DMA(hadc1); // надо ли это?

    // даю семафор задаче.
    xSemaphoreGiveFromISR(SemDMA_VoltMeasHandle,&xHigherPriorityTaskWoken);
  }
}
