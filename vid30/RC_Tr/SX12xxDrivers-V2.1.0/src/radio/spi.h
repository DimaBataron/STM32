/*
 * spi.h
 *
 *  Created on: Dec 29, 2023
 *      Author: dima
 */

#ifndef SX12XXDRIVERS_V2_1_0_SRC_RADIO_SPI_H_
#define SX12XXDRIVERS_V2_1_0_SRC_RADIO_SPI_H_

#include "SX1276_Start.h"
#include "stdint.h"

uint8_t SpiInOut(uint8_t *outData, uint8_t size );

uint8_t SpiReceive(uint8_t *outData, uint8_t size);

#endif /* SX12XXDRIVERS_V2_1_0_SRC_RADIO_SPI_H_ */
