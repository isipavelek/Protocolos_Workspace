/*
 * API_LCDport.c
 *
 *  Created on: 25 mar. 2023
 *      Author: ipave
 */

#include"API_Lcd_port.h"
#include"API_init.h"

static I2C_HandleTypeDef hi2c1;

_Bool LCD_HW_init(void){

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

void GPIO_I2C(I2C_HandleTypeDef  *hi2c)
{
	 GPIO_InitTypeDef GPIO_InitStruct;

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	     /* Peripheral clock enable */
	  __HAL_RCC_I2C1_CLK_ENABLE();

}

void LCD_Write_Byte(uint8_t valor){


	HAL_I2C_Master_Transmit (&hi2c1,0x27<<1,&valor, sizeof(valor),HAL_MAX_DELAY);


}
