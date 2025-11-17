/*
 * sx1276.c
 *
 *  Created on: Dec 28, 2023
 *      Author: dima
 */
#include "sx1276.h"

uint8_t SX1276Regs[0x70];

static bool LoRaOn = false;
static bool LoRaOnState = false;

void SX1276Init( void )
{
    // Initialize FSK and LoRa registers structure

    SX1276LR = ( tSX1276LR* )SX1276Regs;

    SX1276Reset( );

    LoRaOn = true;
    SX1276SetLoRaOn( LoRaOn );
    // Initialize LoRa modem
    SX1276LoRaInit( );
//    HAL_Delay(200);
}

void SX1276Reset( void )
{
    SX1276SetReset( RADIO_RESET_ON );

    HAL_Delay(100);

    SX1276SetReset( RADIO_RESET_OFF );

    HAL_Delay(100);
}

void SX1276SetLoRaOn( bool enable )
{
//    if( LoRaOnState == enable )
//    {
//        return;
//    }
    LoRaOnState = enable;
    LoRaOn = enable;

    if( LoRaOn == true )
    {
        SX1276LoRaSetOpMode( RFLR_OPMODE_SLEEP );

        SX1276LR->RegOpMode = ( SX1276LR->RegOpMode & RFLR_OPMODE_LONGRANGEMODE_MASK ) | RFLR_OPMODE_LONGRANGEMODE_ON;
        //RegOpMode = 0b10000000  (LoRa mode and sleep)
        SX1276Write( REG_LR_OPMODE, SX1276LR->RegOpMode );
        //RegOpmode =0b10000001 (LoRa mode and waiting)
        SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );
                                        // RxDone               RxTimeout                   FhssChangeChannel           CadDone
        SX1276LR->RegDioMapping1 = RFLR_DIOMAPPING1_DIO0_00 | RFLR_DIOMAPPING1_DIO1_00 | RFLR_DIOMAPPING1_DIO2_00 | RFLR_DIOMAPPING1_DIO3_00;
                                        // CadDetected          ModeReady
        SX1276LR->RegDioMapping2 = RFLR_DIOMAPPING2_DIO4_00 | RFLR_DIOMAPPING2_DIO5_00;
//        RegDioMapping1 è 2 = 0b0
        SX1276WriteBuffer( REG_LR_DIOMAPPING1, &SX1276LR->RegDioMapping1, 2 );
// 		here everything is read from memory LoRa but at the same time garbage is written there.
        SX1276ReadBuffer( REG_LR_OPMODE, SX1276Regs + 1, 0x70 - 1 );
    }
    else
    {
        SX1276LoRaSetOpMode( RFLR_OPMODE_SLEEP );

        SX1276LR->RegOpMode = ( SX1276LR->RegOpMode & RFLR_OPMODE_LONGRANGEMODE_MASK ) | RFLR_OPMODE_LONGRANGEMODE_OFF;
        SX1276Write( REG_LR_OPMODE, SX1276LR->RegOpMode );

        SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );

        SX1276ReadBuffer( REG_OPMODE, SX1276Regs + 1, 0x70 - 1 );
    }
}

void SX1276LoRaSetOpMode( uint8_t opMode )
{
    static uint8_t opModePrev = RFLR_OPMODE_STANDBY;
    static bool antennaSwitchTxOnPrev = true;
    bool antennaSwitchTxOn = false;

    opModePrev = SX1276LR->RegOpMode & ~RFLR_OPMODE_MASK;

    if( opMode != opModePrev )
    {
        if( opMode == RFLR_OPMODE_TRANSMITTER )
        {
            antennaSwitchTxOn = true;
        }
        else
        {
            antennaSwitchTxOn = false;
        }
        if( antennaSwitchTxOn != antennaSwitchTxOnPrev )
        {
            antennaSwitchTxOnPrev = antennaSwitchTxOn;
            // Controls DIO3 extension ( antenna circuit selection)
			#ifdef MoskitoV01
            RXTX( antennaSwitchTxOn ); // Antenna switch control
			#endif

        }
    }
    SX1276LR->RegOpMode = ( SX1276LR->RegOpMode & RFLR_OPMODE_MASK ) | opMode;

    SX1276Write( REG_LR_OPMODE, SX1276LR->RegOpMode );
}

void SX1276StartRx( void )
{
    /* if( LoRaOn == false )
    {
        SX1276FskSetRFState( RF_STATE_RX_INIT );
    }

    else
    {
    */
        SX1276LoRaSetRFState( RFLR_STATE_RX_INIT );
    //}
}

void SX1276GetRxPacket( void *buffer, uint16_t *size )
{
	/*
    if( LoRaOn == false )
    {
        SX1276FskGetRxPacket( buffer, size );
    }
    else
    {
    */
        SX1276LoRaGetRxPacket( buffer, size );
    //}
}

void SX1276SetTxPacket( const void *buffer, uint16_t size )
{
	/*
    if( LoRaOn == false )
    {
        SX1276FskSetTxPacket( buffer, size );
    }
    else
    {
    */
        SX1276LoRaSetTxPacket( buffer, size );
    //}
}
void RXTX(bool antennaSwitchTxOn){

	if(antennaSwitchTxOn == true){ 		//Tx PA_BOOST

		HAL_GPIO_WritePin(DIO3_GPIO_Port, DIO3_Pin, GPIO_PIN_RESET);
	}
	else{ 								//Rx
		HAL_GPIO_WritePin(DIO3_GPIO_Port, DIO3_Pin, GPIO_PIN_SET);
	}

}



/*
uint32_t SX1276Process( void )
{
    if( LoRaOn == false )
    {
//        return SX1276FskProcess( );
    }
    else
    {

        return SX1276LoRaProcess( );
    //}
}
    */

//void SX1278RegStartConf( void ){
//	SX1276LR->RegOpMode =  RFLR_OPMODE_FREQMODE_ACCESS_LF | RFLR_OPMODE_STANDBY;
//	SX1276LR->RegFrfMsb = 0x6C;
//	SX1276LR->RegFrfMid = 0x80;
//	SX1276LR->RegFrfLsb = 0x00;
//	SX1276LR->RegPaConfig = RFLR_PACONFIG_PASELECT_RFO | RFLR_PACONFIG_MAX_POWER_Res | RFLR_PACONFIG_OUTPUTPOWER_Res;
//	SX1276LR->RegPaRamp = RFLR_PARAMP_0040_US ; // 40us
//	SX1276LR->RegOcp = RFLR_OCP_ON | RFLR_OCP_TRIM_100_MA;
//	SX1276LR->RegLna = RFLR_LNA_GAIN_G1 | RFLR_LNA_BOOST_LF_DEFAULT | RFLR_LNA_RXBANDFORCE_AUTO;
//	SX1276LR->RegFifoAddrPtr = 		0x00;
//	SX1276LR->RegFifoTxBaseAddr  = 	0x02; //!!!!!???
//	SX1276LR->RegFifoRxBaseAddr = 	0x00;
//	SX1276LR->RegIrqFlagsMask = 	0x00;
//	SX1276LR->RegIrqFlags = 		0x00;
//	SX1276LR->RegModemStat = 		1 << 4;
//	SX1276LR->RegModemConfig1 =     0x00; // it's in lora mode RFLR_MODEMCONFIG1_CODINGRATE_4_5 | RFLR_MODEMCONFIG1_BW_125_KHZ;
//	SX1276LR->RegModemConfig2 =     0x00; // lora 	RFLR_MODEMCONFIG2_SF_7;
//	SX1276LR->RegSymbTimeoutLsb = 	0x68;
//	SX1276LR->RegPreambleMsb = 		0x00;
//	SX1276LR->RegPreambleLsb = 		0x00; // lora 0x08;
//	SX1276LR->RegPayloadLength = 	0x00; // lora 0x01;
//	SX1276LR->RegMaxPayloadLength = 0x00; // lora 0xFF;
//	SX1276LR->RegHopPeriod = 		0x00;
//	SX1276LR->RegModemConfig3 =		0x03; // lora 0x00
//	SX1276LR->RegFeiMsb = 			0x00;
//	SX1276LR->RegFeiMib = 			0x00;
//	SX1276LR->RegFeiLsb =			0x00;
////	SX1276LR->RegTestReserved2B[0] =0x20; ??? see register table.
//	SX1276LR->RegDetectOptimize =   0x40;//lora RFLR_DETECTOPT_DETOP_SF7_SF12 | RFLR_DETECTOPT_Reserv | RFLR_DETECTOPT_AUTO_IF_ON;
//	SX1276LR->RegInvertIQ = RFLR_INVERTIQ_RESERVER;
////	SX1276LR->RegTestReserved34[4] = 0x20; //???
//	SX1276LR->RegDetectionThreshold = 0x00;  //lora RFLR_DETECTION_TRESHOLD_SF7_SF12;
////	SX1276LR->RegTestReserved38[1] = 0x12; //????
//	SX1276LR->RegDioMapping1 = 		0x00;
//	SX1276LR->RegDioMapping2 = 		0x00;
//	SX1276LR->RegVersion = 			0x12;
//	SX1276LR->RegTcxo = RFLR_TCXO_TCXOINPUT_OFF; //???
//	SX1276LR->RegPaDac = RFLR_PADAC_20DBM_ON;	//????
//	SX1276LR->RegAgcRef = 0x13;
//	SX1276LR->RegAgcThresh1 = 0x0E;
//	SX1276LR->RegAgcThresh2 = 0x5B;
//	SX1276LR->RegAgcThresh3 = 0xDB;
////	SX1276LR + 0x70 = 0xD0; //??
//}
