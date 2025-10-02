/*
 * UART_Terminal.c
 *
 *  Created on: Sep 21, 2025
 *      Author: dima
 * Here are functions for receiving and outputting data to the UART.
 * Output functions are used in blocking mode.
 * Input functions use interrupts.
 * If the end of a line is detected, the selected byte is written.
 * (the end of a line in our system) Don't forget to configure PuTTy
 * according to the parameters specified here.
 *
 */
#include "UART_Terminal.h"
#include <string.h>
#include "Console_Func.c"

uint8_t CharUartRX = 0; // принятый символ

void StartUartRX(){
	HAL_UART_RxCpltCallback(NULL);
}


/*
 * The task writes bytes received from the console to the queue
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart!= NULL){
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xQueueSendFromISR(UART_Rx_QueHandle,&CharUartRX, &xHigherPriorityTaskWoken);

		HAL_UART_Receive_IT(huart, &CharUartRX, 1);
	}
	else{
		HAL_UART_Receive_IT(&huart1, &CharUartRX, 1);
	}
	// commented, assuming the context doesn't need to be changed. I'll wait for the tick.
//	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*
 * A function called from the console handler task
 * reads data from the queue (the queue is filled with console characters)
 * and writes it to the passed array.
 * Checks the end-of-line character and replaces it with the one accepted in
 * the given terminal application.
 */

uint32_t USART1_Receive(uint8_t chr, uint8_t *Buffer, uint32_t Length, TickType_t TimesUp)
{
uint8_t Receive;
uint32_t i=0;

    while(1)
    {
        if(pdTRUE!=xQueueReceive(UART_Rx_QueHandle,&Receive,TimesUp)) return 0;

        if(Receive == chr)
        {
            Buffer[i++] = 0x0A; //LF  OLD = chr
            return i;
        }

        if(i<Length)
        {
            Buffer[i++]=Receive;
        }
        else
        {
            return i;
        }
    }
}

/*
* I'm creating a UART output function in blocking mode.
* The function is used by the terminal to output to the console.
 */

void console_write_function(const char* str)
{
	uint16_t Size = strlen(str);
	HAL_UART_Transmit(&huart1, (uint8_t *)str, Size, 5000);
}



/*
 * Console initialization
 * Call this once in the task before using the console
 * Register all new commands here. Before doing this, don't forget to register
 * the macros and functions for these tasks in the Console_Func.c file
 */
void MyConsole_Setup(void)
{
	static console_init_t init_func;
	// Start receiving via UART using interrupts.
	StartUartRX();

	// Set the output function.
	init_func.write_function = console_write_function;
    console_init(&init_func);

    //Register commands. In this case, these are the commands hello, s
    console_command_register(hello);
    console_command_register(s);
//    console_command_register(get);
}
