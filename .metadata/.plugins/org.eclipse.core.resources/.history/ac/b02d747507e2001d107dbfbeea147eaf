/*
 * API_LCDport.c
 *
 *  Created on: 25 mar. 2023
 *      Author: ipave
 */

#include"API_Lcd_port.h"
#include"API_init.h"

extern I2C_HandleTypeDef hi2c1;

/********************************************************************************
 *Funcion:LCD_Write_Byte
 * Acción:  Funciòn que saca el byte a escribir al LCD por I2C, en caso de trabajar de forma paralela reemplazar por
 * 			GPIO. Si hay un error queda el LED2 encendido y el micro en error
 * Recibe: Valor a sacar por el puerto
 * Devuelve:  nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

void LCD_Write_Byte(uint8_t valor){
	if(HAL_I2C_Master_Transmit (&hi2c1,0x27<<1,&valor, sizeof(valor),HAL_MAX_DELAY)!=HAL_OK)Error_Handler();

}


