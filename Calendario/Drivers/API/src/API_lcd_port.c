/*
 * API_LCDport.c
 *
 *  Created on: 25 mar. 2023
 *      Author: ipave
 */

#include"API_Lcd_port.h"
#include"API_init.h"

extern I2C_HandleTypeDef hi2c1;

void LCD_Write_Byte(uint8_t valor){
	if(HAL_I2C_Master_Transmit (&hi2c1,0x27<<1,&valor, sizeof(valor),HAL_MAX_DELAY)!=HAL_OK)Error_Handler();

}


