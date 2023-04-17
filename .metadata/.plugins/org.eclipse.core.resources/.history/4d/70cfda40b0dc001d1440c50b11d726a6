/*
 * API_I2C.c
 *
 *  Created on: 8 abr. 2023
 *      Author: ipave
 */

#include "API_I2C.h"

I2C_HandleTypeDef hi2c1;

/********************************************************************************
 *Funcion: I2C_HW_init
 * Acción: Inicializa el Puerto I2C
 * Recibe:  Nada
 * Devuelve: HAL_ERROR si hubo algun problema o HAL_OK si todo funciono
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/


static void GPIO_I2C(I2C_HandleTypeDef  *hi2c);

_Bool I2C_HW_init(void){

	  hi2c1.Instance = I2C1;
	  hi2c1.Init.ClockSpeed = I2C_CLOCK_RATE;
	  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	  hi2c1.Init.OwnAddress1 = 0;
	  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	  hi2c1.Init.OwnAddress2 = 0;
	  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	  GPIO_I2C(&hi2c1);
	  if (HAL_I2C_Init(&hi2c1) != HAL_OK)return HAL_ERROR;
	  return HAL_OK;

}


/********************************************************************************
 *Funcion:GPIO_I2C
 * Acción:  Funciòn que inicializa la funcón alternativa en los pines de I2C 9 y 8
 * Recibe: Manejador de I2C I2C_HandleTypeDef
 * Devuelve:  nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/
static void GPIO_I2C(I2C_HandleTypeDef  *hi2c){
	 GPIO_InitTypeDef GPIO_InitStruct;

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	     /* Peripheral clock enable */
	  __HAL_RCC_I2C1_CLK_ENABLE();

}
