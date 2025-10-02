/*
 * Console_Func.c
 *
 *  Created on: Sep 22, 2025
 *      Author: dima
 * In this file, write all commands used in the test terminal.
 * Then register them in the void MyConsole_Setup(void) function.
 *
 * Add an engine control command (implements smooth acceleration and stopping).
 *
 */

#ifndef UART_TERMINAL_CONSOLE_FUNC_C_
#define UART_TERMINAL_CONSOLE_FUNC_C_

#include "console.h"
#include "UART_Terminal.h"

#include "stdio.h"

CONSOLE_COMMAND_DEF(hello, "Say hello!");

static void hello_command_handler(const hello_args_t* args)
{
	console_write_function("Hi!\n");
}

/*
 * Console output of task information.
 * Used to determine the memory required by a task.
 */

CONSOLE_COMMAND_DEF(s, "Gets a task info",
		CONSOLE_STR_ARG_DEF(task, "RTOS Task Name"));

static void s_command_handler(const s_args_t* args)
{
	static char Mas[30];
	uint16_t LenStr = 0;
	// Show the free heap size.
	// Calling this function frequently will show if there is a memory leak.
	LenStr = sprintf(Mas,"Heap Size = %d \r\n", (int)xPortGetFreeHeapSize());
	HAL_UART_Transmit(&huart1, (uint8_t*)Mas, LenStr, 5000);

	// Show task uptime in seconds. FreeRTOS counts ticks, but mine are set to 1ms.
	LenStr = sprintf(Mas,"Uptime = %d s \r\n", (int)(xTaskGetTickCount()/1000));
	HAL_UART_Transmit(&huart1, (uint8_t*)Mas, LenStr, 5000);

    TaskStatus_t xTaskStatus; // Create a structure for the status.

    // We read and obtain the title of the desired task.
    //The task's text label is passed as a parameter.
    // The task name is specified in quotation marks when created.
    TaskHandle_t xTask = xTaskGetHandle(args->task);

    // Read the task data by its title
    vTaskGetInfo(xTask, &xTaskStatus, pdTRUE, eInvalid);

    // Display information about the task
    LenStr = sprintf(Mas,"Task name: %s \r\n", xTaskStatus.pcTaskName);
    HAL_UART_Transmit(&huart1, (uint8_t*)Mas, LenStr, 5000);

    // Show the current task status.
    // 0 - running, 1 - waiting to start, ready,
    // 2 - blocked (waiting for something on a timer),
    // 3 - dormant (blocked with an infinite timeout),
    // 4 - deleted,
    // 5 - error.
    LenStr = sprintf(Mas,"Task status: %d \r\n", xTaskStatus.eCurrentState);
    HAL_UART_Transmit(&huart1, (uint8_t*)Mas, LenStr, 5000);

    // Show the current priority of the task.
    LenStr = sprintf(Mas,"Task priority: %d \r\n", (int)xTaskStatus.uxCurrentPriority);
    HAL_UART_Transmit(&huart1, (uint8_t*)Mas, LenStr, 5000);

    // Show the largest stack occupancy in the entire execution history.
    // How much free space remains in the worst case.
    LenStr = sprintf(Mas,"Task Freespace: %d \r\n", xTaskStatus.usStackHighWaterMark);
    HAL_UART_Transmit(&huart1, (uint8_t*)Mas, LenStr, 5000);
}

#endif /* UART_TERMINAL_CONSOLE_FUNC_C_ */
