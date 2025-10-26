/*
 * spi.c
 *
 *  Created on: Dec 29, 2023
 *      Author: dima
 */

#include "spi.h"

#ifndef G03108
extern SPI_HandleTypeDef hspi2;
#else
extern SPI_HandleTypeDef hspi1;
#endif


uint8_t SpiInOut(uint8_t *outData, uint8_t size )
{
    /* Send SPIy data */
    //SPI_I2S_SendData( SPI_INTERFACE, outData );
#ifndef G03108
	HAL_SPI_Transmit(&hspi2, outData, (uint16_t)size, 2000);
#else
	HAL_SPI_Transmit(&hspi1, outData, (uint16_t)size, 2000);
#endif
	//while( SPI_I2S_GetFlagStatus( SPI_INTERFACE, SPI_I2S_FLAG_RXNE ) == RESET );
    //return SPI_I2S_ReceiveData( SPI_INTERFACE );
	return 0;
}

uint8_t SpiReceive(uint8_t *outData, uint8_t size){

#ifndef G03108
	HAL_SPI_Receive(&hspi2, outData, (uint16_t)size,2000);
#else
	HAL_SPI_Receive(&hspi1, outData, (uint16_t)size,2000);
#endif
	return 0;
}
