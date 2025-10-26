/*
 * sx1276.h
 *
 *  Created on: Dec 28, 2023
 *      Author: dima
 */


#ifndef SX12XXDRIVERS_V2_1_0_SRC_RADIO_SX1276_H_
#define SX12XXDRIVERS_V2_1_0_SRC_RADIO_SX1276_H_
#include "SX1276_Start.h"
#include "stdbool.h"


#ifdef STARTTEST_H_
extern uint8_t SX1276Regs[0x70];
#endif
void SX1276Init( void );

void SX1276Reset( void );

//void SX1278RegStartConf( void );

void SX1276SetLoRaOn( bool enable );

/*!
 * \brief Sets the SX1276 operating mode
 *
 * \param [IN] opMode New operating mode
 */
void SX1276LoRaSetOpMode( uint8_t opMode );

void SX1276StartRx( void );

void SX1276GetRxPacket( void *buffer, uint16_t *size );

void SX1276SetTxPacket( const void *buffer, uint16_t size );

uint32_t SX1276Process( void );

void RXTX(bool antennaSwitchTxOn);



#endif /* SX12XXDRIVERS_V2_1_0_SRC_RADIO_SX1276_H_ */
