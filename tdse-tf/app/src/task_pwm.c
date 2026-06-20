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
#include "task_pwm_attribute.h"
#include "task_pwm_interface.h"

/********************** macros and definitions *******************************/
#define PWM_CFG_QTY	(sizeof(task_pwm_cfg_list)/sizeof(task_pwm_cfg_t))
#define PWM_DTA_QTY	PWM_CFG_QTY

extern TIM_HandleTypeDef htim3;

/********************** internal data declaration ****************************/
task_pwm_cfg_t task_pwm_cfg_list[] = {
	{ID_PWM_MOTOR,  GPIOB,  GPIO_PIN_4, 0.0, 0.0, &htim3, TIM_CHANNEL_1},
};

task_pwm_dta_t task_pwm_dta_list[PWM_DTA_QTY];

/********************** internal functions declaration ***********************/
void task_pwm_statechart(uint32_t index);

/********************** internal data definition *****************************/
const char *p_task_pwm 		= "Task pwm (pwm Statechart)";
const char *p_task_pwm_ 		= "Non-Blocking Code";
const char *p_task_pwm__ 		= "(Update by Time Code, period = 1mS)";

/********************** external data declaration ****************************/

/********************** external functions definition ************************/
void task_pwm_init(void *parameters)
{
	uint32_t index;
	const task_pwm_cfg_t *p_task_pwm_cfg;
	task_pwm_dta_t *p_task_pwm_dta;
	task_pwm_st_t state;
	task_pwm_ev_t event;
	bool b_event;

	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_pwm_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_pwm), p_task_pwm);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_pwm), p_task_pwm_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_pwm), p_task_pwm__);

	for (index = 0; PWM_DTA_QTY > index; index++)
	{
		/* Update Task PWM Configuration & Data Pointer */
		p_task_pwm_cfg = &task_pwm_cfg_list[index];
		p_task_pwm_dta = &task_pwm_dta_list[index];

		/* Init & Print out: Index & Task execution FSM */
		state = ST_PWM_OFF;
		p_task_pwm_dta->state = state;

		event = EV_PWM_OFF;
		p_task_pwm_dta->event = event;

		b_event = false;
		p_task_pwm_dta->flag = b_event;

		LOGGER_INFO(" ");
		LOGGER_INFO("   %s = %lu   %s = %lu   %s = %lu   %s = %s",
					 GET_NAME(index), index,
					 GET_NAME(state), (uint32_t)state,
					 GET_NAME(event), (uint32_t)event,
					 GET_NAME(b_event), (b_event ? "true" : "false"));

		__HAL_TIM_SET_COMPARE(p_task_pwm_cfg->htim, p_task_pwm_cfg->channel, 1000);
		HAL_TIM_PWM_Start(p_task_pwm_cfg->htim, p_task_pwm_cfg->channel);
	}
}

void task_pwm_update(void *parameters)
{
	uint32_t index;

	for (index = 0; PWM_DTA_QTY > index; index++)
	{
		/* Run Task Statechart */
		task_pwm_statechart(index);
	}
}

void task_pwm_statechart(uint32_t index)
{
	task_pwm_cfg_t *p_task_pwm_cfg;
	task_pwm_dta_t *p_task_pwm_dta;

	/* Update Task PWM Configuration & Data Pointer */
	p_task_pwm_cfg = &task_pwm_cfg_list[index];
	p_task_pwm_dta = &task_pwm_dta_list[index];

	switch (p_task_pwm_dta->state)
	{
		case ST_PWM_OFF:
		//case ST_PWM_IDLE:

			/*if ((true == p_task_pwm_dta->flag) && (EV_PWM_MOVE == p_task_pwm_dta->event))
			{
				p_task_pwm_dta->flag = false;
				//por si el servo no se posiciona exactamente en 0.0
				if (p_task_pwm_cfg->current_angle < 1.0f)
					p_task_pwm_cfg->target_angle = 180.0f;
				else
					p_task_pwm_cfg->target_angle = 0.0f;
				p_task_pwm_dta->state = ST_PWM_MOVING;
			}*/

			if ((true == p_task_pwm_dta->flag) && (EV_PWM_ON == p_task_pwm_dta->event))
			{
				if (p_task_pwm_cfg->current_angle < 1.0f)
					p_task_pwm_cfg->target_angle = 180.0f;
				p_task_pwm_dta->state = ST_PWM_MOVING;
			}

			break;

		case ST_PWM_ON:

			if ((true == p_task_pwm_dta->flag) && (EV_PWM_OFF == p_task_pwm_dta->event))
			{
				if (p_task_pwm_cfg->current_angle > 179.0f)
					p_task_pwm_cfg->target_angle = 0.0f;
				p_task_pwm_dta->state = ST_PWM_MOVING;
			}

			break;

		case ST_PWM_MOVING:
			if (p_task_pwm_cfg->current_angle < p_task_pwm_cfg->target_angle){
				p_task_pwm_cfg->current_angle += 1.0f;
				uint32_t ticks = 1000 + (uint32_t)((p_task_pwm_cfg->current_angle / 180.0f) * 1000.0f);
				__HAL_TIM_SET_COMPARE(p_task_pwm_cfg->htim, p_task_pwm_cfg->channel, ticks);
			} else if (p_task_pwm_cfg->current_angle > p_task_pwm_cfg->target_angle){
				p_task_pwm_cfg->current_angle -= 1.0f;
				uint32_t ticks = 1000 + (uint32_t)((p_task_pwm_cfg->current_angle / 180.0f) * 1000.0f);
				__HAL_TIM_SET_COMPARE(p_task_pwm_cfg->htim, p_task_pwm_cfg->channel, ticks);
			} else {
				//p_task_pwm_dta->state = ST_PWM_IDLE;
				if(p_task_pwm_cfg->current_angle > 179.0f)
					p_task_pwm_dta->state = ST_PWM_ON;
				else
					p_task_pwm_dta->state = ST_PWM_OFF;
			}

		    break;

		default:

			p_task_pwm_dta->state = ST_PWM_OFF;
			p_task_pwm_dta->event = EV_PWM_OFF;
			p_task_pwm_dta->flag = false;

			break;
	}
}

/********************** end of file ******************************************/
