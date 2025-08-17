/*
 * ChaeburatorIT_Proc.c
 *
 *  Created on: Aug 15, 2025
 *      Author: dima
 */


#include "ChaeburatorIT_Proc.h"



int8_t Acceleration = 0;
int8_t SteerTurn 	= 0;
int8_t CamHorizont 	= 0;
int8_t CamVertical	= 0;
int8_t HeadLights	= 0;
int8_t Load1		= 0;
int8_t Load2		= 0;
int8_t CamHome		= 0;

// ��������� ���� ��� ���������� ��� ������ ������ ������.
// ��������� ������ ������� ��������� DMA
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
//	IT_GPIO_Handl(GPIO_Pin);
	if(GPIO_Pin == DIO0_Pin){
//		RxContLoRaCmpl(ComArr1,&hspi1);
		BaseType_t xHigherPriorityTaskWoken;
		xSemaphoreGiveFromISR(SemDMA_LoRaHandle,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
//		RxContLoRaCmplV2(&hspi1);
		RxContLoRaCmpl(ComArr1, &hspi1);
	}

}

// ���� ��������� ����� DMA ������� �������� ������� �� ������.
// DMA ���� ������� � ������ RxContLoRaCmplV2 �� ����������
//void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	// ���� ������� ����� ������ ���� �������� �� ������
//	// ���� ������� ��������� ����������� ������
//	if(hspi == &hspi1){
//		BaseType_t xHigherPriorityTaskWoken;
//		xSemaphoreGiveFromISR(SemDMA_LoRaHandle,&xHigherPriorityTaskWoken);
//		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
//
//	}
//}

//����� ������ RxContLoRaCmplV2 � ������� ComArr1 ����������� �������
//������� ��������� ������� ������� ����� ����� ������������ �������� ��� ���������� ���������.
void CalcRxCommands(){
	static int32_t BufComArr1;

	BufComArr1 = (int32_t) ComArr1[ACCELER];
	CheckRange(&BufComArr1, &Acceleration);

	BufComArr1 = (int32_t)((int8_t)ComArr1[STEER_TURN] + (int8_t)ComArr1[STEER_TRIM]);
	CheckRange(&BufComArr1, &SteerTurn);

	BufComArr1 = (int32_t)((int8_t)ComArr1[CAM_HORIZONT] + (int8_t)ComArr1[CAM_TRIM_HORIZ]);
	CheckRange(&BufComArr1, &CamHorizont);

	BufComArr1 = (int32_t)((int8_t)ComArr1[CAM_VERTICAL] + (int8_t)ComArr1[CAM_TRIM_VERT]);
	CheckRange(&BufComArr1, &CamVertical);

	HeadLights = (int8_t)ComArr1[HEADLIGHTS];
	Load1 = (int8_t)ComArr1[LOAD1];
	Load2 = (int8_t)ComArr1[LOAD2];
	CamHome = (int8_t)ComArr1[CAM_HOME];


}

//������� �������� ������������ ���������� (int8_t)
// BufComArr1 ����������� ��������
// Command ������������ ��������.
void CheckRange(int32_t *BufComArr1, int8_t *Command){
	int32_t value = *BufComArr1;
	if(value > 127){
		*Command = 127;
	}
	else {
		if(value < -128){
			*Command = -128;
		}
		else *Command = (int8_t)value;
	}
}

