/*
 * sx1276-Lora.c
 *
 *  Created on: Dec 28, 2023
 *      Author: dima
 */
#include "sx1276-Lora.h"


tSX1276LR* SX1276LR;

extern uint8_t SX1276Regs[0x70];

/*!
 * Local RF buffer for communication support
 */
//static uint8_t RFBuffer[RF_BUFFER_SIZE];
/*!
 * RF state machine variable
 */
static uint8_t RFLRState = RFLR_STATE_IDLE;

/*!
 * Constant values need to compute the RSSI value
 */
#define RSSI_OFFSET_LF                              -164.0
#define RSSI_OFFSET_HF                              -157.0


// Default settings
tLoRaSettings LoRaSettings =
{
	433500000,        // RFFrequency
    17, //20               // Power
    9,                // SignalBw [0: 7.8kHz, 1: 10.4 kHz, 2: 15.6 kHz, 3: 20.8 kHz, 4: 31.2 kHz,
                      // 5: 41.6 kHz, 6: 62.5 kHz, 7: 125 kHz, 8: 250 kHz, 9: 500 kHz, other: Reserved]
	9, //12,         // SpreadingFactor [6: 64, 7: 128, 8: 256, 9: 512, 10: 1024, 11: 2048, 12: 4096  chips]
	2,				  // ErrorCoding [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
    true,             // CrcOn [0: OFF, 1: ON]
    false,            // ImplicitHeaderOn [0: OFF, 1: ON]
    false,                // RxSingleOn [0: Continuous, 1 Single]
    0,                // FreqHopOn [0: OFF, 1: ON]
    0,                // HopPeriod Hops every frequency hopping period symbols
    100,              // TxPacketTimeout
    100,              // RxPacketTimeout
    128,              // PayloadLength (used for implicit header mode)
};
/*!
 * Frequency hopping frequencies table
 */
const int32_t HoppingFrequencies[] =
{
    916500000,
    923500000,
    906500000,
    917500000,
    917500000,
    909000000,
    903000000,
    916000000,
    912500000,
    926000000,
    925000000,
    909500000,
    913000000,
    918500000,
    918500000,
    902500000,
    911500000,
    926500000,
    902500000,
    922000000,
    924000000,
    903500000,
    913000000,
    922000000,
    926000000,
    910000000,
    920000000,
    922500000,
    911000000,
    922000000,
    909500000,
    926000000,
    922000000,
    918000000,
    925500000,
    908000000,
    917500000,
    926500000,
    908500000,
    916000000,
    905500000,
    916000000,
    903000000,
    905000000,
    915000000,
    913000000,
    907000000,
    910000000,
    926500000,
    925500000,
    911000000,
};

/*!
 * PacketTimeout Stores the Rx window time value for packet reception
 */
//static uint32_t PacketTimeout;

void SX1276LoRaInit( void )
{
    RFLRState = RFLR_STATE_IDLE;
//    SX1276LR->RegOpMode = RFLR_OPMODE_SLEEP;


    SX1276LoRaSetDefaults( );

    SX1276ReadBuffer( REG_LR_OPMODE, SX1276Regs + 1, 0x70 - 1 );

    SX1276LR->RegLna = RFLR_LNA_GAIN_G1;
//    RegLna=0b100000 = Maximum amplifier gain
    SX1276WriteBuffer( REG_LR_OPMODE, SX1276Regs + 1, 0x70 - 1 );

    // set the RF settings
    SX1276LoRaSetRFFrequency( LoRaSettings.RFFrequency );

    // SF6 only operates in implicit header mode.
    SX1276LoRaSetSpreadingFactor( LoRaSettings.SpreadingFactor );
    SX1276LoRaSetErrorCoding( LoRaSettings.ErrorCoding );
    SX1276LoRaSetPacketCrcOn( LoRaSettings.CrcOn );
    SX1276LoRaSetSignalBandwidth( LoRaSettings.SignalBw );

    SX1276LoRaSetImplicitHeaderOn( LoRaSettings.ImplicitHeaderOn );
    SX1276LoRaSetSymbTimeout( 0x3FF );
    SX1276LoRaSetPayloadLength( LoRaSettings.PayloadLength );
    SX1276LoRaSetLowDatarateOptimize( true );

    if( LoRaSettings.RFFrequency > 860000000 )
    {
        SX1276LoRaSetPAOutput( RFLR_PACONFIG_PASELECT_RFO );
        SX1276LoRaSetPa20dBm( false );
        LoRaSettings.Power = 14;
        SX1276LoRaSetRFPower( LoRaSettings.Power );
    }
    else
    {

  // Here change to the required one using the amplifier features,



#ifdef MoskitoV02
        SX1276LoRaSetPAOutput(RFLR_PACONFIG_PASELECT_RFO);
#endif
#ifdef Ra_02_AI_Thinker
        SX1276LoRaSetPAOutput( RFLR_PACONFIG_PASELECT_PABOOST );
#endif
#ifdef MoskitoV01
        SX1276LoRaSetPAOutput( RFLR_PACONFIG_PASELECT_PABOOST );
#endif
        //true Power limited to +20dBm
//       SX1276LoRaSetPa20dBm( true );
        SX1276LoRaSetPa20dBm( false );
//        LoRaSettings.Power = 5;
//        LoRaSettings.Power = 17;
        SX1276LoRaSetRFPower( LoRaSettings.Power );
    }
    SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );
}

void SX1276LoRaSetDefaults( void )
{
    // REMARK: See SX1276 datasheet for modified default values.
	SX1276Read( REG_LR_VERSION, &SX1276LR->RegVersion ); //old version
//    SX1276Read( REG_LR_VERSION, SX1276LR->RegVersion );
}

void SX1276LoRaSetRFState( uint8_t state )
{
    RFLRState = state;
}

uint8_t SX1276LoRaReadRxGain( void )
{
    SX1276Read( REG_LR_LNA, &SX1276LR->RegLna );
    return( SX1276LR->RegLna >> 5 ) & 0x07;
}
