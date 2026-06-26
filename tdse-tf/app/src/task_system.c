/*
 * Copyright (c) 2026 Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 */

/********************** inclusions *******************************************/
/* Project includes */
#include "main.h"

/* Demo includes */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes */
#include "board.h"
#include "app.h"
#include "task_system_attribute.h"
#include "task_system_interface.h"
#include "task_actuator_attribute.h"
#include "task_actuator_interface.h"
#include "task_pwm_attribute.h"
#include "task_pwm_interface.h"
#include "task_thermometer_attribute.h"

/********************** macros and definitions *******************************/
#define DEL_SYS_MIN			0ul
#define DEL_SYS_MED			250ul
#define DEL_SYS_MAX			500ul

#define SYSTEM_DTA_QTY	MODE_QTY

extern sendMessage(char* message);

/********************** internal data declaration ****************************/
task_system_dta_t task_system_dta_list[SYSTEM_DTA_QTY];

/********************** internal functions declaration ***********************/
void task_system_auto_statechart(void);
void task_system_manual_statechart(void);

/********************** internal data definition *****************************/
const char *p_task_system 		= "Task System (System Statechart)";
const char *p_task_system_ 		= "Non-Blocking Code";
const char *p_task_system__ 	= "(Update by Time Code, period = 1mS)";

task_system_mode_t g_task_system_mode;

/********************** external functions definition ************************/
void task_system_init(void *parameters)
{
	uint32_t index;
	task_system_dta_t 	*p_task_system_dta;
	task_system_st_t	state;
	task_system_ev_t	event;
	bool b_event;

	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_system_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_system), p_task_system);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_system), p_task_system_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_system), p_task_system__);

	init_event_task_system();

	for (index = 0; SYSTEM_DTA_QTY > index; index++)
	{
		/* Update Task System Data Pointer */
		p_task_system_dta = &task_system_dta_list[index];

		/* Init & Print out: Task execution FSM */
		state = ST_SYS_IDLE;
		p_task_system_dta->state = state;

		event.event = EV_SYS_IDLE;
		event.mode = AUTO;
		p_task_system_dta->event = event;

		b_event = false;
		p_task_system_dta->flag = b_event;

		LOGGER_INFO(" ");
		LOGGER_INFO("   %s = %lu   %s = %lu   %s = %s",
					GET_NAME(state), (uint32_t)state,
					GET_NAME(event.event), (uint32_t)event.event,
					GET_NAME(b_event), (b_event ? "true" : "false"));
	}

	task_system_set_mode(AUTO);
}

void task_system_update(void *parameters)
{
	/* Run Task Statechart */
	switch (g_task_system_mode)
	{
		case AUTO:

			task_system_auto_statechart();

			break;

		case MANUAL:

			task_system_manual_statechart();

			break;

		default:

			//task_system_set_mode(AUTO);

			break;
		}
}

void statechart(task_system_dta_t *p_task_system_dta) {
	switch (p_task_system_dta->state) {
	case ST_SYS_IDLE:
		if ((true == p_task_system_dta->flag)
				&& (EV_SYS_FILTER_ON == p_task_system_dta->event.event)) {
			p_task_system_dta->flag = false;
			put_event_task_actuator(EV_ACT_ACTIVE, ID_RELAY_FILTER);
			p_task_system_dta->state = ST_SYS_FILTERING;
			sendMessage("Filter: ON\r\n");
		}
		if ((true == p_task_system_dta->flag)
				&& (EV_SYS_FEEDER_ON == p_task_system_dta->event.event)) {
			p_task_system_dta->flag = false;
			put_event_task_pwm(EV_PWM_ON, ID_PWM_MOTOR);
			p_task_system_dta->state = ST_SYS_FEEDING;
			sendMessage("Feeder: ON\r\n");
		}
		break;
	case ST_SYS_FILTERING:
		if ((true == p_task_system_dta->flag)
				&& (EV_SYS_FILTER_OFF == p_task_system_dta->event.event)) {
			p_task_system_dta->flag = false;
			put_event_task_actuator(EV_ACT_IDLE, ID_RELAY_FILTER);
			p_task_system_dta->state = ST_SYS_IDLE;
			sendMessage("Filter: OFF\r\n");
		}
		if ((true == p_task_system_dta->flag)
				&& (EV_SYS_FEEDER_ON == p_task_system_dta->event.event)) {
			p_task_system_dta->flag = false;
			put_event_task_actuator(EV_ACT_IDLE, ID_RELAY_FILTER);
			put_event_task_pwm(EV_PWM_ON, ID_PWM_MOTOR);
			p_task_system_dta->state = ST_SYS_FEEDING;
			sendMessage("Feeder: ON\r\n");
		}
		break;
	case ST_SYS_FEEDING:
		if ((true == p_task_system_dta->flag)
				&& (EV_SYS_FEEDER_OFF == p_task_system_dta->event.event)) {
			p_task_system_dta->flag = false;
			put_event_task_pwm(EV_PWM_OFF, ID_PWM_MOTOR);
			p_task_system_dta->state = ST_SYS_IDLE;
			sendMessage("Feeder: OFF\r\n");
		}
		break;
	default:
		p_task_system_dta->tick = DEL_SYS_MIN;
		p_task_system_dta->state = ST_SYS_IDLE;
		p_task_system_dta->event.event = EV_SYS_IDLE;
		p_task_system_dta->flag = false;
		break;
	}
}

void task_system_auto_statechart(void)
{
	task_system_dta_t *p_task_system_dta;

	/* Update Task System Data Pointer */
	p_task_system_dta = &task_system_dta_list[AUTO];

	if (true == any_event_task_system())
	{
		p_task_system_dta->flag = true;
		p_task_system_dta->event = get_event_task_system();
	}

	if ((true == p_task_system_dta->flag) && (EV_SYS_APP_CONNECTED == p_task_system_dta->event.event)) {
		p_task_system_dta->flag = false;
		task_system_set_mode(MANUAL);
		put_event_task_pwm(EV_PWM_OFF, ID_PWM_MOTOR);
		put_event_task_actuator(EV_ACT_IDLE, ID_RELAY_FILTER);
		p_task_system_dta->state = ST_SYS_IDLE;
		sendMessage("MANUAL mode: ON\r\n");
		return;
	} else if ((true == p_task_system_dta->flag) && (EV_SYS_APP_DISCONNECTED == p_task_system_dta->event.event)) {
		p_task_system_dta->flag = false;
		//aviso de que ya esta en auto
  		sendMessage("Already in AUTO mode.\r\n");
		return;
	}

	if ((true == p_task_system_dta->flag) && (p_task_system_dta->event.mode != AUTO)) {
		p_task_system_dta->flag = false;
		sendMessage("Manual commands not allowed in AUTO mode.\r\n");
		return;
	}

	statechart(p_task_system_dta);
}

void task_system_manual_statechart(void)
{
	task_system_dta_t *p_task_system_dta;

	/* Update Task System Data Pointer */
	p_task_system_dta = &task_system_dta_list[MANUAL];

	if (true == any_event_task_system())
	{
		p_task_system_dta->flag = true;
		p_task_system_dta->event = get_event_task_system();
	}

	if ((true == p_task_system_dta->flag) && (EV_SYS_APP_CONNECTED == p_task_system_dta->event.event)) {
		p_task_system_dta->flag = false;
		sendMessage("Already in MANUAL mode.\r\n");
		return;
	} else if ((true == p_task_system_dta->flag) && (EV_SYS_APP_DISCONNECTED == p_task_system_dta->event.event)) {
		p_task_system_dta->flag = false;
		task_system_set_mode(AUTO);
		//tengo que reiniciar los timers de alguna forma
		put_event_task_pwm(EV_PWM_OFF, ID_PWM_MOTOR);
		put_event_task_actuator(EV_ACT_IDLE, ID_RELAY_FILTER);
		sendMessage("MANUAL mode: OFF\r\n");
		return;
	}

	if ((true == p_task_system_dta->flag) && (p_task_system_dta->event.mode != MANUAL)) {
		p_task_system_dta->flag = false;
		printf("AUTO event detected while in MANUAL mode, discarding...\n");
		return;
	}

	statechart(p_task_system_dta);
}

void task_system_set_mode(task_system_mode_t task_system_mode)
{
	g_task_system_mode = task_system_mode;
}

/********************** end of file ******************************************/
