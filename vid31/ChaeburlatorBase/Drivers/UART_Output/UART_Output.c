/*
 * UART_Output.c
 *
 *  Created on: Aug 17, 2025
 *      Author: dima
 */
#include "UART_Outpt.h"
#include "Servo.h"

// Функция выделяет память полностью для всего массива подлежащего передаче
// возвращает структуру в которой содержиться указатель на выделенную память и
// его длинна. ( это надо для функция вывода в UART)
// Не забыть освобождать память после использования этой процедуры.
// иначе произойдет переполнение.

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


// Записываю все строки в выделенную память
// Теперь видно что строки имеют одну длинну.
// можно не считать теперь, все данные можно сразу записать, мне известна длинна.
	Acceler = MemReqString("Acceler = %d \r\n", Acceleration);
	Steer	= MemReqString("Steer   = %d \r\n", SteerTurn);
	CamH	= MemReqString("CamHoriz= %d \r\n", CamHorizont);
	CamV	= MemReqString("CamVert = %d \r\n", CamVertical);
	Lights	= MemReqString("Lights  = %d \r\n", HeadLights);
	Lo1		= MemReqString("Load1   = %d \r\n", Load1);
	Lo2		= MemReqString("Load2   = %d \r\n", Load2);

	// вычисляю длинну всех массивов
	OllMass.Quantity = Acceler.Quantity + Steer.Quantity + CamH.Quantity + \
			CamV.Quantity + Lights.Quantity + Lo1.Quantity + Lo2.Quantity;
	OllMass.StrSymb = (char*) pvPortMalloc((OllMass.Quantity * sizeof(char))+1);

	//теперь записываю все строки в один большой массив.
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
	// Вывод массива.
	HAL_UART_Transmit(&huart1, (uint8_t*)OllMass.StrSymb, OllMass.Quantity, HAL_MAX_DELAY);
	// освобождаю выделенный массив.
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
// Функция принимает строку и параметры, запрашивает память
// после возвращает указатель на выделенную память с записанным массивом и
// количество записанных символов без \0 (признак конца строки)
MemAllocData MemReqString(const char *Str, int8_t DataOutput){
	MemAllocData TempMass = {0};
	TempMass.Quantity = strlen(Str) + ADDIT_SYMB_REQUIR;
	// выделение памяти
	TempMass.StrSymb = (char*) pvPortMalloc(TempMass.Quantity * sizeof(char));

	//Запись в выделенную память переданной строки
	sprintf(TempMass.StrSymb, Str, DataOutput );
	return TempMass;
}

// копирует один массив в другой.
// возвращает количество записанных символов
// освобождает выделенную память
uint16_t MemCpyStr(char *Purpose, char *Source, uint16_t Len){
	memcpy(Purpose, Source, Len);
	//Освобождает источник
	vPortFree(Source);
	return Len;
}
////Функция вывода массива используя Idle, после заменить на DMA.
//void DataOutputUart(UART_HandleTypeDef *huart, uint8_t *uart_buf, uint16_t Size, uint32_t Timeout){
//
//}

// 20 Байт каждая строка 7 строк.  7*20 = 140 байт вместе с управляющими символами.
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

void OutDataRxLoRa(UART_HandleTypeDef *huart){
	static char Mas[75];
	uint16_t LenStr = 0;
	if(huart->gState == HAL_UART_STATE_READY){
		LenStr += sprintf(Mas+LenStr,"Acceler = %d \r\n", Acceleration);
		LenStr += sprintf(Mas+LenStr,"Steer   = %d \r\n", SteerTurn);
		LenStr += sprintf(Mas+LenStr,"CamHoriz= %d \r\n", CamHorizont);
		LenStr += sprintf(Mas+LenStr,"CamVert = %d \r\n", CamVertical);
		HAL_UART_Transmit(huart, (uint8_t*)Mas, 75, HAL_MAX_DELAY);
	}
}

/*
 * Функция выводит угол поворота сервы в консоль.
 * (использую в команде Out 2 терминала).
 * Сделал чтоб выводила каждую секунду.
 */

void OurServRotPerc(UART_HandleTypeDef *huart){
	static char Mas[50];
	uint16_t LenStr = 0;
	float RotA;
	if(huart->gState == HAL_UART_STATE_READY){
		RotA =  RotAngl(SteerTurn);
		LenStr = sprintf(Mas,"SteeringWheel = %.1f \r\n", RotA);
		RotA = RotAngl(CamVertical);
		LenStr+= sprintf( Mas + LenStr,"CamVert  = %.1f \r\n", RotA);
		HAL_UART_Transmit(huart, (uint8_t*)Mas, LenStr+1, HAL_MAX_DELAY);
	}
}

/*
 * Функция вывода количества принятых пакетов.
 */
void NumRxPack(UART_HandleTypeDef *huart){
	static char Mas[19];
	if(huart->gState == HAL_UART_STATE_READY){
		sprintf(Mas,"Pac Sec: = %d \r\n", (int)NumSuccessPack);
		NumSuccessPack = 0;
		HAL_UART_Transmit(huart, (uint8_t*)Mas, 19, HAL_MAX_DELAY);
	}
}

/*
 * Функция выводит измеренное напряжение.
 */
void OutMeasVal(UART_HandleTypeDef *huart){
	static char Mas[21];
	uint16_t LenStr = 0;
	if(huart->gState == HAL_UART_STATE_READY){
		LenStr = sprintf(Mas,"Bat U = %.2f V \r\n", Volt);
		HAL_UART_Transmit(huart, (uint8_t*)Mas, LenStr+1, HAL_MAX_DELAY);
	}
}

//// Переходит в это прерывание после отправки массива в UART используя DMA
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
//	// перешли после удачной передачи сюда
//	if (huart->Instance == USART1){
//		BaseType_t xHigherPriorityTaskWoken;
//		xSemaphoreGiveFromISR(SemDMA_UARTHandle,&xHigherPriorityTaskWoken);
//		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
//	}
//}

