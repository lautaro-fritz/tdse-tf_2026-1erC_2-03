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


//ARRANCAR A MODIFICAR!!!

/********************** macros and definitions *******************************/
#define DEL_LED_MIN		0ul
#define DEL_LED_MED		250ul
#define DEL_LED_MAX		500ul
#define DEL_BUZZER_MAX		500ul

#define ACTUATOR_CFG_QTY	(sizeof(task_actuator_cfg_list)/sizeof(task_actuator_cfg_t))
#define ACTUATOR_DTA_QTY	ACTUATOR_CFG_QTY

/********************** internal functions declaration ***********************/
void task_lcd_init(void *parameters);

/********************** internal data declaration ****************************/
const task_actuator_cfg_t task_actuator_cfg_list[] = {
	{ID_LED_A,  LED_A_PORT,  LED_A_PIN, LED_A_ON,  LED_A_OFF, DEL_LED_MAX,
			 ST_ACT_IDLE, EV_ACT_IDLE, task_actuator_sc_generic},
	{ID_RELAY_FILTER,  GPIOB,  GPIO_PIN_5, REL_LAMP_ON,  REL_LAMP_OFF, DEL_LED_MAX,
			 ST_ACT_IDLE, EV_ACT_IDLE, task_actuator_sc_generic},
	{ID_BUZZER,  BUZZER_1_GPIO_Port,  BUZZER_1_Pin, BUZZER_ON,  BUZZER_OFF, DEL_BUZZER_MAX,
			 ST_ACT_OFF, EV_BUZZER_OFF, task_actuator_sc_buzzer}
};

task_actuator_dta_t task_actuator_dta_list[ACTUATOR_DTA_QTY];

/********************** internal data definition *****************************/
const char *p_task_actuator 		= "Task Actuator (Actuator Statechart)";
const char *p_task_actuator_ 		= "Non-Blocking Code";
const char *p_task_actuator__ 		= "(Update by Time Code, period = 1mS)";

/********************** external data declaration ****************************/

/********************** external functions definition ************************/


/********************** end of file ******************************************/
