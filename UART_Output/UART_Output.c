/*
 * UART_Output.c
 *
 *  Created on: Aug 17, 2025
 *      Author: dima
 */
#include "UART_Outpt.h"


// ������� �������� ������ ��������� ��� ����� ������� ����������� ��������
// ���������� ��������� � ������� ����������� ��������� �� ���������� ������ �
// ��� ������. ( ��� ���� ��� ������� ������ � UART)
// �� ������ ����������� ������ ����� ������������� ���� ���������.
// ����� ���������� ������������.

MemAllocData TransArrayLayout(){
	MemAllocData OllMass = {0};
	MemAllocData Acceler = {0};
	MemAllocData Steer = {0};
	MemAllocData CamH = {0};
	MemAllocData CamV = {0};
	MemAllocData Lights = {0};
	MemAllocData Lo1 = {0};
	MemAllocData Lo2 = {0};
	uint16_t Len	= 0;


// ��������� ��� ������ � ���������� ������
// ������ ����� ��� ������ ����� ���� ������.
// ����� �� ������� ������, ��� ������ ����� ����� ��������, ��� �������� ������.
	Acceler = MemReqString("Acceler = %d \r\n", Acceleration);
	Steer	= MemReqString("Steer   = %d \r\n", SteerTurn);
	CamH	= MemReqString("CamHoriz= %d \r\n", CamHorizont);
	CamV	= MemReqString("CamVert = %d \r\n", CamVertical);
	Lights	= MemReqString("Lights  = %d \r\n", HeadLights);
	Lo1		= MemReqString("Load1   = %d \r\n", Load1);
	Lo2		= MemReqString("Load2   = %d \r\n", Load2);

	// �������� ������ ���� ��������
	OllMass.Quantity = Acceler.Quantity + Steer.Quantity + CamH.Quantity + \
			CamV.Quantity + Lights.Quantity + Lo1.Quantity + Lo2.Quantity;
	OllMass.StrSymb = (char*) pvPortMalloc((OllMass.Quantity * sizeof(char))+1);

	//������ ��������� ��� ������ � ���� ������� ������.
	if(OllMass.StrSymb != NULL){
		Len += MemCpyStr(OllMass.StrSymb + Len, Acceler.StrSymb, Acceler.Quantity);
		Len += MemCpyStr(OllMass.StrSymb + Len, Steer.StrSymb, Steer.Quantity);
		Len += MemCpyStr(OllMass.StrSymb + Len, CamH.StrSymb, CamH.Quantity);
		Len += MemCpyStr(OllMass.StrSymb + Len, CamV.StrSymb, CamV.Quantity);
		Len += MemCpyStr(OllMass.StrSymb + Len, Lights.StrSymb, Lights.Quantity);
		Len	+= MemCpyStr(OllMass.StrSymb + Len, Lo1.StrSymb, Lo1.Quantity);
		Len += MemCpyStr(OllMass.StrSymb + Len, Lo2.StrSymb, Lo2.Quantity);
	}
	else while(1){

	}
	vPortFree(OllMass.StrSymb);
	// ����� �������.
	HAL_UART_Transmit(&huart1, (uint8_t*)OllMass.StrSymb, OllMass.Quantity, HAL_MAX_DELAY);
	// ���������� ���������� ������.
//	vPortFree(OllMass.StrSymb);
	return OllMass;
}

//extern int8_t Acceleration 	= 0;
//extern int8_t SteerTurn 	= 0;
//extern int8_t CamHorizont 	= 0;
//extern int8_t CamVertical	= 0;
//extern int8_t HeadLights	= 0;
//extern int8_t Load1			= 0;
//extern int8_t Load2			= 0;
//extern int8_t CamHome		= 0;
// ������� ��������� ������ � ���������, ����������� ������
// ����� ���������� ��������� �� ���������� ������ � ���������� �������� �
// ���������� ���������� �������� ��� \0 (������� ����� ������)
MemAllocData MemReqString(const char *Str, int8_t DataOutput){
	MemAllocData TempMass = {0};
	TempMass.Quantity = strlen(Str) + ADDIT_SYMB_REQUIR;
	// ��������� ������
	TempMass.StrSymb = (char*) pvPortMalloc(TempMass.Quantity * sizeof(char));

	//������ � ���������� ������ ���������� ������
	sprintf(TempMass.StrSymb, Str, DataOutput );
	return TempMass;
}

// �������� ���� ������ � ������.
// ���������� ���������� ���������� ��������
// ����������� ���������� ������
uint16_t MemCpyStr(char *Purpose, char *Source, uint16_t Len){
	memcpy(Purpose, Source, Len);
	//����������� ��������
	vPortFree(Source);
	return Len;
}
////������� ������ ������� ��������� Idle, ����� �������� �� DMA.
//void DataOutputUart(UART_HandleTypeDef *huart, uint8_t *uart_buf, uint16_t Size, uint32_t Timeout){
//
//}

// 20 ���� ������ ������ 7 �����.  7*20 = 140 ���� ������ � ������������ ���������.
void OutStringTask(){
	static char Mas[160];
	uint16_t LenStr = 0;
	LenStr += sprintf(Mas+LenStr,"Acceler = %d \r\n", Acceleration);
	LenStr += sprintf(Mas+LenStr,"Steer   = %d \r\n", SteerTurn);
	LenStr += sprintf(Mas+LenStr,"CamHoriz= %d \r\n", CamHorizont);
	LenStr += sprintf(Mas+LenStr,"CamVert = %d \r\n", CamVertical);
	LenStr += sprintf(Mas+LenStr,"Lights  = %d \r\n", HeadLights);
	LenStr += sprintf(Mas+LenStr,"Load1   = %d \r\n", Load1);
	LenStr += sprintf(Mas+LenStr,"Load2   = %d \r\n", Load2);
	LenStr += sprintf(Mas+LenStr,"RxPack  = %d \r\n", OutputNumSuccessPack);
	LenStr += sprintf(Mas+LenStr,"================\r\n");
//	HAL_UART_Transmit(&huart1, (uint8_t*)Mas, 140, HAL_MAX_DELAY);
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*)Mas, LenStr+1);

}

// ��������� � ��� ���������� ����� �������� ������� � UART ��������� DMA
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	// ������� ����� ������� �������� ����
	if (huart->Instance == USART1){
		BaseType_t xHigherPriorityTaskWoken;
		xSemaphoreGiveFromISR(SemDMA_UARTHandle,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
}

