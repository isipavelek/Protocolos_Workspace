/*
 * API_rtc.h
 *
 *  Created on: 2 abr. 2023
 *      Author: ipave
 */

#ifndef API_INC_API_RTC_H_
#define API_INC_API_RTC_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdbool.h>
#include "API_reloj.h"
#include "API_init.h"

typedef struct {
	uint8_t temp_ent;
	uint8_t temp_dec;

}temp_t;


#define RTC_DIR 0x68
#define RTC_DIR_SEG 0x00
#define RTC_TEMP_DIR 0x11

void RTC_Write_Cal(reloj reloj1);
void RTC_Read_Cal(reloj * reloj1);
void RTC_Write_Byte(uint8_t valor,uint8_t dir);
void RTC_Read_Byte(uint8_t * valo,uint8_t dir);
temp_t RTC_Read_Temp(void);



#endif /* API_INC_API_RTC_H_ */
