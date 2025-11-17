/*
 * DataProcess.c
 *
 *  Created on: Jan 14, 2024
 *      Author: dima
 */
#include "DataProcess.h"
#include "sx1276-Lora.h"



//Commands that are currently being transmitted
uint8_t ComArr1[NumberCommands];



void InitTxLoRa(){

	SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );
	SX1276LR->RegIrqFlagsMask = RFLR_IRQFLAGS_RXTIMEOUT |
	                                        RFLR_IRQFLAGS_RXDONE |
	                                        RFLR_IRQFLAGS_PAYLOADCRCERROR |
	                                        RFLR_IRQFLAGS_VALIDHEADER |
	                                        //RFLR_IRQFLAGS_TXDONE |
	                                        RFLR_IRQFLAGS_CADDONE |
	                                        RFLR_IRQFLAGS_FHSSCHANGEDCHANNEL |
	                                        RFLR_IRQFLAGS_CADDETECTED;
	SX1276LR->RegHopPeriod = 0;
	SX1276Write( REG_LR_HOPPERIOD, SX1276LR->RegHopPeriod );
	SX1276Write( REG_LR_IRQFLAGSMASK, SX1276LR->RegIrqFlagsMask );
    									// TxDone               RxTimeout                   FhssChangeChannel          ValidHeader
	SX1276LR->RegDioMapping1 = RFLR_DIOMAPPING1_DIO0_01 | RFLR_DIOMAPPING1_DIO1_00 | RFLR_DIOMAPPING1_DIO2_00 | RFLR_DIOMAPPING1_DIO3_01;
    									// PllLock              Mode Ready
	SX1276LR->RegDioMapping2 = RFLR_DIOMAPPING2_DIO4_01 | RFLR_DIOMAPPING2_DIO5_00;
    SX1276WriteBuffer( REG_LR_DIOMAPPING1, &SX1276LR->RegDioMapping1, 2 );

}

void StartTxLoRa(){

	TxInterHandl();

	SX1276LR->RegPayloadLength = NumberCommands;
	SX1276Write( REG_LR_PAYLOADLENGTH, SX1276LR->RegPayloadLength );

	SX1276LR->RegFifoTxBaseAddr=FIFOAdrComArr1;
	SX1276Write( REG_LR_FIFOTXBASEADDR, SX1276LR->RegFifoTxBaseAddr );
	SX1276LoRaSetOpMode( RFLR_OPMODE_TRANSMITTER );
}

void TxInterHandl(){
        // Clear Irq
    SX1276Write( REG_LR_IRQFLAGS, RFLR_IRQFLAGS_TXDONE  );
    // optimize the power consumption by switching off the transmitter as soon as the packet has been sent
    SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );

}

void InitRxContLoRa(){
	SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );

	SX1276LR->RegIrqFlagsMask = RFLR_IRQFLAGS_RXTIMEOUT |
	                           //RFLR_IRQFLAGS_RXDONE |
	                           //RFLR_IRQFLAGS_PAYLOADCRCERROR |
	                            RFLR_IRQFLAGS_VALIDHEADER |
	                            RFLR_IRQFLAGS_TXDONE |
	                            RFLR_IRQFLAGS_CADDONE |
	                            RFLR_IRQFLAGS_FHSSCHANGEDCHANNEL |
	                            RFLR_IRQFLAGS_CADDETECTED;
	SX1276Write( REG_LR_IRQFLAGSMASK, SX1276LR->RegIrqFlagsMask );
	SX1276LR->RegHopPeriod = 255;
	SX1276Write( REG_LR_HOPPERIOD, SX1276LR->RegHopPeriod );

	                                 // RxDone                    RxTimeout                   FhssChangeChannel           CadDone
	SX1276LR->RegDioMapping1 = RFLR_DIOMAPPING1_DIO0_00 | RFLR_DIOMAPPING1_DIO1_00 | RFLR_DIOMAPPING1_DIO2_00 | RFLR_DIOMAPPING1_DIO3_00;
	                                // CadDetected               ModeReady
	SX1276LR->RegDioMapping2 = RFLR_DIOMAPPING2_DIO4_00 | RFLR_DIOMAPPING2_DIO5_00;
	SX1276WriteBuffer( REG_LR_DIOMAPPING1, &SX1276LR->RegDioMapping1, 2 );

	// Rx continuous mode
	SX1276LR->RegFifoRxBaseAddr = FIFOAdrComArr1;
	SX1276Write( REG_LR_FIFORXBASEADDR,SX1276LR->RegFifoRxBaseAddr );
	// Pointer of the current address for SPI (from which it will be read) to the same place.
	SX1276LR->RegFifoAddrPtr = SX1276LR->RegFifoRxBaseAddr;
	SX1276Write( REG_LR_FIFOADDRPTR, SX1276LR->RegFifoAddrPtr );
	SX1276LoRaSetOpMode( RFLR_OPMODE_RECEIVER );
//#else
//	SX1276LoRaSetOpMode( RFLR_OPMODE_RECEIVER_SINGLE  );
//#endif
}

//Start by interrupt DIO0==1 RxDone (when parcel reception is finished)
uint32_t RxContLoRaCmpl(uint8_t *Arr,SPI_HandleTypeDef *hspi){
	// Data is always written regardless of whether I have time to read it or not
	// if not transferred to STANDBY

	// switch off the reception mode to standby mode
	SX1276LoRaSetOpMode(RFLR_OPMODE_STANDBY);

	SX1276Write( REG_LR_IRQFLAGS, RFLR_IRQFLAGS_RXDONE  );
	SX1276Read( REG_LR_IRQFLAGS, &SX1276LR->RegIrqFlags );
	if( ( SX1276LR->RegIrqFlags & RFLR_IRQFLAGS_PAYLOADCRCERROR ) == RFLR_IRQFLAGS_PAYLOADCRCERROR ){
//		PayLoadCRCError++; // corrupted CRC
		SX1276Write( REG_LR_IRQFLAGS, RFLR_IRQFLAGS_PAYLOADCRCERROR  );
		SX1276LoRaSetOpMode( RFLR_OPMODE_RECEIVER );
		//If the package is corrupted do nothing
		return HAL_ERROR;
	}
//	NumSuccessPack++;
	SX1276Read( REG_LR_PKTSNRVALUE, &SX1276LR->RegPktSnrValue );
	SX1276Read( REG_LR_PKTRSSIVALUE, &SX1276LR->RegPktRssiValue );
	//???
	SX1276Write( REG_LR_IRQFLAGS, RFLR_IRQFLAGS_PAYLOADCRCERROR  );

	SX1276Read( REG_LR_FIFORXCURRENTADDR, &SX1276LR->RegFifoRxCurrentAddr );
	SX1276Read( REG_LR_NBRXBYTES, &SX1276LR->RegNbRxBytes );
	SX1276LR->RegFifoAddrPtr = SX1276LR->RegFifoRxCurrentAddr;
	SX1276Write( REG_LR_FIFOADDRPTR, SX1276LR->RegFifoAddrPtr );
//	SX1276LoRaSetOpMode( RFLR_OPMODE_RECEIVER );

//#ifndef	TESTSX1278_TESTSX1278_H_
//	ComArr2[0]= 0;
//	//Waiting for the end of recording
//	while(hspi->State!=HAL_SPI_STATE_READY);
//
//	HAL_GPIO_WritePin(NSS_GPIO_Port,NSS_Pin,GPIO_PIN_RESET);
//	HAL_SPI_TransmitReceive_DMA(hspi, ComArr2, ComArr2, SX1276LR->RegNbRxBytes+1);
//	// calculate SNR and RSSI
//	RxParamCalc();
//	// check the packet data, and save the best
//	// data at which the CRC was corrupted
//	CheckParam();
//#else
	if(SX1276LR->RegNbRxBytes > NumberCommands - 1  ){
		SX1276ReadBuffer(REG_LR_FIFO, Arr,NumberCommands);
//		SX1276LoRaSetOpMode( RFLR_OPMODE_RECEIVER );
	}
	else{
		return HAL_ERROR;
	}

//#endif
	// maybe we need to return pointers to the right position?
//	SX1276LoRaSetOpMode( RFLR_OPMODE_RECEIVER );
	return HAL_OK;
}



// the test function transfers the array to the µ memory.
void TxArrWriteFiFo(uint8_t LocateArrayFifo, uint8_t *DataMas, uint8_t LenArr){

	SX1276Write(REG_LR_FIFOADDRPTR , LocateArrayFifo );
	SX1276WriteBuffer(REG_LR_FIFO, DataMas, LenArr);
}

// write keys to the array before passing.
// I assume that the array will be 4 bytes long.
// keys in the 1st and 3rd byte.
void TxArrWriteKey(uint8_t *DataMass,uint8_t (*KeyMass)[2], int32_t NumMasKey){
	// Can check if DataMass and KeyMass are not out of bounds.
	DataMass[1] = KeyMass[NumMasKey][0];
	DataMass[3] = KeyMass[NumMasKey][1];
}

//функци€ отправл€ет данные в буфер LoRa использу€ DMA.
//ѕосле по окончанию передачи в обработчике прерывани€ от DMA
// провести необходимые действи€.
//LocateArrayFifo указывает с какого адреса в буфере будут находитс€ байты.
// Ё“ќ Ќ≈ –јЅќ„≈≈!!! Ќ≈ ћќ√” «ј—“ј¬»“№ –јЅќ“ј“№ »—ѕќЋ№«”я DMA
void TxArrWriteFiFoDMA(SPI_HandleTypeDef *hspi, \
		uint8_t LocateArrayFifo, uint8_t *DataMas, uint8_t LenArr){
	const uint8_t addr = REG_LR_FIFO | 80 ;
	while(hspi->State!=HAL_SPI_STATE_READY);
	SX1276Write(REG_LR_FIFOADDRPTR , LocateArrayFifo );

	HAL_GPIO_WritePin( NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET );
	//”казываем что будет запись
	HAL_SPI_Transmit(hspi,&addr , 1, 2000);
	HAL_GPIO_WritePin( NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET );

	HAL_GPIO_WritePin( NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET );
	HAL_SPI_TransmitReceive_DMA(hspi, DataMas, DataMas, NumberCommands);
	// по прерыванию от DMA подн€ть NSS.

}


