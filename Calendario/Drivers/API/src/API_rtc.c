/*
 * API_rtc.c
 *
 *  Created on: 2 abr. 2023
 *      Author: ipave
 */

#include "API_rtc.h"


extern I2C_HandleTypeDef hi2c1;

void RTC_Write_Cal(reloj reloj1){

	if(HAL_I2C_Mem_Write(&hi2c1,0x68<<1,0,I2C_MEMADD_SIZE_8BIT,(uint8_t *)&reloj1,sizeof(reloj),HAL_MAX_DELAY)!=HAL_OK)Error_Handler();

}

void RTC_Read_Cal(reloj * reloj1){
	if(HAL_I2C_Mem_Read(&hi2c1,0x68<<1,0,I2C_MEMADD_SIZE_8BIT,(uint8_t *)reloj1,sizeof(reloj),HAL_MAX_DELAY)!=HAL_OK)Error_Handler();

}

void RTC_Write_Byte(uint8_t valor,uint8_t dir){
	if(HAL_I2C_Mem_Write(&hi2c1,0x68<<1,dir,I2C_MEMADD_SIZE_8BIT,&valor,1,HAL_MAX_DELAY)!=HAL_OK)Error_Handler();
}

void RTC_Read_Byte(uint8_t * valor,uint8_t dir){
	if(HAL_I2C_Mem_Read(&hi2c1,0x68<<1,dir,I2C_MEMADD_SIZE_8BIT,(uint8_t *)valor,1,HAL_MAX_DELAY)!=HAL_OK)Error_Handler();

}


