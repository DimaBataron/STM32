/*
 * PalenishIT_Proc.c
 *
* Created on: Mar 27, 2025
* Author: dima
*
*
* 	- buttons are used for control (Down, Up, Select, Left, Right, Apply, Exit)
* 	Left (139), Right (141), Up (130), Down (150), Select (140), Exit (129)
* 	Start Transmission (131)
* 	Select LoRa initialization settings. (149)
* 	Start Stop Calibration 155
*
*
 	KEY_STEER_TRIM_P 		129
	KEY_STEER_TRIM_N		139
	KEY_CAM_TRIM_HORIZ_P	130
	KEY_CAM_TRIM_HORIZ_N	140
	KEY_CAM_TRIM_VERT_P		131
	KEY_CAM_TRIM_VERT_N		141
	KEY_HEADLIGHTS			149
	KEY_LOAD1				135
	KEY_LOAD2				145
	KEY_CAM_HOME			154
*
*
* - in addition to the keys pressed, the position of the pointer on the page is also required.
* Current
*
* The menu is divided into pages, each with its own field.
*
* Page 0 displays the greeting.
* Page 1 displays the ADC values ​​and the number of conversions per second.
* Pages 2-3 Display the transmission parameter settings menu.
* Page 4 Displays the ADC values ​​and the number of packets sent per second. * (this is after pressing start)
* Page 5 to display calibration values.
 */
#include "PalenishIT_Proc.h"
#include "ProgMem.h"
// You can add pages here
#define TotalPages 5


PositionMenuStruct MenuStructOld = {0};
CalibrStruct CalibrValues;
//PositionMenuStruct Old;
uint32_t NumberOfPackets = 0;

//Вычисленные команды
int16_t SteerTrim 		= 0;
int16_t CamTrimHoriz	= 0;
int16_t	CamTrimVert	 	= 0;
int16_t Headlights		= 0;
int16_t Load1			= 0;
int16_t	Load2			= 0;
int16_t CamHome			= 0;


/*
* This function handles two types of interrupts. If the interrupts are from:
* - the keyboard, it then runs the menu handler PressHandl(MassPressKey, &MenuStructOld)
* and, depending on the pressed button and the previous state, either switches the
* system to a new state or changes the command variable.
*
* - the LoRa radio module. A new command array is generated, taking into account
* the coefficients. A command buffer is generated for transmission.
* Transmission is started.
 */
HAL_StatusTypeDef IT_GPIO_Handl(uint16_t GPIO_Pin){
	// Interrupt from keyboard.
	if(GPIO_Pin == INT_TCA_Pin){
		  if(HAL_ERROR != ReadFIFO(&hi2c1)){

			#ifdef Palenish_Test
			  // the test function displays the pressed keys on the screen.
			  PrintSymbASCII(MassPressKey);
			#endif

			  PressHandl(MassPressKey, &MenuStructOld);
			  MenuHandl(&MenuStructOld);
		  }
	}
	else{
		// interrupt from LoRa
		if((&MenuStructOld)->PressStart == 1){
			FormArrComm();
			TxArrWriteFiFo((uint8_t)FIFOAdrComArr1, ComArr1, NumberCommands);
			StartTxLoRa();
			NumberOfPackets ++;
		}

	}
	return HAL_OK;
}

// Jumps from the GPIO interrupt handler.
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	IT_GPIO_Handl(GPIO_Pin);
}

// Функция первоначальной инициализации, инициализирует структуру, проверить
HAL_StatusTypeDef MenuInit(){
	// для тестов вывожу сразу какуюто из страниц.
	MenuStructOld.Page = 0;
	MenuStructOld.PositionMarker = 0;
	MenuStructOld.PressKey = 0;
	MenuStructOld.NestMenuItem = 0;
	MenuStructOld.PressSelectLoraInit = 0; // Настройки LoRa.
	MenuStructOld.PressStart = 0;
	MenuStructOld.NestPressDown = 0;
	MenuStructOld.NestPressUP = 0;
	return HAL_OK;
}
// Обрабатывает все нажатия из массива. Формирует структуру. Которую позже
// используют обработчики.
// Обработчик меню вызывает и передает в функцию нужные параметры для ее работы.
HAL_StatusTypeDef PressHandl(uint8_t *MassPressKey, PositionMenuStruct *MenuStructOld){
	uint32_t i = 0;
	// Отключает прерывания от выводов GPIO
	//Внимание отключатся и от схемы LoRa (DIO0)
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
	do{
		if(MassPressKey[i]==0){
			break;
		}
		NewPressState(MassPressKey[i], MenuStructOld);
		if(MenuStructOld->PressStart == 1){
			// if the transmission is running, searches for pressed control keys.
			PressContrKeys(MassPressKey[i]);
		}
		i++;
	}
	while(i<10);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	return HAL_OK;
}

// Ищет нажатые клавиши управления записывает их в массив комманд.
void PressContrKeys(uint8_t MassPressKey){
	static int8_t TrimStep = 3;
	switch(MassPressKey){
	case KEY_STEER_TRIM_P : {
		SteerTrim += TrimStep;
		if(SteerTrim > 127) SteerTrim = 127;
		break;
	}
	case KEY_STEER_TRIM_N : {
		SteerTrim -= TrimStep;
		if(SteerTrim < -128) SteerTrim = -128;
		break;
	}
	case KEY_CAM_TRIM_HORIZ_P : {
		CamTrimHoriz += TrimStep;
		if(CamTrimHoriz >127) CamTrimHoriz = 127;
		break;
	}
	case KEY_CAM_TRIM_HORIZ_N : {
		CamTrimHoriz -= TrimStep;
		if(CamTrimHoriz < -128) CamTrimHoriz = -128;
		break;
	}
	case KEY_CAM_TRIM_VERT_P : {
		CamTrimVert += TrimStep;
		if(CamTrimVert > 127) CamTrimVert = 127;
		break;
	}
	case KEY_CAM_TRIM_VERT_N : {
		CamTrimVert -= TrimStep;
		if(CamTrimVert < -128) CamTrimVert = -128;
		break;
	}
	case KEY_HEADLIGHTS : {
		if(Headlights == 1){
			Headlights = 0;
		}
		else Headlights = 1;
		break;
	}
	case KEY_LOAD1 : {
		if(Load1 == 0) Load1 = 1;
		else Load1 = 0;
		break;
	}
	case KEY_LOAD2 : {
		if(Load2 == 0) Load2 = 1;
		else Load2 = 0;
		break;
	}
	case KEY_CAM_HOME : {
		if(CamHome == 0) CamHome = 1;
		else CamHome = 0;
	}

	}
}

// обновляет структуру в зависимости от текущего нажатия.
void NewPressState(uint8_t MassPressKey, PositionMenuStruct *MenuStructOld){
	// если была нажата кнопка то keypad выглядит по другому совсем.
	if(MenuStructOld->PressStart == 1){
		switch(MassPressKey){
			case 152 : {
				MenuStructOld->PressStart = 0;
				MenuStructOld->Page = 1;
				MenuStructOld->NestMenuItem = 0;
				MenuStructOld->PositionMarker = 0;
				MenuStructOld->CalibrStartStop = 0;
				break;
			}
		}
	}
	else{

		if(MassPressKey == 149){ // Кнопка настроек LoRa
			MenuStructOld->PressSelectLoraInit = 1;
			MenuStructOld->PressKey = 0;
			MenuStructOld->PressStart = 0;
			MenuStructOld->CalibrStartStop = 0;
			if(MenuStructOld->Page !=2 ){
				MenuStructOld->Page =2;
			}
			else {
				MenuStructOld->Page =3 ;
			}

			MenuStructOld->PressStart = 0;
			if(MenuStructOld->PositionMarker == 0){
				MenuStructOld->PositionMarker =1;
			}
			return;
		}

		if(MassPressKey == 155){ // старт калибровки
			if(MenuStructOld->CalibrStartStop == 1){
				MenuStructOld->CalibrStartStop = 0;
				MenuStructOld->Page = 1;
				MenuStructOld->NestMenuItem = 0;
				MenuStructOld->PositionMarker = 0;
				CalcCalVal(CAL_WRITE, &CalibrValues);
			}
			else{
				MenuStructOld->CalibrStartStop =1;
				MenuStructOld->Page = 5;
			}
		}

		if(MassPressKey == 131) { // Start of transmission.
			if(MenuStructOld->PressStart != 1)
			{
				LoRaInitTx(MenuStructOld);
				MenuStructOld->PressStart = 1;
				MenuStructOld->PressSelectLoraInit = 0;
				MenuStructOld->CalibrStartStop = 0;
				MenuStructOld->NestMenuItem = 0;
				MenuStructOld->PositionMarker = 0;

				MenuStructOld->Page = 4;
				CamTrimVert--;
				//Forced start of transfer
				IT_GPIO_Handl(0);
			}
			return;
		}
		if(MassPressKey == 151){ // нажата клавиша сброса значений калибровки.
			ClearProgMem();
			MenuStructOld->PressStart = 0;
			MenuStructOld->Page = 1;
			MenuStructOld->NestMenuItem = 0;
			MenuStructOld->PositionMarker = 0;
			MenuStructOld->CalibrStartStop = 0;
			return;
		}

	// Вот здесь возможно не так работает для останова передачи я хочу использовать
//	другую кнопку.
		if(MassPressKey == 129){ 		// Вывод Данных  АЦП
		// здесь возможно тоже надо будет как-то определять что остановили передачу.
			MenuStructOld->CalibrStartStop = 0;
			if(MenuStructOld->PressSelectLoraInit ==1){
				if(MenuStructOld->NestMenuItem == 0){
					MenuStructOld->NestPressDown 	= 	0;
					MenuStructOld->NestPressUP 		=	0;
					MenuStructOld->NestMenuItem 	= 	0;
					MenuStructOld->PositionMarker 	= 	1;
					MenuStructOld->PressSelectLoraInit = 0;
				}
				else {
					MenuStructOld->NestMenuItem = 0;
					}
				}
			MenuStructOld->Page = 1;
			return;
		}

//==========Выбраны настройки инициализации LoRa=======================

		if(MenuStructOld->PressSelectLoraInit == 1){
			switch(MassPressKey){
			case 139 : { // лево
				if (MenuStructOld->NestMenuItem <1){
					MenuStructOld->NestMenuItem = 6;
				}
				else {
					MenuStructOld->NestMenuItem --;
				}
				break;
			}
			case 141 : { // право
				if(MenuStructOld->NestMenuItem >5){
					MenuStructOld->NestMenuItem = 1;
				}
				else{
					MenuStructOld->NestMenuItem++;
				}
				break;
			}
	// эти можно вычитать складывать и после вычислять в цикле например.
			case 130 : { //вверх
				if(MenuStructOld->NestMenuItem!=0){
					MenuStructOld->NestPressUP++;
				}
				else{
					if(MenuStructOld->Page ==2){
						if(MenuStructOld->PositionMarker < 2){
							MenuStructOld->PositionMarker =1 ;
							MenuStructOld->Page = 3;
						}
						else MenuStructOld->PositionMarker --;
					}
					else{ // page3
						if(MenuStructOld->PositionMarker < 2){
							MenuStructOld->PositionMarker= 1;
							MenuStructOld->Page =2;
						}
						else MenuStructOld->PositionMarker = 1;
					}
				}
				break;

			}

			case 150 : { //низ
				if(MenuStructOld->NestMenuItem!=0){
					MenuStructOld->NestPressDown++;
				}
				else{
					if(MenuStructOld->Page ==2){
						if(MenuStructOld->PositionMarker>2){
							MenuStructOld->PositionMarker=1;
							MenuStructOld->Page =3;
						}
						else MenuStructOld->PositionMarker ++;
					}
					else{ // page3
						if(MenuStructOld->PositionMarker  > 1){
							MenuStructOld->PositionMarker=1;
							MenuStructOld->Page =2;
						}
						else MenuStructOld->PositionMarker = 2;
					}
				}
				break;
			}
			case 140 : { //нажатие
				if(MenuStructOld->PressKey == 1){
					MenuStructOld->PressKey = 0;
					MenuStructOld->NestMenuItem = 0;
				}
				else{
					if(MenuStructOld->NestMenuItem!=0){
						MenuStructOld->PressKey = 0;
						MenuStructOld->NestMenuItem = 0;
					}
					else{
						MenuStructOld->PressKey = 1;
						if(MenuStructOld->NestMenuItem ==0){
							MenuStructOld->NestMenuItem = 1;
						}
					}

				}
				break;
			}
			}
		}
	}
}

/*
 * This function accepts a structure and runs functions based on the current page,
 * passing it the appropriate parameters.
 * The handler runs page functions, passing them a structure.
 *  The functions themselves determine how to output based on the structure.
 */
HAL_StatusTypeDef MenuHandl(PositionMenuStruct *MenuStructOld){
	disp1color_FillScreenbuff(0);
	if(MenuStructOld->PressStart==1){
		// you can add battery charge output here!!!
		// Packets transmitted per second
		NumPacSec();
		// ADC data.
		BufFormStick();
	}
	else {
		switch (MenuStructOld->Page) {
			case 0 : {
				disp1color_printf(5, 10, FONTID_10X16F, "Start Palenish");
				break;
			}
			case 1 : {
				//output ADC data
				BufFormStick();
				// Print the number of transformations.
				BufFormNumbConv();
				break;
			}
			case 2 : {
				printFreqMenu(MenuStructOld);
				printPowerMenu(MenuStructOld);
				printSignalBw(MenuStructOld);
				break;
			}
			case 3 : {
				printSfMenu(MenuStructOld);
				printErrCod(MenuStructOld);
				break;
			}
			case 5 : {
				// create a buffer of maximum and minimum values
				PrintCalibMaxMin(CalcCalVal(START_CAL, &CalibrValues));
			}

		}

	}

	disp1color_UpdateFromBuff();
	return HAL_OK;
}

// Прерывания происходят каждую секунду.
void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc){
	// не все режимы нужно выводить по прерываниям.
	if(MenuStructOld.Page != 3){
		if(MenuStructOld.Page !=2){
			MenuHandl(&MenuStructOld);
		}
	}

}



// Выводит количество пакетов отправляемых в секунду
// Количество пакетов увеличивается по прерываниям от DMA.
void NumPacSec(){

	disp1color_printf(1, 50, FONTID_6X8M, "Packets: %d ",NumberOfPackets);
	NumberOfPackets = 0;
}

// Generates an array of commands before sending them to the FiFo buffer
void FormArrComm(){
	//first writes the ADC conversion data
	if(Adc1Calc[0] > 0){
		ComArr1[ACCELER] = (int8_t)(Adc1Calc[0]*CalibrValues.CalibrValMax[0]);
	}
	else{
		ComArr1[ACCELER] = (int8_t)(-(Adc1Calc[0]*CalibrValues.CalibrValMin[0]));
	}

	if(Adc1Calc[1] > 0){
		ComArr1[STEER_TURN] = (int8_t)(Adc1Calc[1]*CalibrValues.CalibrValMax[1]);
	}
	else{
		ComArr1[STEER_TURN] = (int8_t)(-(Adc1Calc[1]*CalibrValues.CalibrValMin[1]));
	}

	if(Adc1Calc[3] > 0){
		ComArr1[CAM_HORIZONT] = (int8_t)(Adc1Calc[3]*CalibrValues.CalibrValMax[3]);
	}
	else{
		ComArr1[CAM_HORIZONT] = (int8_t)(-(Adc1Calc[3]*CalibrValues.CalibrValMin[3]));
	}

	if(Adc1Calc[2] > 0) {
		ComArr1[CAM_VERTICAL] = (int8_t)(Adc1Calc[2]*CalibrValues.CalibrValMax[2]);
	}
	else{
		ComArr1[CAM_VERTICAL] =(int8_t)(-(Adc1Calc[2]*CalibrValues.CalibrValMin[2]));
	}

	ComArr1[STEER_TRIM] 	= 	(uint8_t)SteerTrim;
	ComArr1[CAM_TRIM_HORIZ] =	(uint8_t)CamTrimHoriz ;
	ComArr1[CAM_TRIM_VERT] 	=	(uint8_t)CamTrimVert ;
	ComArr1[HEADLIGHTS] 	=	(uint8_t)Headlights ;
	ComArr1[LOAD1] 			=	(uint8_t)Load1 ;
	ComArr1[LOAD2] 			=	(uint8_t)Load2 ;
	ComArr1[CAM_HOME] 		=	(uint8_t)CamHome ;
}

// This function configures the LoRa chip, then sets it up to transmit Tx
HAL_StatusTypeDef LoRaInitTx(PositionMenuStruct *MenuStructOld){

	// The structure is initialized with the parameters configured in the menu.
	LoRaParamCalc();
	//the LORA chip is initialized with the given parameters
	SX1276Init();
	// preparing for transmission.
	InitTxLoRa();
	return HAL_OK;
}

// Сюда переходит когда DMA успешно записал команды в память.
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	// Сюда перешли когда данные были записаны в буфер или были прочтены из буфера

	if(hspi == &hspi2){
		HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);
		if(MenuStructOld.PressStart==1){
			StartTxLoRa();
			NumberOfPackets ++;
		}

	}
}


/*
 * The function of reading the maximum values ​​of sticks and generating calibration coefficients.
 */
MaxMinCalStruct *CalcCalVal(StatCalibr Mode,CalibrStruct *Calib ){
	static MaxMinCalStruct CalStruct;
	uint32_t i=0;
	const uint32_t Const = 127;
	ProgMemStruct FlashMemCal;

	if(Mode == START_CAL){
		while(i<4){
			if(CalStruct.MaxADC1Calc[i] < Adc1Calc[i]){
				CalStruct.MaxADC1Calc[i] = Adc1Calc[i];
			}
			else {
				if(CalStruct.MinADC1Calc[i] > Adc1Calc[i]){
					CalStruct.MinADC1Calc[i] = Adc1Calc[i];
				}
			}
			i++;
		}
	}
	// вычисление коэффициэнтов
	else{
		while(i<4){
			Calib->CalibrValMax[i] = (float)Const/CalStruct.MaxADC1Calc[i];
			Calib->CalibrValMin[i] = (float)Const/CalStruct.MinADC1Calc[i];
			FlashMemCal.CalibrValues.CalibrValMax[i] = Calib->CalibrValMax[i];
			FlashMemCal.CalibrValues.CalibrValMin[i] = Calib->CalibrValMin[i];
			FlashMemCal.CalibrValues.Adc1NULL[i] = Adc1Null[i];
			i++;
		}
// Запись значений калибровки в память программ.
		FlashMemCal.KeySt = Key;
		write_config_to_flash(&FlashMemCal);
	}
	return &CalStruct;
}

// Функция заполнения значений калибровки при первом старте системы
void CalibrStartInit(CalibrStruct *Calib){
	uint32_t i = 0;
	while(i<4){
		Calib->CalibrValMax[i] = 	1;
		Calib->CalibrValMin[i] = 	-1;
		i++;
	}
}

// Функция формирует буфер экрана Максимальными и минимальными значениями калибровки.
void PrintCalibMaxMin(MaxMinCalStruct *CalStruct){
	disp1color_printf(1,  10, FONTID_6X8M, "MaxA1:%d",CalStruct->MaxADC1Calc[0]);
	disp1color_printf(60, 10, FONTID_6X8M, "MinA1:%d",CalStruct->MinADC1Calc[0]);

	disp1color_printf(1, 20, FONTID_6X8M, "MaxA2:%d", CalStruct->MaxADC1Calc[1]);
	disp1color_printf(60, 20, FONTID_6X8M, "MinA2:%d", CalStruct->MinADC1Calc[1]);

	disp1color_printf(1, 30, FONTID_6X8M, "MaxB1:%d", CalStruct->MaxADC1Calc[3]);
	disp1color_printf(60, 30, FONTID_6X8M, "MinB1:%d", CalStruct->MinADC1Calc[3]);

	disp1color_printf(1, 40, FONTID_6X8M, "MaxB2:%d", CalStruct->MaxADC1Calc[2]);
	disp1color_printf(60, 40, FONTID_6X8M, "MinB2:%d", CalStruct->MinADC1Calc[2]);
}

/*
 * Функция сброса значений калибровки и нулевого положения.
 * Очишает память программ, от старых значений (плохой калибровки)
 * Запускаю при нажатии кнопки сброса калибровки.
 */
void ClearCalValues(){
//	Записываю в калибровочные ячейки значения по дефолту
	CalibrStartInit(&CalibrValues);

	// Задание нулевого положения по новой.
	StickCal(Adc1Value,&hadc1,Adc1Null);
	// Очистка памяти где хранятся значения калибровки.
	ClearProgMem();
}

