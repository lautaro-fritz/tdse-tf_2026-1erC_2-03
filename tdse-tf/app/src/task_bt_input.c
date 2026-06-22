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
	task_system_ev_t event = {EV_SYS_IDLE, MANUAL};
	char* message;

    if (huart->Instance == USART3) {
    	if(strcmp(command_string, (uint8_t*) "/manual:1\r\n") == 0) {
    		event.event = EV_SYS_APP_CONNECTED;
		} else if(strcmp(command_string, (uint8_t*) "/manual:0\r\n") == 0) {
			event.event = EV_SYS_APP_DISCONNECTED;
		} else if(strcmp(command_string, (uint8_t*) "/filter:1\r\n") == 0) {
    		event.event = EV_SYS_FILTER_ON;
    	} else if(strcmp(command_string, (uint8_t*) "/filter:0\r\n") == 0) {
			event.event = EV_SYS_FILTER_OFF;
		} else if(strcmp(command_string, (uint8_t*) "/feeder:1\r\n") == 0) {
			event.event = EV_SYS_FEEDER_ON;
		} else if(strcmp(command_string, (uint8_t*) "/feeder:0\r\n") == 0) {
			event.event = EV_SYS_FEEDER_OFF;
		} else {
			sendMessage("Comando no reconocido.\r\n");
			HAL_UART_Receive_DMA(&huart3, command, DMA_BUFFER_SIZE);
			return;
		}
    	put_event_task_system(event);
    }

    HAL_UART_Receive_DMA(&huart3, command, DMA_BUFFER_SIZE);
}

void sendMessage(char* message){
	uint8_t dma_buffer[64];

	strcpy(dma_buffer, message);

    HAL_UART_Transmit_DMA(&huart3, message, strlen(message));
}
