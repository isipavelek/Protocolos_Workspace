/*
 * API_rtc.c
 *
 *  Created on: 2 abr. 2023
 *      Author: ipave
 */

#include "API_rtc.h"


extern I2C_HandleTypeDef hi2c1;
/********************************************************************************
 *Funcion:RTC_Write_Cal
 * Acción: Funciòn que escribe la estructura de reloj en el RTC por I2C
 * Recibe: Estructura Reloj con los datos a escribir
 * Devuelve: Nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/
void RTC_Write_Cal(reloj reloj1){

	if(HAL_I2C_Mem_Write(&hi2c1,RTC_DIR<<1,0,I2C_MEMADD_SIZE_8BIT,(uint8_t *)&reloj1,sizeof(reloj),HAL_MAX_DELAY)!=HAL_OK)Error_Handler();

}

/********************************************************************************
 *Funcion:RTC_Read_Cal
 * Acción:Funciòn que lee la estructura de reloj en el RTC por I2C
 * Recibe: Un punter a estructura Reloj con los datos a leer
 * Devuelve: Nada (lo deja en la escructura)
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

void RTC_Read_Cal(reloj * reloj1){
	if(HAL_I2C_Mem_Read(&hi2c1,RTC_DIR<<1,0,I2C_MEMADD_SIZE_8BIT,(uint8_t *)reloj1,sizeof(reloj),HAL_MAX_DELAY)!=HAL_OK)Error_Handler();

}

/********************************************************************************
 *Funcion: RTC_Write_Byte
 * Acción: Funciòn que escribe un byte en el RTC I2C
 * Recibe: Entero valor a escribir, Entero dir, direcciòn a escribir
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

void RTC_Write_Byte(uint8_t valor,uint8_t dir){
	if(HAL_I2C_Mem_Write(&hi2c1,RTC_DIR<<1,dir,I2C_MEMADD_SIZE_8BIT,&valor,1,HAL_MAX_DELAY)!=HAL_OK)Error_Handler();
}

/********************************************************************************
 *Funcion:RTC_Read_Byte
 * Acción:Funciòn que lee un byte en el RTC I2C
 * Recibe: Puntero a Entero valor a leer, Entero dir, direcciòn a escribir
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

void RTC_Read_Byte(uint8_t * valor,uint8_t dir){
	if(HAL_I2C_Mem_Read(&hi2c1,RTC_DIR<<1,dir,I2C_MEMADD_SIZE_8BIT,(uint8_t *)valor,1,HAL_MAX_DELAY)!=HAL_OK)Error_Handler();

}


