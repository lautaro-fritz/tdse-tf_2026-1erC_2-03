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

#ifndef TASK_THERMOMETER_ATTRIBUTE_H_
#define TASK_THERMOMETER_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include "ds18b20.h"

/********************** macros ***********************************************/

/********************** typedef **********************************************/
/* Events to excite Task Thermometer */
typedef enum task_thermometer_ev {
	EV_THERM_IDLE,
	EV_THERM_START_READ
} task_thermometer_ev_t;

/* States of Task Thermometer */
typedef enum task_thermometer_st {
	ST_THERM_IDLE,
    ST_THERM_WAITING_CONVERSION,
    ST_THERM_WAITING_READ
} task_thermometer_st_t;

/* Identifier of Task Thermometer */
typedef enum task_thermometer_id {
	ID_THERM_A
} task_thermometer_id_t;

typedef struct {
    task_thermometer_id_t  identifier;
    // Podrías agregar factores de calibración aquí si el sensor lo requiere
} task_thermometer_cfg_t;

typedef struct {
    uint32_t               tick;
    task_thermometer_st_t  state;
    task_thermometer_ev_t  event;
    bool                   flag;
    int16_t                temperature; // La librería devuelve la temp en int16_t
} task_thermometer_dta_t;

/********************** external data declaration ****************************/
extern const task_thermometer_cfg_t task_thermometer_cfg_list[];
extern task_thermometer_dta_t task_thermometer_dta_list[];

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_THERMOMETER_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
