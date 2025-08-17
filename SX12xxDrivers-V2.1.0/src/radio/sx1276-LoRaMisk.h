/*
 * sx1276-LoRaMisk.h
 *
 *  Created on: Dec 29, 2023
 *      Author: dima
 */

#ifndef SX12XXDRIVERS_V2_1_0_SRC_RADIO_SX1276_LORAMISK_H_
#define SX12XXDRIVERS_V2_1_0_SRC_RADIO_SX1276_LORAMISK_H_

#include "SX1276_Start.h"
#include "stdbool.h"
/*!
 * \brief Writes the new RF frequency value
 *
 * \param [IN] freq New RF frequency value in [Hz]
 */
void SX1276LoRaSetRFFrequency( uint32_t freq );

void SX1276LoRaSetSpreadingFactor( uint8_t factor );

void SX1276LoRaSetNbTrigPeaks( uint8_t value );

void SX1276LoRaSetErrorCoding( uint8_t value );

void SX1276LoRaSetPacketCrcOn( bool enable );

void SX1276LoRaSetSignalBandwidth( uint8_t bw );

void SX1276LoRaSetImplicitHeaderOn( bool enable );

void SX1276LoRaSetSymbTimeout( uint16_t value );

void SX1276LoRaSetPayloadLength( uint8_t value );

void SX1276LoRaSetLowDatarateOptimize( bool enable );

void SX1276LoRaSetPAOutput( uint8_t outputPin );

void SX1276LoRaSetPa20dBm( bool enale );

void SX1276LoRaSetRFPower( int8_t power );
#endif /* SX12XXDRIVERS_V2_1_0_SRC_RADIO_SX1276_LORAMISK_H_ */
