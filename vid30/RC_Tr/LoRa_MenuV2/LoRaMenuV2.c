/*
 * LoRaMenuV2.c
 *
 *  Created on: Mar 29, 2025
 *      Author: dima
 */

#include "LoRa_MenuV2.h"

//Структура с цифрами частоты котору потом надо записать в ячейки.
uint8_t digitNum[DIGIT_LEN+1];

uint8_t LoRaPower;
uint8_t LoRaBw;
uint8_t LoRaSf;
uint8_t LoRaErrCode;

void LoRaMenuInit(){
	digitNum[0] = 4;
	digitNum[1] = 3;
	digitNum[2] = 3;
	digitNum[3] = 5;
	for(uint32_t i=4; i < DIGIT_LEN; i++){ //DIGIT_LEN
		digitNum[i]=0;
	}

	LoRaPower = 17;
	LoRaBw = 9;
	LoRaSf = 10;
	LoRaErrCode = 2;
}

//Функция вывода меню частоты

void printFreqMenu(struct PositionMenuStruct *MenuStructOld){
	static char freq[] = "Freq:";
	static char ext[] = "МГц";
	char asciiChar[DIGIT_LEN+2];
	char asciiSymb[3];
	int8_t posInvert = -1;
	char digitInvert = 0;
	int32_t NewState = 0;

	//Выбрана эта ячейка вывод инфы, нажатия не было на ней
	if((MenuStructOld->PositionMarker == 1) && (MenuStructOld->PressKey == 0) && \
			MenuStructOld->NestMenuItem == 0){
		disp1color_DrawString_Invert(1, 0, FONTID_10X16F, (uint8_t*)freq);
	}
	else{ //Выбрана другая ячейка
		disp1color_DrawString(1, 0, FONTID_10X16F, (uint8_t*)freq);
	}

	// Изменяет цифры числа в зависимости от нажатий вверх вниз.
	if((MenuStructOld->PositionMarker == 1) && (MenuStructOld->NestMenuItem > 0) ){
		NewState = MenuStructOld->NestPressUP - MenuStructOld->NestPressDown;
		if(NewState!=0){ //были изменения.

			while(NewState>0){
				NewState --;
				digitNum[MenuStructOld->NestMenuItem-1]++;
				if(digitNum[MenuStructOld->NestMenuItem-1] >9){
					digitNum[MenuStructOld->NestMenuItem-1] = 0;
				}
			}
			while(NewState < 0){
				NewState ++;
				digitNum[MenuStructOld->NestMenuItem-1]--;
				if(digitNum[MenuStructOld->NestMenuItem-1] == 255){
					digitNum[MenuStructOld->NestMenuItem-1] = 9;
				}
			}
			MenuStructOld->NestPressUP 	 = 0;
			MenuStructOld->NestPressDown = 0;

		}
	}

	//Записывает в строку коды чисел
	// вместо выбранной цифры ставит пробел
	for(uint32_t i=0; i < DIGIT_LEN+1; i++){
		if(i!=3){
			if(i>3) {
				sprintf(asciiChar+i, "%d",digitNum[i-1]); // Правильно??
				if(((MenuStructOld->NestMenuItem - 1) == (i-1)) && (MenuStructOld->NestMenuItem > 0) \
						&& (MenuStructOld->PositionMarker ==1 )	){
					asciiChar[i] = ' ';
					posInvert = i;
					digitInvert = digitNum[i-1];
				}
			}
			else {
				sprintf(asciiChar+i, "%d",digitNum[i]);
				if(((MenuStructOld->NestMenuItem - 1) == (i)) && (MenuStructOld->NestMenuItem > 0) \
						&& (MenuStructOld->PositionMarker ==1 )){
									asciiChar[i] = ' ';
									posInvert = i;
									digitInvert = digitNum[i];
								}
			}
		}
		else asciiChar[i]=',';
	}

	//Вывод цифр частоты
	disp1color_DrawString(4*10-3, 0, FONTID_10X16F, (uint8_t*)asciiChar);
	//если надо вывести инвертированную цифру
	if(posInvert > -1){
		sprintf(asciiSymb,"%d", digitInvert);
		// если надо вывести инвертированный символ
		if(posInvert>3){
			disp1color_DrawString_Invert(4*10 +posInvert*10 - 15 , 0, FONTID_10X16F, (uint8_t*)asciiSymb);
		}
		else{
			disp1color_DrawString_Invert(4*10  + posInvert*10 -5 , 0, FONTID_10X16F, (uint8_t*)asciiSymb);
		}
	}

	//Вывод расширения
	disp1color_DrawString(4*10 + 6*10 -4, 0, FONTID_10X16F, (uint8_t*)ext);
}


//Меню выбора мощности.
void printPowerMenu(struct PositionMenuStruct *MenuStructOld){
	char asciiChar[2];
	static char menu[] = "Power:";
	static char exten[] = "dBm";
	int32_t NewState = 0;

	//Выбрана эта ячейка вывод инфы, нажатия не было на ней
	if((MenuStructOld->PositionMarker == 2) && (MenuStructOld->PressKey == 0) && \
			(MenuStructOld->NestMenuItem == 0)){
			disp1color_DrawString_Invert(1, 18, FONTID_10X16F, (uint8_t*)menu);
	}
	else{ //Выбрана другая ячейка, или было нажатие.
			disp1color_DrawString(1, 18, FONTID_10X16F, (uint8_t*)menu);
	}

	if(MenuStructOld->PositionMarker ==2){
		if(MenuStructOld->NestMenuItem >1){
			MenuStructOld->NestMenuItem =0;
			MenuStructOld->PressKey = 0;
		}
	}


	if((MenuStructOld->PositionMarker == 2) && (MenuStructOld->NestMenuItem > 0) ){
			NewState = MenuStructOld->NestPressUP - MenuStructOld->NestPressDown;
			if(NewState!=0){ //были изменения.

				while(NewState>0){
					NewState --;
					LoRaPower++;
					if(LoRaPower >17){
						LoRaPower = 5;
					}
				}
				while(NewState < 0){
					NewState ++;
					LoRaPower--;
					if(LoRaPower < 5){
						LoRaPower = 17;
					}
				}
				MenuStructOld->NestPressUP 	 = 0;
				MenuStructOld->NestPressDown = 0;

			}
		}
	sprintf(asciiChar, "%d",LoRaPower);
	//Вывод цифр числа
//	(MenuStructOld->PressKey ==1) &&
	if((MenuStructOld->NestMenuItem > 0) \
			&& (MenuStructOld->PositionMarker ==2) ){
		disp1color_DrawString_Invert(5*10 + 2, 18, FONTID_10X16F, (uint8_t*)asciiChar);
	}
	else {
		disp1color_DrawString(5*10 + 2 , 18, FONTID_10X16F, (uint8_t*)asciiChar);
	}
	//Вывод расширения
	disp1color_DrawString(5*10 + 2*10 +2 , 18, FONTID_10X16F, (uint8_t*)exten);
}

void printSignalBw(struct PositionMenuStruct *MenuStructOld){
	static char BwMenu[] = "Bw:";
	static char *Exten2[] = { "7,8", "10,4", "15,6", "20,8", "31,2",
					   "41,6", "62,5", "125","250", "500", "кГц" };
	int32_t NewState = 0;


	//Выбрана эта ячейка вывод инфы, нажатия не было на ней
	if((MenuStructOld->PositionMarker == 3) && (MenuStructOld->PressKey == 0) && \
			(MenuStructOld->NestMenuItem == 0)){
			disp1color_DrawString_Invert(1, 36, FONTID_10X16F, (uint8_t*)BwMenu);
	}
	else{ //Выбрана другая ячейка, или было нажатие.
			disp1color_DrawString(1, 36, FONTID_10X16F, (uint8_t*)BwMenu);
	}

	if(MenuStructOld->PositionMarker == 3){
		if(MenuStructOld->NestMenuItem >1){
			MenuStructOld->NestMenuItem =0;
			MenuStructOld->PressKey = 0;
		}
	}

	if((MenuStructOld->PositionMarker == 3) && (MenuStructOld->NestMenuItem > 0) ){
			NewState = MenuStructOld->NestPressUP - MenuStructOld->NestPressDown;
			if(NewState!=0){ //были изменения.

				while(NewState>0){
					NewState --;
					LoRaBw++;
					if(LoRaBw > 9){
						LoRaBw = 0;
					}
				}
				while(NewState < 0){
					NewState ++;
					LoRaBw--;
					if(LoRaBw == 255){
						LoRaBw = 9;
					}
				}
				MenuStructOld->NestPressUP 	 = 0;
				MenuStructOld->NestPressDown = 0;

			}
		}
	//Вывод цифр числа
	if((MenuStructOld->NestMenuItem > 0) \
				&& (MenuStructOld->PositionMarker == 3) ){
		disp1color_DrawString_Invert(4*10 + 2, 36, FONTID_10X16F, \
				(uint8_t*)(Exten2[LoRaBw]));
	}
	else {
		disp1color_DrawString(4*10 , 36, FONTID_10X16F, \
				(uint8_t*)(Exten2[LoRaBw]));
	}
	//Вывод расширения
	disp1color_DrawString(4*10 + 4*10 + 2 , 36 , FONTID_10X16F, (uint8_t*)(Exten2[10]));

}

void printSfMenu( struct PositionMenuStruct *MenuStructOld){
	static char CharSF[] = "SF:";
	static char Exten3[] = "chips";
	int32_t NewState;
	char asciiSymb[2];
	int digitPrint = 1;

	digitPrint = digitPrint << LoRaSf;
	sprintf(asciiSymb,"%d", digitPrint);

	//Выбрана эта ячейка вывод инфы, нажатия не было на ней
	if((MenuStructOld->PositionMarker == 1) && (MenuStructOld->PressKey == 0) && \
			(MenuStructOld->NestMenuItem == 0)){
			disp1color_DrawString_Invert(1, 0, FONTID_10X16F, (uint8_t*)CharSF);
	}
	else{ //Выбрана другая ячейка, или было нажатие.
			disp1color_DrawString(1, 0, FONTID_10X16F, (uint8_t*)CharSF);
	}

	if(MenuStructOld->PositionMarker == 1){
		if(MenuStructOld->NestMenuItem >1){
			MenuStructOld->NestMenuItem =0;
			MenuStructOld->PressKey = 0;
		}
	}

	if((MenuStructOld->PositionMarker == 1) && (MenuStructOld->NestMenuItem > 0) ){
			NewState = MenuStructOld->NestPressUP - MenuStructOld->NestPressDown;
			if(NewState!=0){ //были изменения.

				while(NewState>0){
					NewState --;
					LoRaSf++;
					if(LoRaSf > 12){
						LoRaSf = 6;
					}
				}
				while(NewState < 0){
					NewState ++;
					LoRaSf--;
					if(LoRaSf < 6){
						LoRaSf = 12;
					}
				}
				MenuStructOld->NestPressUP 	 = 0;
				MenuStructOld->NestPressDown = 0;

			}
	}
			//Вывод цифр числа
			if((MenuStructOld->NestMenuItem > 0) \
					&& (MenuStructOld->PositionMarker == 1) ){
				digitPrint = digitPrint << LoRaSf;
				disp1color_DrawString_Invert(3*10 +2 , 0, FONTID_10X16F, (uint8_t*) asciiSymb);
			}
			else {
				disp1color_DrawString(3*10 +2 , 0, FONTID_10X16F, (uint8_t*) asciiSymb);
			}
			//Вывод расширения
			disp1color_DrawString(3*10 + 4*10 + 2 ,0 , FONTID_10X16F, (uint8_t*)Exten3);
}

void printErrCod(struct PositionMenuStruct *MenuStructOld){
	static char ErrCodStr[] = "ErrCod:";
	static char *Exten4[] = { "4/5", "4/6","4/7", "4/8" };
	int32_t NewState;


	//Выбрана эта ячейка вывод инфы, нажатия не было на ней
	if((MenuStructOld->PositionMarker == 2) && (MenuStructOld->PressKey == 0) && \
			(MenuStructOld->NestMenuItem == 0)){
			disp1color_DrawString_Invert(1, 18, FONTID_10X16F, (uint8_t*)ErrCodStr);
	}
	else{ //Выбрана другая ячейка, или было нажатие.
			disp1color_DrawString(1, 18, FONTID_10X16F, (uint8_t*)(ErrCodStr));
	}

	if(MenuStructOld->PositionMarker == 2){
		if(MenuStructOld->NestMenuItem >1){
			MenuStructOld->NestMenuItem =0;
			MenuStructOld->PressKey = 0;
		}
	}

	if((MenuStructOld->PositionMarker == 2) && (MenuStructOld->NestMenuItem > 0) ){
				NewState = MenuStructOld->NestPressUP - MenuStructOld->NestPressDown;
				if(NewState!=0){ //были изменения.

					while(NewState>0){
						NewState --;
						LoRaErrCode++;
						if(LoRaErrCode > 4){
							LoRaErrCode = 1;
						}
					}
					while(NewState < 0){
						NewState ++;
						LoRaErrCode--;
						if(LoRaErrCode < 1){
							LoRaErrCode = 4;
						}
					}
					MenuStructOld->NestPressUP 	 = 0;
					MenuStructOld->NestPressDown = 0;

				}
		}

	//Вывод цифр числа
	if((MenuStructOld->NestMenuItem > 0) \
			&& (MenuStructOld->PositionMarker == 2)){
		disp1color_DrawString_Invert(7*10 , 18, FONTID_10X16F,
				(uint8_t*) Exten4[LoRaErrCode - 1]);
	}
	else {
		disp1color_DrawString(7*10 , 18, FONTID_10X16F,
				(uint8_t*) Exten4[LoRaErrCode - 1]);
	}
}

//Calculation of parameters and writing to LoRa initialization structure
void LoRaParamCalc(){
	// Recording frequency
	LoRaSettings.RFFrequency = checkParamRf();

	//record power
	LoRaSettings.Power = LoRaPower;

	//Record bandwidth
	LoRaSettings.SignalBw = LoRaBw;

	//Record SF
	LoRaSettings.SpreadingFactor = LoRaSf;

	// ErrorCoding record
	LoRaSettings.ErrorCoding = LoRaErrCode;

}

// check the entered values.
uint32_t checkParamRf(){
	uint32_t RFFreq;
	uint32_t LoRaFreq = 0;
	//Вычисление частоты
	for(uint32_t i =0,j=7,k;i < DIGIT_LEN;i++,j--){
		k=j;
		RFFreq = 10;
		while(k>0){
			RFFreq *= 10;
			k--;
		}
		LoRaFreq +=  digitNum[i] * RFFreq;
	}
	//Проверка частоты не вышла ли за заданные пределы. 137-525 мГц
	if(LoRaFreq < 137000000){
		LoRaFreq = 137000000;
		digitNum[0] = 1;
		digitNum[1] = 3;
		digitNum[2] = 7;
	}
	else{
		if(LoRaFreq> 525000000){
			LoRaFreq=525000000;
			digitNum[0] = 5;
			digitNum[1] = 2;
			digitNum[2] = 5;
			digitNum[3] = 0;
			digitNum[4] = 0;
			digitNum[5] = 0;
		}
	}
	return LoRaFreq;
}

