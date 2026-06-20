/*
 * task_timer.c
 *
 *  Created on: Jun 19, 2026
 *      Author: Lautaro Gastón Fritz
 */

#include "main.h"
#include "logger.h"
#include "app.h"
#include "task_system_attribute.h"
#include "task_system_interface.h"

#define DMA_BUFFER_SIZE 11u

extern UART_HandleTypeDef huart3;

const char *p_task_bt 		= "Task BT Input";
const char *p_task_bt_ 		= "Non-Blocking Code";
const char *p_task_bt__ 	= "(Update by Time Code, period = 1mS)";

uint8_t command[DMA_BUFFER_SIZE];

void task_bt_input_init(void *parameters)
{
	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_bt_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_bt), p_task_bt);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_bt), p_task_bt_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_bt), p_task_bt__);

	HAL_UART_Receive_DMA(&huart3, command, DMA_BUFFER_SIZE);
}

void task_bt_input_update(void *parameters)
{

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	uint8_t command_string[DMA_BUFFER_SIZE + 1];
	strcpy(command_string, command);
	command_string[DMA_BUFFER_SIZE] = '\0';

    if (huart->Instance == USART3) {
    	if(strcmp(command_string, (uint8_t*) "/filter:1\r\n") == 0) {
    		printf("aaa\n");
    	}

        HAL_UART_Transmit(&huart3, command, DMA_BUFFER_SIZE, 100);
    }

    HAL_UART_Receive_DMA(&huart3, command, DMA_BUFFER_SIZE);
}
