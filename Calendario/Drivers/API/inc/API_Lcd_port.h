/*
 * API_LCDport.h
 *
 *  Created on: 25 mar. 2023
 *      Author: ipave
 */


#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdbool.h>
#include "API_reloj.h"

#define I2C_CLOCK_RATE 100000


_Bool LCD_HW_init(void);
void LCD_Write_Byte(uint8_t valor);
void GPIO_I2C(I2C_HandleTypeDef  *hi2c);
void RTC_Write_Byte(uint8_t valor,uint8_t dir);
void RTC_Read_Cal(reloj * reloj1);