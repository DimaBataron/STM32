/*
 * radio.h
 *
 *  Created on: Dec 28, 2023
 *      Author: dima
 */

#ifndef SX12XXDRIVERS_V2_1_0_SRC_RADIO_RADIO_H_
#define SX12XXDRIVERS_V2_1_0_SRC_RADIO_RADIO_H_
#include "SX1276_Start.h"
#include "stdint.h"
typedef struct sRadioDriver
{
    void ( *Init )( void );
    void ( *Reset )( void );
    void ( *StartRx )( void );
    void ( *GetRxPacket )( void *buffer, uint16_t *size );
    void ( *SetTxPacket )( const void *buffer, uint16_t size );
    uint32_t ( *Process )( void );
}tRadioDriver;

/*!
 * RF process function return codes
 */
typedef enum
{
    RF_IDLE,
    RF_BUSY,
    RF_RX_DONE,
    RF_RX_TIMEOUT,
    RF_TX_DONE,
    RF_TX_TIMEOUT,
    RF_LEN_ERROR,
    RF_CHANNEL_EMPTY,
    RF_CHANNEL_ACTIVITY_DETECTED,
}tRFProcessReturnCodes;
tRadioDriver* RadioDriverInit( void );
#endif /* SX12XXDRIVERS_V2_1_0_SRC_RADIO_RADIO_H_ */
