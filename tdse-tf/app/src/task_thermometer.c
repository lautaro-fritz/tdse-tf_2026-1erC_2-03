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
#include "task_thermometer_attribute.h"
#include "ds18b20.h"
#include "task_system_attribute.h"
#include "task_system_interface.h"

/********************** macros and definitions *******************************/
#define DEL_BTN_MIN		0ul
#define DEL_BTN_MED		25ul
#define DEL_BTN_MAX		50ul

#define THERMOMETER_CFG_QTY		(sizeof(task_thermometer_cfg_list)/sizeof(task_thermometer_cfg_t))
#define THERMOMETER_DTA_QTY		THERMOMETER_CFG_QTY


extern TIM_HandleTypeDef htim1; // El timer que configuraste en CubeMX
ds18b20_t ds18;                 // La instancia de nuestro sensor

/********************** internal data declaration ****************************/
// 1. Instanciamos la configuración (solo el ID)
const task_thermometer_cfg_t task_thermometer_cfg_list[] = {
    {ID_THERM_A}
};

// 2. Instanciamos los datos iniciales (Arranca inactivo, sin flag, temp 0)
task_thermometer_dta_t task_thermometer_dta_list[] = {
    {0, ST_THERM_IDLE, EV_THERM_IDLE, false, 0}
};

/********************** internal functions declaration ***********************/
void task_thermometer_statechart(uint32_t index);

/********************** internal data definition *****************************/
const char *p_task_thermometer 		= "Task Sensor (Sensor Statechart)";
const char *p_task_thermometer_ 		= "Non-Blocking Code";
const char *p_task_thermometer__ 	= "(Update by Time Code, period = 1mS)";

/********************** external data declaration ****************************/

/********************** external functions definition ************************/
void ds18_tim_cb(TIM_HandleTypeDef *htim)
{
    ow_callback(&ds18.ow);
}

void task_thermometer_init(void *parameters)
{
	uint32_t index;
	task_thermometer_dta_t *p_task_thermometer_dta;
	task_thermometer_st_t state;
	task_thermometer_ev_t event;

	// 1. Configuramos el 1-Wire
	ow_init_t ow_init_struct;
	ow_init_struct.tim_handle = &htim1;
	ow_init_struct.gpio = GPIOA;
	ow_init_struct.pin = GPIO_PIN_8;
	ow_init_struct.tim_cb = ds18_tim_cb;
	ow_init_struct.done_cb = NULL;
	//ow_init_struct.rom_id_filter = DS18B20_ID;

	// 2. Inicializamos la librería del sensor (que por dentro inicializa el 1-Wire)
	ds18b20_init(&ds18, &ow_init_struct);

	// 3. ¡Arrancamos el Timer por interrupción!
	HAL_TIM_Base_Start_IT(&htim1);



	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_thermometer_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_thermometer), p_task_thermometer);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_thermometer), p_task_thermometer_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_thermometer), p_task_thermometer__);

	for (index = 0; THERMOMETER_DTA_QTY > index; index++)
	{
		/* Update Task Thermometer Data Pointer */
		p_task_thermometer_dta = &task_thermometer_dta_list[index];

		/* Init & Print out: Index & Task execution FSM */
		state = ST_THERM_IDLE;
		p_task_thermometer_dta->state = state;

		event = EV_THERM_IDLE;
		p_task_thermometer_dta->event = event;

		LOGGER_INFO(" ");
		LOGGER_INFO("   %s = %lu   %s = %lu   %s = %lu",
				    GET_NAME(index), index,
					GET_NAME(state), (uint32_t)state,
					GET_NAME(event), (uint32_t)event);
	}

	// NOTA: Para no complicar la inicialización asíncrona ahora,
	// hacemos la configuración inicial con el while porque
	// ESTO SE EJECUTA UNA SOLA VEZ AL ARRANCAR (fuera del bucle infinito)
	ds18b20_update_rom_id(&ds18);
	while(ds18b20_is_busy(&ds18));
}

void task_thermometer_update(void *parameters)
{
	uint32_t index;

	for (index = 0; THERMOMETER_DTA_QTY > index; index++)
	{
		/* Run Task Statechart */
		task_thermometer_statechart(index);
	}
}

void task_thermometer_statechart(uint32_t index)
{

    const task_thermometer_cfg_t *p_cfg = &task_thermometer_cfg_list[index];
    task_thermometer_dta_t *p_dta = &task_thermometer_dta_list[index];

    switch (p_dta->state) {

    case ST_THERM_IDLE:
		if ((true == p_dta->flag) && (EV_THERM_START_READ == p_dta->event)) {
			p_dta->flag = false;

			// 1. Damos la orden de iniciar conversión
			ds18b20_cnv(&ds18);

			// Pasamos a esperar que termine
			p_dta->state = ST_THERM_WAITING_CONVERSION;
		}
		break;

	case ST_THERM_WAITING_CONVERSION:
		// Reemplazamos el while() del ejemplo por este IF asíncrono
		// Preguntamos si NO está ocupado y si la conversión terminó
		if (!ds18b20_is_busy(&ds18) && ds18b20_is_cnv_done(&ds18)) {

			// 2. Le pedimos que nos prepare el dato del sensor índice 0
			ds18b20_req_read(&ds18);

			p_dta->state = ST_THERM_WAITING_READ;
		}
		break;

	case ST_THERM_WAITING_READ:
		// Esperamos que termine de mandarnos los datos por el cable
		if (!ds18b20_is_busy(&ds18)) {

			// 3. ¡Leemos la temperatura!
			p_dta->temperature = ds18b20_read_c(&ds18);

			// Acá ya tienes el dato listo para mandarlo a `task_system` o imprimirlo.
			// put_event_task_system(EV_SYS_TEMP_READY);

			// Dividimos por 100 porque la librería NimaLTD devuelve enteros escalados (Ej: 2550 = 25.50°C)
			LOGGER_LOG("Temperatura: %d.%02d C\r\n", p_dta->temperature / 100, abs(p_dta->temperature % 100));

			p_dta->state = ST_THERM_IDLE;
		}
		break;
    }
}

/********************** end of file ******************************************/
