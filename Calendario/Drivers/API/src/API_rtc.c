/// @file API_rtc.c
/// @version 1.0
/// @date 23/4/2023
/// @author Ing. Pavelek Israel
/// @title API_rrtc.c
/// @brief Funciones del rtc

#include "API_rtc.h"

extern I2C_HandleTypeDef hi2c1;
/**
  * @brief  RTC_Write_Cal Funcion que escribe el calendario
  * @param  reloj estructura de reloj con los valores a escribir
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/
void RTC_Write_Cal(reloj reloj1){

	if(HAL_I2C_Mem_Write(&hi2c1,RTC_DIR<<1,0,I2C_MEMADD_SIZE_8BIT,(uint8_t *)&reloj1,sizeof(reloj),HAL_MAX_DELAY)!=HAL_OK)Error_Handler();

}

/**
  * @brief  RTC_Read_Cal  Funcion que lee el calendario
  * @param  reloj* puntero  estructura para traer los valores
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/

void RTC_Read_Cal(reloj * reloj1){
	if(HAL_I2C_Mem_Read(&hi2c1,RTC_DIR<<1,RTC_DIR_SEG,I2C_MEMADD_SIZE_8BIT,(uint8_t *)reloj1,sizeof(reloj),HAL_MAX_DELAY)!=HAL_OK)Error_Handler();

}

/**
  * @brief  RTC_Write_Byte  Funcion que escribe un byte en el RTC
  * @param  uint8_t valor a escribir
  * @param uint8_t dirección donde escribirlo
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/

void RTC_Write_Byte(uint8_t valor,uint8_t dir){
	if(HAL_I2C_Mem_Write(&hi2c1,RTC_DIR<<1,dir,I2C_MEMADD_SIZE_8BIT,&valor,1,HAL_MAX_DELAY)!=HAL_OK)Error_Handler();
}

/**
  * @brief  RTC_Read_Byte  Funcion que lee un byte en el RTC
  * @param  uint8_t * valor puntero en donde guardar la lectura
  * @param uint8_t dirección donde leer
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/

void RTC_Read_Byte(uint8_t * valor,uint8_t dir){
	if(HAL_I2C_Mem_Read(&hi2c1,RTC_DIR<<1,dir,I2C_MEMADD_SIZE_8BIT,(uint8_t *)valor,1,HAL_MAX_DELAY)!=HAL_OK)Error_Handler();

}
/**
  * @brief  RTC_Read_Temp  Funciòn que lee la temperatura del RTC
  * @param  void
  * @return la temperatura leida
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/

temp_t RTC_Read_Temp(void){
	temp_t temp;
	if(HAL_I2C_Mem_Read(&hi2c1,RTC_DIR<<1,RTC_TEMP_DIR,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&temp,sizeof(temp),HAL_MAX_DELAY)!=HAL_OK)Error_Handler();
	return temp;
}


