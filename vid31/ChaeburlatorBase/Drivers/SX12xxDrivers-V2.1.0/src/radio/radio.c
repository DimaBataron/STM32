/*
 * radio.c
 *
 *  Created on: Dec 28, 2023
 *      Author: dima
 */
//#include "main.h"
#include "radio.h"
tRadioDriver RadioDriver;

tRadioDriver* RadioDriverInit( void )
{
    RadioDriver.Init = SX1276Init;
    RadioDriver.Reset = SX1276Reset;
    RadioDriver.StartRx = SX1276StartRx;
    RadioDriver.GetRxPacket = SX1276GetRxPacket;
    RadioDriver.SetTxPacket = SX1276SetTxPacket;
    RadioDriver.Process = SX1276Process;
    return &RadioDriver;
}

