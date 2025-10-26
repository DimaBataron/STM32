/*
 * sx1276-Hal.c
 *
 *  Created on: Dec 28, 2023
 *      Author: dima
 */
#include "sx1276-Hal.h"

void SX1276SetReset( uint8_t state ) //OK
{

    if( state == RADIO_RESET_ON )
    {
        HAL_GPIO_WritePin( Reset_GPIO_Port, Reset_Pin, GPIO_PIN_RESET );
    }
    else
    {
        HAL_GPIO_WritePin( Reset_GPIO_Port, Reset_Pin, GPIO_PIN_SET );
    }
}

void SX1276Write( uint8_t addr, uint8_t data )
{
    SX1276WriteBuffer( addr, &data, 1 );
}

void SX1276WriteBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
    //NSS = 0;
    HAL_GPIO_WritePin( NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET );
    // rewritten using HAL_SPI_Transmit
    uint8_t adr = addr | 0x80;
    SpiInOut( &adr , 1);

    SpiInOut(buffer,size);

    //NSS = 1;
    HAL_GPIO_WritePin( NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);
}

void SX1276ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
    //NSS = 0;
    HAL_GPIO_WritePin( NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET );

    uint8_t adr = addr & 0x7F;
    SpiInOut( &adr, 1 );
    //This one is written, maybe it makes sense to change both to Hal transmitRecieve?
    SpiReceive(buffer, size);

    //NSS = 1;
    HAL_GPIO_WritePin( NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);
}

void SX1276Read( uint8_t addr, uint8_t *data )
{
    SX1276ReadBuffer( addr, data, 1 );
}

void SX1276ReadFifo( uint8_t *buffer, uint8_t size )
{
    SX1276ReadBuffer( 0, buffer, size );
}

void SX1276WriteFifo( uint8_t *buffer, uint8_t size )
{
    SX1276WriteBuffer( 0, buffer, size );
}
