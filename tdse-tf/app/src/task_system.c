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
#include "task_thermometer_interface.h"

/********************** macros and definitions *******************************/
#define DEL_SYS_MIN			0ul
#define DEL_SYS_MED			250ul
#define DEL_SYS_MAX			500ul

#define TEMP_LIMIT_MAX 2400 // Representa 24.00 °C
#define TEMP_LIMIT_MIN 1500 // Representa 15.00 °C

#define SYSTEM_DTA_QTY	MODE_QTY

extern sendMessage(char* message);
extern reset_timers();

/********************** internal data declaration ****************************/
task_system_dta_t task_system_dta_list[SYSTEM_DTA_QTY];

static task_system_therm_st_t g_therm_state = ST_SYS_THERM_IDLE;
static uint32_t               g_therm_timer = 0;

static task_system_bt_st_t    g_bt_state = ST_SYS_BT_DISCONNECTED;

/********************** internal functions declaration ***********************/
void task_system_auto_statechart(void);
void task_system_manual_statechart(void);
void task_system_actuators_statechart(void);
void task_system_thermometer_statechart(void);
void task_system_bluetooth_statechart(void);

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
	//LOGGER_INFO(" ");
	//LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_system_init), HAL_GetTick());
	//LOGGER_INFO("   %s is a %s", GET_NAME(task_system), p_task_system);
	//LOGGER_INFO("   %s is a %s", GET_NAME(task_system), p_task_system_);
	//LOGGER_INFO("   %s is a %s", GET_NAME(task_system), p_task_system__);

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

		//LOGGER_INFO(" ");
		/*LOGGER_INFO("   %s = %lu   %s = %lu   %s = %s",
					GET_NAME(state), (uint32_t)state,
					GET_NAME(event.event), (uint32_t)event.event,
					GET_NAME(b_event), (b_event ? "true" : "false"));
		*/
	}

	// El sistema inicia por default en estado automatico AUTO
	task_system_set_mode(AUTO);
}

void task_system_update(void *parameters)
{
	/* 1. Máquina de Estado Paralela: Comunicación Bluetooth */
	task_system_bluetooth_statechart();

	/* 2. Máquina de Estado Paralela: Sensor de Temperatura */
	task_system_thermometer_statechart();

	/* 3. Máquina de Estado Paralela: Actuadores (según modo AUTO/MANUAL) */
	task_system_actuators_statechart();
}

void task_system_bluetooth_statechart(void)
{
    task_system_ev_t ev = {EV_SYS_IDLE, AUTO};

    /* 1. Verificamos si hay un evento pendiente en la cola del sistema */
    if (true == any_event_task_system()) {
        ev = get_event_task_system();
    }

    switch (g_bt_state)
    {
        case ST_SYS_BT_DISCONNECTED:
            /* Si llega el comando /manual:1 pasamos a conectados */
            if (EV_SYS_APP_CONNECTED == ev.event) {
                g_bt_state = ST_SYS_BT_CONNECTED;
                task_system_set_mode(MANUAL);

                /* Apagamos actuadores al pasar a control manual por seguridad */
                put_event_task_pwm(EV_PWM_OFF, ID_PWM_MOTOR);
                put_event_task_actuator(EV_ACT_IDLE, ID_RELAY_FILTER);
                put_event_task_pwm(EV_PWM_OFF, ID_PWM_LIGHT);

                task_lcd_set_line2("MANUAL mode: ON");
                sendMessage("MANUAL mode: ON\r\n");
            }
            else if (EV_SYS_APP_DISCONNECTED == ev.event) {
                sendMessage("Already in AUTO mode.\r\n");
            }
            break;

        case ST_SYS_BT_CONNECTED:
            /* Si llega el comando /manual:0 nos desconectamos */
            if (EV_SYS_APP_DISCONNECTED == ev.event) {
                g_bt_state = ST_SYS_BT_DISCONNECTED;
                task_system_set_mode(AUTO);

                /* Reiniciamos temporizadores y apagamos actuadores */
                reset_timers();
                put_event_task_pwm(EV_PWM_OFF, ID_PWM_MOTOR);
                put_event_task_actuator(EV_ACT_IDLE, ID_RELAY_FILTER);
                put_event_task_pwm(EV_PWM_OFF, ID_PWM_LIGHT);

                task_lcd_set_line2("MANUAL mode: OFF");
                sendMessage("MANUAL mode: OFF\r\n");
            }
            else if (EV_SYS_APP_CONNECTED == ev.event) {
                sendMessage("Already in MANUAL mode.\r\n");
            }
            break;

        default:
            g_bt_state = ST_SYS_BT_DISCONNECTED;
            break;
    }

    /* 2. IMPORTANTE: Si el evento NO era de conexión (/filter:1, /lights:1, etc.),
     * lo volvemos a colocar en la cola para que lo procese task_system_actuators_statechart() */
    if ((ev.event != EV_SYS_IDLE) &&
        (ev.event != EV_SYS_APP_CONNECTED) &&
        (ev.event != EV_SYS_APP_DISCONNECTED))
    {
        put_event_task_system(ev);
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

    /* 1. Filtro de seguridad: en modo AUTO bloqueamos eventos que vengan de la App/Manual */
    if ((true == p_task_system_dta->flag) && (p_task_system_dta->event.mode != AUTO)) {
        p_task_system_dta->flag = false;
        sendMessage("Manual commands not allowed in AUTO mode.\r\n");
        return;
    }

    /* 2. Ejecutamos el statechart de actuadores (luces, filtro, alimentador) */
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

    /* 1. Filtro de seguridad: en modo MANUAL ignoramos comandos internos del modo AUTO */
    if ((true == p_task_system_dta->flag) && (p_task_system_dta->event.mode != MANUAL)) {
        p_task_system_dta->flag = false;
        return;
    }

    /* 2. Ejecutamos el statechart de actuadores */
    statechart(p_task_system_dta);
}

void task_system_actuators_statechart(void)
{
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

// Termometro, se piden lecturas cada 3000 ms (3 segundos)
void task_system_thermometer_statechart(void)
{
    uint32_t current_time = HAL_GetTick();
    int16_t current_temp = task_thermometer_dta_list[ID_THERM_A].temperature;
    char temp_str[17];

    switch (g_therm_state)
    {
        case ST_SYS_THERM_IDLE:
            /* 1. Al arrancar, pedimos la PRIMERA lectura al hardware inmediatamente */
            put_event_task_thermometer(EV_THERM_START_READ, ID_THERM_A);

            /* 2. Seteamos textos iniciales indicando que el sistema está midiendo */
            task_lcd_set_line1("Temp: Midiendo..");
            task_lcd_set_line2("Estado: Normal  ");

            /* 3. Guardamos el tiempo y pasamos al ciclo normal */
            g_therm_timer = current_time;
            g_therm_state = ST_SYS_THERM_WAITING_CYCLE;
            break;

        case ST_SYS_THERM_WAITING_CYCLE:  /* ESTADO NORMAL */
            if ((current_time - g_therm_timer) >= 3000ul) {
                g_therm_timer = current_time;

                /* 1. Actualizamos pantalla con el valor que ya tuvo 3 segundos para leerse */
                snprintf(temp_str, sizeof(temp_str), "Temp: %2d.%02d C  ",
                         current_temp / 100, abs(current_temp % 100));
                task_lcd_set_line1(temp_str);

                /* 2. PEDIMOS LA SIGUIENTE LECTURA para el próximo ciclo */
                put_event_task_thermometer(EV_THERM_START_READ, ID_THERM_A);

                /* 3. Ahora sí es seguro evaluar los límites de alarma */
                if (current_temp >= TEMP_LIMIT_MAX || current_temp <= TEMP_LIMIT_MIN) {
                    g_therm_state = ST_SYS_THERM_ALERT;

                    task_lcd_set_line2("Estado: ALERTA!");
                    put_event_task_actuator(EV_BUZZER_BLINK, ID_BUZZER);
                    break;
                }
                task_lcd_set_line2("Estado: Normal  ");
            }
            break;

        case ST_SYS_THERM_ALERT:  /* ESTADO ALERTA */
            if ((current_time - g_therm_timer) >= 3000ul) {
                g_therm_timer = current_time;

                /* 1. Actualizamos pantalla */
                snprintf(temp_str, sizeof(temp_str), "Temp: %2d.%02d C  ",
                         current_temp / 100, abs(current_temp % 100));
                task_lcd_set_line1(temp_str);

                /* 2. Pedimos lectura para el próximo ciclo */
                put_event_task_thermometer(EV_THERM_START_READ, ID_THERM_A);

                /* 3. Verificamos si volvió a la normalidad */
                if (current_temp < TEMP_LIMIT_MAX && current_temp > TEMP_LIMIT_MIN) {
                    g_therm_state = ST_SYS_THERM_WAITING_CYCLE;

                    task_lcd_set_line2("Estado: Normal  ");
                    put_event_task_actuator(EV_BUZZER_OFF, ID_BUZZER);
                }
                task_lcd_set_line2("Estado: ALERTA!");
            }
            break;

        default:
            g_therm_state = ST_SYS_THERM_IDLE;
            break;
    }
}

void statechart(task_system_dta_t *p_task_system_dta) {

	if ((true == p_task_system_dta->flag)
			&& (EV_SYS_LIGHT_ON == p_task_system_dta->event.event)) {
		p_task_system_dta->flag = false;
		put_event_task_pwm(EV_PWM_ON, ID_PWM_LIGHT);
		sendMessage("Lights: ON\r\n");
		p_task_system_dta->event.event = EV_SYS_IDLE;
		return;
	} else if ((true == p_task_system_dta->flag)
			&& (EV_SYS_LIGHT_OFF == p_task_system_dta->event.event)) {
		p_task_system_dta->flag = false;
		put_event_task_pwm(EV_PWM_OFF, ID_PWM_LIGHT);
		sendMessage("Lights: OFF\r\n");
		return;
	}

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
		} else if ((true == p_task_system_dta->flag)
				&& (EV_SYS_FILTER_ON == p_task_system_dta->event.event)) {
				p_task_system_dta->flag = false;
				sendMessage("Cannot turn filter ON while feeding.\n");
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



void task_system_set_mode(task_system_mode_t task_system_mode)
{
	g_task_system_mode = task_system_mode;
}

/********************** end of file ******************************************/
