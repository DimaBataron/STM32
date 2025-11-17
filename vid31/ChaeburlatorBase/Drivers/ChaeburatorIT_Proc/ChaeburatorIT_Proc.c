/*
 * ChaeburatorIT_Proc.c
 *
 *  Created on: Aug 15, 2025
 *      Author: dima
 */


#include "ChaeburatorIT_Proc.h"
#include "DataProcess.h"

// Command codes.
int8_t Acceleration = 0;
int8_t SteerTurn 	= 0;
int8_t CamHorizont 	= 0;
int8_t CamVertical	= 0;
int8_t HeadLights	= 0;
int8_t Load1		= 0;
int8_t Load2		= 0;
int8_t SoundSignal	= 0;

// Error indicator variables
uint32_t PayLoadCRCError = 0; // corrupted CRC
uint32_t NumSuccessPack = 0; // successfully received LoRa packets

// Variable used to output data of successfully received packets.
int8_t OutputNumSuccessPack = 0;

// Variable indicating the reason for the sound and light alarm
uint8_t BatteryStatus = BATTERY_OK;

/*
* Jumps here when interrupted upon receiving a new packet.
* Starts reading packets (DMA usage failed)
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
//	IT_GPIO_Handl(GPIO_Pin);
	if(GPIO_Pin == DIO0_Pin){
		BaseType_t xHigherPriorityTaskWoken;
		xSemaphoreGiveFromISR(SemDMA_LoRaHandle,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
//		RxContLoRaCmplV2(&hspi1);
		RxContLoRaCmpl(ComArr1, &hspi1);
		// Can you add a function to check the received key?
	}

}

// Jumps here when DMA successfully reads commands from memory.
// DMA was called in the RxContLoRaCmplV2 task via an interrupt.
//void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	// Сюда перешли когда данные были прочтены из буфера
//	// дать семафор программе обработчика команд
//	if(hspi == &hspi1){
//		BaseType_t xHigherPriorityTaskWoken;
//		xSemaphoreGiveFromISR(SemDMA_LoRaHandle,&xHigherPriorityTaskWoken);
//		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
//
//	}
//}


//After calling RxContLoRaCmplV2, the ComArr1 array contains commands
//The function calculates commands that will later be used by tasks to control movement.
void CalcRxCommands(){
	static int32_t BufComArr1;

	BufComArr1 = (int8_t) ComArr1[ACCELER];
	CheckRange(&BufComArr1, &Acceleration);

	BufComArr1 = (int32_t)((int8_t)ComArr1[STEER_TURN] + (int8_t)ComArr1[STEER_TRIM]);
	CheckRange(&BufComArr1, &SteerTurn);

	BufComArr1 = (int32_t)((int8_t)ComArr1[CAM_HORIZONT] + (int8_t)ComArr1[CAM_TRIM_HORIZ]);
	CheckRange(&BufComArr1, &CamHorizont);

	BufComArr1 = (int32_t)((int8_t)ComArr1[CAM_VERTICAL] + (int8_t)ComArr1[CAM_TRIM_VERT]);
	CheckRange(&BufComArr1, &CamVertical);


	Load1 = (int8_t)ComArr1[LOAD1];
	Load2 = (int8_t)ComArr1[LOAD2];
	if(HeadLights != ComArr1[HEADLIGHTS]){
		HeadLights = (int8_t)ComArr1[HEADLIGHTS];
		HAL_GPIO_TogglePin(LIGHT1_GPIO_Port, LIGHT1_Pin);
	}

	if(SoundSignal != ComArr1[SOUND_SIG]){
		SoundSignal = (int8_t)ComArr1[SOUND_SIG];
		if(SoundSignal == 1){
			xEventGroupSetBits(xControlEventGroup, BIT_SOUND_ALARM);
		}
		else {
			xEventGroupClearBits(xControlEventGroup, BIT_SOUND_ALARM);
		}
	}

}

//функция проверки передаваемых параметров (int8_t)
// BufComArr1 проверяемое значение
// Command записываемое значение.
void CheckRange(int32_t *BufComArr1, int8_t *Command){
	int32_t value = *BufComArr1;
	if(value > 127){
		*Command = 127;
	}
	else {
		if(value < -127){
			*Command = -127;
		}
		else *Command = (int8_t)value;
	}
}

// Прерывания обратного вызова от таймера1. Я его настроил на секундные прерывания.
// Здесь проверяется количество успешно принятых байт и поврежденных
// Если количество поврежденных больше успешно принятых
// Можно остановить задачи, включить сигнализацию.

// Может приостановить задачу приема, обнулить массив команд.

// Если принятых пакетов нет включить сигнализацию.
/*
 * Временно не используется поэтому закомментарил

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	BaseType_t xHigherPriorityTaskWoken;

  if (htim->Instance == TIM1)
  {
	  if(NumSuccessPack == 0){
		  // Если нет принятых пакетов включить сигнализацию ( задачу сигнализации)
			xSemaphoreGiveFromISR(Sem_Time_RxErrHandle,&xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	  }
	  else {
		  if(PayLoadCRCError > NumSuccessPack){
			  // Много поврежденных пакетов тоже включить сигнализацию.
				xSemaphoreGiveFromISR(Sem_Time_RxErrHandle,&xHigherPriorityTaskWoken);
				portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
		  }
		  else{
			  // отключаю гудело и фары если запущены из этой задачи
			  if(BatteryStatus == VOLT_OK){
					xSemaphoreGiveFromISR(SemControlTaskHandle,&xHigherPriorityTaskWoken);
			  }
		  }
	  }
//	В противном случае ничего не делать все хорошо. Принимать пакеты дальше.

	  OutputNumSuccessPack = (int8_t)NumSuccessPack;
	  NumSuccessPack = 	0;
	  PayLoadCRCError = 0;
  }
}
 */

/*
 * The procedure resets the array with the command.
 */
void ZeroCommArr(){
	int8_t Zero = 0;

	Acceleration = Zero;
	SteerTurn 	= Zero;
	CamHorizont = Zero;
	CamVertical	= Zero;
	HeadLights	= Zero;
	Load1		= Zero;
	Load2		= Zero;
	SoundSignal	= Zero;
}

// Функция проверки вычисленных значений, на то не вышли ли они за пределы
uint8_t CheckBatVolt(float U){
	if(U < WARNING_BAT_VOLTAGE){
		if(U < SHUTDOWN_BAT_VOLTAGE){
			return VOLT_SHUTDOWN;
		}
		else return VOLT_CAUTION;
	}
	else return VOLT_OK;
}


/*
 * Procedure for switching the Cheburlator into warning mode (light signaling)
 */
void Caution(){
	xEventGroupSetBits(xControlEventGroup, BIT_LIGHT_SIGNAL);
}

/*
* Emergency mode stops packet reception, turns on the audible alarm,
* turns on the visual alarm
* cuts off power where possible.
 */
void EmergMode(){
	xEventGroupSetBits(xControlEventGroup, BIT_LIGHT_SIGNAL);
	xEventGroupSetBits(xControlEventGroup, BIT_SOUND_ALARM);

	xEventGroupClearBits(xControlEventGroup, BIT_ACCEPT_PAC);
	ZeroCommArr();
	BatteryStatus = BATTERY_DISC;
	PayLoadCRCError = 0;
	NumSuccessPack = 0;
//	HAL_GPIO_WritePin(P_CONTROL_GPIO_Port, P_CONTROL_Pin, GPIO_PIN_RESET);
}


