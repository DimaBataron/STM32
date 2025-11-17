/*
 * ADCStick.c
 *
 *  Created on: Apr 20, 2024
 *      Author: dima
 *
 *
 */

#ifndef ADC_STICK_ADCSTICK_C_
#define ADC_STICK_ADCSTICK_C_

#include "ADCStick.h"

// считанные значения
uint32_t Adc1Value[5];

// Нулевое, начальное положение стика.
uint32_t Adc1Null[4];

//вычисленное значение отклонения.
int8_t Adc1Calc[4];

// Переменная количества преобразований в сукунду.
int32_t ConvPerSec = 0;

// вычисление заряда акума.
float BattCrarg = 0;

void InitADCStick(ADC_HandleTypeDef* hadc){
	  HAL_ADCEx_Calibration_Start(hadc);
	  StickCal(Adc1Value,hadc,Adc1Null);
}

//This function sets the neutral position of the sticks
void StickCal(uint32_t* Adc1Value,ADC_HandleTypeDef* hadc, uint32_t* Adc1Null) {
	HAL_ADC_Start_DMA(hadc, Adc1Value, 5);
	HAL_NVIC_DisableIRQ(DMA1_Channel1_IRQn);
	HAL_Delay(100);

	Adc1Null[0] = Adc1Value[0] ;
	Adc1Null[1] = Adc1Value[1] ;
	Adc1Null[2] = Adc1Value[2] ;
	Adc1Null[3] = Adc1Value[3] ;
	HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

//The procedure calculates the values ​​that will be sent
//The function calculates the current value to which the potentiometer is turned.
void StickCalc(uint32_t* Adc1Value,ADC_HandleTypeDef* hadc, uint32_t* Adc1Null){
		static int32_t AdcSqr[4];
		static int32_t i=0;
		HAL_ADC_Start_DMA(hadc, Adc1Value, 5);

		if(i>150){
			// add here the use of calibration coefficients.
			Adc1Calc[0] = (int8_t)(AdcSqr[0]/i);
			Adc1Calc[1] = (int8_t)(AdcSqr[1]/i);
			Adc1Calc[2] = (int8_t)(AdcSqr[2]/i);
			Adc1Calc[3] = (int8_t)(AdcSqr[3]/i);
			i=0;
			AdcSqr[0] = 0;
			AdcSqr[1] = 0;
			AdcSqr[2] = 0;
			AdcSqr[3] = 0;
		}
		i++;

		AdcSqr[0] += ((int32_t)(Adc1Value[0] - Adc1Null[0]) >> 3);
		AdcSqr[1] += ((int32_t)(Adc1Value[1] - Adc1Null[1]) >> 3);
		AdcSqr[2] += ((int32_t)(Adc1Value[2] - Adc1Null[2]) >> 3);
		AdcSqr[3] += ((int32_t)(Adc1Value[3] - Adc1Null[3]) >> 3);
		ConvPerSec ++;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	//calculate potentiometer position
	StickCalc(Adc1Value, hadc, Adc1Null);
}

// returns the calculated battery percentage
float BattCharge(uint32_t Adc1Value){
	return ((float)(Adc1Value-2761)/(float)11.98);
}
// frame buffer formation
void BufFormCharge(){
//	char AsciiSymb[4];
//	sprintf(AsciiSymb, "%3d",(int)BattCharge(Adc1Value[4]));
	disp1color_printf(1, 0, FONTID_6X8M, "BatCharge: %d %%",(uint32_t)BattCharge(Adc1Value[4]));
}

//frame buffer stick formation
void BufFormStick(){
	disp1color_printf(1, 18, FONTID_6X8M, "StickA A1:%d ",Adc1Calc[0]);
	disp1color_printf(80, 18, FONTID_6X8M, " A2:%d ",Adc1Calc[1]);

	disp1color_printf(1, 34, FONTID_6X8M, "StickB B1:%d ",Adc1Calc[3]);
	disp1color_printf(80, 34, FONTID_6X8M, " B2:%d ",Adc1Calc[2]);
}

// Функция вызывается по прерываниям от RTC выводик количество преобразований АЦП в секунду.
void BufFormNumbConv(){
	disp1color_printf(1, 50, FONTID_6X8M, "Convers :%d ",ConvPerSec);
	ConvPerSec = 0;
}

#endif /* ADC_STICK_ADCSTICK_C_ */
