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
#include "i2c_lcd.h"

extern I2C_HandleTypeDef hi2c1;

/********************** macros and definitions *******************************/

/********************** internal functions declaration ***********************/

/********************** internal data declaration ****************************/


/********************** internal data definition *****************************/

/********************** external data declaration ****************************/

/********************** external functions definition ************************/
void lcd_send_cmd(char cmd)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd & 0xf0);
    data_l = ((cmd << 4) & 0xf0);
    data_t[0] = data_u | 0x0C;  // en=1, rs=0
    data_t[1] = data_u | 0x08;  // en=0, rs=0
    data_t[2] = data_l | 0x0C;  // en=1, rs=0
    data_t[3] = data_l | 0x08;  // en=0, rs=0

    // Transmisión por hardware directa. A 100kHz tarda solo ~360 microsegundos
    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, (uint8_t *) data_t, 4, 100);
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
    lcd_send_cmd(col);
}

void lcd_send_string(char *str)
{
    static uint8_t dma_buffer[64];
    uint16_t idx = 0;

    for (uint8_t i = 0; i < 16; i++) {
        char c = (str[i] != '\0' && i < strlen(str)) ? str[i] : ' ';

        char data_u = (c & 0xf0);
        char data_l = ((c << 4) & 0xf0);

        dma_buffer[idx++] = data_u | 0x0D;
        dma_buffer[idx++] = data_u | 0x09;
        dma_buffer[idx++] = data_l | 0x0D;
        dma_buffer[idx++] = data_l | 0x09;
    }

    HAL_I2C_Master_Transmit_DMA(&hi2c1, SLAVE_ADDRESS_LCD, dma_buffer, idx);
}

void lcd_init(void)
{
    // Secuencia de inicio estricta de 4 bits (SÍ usamos HAL_Delay porque se llama antes del bucle infinito)
    HAL_Delay(50);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20);
    HAL_Delay(10);

    // Configuración de pantalla
    lcd_send_cmd(0x28); // 4 bit, 2 lineas, 5x8
    HAL_Delay(1);
    lcd_send_cmd(0x08); // Display off
    HAL_Delay(1);
    lcd_send_cmd(0x01); // Clear display
    HAL_Delay(2);
    lcd_send_cmd(0x06); // Entry mode
    HAL_Delay(1);
    lcd_send_cmd(0x0C); // Display on, cursor off
}

/********************** end of file ******************************************/
