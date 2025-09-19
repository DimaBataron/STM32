/*
 * ADC_LoadCell.c
 *
 *  Created on: Aug 22, 2025
 *      Author: dima
 */

#include "ADC_LoadCell.h"




// ������ ���������� ��������������
uint16_t AdcConvBuf[ADC_BUFFER_SIZE];


// ���������� ���������� �������� ��������� �������� ��� ������ � UART?


// ��������� ��������� �������������� ��������� DMA.
void StartMeasure(){
	// 1. ��������� ��� � ������ DMA ��� ����� ADC_BUFFER_SIZE? ��������.
	    // ������� HAL_ADC_Start_DMA() ��������� ����������� ��������������,
	    // � DMA �������� ��������� �����.
	    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)AdcConvBuf, ADC_BUFFER_SIZE);

}

// ���������� ����������� ����������
//U =  (result/4096)*3,3 = result * 0.0008057
// �� ����� ��� ���������� ��������� �����.
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

// ������� �������� ����������� ��������, �� �� �� ����� �� ��� �� �������


// ������� ��������� ������ ������������ ������
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	BaseType_t xHigherPriorityTaskWoken;
  if(hadc->Instance == ADC1)
  {
    // �����: ������������� ��� � DMA, ����� ��� �� ������
    // �������������� ��� ����� �� ��������� ������� ������.
    // �� �������� �� ����� � �������� �����, ����� ����� ������.
    HAL_ADC_Stop_DMA(&hadc1); // ���� �� ���?

    // ��� ������� ������.
    xSemaphoreGiveFromISR(SemDMA_VoltMeasHandle,&xHigherPriorityTaskWoken);
  }
}
