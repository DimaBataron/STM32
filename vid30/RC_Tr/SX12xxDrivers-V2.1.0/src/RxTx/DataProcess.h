/*
 * DataProcess.h
 *
 *  Created on: Jan 14, 2024
 *      Author: dima
 */

#ifndef SX12XXDRIVERS_V2_1_0_SRC_RXTX_DATAPROCESS_H_
#define SX12XXDRIVERS_V2_1_0_SRC_RXTX_DATAPROCESS_H_

#include "main.h"

// Defines the number of commands to be transmitted
#ifdef BUGSEARCHTEST_H_
#define NumberCommands 4
#else
	#ifdef PETROVICHOTSOSTEST_H_
		#define NumberCommands 4
	#else
		#define NumberCommands 11
	#endif
#endif

#define FIFOAdrComArr1 0

#define FIFOAdrComArr2 17

#define RSSI_OFFSET_LF                              -164.0

//��������� ���������� ������ � ����� sx1276
// ���������� ������ ������� ��� ��������� �� ������ ��������� DMA.
uint8_t* WriteArrFIFO(SPI_HandleTypeDef *hspi);


extern uint8_t ComArr1[NumberCommands];
//extern uint8_t ComArr2[NumberCommands];

//��������� ������ �� ��������.
void InitTxLoRa();

//����� �������� �� �����������
void StartTxLoRa();

//���� ��������� �� ���������� �� ��������� GPIO
void TxInterHandl();

//���������� �������� �� ����������� ����� �������
void InitRxContLoRa();

//Start on interrupts DIO0==1 RxDone
uint32_t RxContLoRaCmpl(uint8_t *Arr,SPI_HandleTypeDef *hspi);

//��������� ��������� ��������
void RxParamCalc();

//�������� ������� � ������ ������������ ���������� ��� ������� ��������� ��������������

void CheckParam();

//�������� ������� ��������� �������
void TxRxArrFill(void);

//�������� ������� ������ ������� � ������
void TxArrWriteFiFo(uint8_t LocateArrayFifo, uint8_t *DataMas, uint8_t LenArr);

//Record keys for the ignition device
void TxArrWriteKey(uint8_t *DataMass, uint8_t (*KeyMass)[2], int32_t NumMasKey);

void TxArrWriteFiFoDMA(SPI_HandleTypeDef *hspi, \
		uint8_t LocateArrayFifo, uint8_t *DataMas, uint8_t LenArr);

#endif /* SX12XXDRIVERS_V2_1_0_SRC_RXTX_DATAPROCESS_H_ */
