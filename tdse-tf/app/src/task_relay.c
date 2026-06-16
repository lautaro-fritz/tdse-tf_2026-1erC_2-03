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
#include "task_relay_attribute.h"
#include "task_relay_interface.h"

/********************** macros and definitions *******************************/
#define RELAY_CFG_QTY	(sizeof(task_relay_cfg_list)/sizeof(task_relay_cfg_t))
#define RELAY_DTA_QTY	RELAY_CFG_QTY

/********************** internal data declaration ****************************/
const task_relay_cfg_t task_relay_cfg_list[] = {
	{ID_REL_LAMP,  RELAY_LAMP_GPIO_Port,  RELAY_LAMP_Pin, REL_LAMP_ON,  REL_LAMP_OFF},
	{ID_REL_FILTER,  RELAY_FILTER_GPIO_Port,  RELAY_FILTER_Pin, REL_LAMP_ON,  REL_LAMP_OFF}
};

task_relay_dta_t task_relay_dta_list[RELAY_DTA_QTY];

/********************** internal functions declaration ***********************/
void task_relay_statechart(uint32_t index);

/********************** internal data definition *****************************/
const char *p_task_relay 		= "Task relay (relay Statechart)";
const char *p_task_relay_ 		= "Non-Blocking Code";
const char *p_task_relay__ 		= "(Update by Time Code, period = 1mS)";

/********************** external data declaration ****************************/

/********************** external functions definition ************************/
void task_relay_init(void *parameters)
{
	uint32_t index;
	const task_relay_cfg_t *p_task_relay_cfg;
	task_relay_dta_t *p_task_relay_dta;
	task_relay_st_t state;
	task_relay_ev_t event;
	bool b_event;

	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_relay_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_relay), p_task_relay);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_relay), p_task_relay_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_relay), p_task_relay__);

	for (index = 0; RELAY_DTA_QTY > index; index++)
	{
		/* Update Task Relay Configuration & Data Pointer */
		p_task_relay_cfg = &task_relay_cfg_list[index];
		p_task_relay_dta = &task_relay_dta_list[index];

		/* Init & Print out: Index & Task execution FSM */
		state = ST_REL_OFF;
		p_task_relay_dta->state = state;

		event = EV_REL_TOGGLE;
		p_task_relay_dta->event = event;

		b_event = false;
		p_task_relay_dta->flag = b_event;

		LOGGER_INFO(" ");
		LOGGER_INFO("   %s = %lu   %s = %lu   %s = %lu   %s = %s",
					 GET_NAME(index), index,
					 GET_NAME(state), (uint32_t)state,
					 GET_NAME(event), (uint32_t)event,
					 GET_NAME(b_event), (b_event ? "true" : "false"));

		HAL_GPIO_WritePin(p_task_relay_cfg->gpio_port, p_task_relay_cfg->pin, p_task_relay_cfg->rel_off);
	}
}

void task_relay_update(void *parameters)
{
	uint32_t index;

	for (index = 0; RELAY_DTA_QTY > index; index++)
	{
		/* Run Task Statechart */
		task_relay_statechart(index);
	}
}

void task_relay_statechart(uint32_t index)
{
	const task_relay_cfg_t *p_task_relay_cfg;
	task_relay_dta_t *p_task_relay_dta;

	/* Update Task Relay Configuration & Data Pointer */
	p_task_relay_cfg = &task_relay_cfg_list[index];
	p_task_relay_dta = &task_relay_dta_list[index];

	switch (p_task_relay_dta->state)
	{
		case ST_REL_OFF:

			if ((true == p_task_relay_dta->flag) && (EV_REL_TOGGLE == p_task_relay_dta->event))
			{
				p_task_relay_dta->flag = false;
				HAL_GPIO_WritePin(p_task_relay_cfg->gpio_port, p_task_relay_cfg->pin, p_task_relay_cfg->rel_on);
				p_task_relay_dta->state = ST_REL_ON;
			}

			break;

		case ST_REL_ON:

			if ((true == p_task_relay_dta->flag) && (EV_REL_TOGGLE == p_task_relay_dta->event))
			{
				p_task_relay_dta->flag = false;
				HAL_GPIO_WritePin(p_task_relay_cfg->gpio_port, p_task_relay_cfg->pin, p_task_relay_cfg->rel_off);
				p_task_relay_dta->state = ST_REL_OFF;
			}

			break;

		default:

			p_task_relay_dta->state = ST_REL_OFF;
			p_task_relay_dta->event = EV_REL_TOGGLE;
			p_task_relay_dta->flag = false;

			break;
	}
}

/********************** end of file ******************************************/
