/*
 * sx1276-Hal.h
 *
 *  Created on: Dec 28, 2023
 *      Author: dima
 */

#ifndef SX12XXDRIVERS_V2_1_0_SRC_RADIO_SX1276_HAL_H_
#define SX12XXDRIVERS_V2_1_0_SRC_RADIO_SX1276_HAL_H_

#include "SX1276_Start.h"
#include "stdint.h"
typedef enum
{
    RADIO_RESET_OFF,
    RADIO_RESET_ON,
}tRadioResetState;

#define TICK_RATE_MS( ms )                          ( ms )

void SX1276SetReset( uint8_t state );

/*!
 * \brief Writes the radio register at the specified address
 *
 * \param [IN]: addr Register address
 * \param [IN]: data New register value
 */
void SX1276Write( uint8_t addr, uint8_t data );

void SX1276WriteBuffer( uint8_t addr, uint8_t *buffer, uint8_t size );

void SX1276ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size );

void SX1276Read( uint8_t addr, uint8_t *data );

void SX1276ReadFifo( uint8_t *buffer, uint8_t size );

void SX1276WriteFifo( uint8_t *buffer, uint8_t size );

#endif /* SX12XXDRIVERS_V2_1_0_SRC_RADIO_SX1276_HAL_H_ */
