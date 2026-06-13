/*
 * task_timer.c
 *
 *  Created on: Jun 12, 2026
 *      Author: Lautaro Gastón Fritz
 */

#include "main.h"
#include "logger.h"
#include "app.h"
#include "task_system_attribute.h"
#include "task_system_interface.h"

const char *p_task_timer 		= "Task Timer";
const char *p_task_timer_ 		= "Non-Blocking Code";
const char *p_task_timer__ 	= "(Update by Time Code, period = 1mS)";

void task_timer_init(void *parameters)
{
	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_timer_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_timer), p_task_timer);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_timer), p_task_timer_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_timer), p_task_timer__);

	//leer valores para intervalos desde la memoria interna
}

void task_timer_update(void *parameters)
{
	static uint32_t last_relay_cycle_time = 0, last_feeder_cycle_time = 0;
	uint32_t current_time = HAL_GetTick();
	static bool relay_on, feeder_on = false;
	task_system_ev_t system_event = {EV_SYS_IDLE, AUTO};

	if (current_time - last_relay_cycle_time >= 2000)
	{
		if (relay_on)
			system_event.event = EV_SYS_FILTER_ON;
		else
			system_event.event = EV_SYS_FILTER_OFF;

		put_event_task_system(system_event);

		relay_on = !relay_on;
		last_relay_cycle_time = current_time;
	}

	if (current_time - last_feeder_cycle_time >= 5000)
	{
		if (feeder_on)
			system_event.event = EV_SYS_FEEDER_ON;
		else
			system_event.event = EV_SYS_FEEDER_OFF;

		put_event_task_system(system_event);

		feeder_on = !feeder_on;
		last_feeder_cycle_time = current_time;
	}
}
