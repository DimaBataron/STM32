/*
 * 22keypadTCA8418.c
 *
 *  Created on: Aug 5, 2024
 *      Author: dima
 *      ���������� ��� ������ � TCA8418.
 *      �������� ��� ������ ������� ������ �� 22 ��������� "�����"
 *      �������� � ��������� ���������� HAL.
 *      �������� � ���� ���������:
 *      - ��������� �� TCA8418 � ����� ������
 *      - �������� �������
 *      - ������ FIFO
 *
 */
//������ ������� ��� ��������� TCA8418 � ����� ������ �������
// ������������������ �������� :
// 			C����- ����� ��������� � ����� �� ������ (0)-
//		 	����� �������� -������ - C���
#include "22keypadTCA8418.h"

uint8_t *AdrrComm8418; // ����� ������� ������� ������� ���� ��������
uint8_t CommMatr8418[] = { 	REG_KP_GPIO1, (ROW0|ROW1|ROW2), \
							REG_KP_GPIO2, (COL0|COL1|COL2|COL3|COL4|COL5|COL6|COL7), \
							REG_CFG,	  (CFG_AI|CFG_INT_CFG|CFG_KE_IEN)
};

uint8_t MassPressKey[10];
uint8_t FlagPress = 0;
#ifndef ENCODER_H
//menu event handling
uint32_t ConditionEncoder;
#endif
/*
* The procedure sends initialization commands to the TCA8418 device
* Receives a pointer to the hi2c header file structure
*/

HAL_StatusTypeDef MatrixConfig8418(I2C_HandleTypeDef *hi2c){
	AdrrComm8418 = CommMatr8418;
	HAL_GPIO_WritePin(RESET_TCA_GPIO_Port, RESET_TCA_Pin, RESET);
	HAL_Delay(49);
	for(int i = 0; i<10 ; i++ ){
		MassPressKey[i] = 0;
	}
	HAL_GPIO_WritePin(RESET_TCA_GPIO_Port, RESET_TCA_Pin, SET);
	HAL_Delay(50);
	for(int i = 0 ; i < 3; i++ ){
		if(HAL_I2C_Master_Transmit(hi2c, (uint16_t)AddrTCA8418, AdrrComm8418, 2, (uint32_t)Timeout_I2C_Tr)!= HAL_OK){
			return HAL_ERROR;
		}
		AdrrComm8418+=2;
	}
	return HAL_OK;
}
/* ���������� ���������� ����� INT �� ���������� ����������� TCA8418
 * ��������� �������� ������ ������ �� �����������
 * ��� ������� �������� �� �����������.
 * ����� ����� ���������� ������� ������ ����������� ����� ����� ����� ����������� ������
 * ������� ������� ����������� ����� ���������� ��.
 * �������� ����� ����� ������������ ������������ ��.
 */
HAL_StatusTypeDef ReadFIFO(I2C_HandleTypeDef *hi2c){
	uint8_t DataMas[2];
	uint8_t TrData;
	uint8_t ReadData;
	//0 ������� ����� ������.
	MassPressKey[0] = 0;

	TrData = REG_INT_STAT;
	// 1. ����� ������� INT_STAT
	if(HAL_I2C_Master_Transmit(hi2c, (uint16_t)AddrTCA8418, &TrData, 1, (uint32_t)Timeout_I2C_Tr)!= HAL_OK){
		return HAL_ERROR;
	}
	if(HAL_I2C_Master_Receive(hi2c,(uint16_t)AddrTCA8418 | 0x01, &ReadData, 1, (uint32_t)Timeout_I2C_Tr)!= HAL_OK){
		return HAL_ERROR;
	}

	//2. �������� ������ ����������
	if(ReadData & K_INT){
		//���� ������� ����� ��������� ������� ����������
		TrData = REG_KEY_EVENT_A;
	//3.����� ���� ������
		if(HAL_I2C_Master_Transmit(hi2c, (uint16_t)AddrTCA8418, &TrData, 1, (uint32_t)Timeout_I2C_Tr)!= HAL_OK){
					return HAL_ERROR;
				}

		do{
			if(HAL_I2C_Master_Receive(hi2c,(uint16_t)AddrTCA8418 | 0x01, &ReadData, 1, (uint32_t)Timeout_I2C_Tr)!= HAL_OK){
					return HAL_ERROR;
				}

			if(FlagPress > 9) FlagPress = 0;
			// ��� ������� ��� ���� ���������, �� ������ ���� 100.
			// ������� ���� �� ����������
			if(ReadData>100){
				MassPressKey[FlagPress++] = ReadData;
			}


//			MenuEventPress(ReadData);

		}while(ReadData!=0);
		if(ReadData==0){
		// ���������� ������ �������� ������
			MassPressKey[FlagPress] = 0;
			FlagPress = 0;
		}

//	4. INT_STAT �� ������ ������ ���� ���������� ��� �� �� ������������.
		DataMas[0] = REG_INT_STAT;
		DataMas[1] = K_INT;
		if(HAL_I2C_Master_Transmit(hi2c, (uint16_t)AddrTCA8418, DataMas, 2, (uint32_t)Timeout_I2C_Tr)!= HAL_OK){
						return HAL_ERROR;
		}
	}
	else return HAL_ERROR;
	return HAL_OK;
}

//form buffer press key
void BufFormKey(uint8_t X){
	uint8_t i = 0;
	uint8_t Str = 0;
	uint8_t Col = 0;
	while(FlagPress != i){
		if((i*20)>100) {
			Str = 9;
			Col = 100;
		}
		disp1color_printf(i*20 - Col,X + Str , FONTID_6X8M,"%d",MassPressKey[i]);
		i++;
		}
}



// ������� ������� �������� ��������� �� �����
// ������� ������ � ���������� ������ � �������.
void PrintSymbASCII(uint8_t *MassPressKey){
//	char asciiSymb[1];
	uint32_t i = 0;

	// ��������� ���������� �� ������� GPIO
	//�������� ���������� � �� ����� LoRa (DIO0)
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);

	// ������ �� ������� � ��������� � ������� ����� ����.
	do{
		if(MassPressKey[i]==0){
			break;
		}
		disp1color_FillScreenbuff(0);
//		sprintf(asciiSymb, "%d",MassPressKey[i]);
		disp1color_printf(20, 10, FONTID_10X16F, "Symb: %d",MassPressKey[i]);
//		disp1color_DrawString(10, 20, FONTID_10X16F, (uint8_t*)asciiSymb);
		disp1color_UpdateFromBuff();
		HAL_Delay(950);

		i++;
	}
	while(i<10);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}




