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
#include <stdio.h> // Necesario para sprintf()

/* Demo includes */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes */
#include "board.h"
#include "app.h"
#include "i2c_lcd.h"               // La librería I2C que creamos
#include "task_lcd_attribute.h"
#include "task_lcd_interface.h"
#include "task_thermometer_attribute.h"

/********************** macros and definitions *******************************/
#define DEL_LCD_UPDATE      500ul  // Refrescar la pantalla cada 500 milisegundos

/********************** internal functions declaration ***********************/
void task_lcd_statechart(void);

/********************** internal data declaration ****************************/
// Objeto único para manejar los estados y tiempos del LCD
task_lcd_dta_t task_lcd_dta;

/********************** internal data definition *****************************/
const char *p_task_lcd 		= "Task LCD (LCD Statechart)";
const char *p_task_lcd_ 	= "Non-Blocking Code";
const char *p_task_lcd__ 	= "(Update by Time Code, period = 500mS)";
uint8_t row = 0;

/********************** external data declaration ****************************/
// Acá importamos variables globales que queramos mostrar.
// Ejemplo: asumo que tenés la temperatura en un entero global.
//extern uint32_t temperatura_actual = task_thermometer_dta_list[ID_THERM_A].temperature;
extern I2C_HandleTypeDef hi2c1;
/********************** external functions definition ************************/
void task_lcd_init(void *parameters)
{
	/* Print out: Task Initialized */
	/*LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_lcd_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_bt), p_task_lcd);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_bt), p_task_lcd_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_bt), p_task_lcd__);
*/
    // 1. Inicializamos el hardware de la pantalla
    lcd_init();

    // 2. Inicializamos la máquina de estados
    task_lcd_dta.state = ST_LCD_IDLE;
    task_lcd_dta.event = EV_LCD_IDLE;
    task_lcd_dta.flag  = false;
    task_lcd_dta.tick  = HAL_GetTick();

    // 3. Imprimimos el mensaje de arranque (Estático)
    lcd_put_cur(0, 0);
    lcd_send_string("Sistema Iniciado");
    lcd_put_cur(1, 0);
    lcd_send_string("Cargando...     ");
}

void task_lcd_update(void *parameters)
{
    // Ejecutamos la máquina de estados en cada ciclo
    task_lcd_statechart();
}

/********************** internal functions definition ************************/
void task_lcd_statechart(void)
{
    // Buffers para guardar los textos de cada línea (16 caracteres + terminador nulo)
    char buffer_linea1[17];
    char buffer_linea2[17];

    switch (task_lcd_dta.state)
    {
        case ST_LCD_IDLE:
            // Evaluamos si pasaron los 500ms usando código no bloqueante
            if ((HAL_GetTick() - task_lcd_dta.tick) >= DEL_LCD_UPDATE)
            {
                task_lcd_dta.tick = HAL_GetTick(); // Reseteamos el contador
                task_lcd_dta.state = ST_LCD_UPDATE;
            }
            break;

        case ST_LCD_UPDATE:
        	int16_t temperatura_actual = task_thermometer_dta_list[ID_THERM_A].temperature;

        	// Separamos la parte entera y la decimal usando matemática de enteros
        	int16_t parte_entera  = temperatura_actual / 100;
        	int16_t parte_decimal = temperatura_actual % 100;

			// %2lu: entero largo de 2 dígitos.
			// %02lu: entero largo de 2 dígitos rellenado con cero a la izquierda (ej: 05 si es .05)
			sprintf(buffer_linea1, "Temp: %2lu.%02lu C   ", parte_entera, parte_decimal);
			sprintf(buffer_linea2, "Estado: Normal  ");

			lcd_put_cur(row, 0);
			if (row == 0) {
				lcd_send_string(buffer_linea1);
			} else {
				lcd_send_string(buffer_linea2);
			}

			task_lcd_dta.state = ST_LCD_IDLE;
			break;

        default:
            task_lcd_dta.state = ST_LCD_IDLE;
            break;
    }
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	if (hi2c->Instance == I2C1) {
		row = row == 0 ? 1 : 0;
	}
}

/********************** end of file ******************************************/
