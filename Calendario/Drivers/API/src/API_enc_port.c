/// @file API_enc_port.c
/// @version 1.0
/// @date 23/4/2023
/// @author Ing. Pavelek Israel
/// @title API de manejo de encoder de bajo nivel
/// @brief Funciones para el manejo del encoder de bajo nivel

#include "API_enc_port.h"


/**
  * @brief  Init_Enc_port funcion que inicializa los GPIO del encoder
  * @param  void
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/

void Init_Enc_port(void){


	GPIO_InitTypeDef GPIO_InitStruct;

	  /* Enable the BUTTON Clock */
  	__HAL_RCC_GPIOD_CLK_ENABLE();

	    /* Configure Button pin as input */
	GPIO_InitStruct.Pin = PINCLK| PINDT;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(PORTCLK, &GPIO_InitStruct);
	__HAL_RCC_GPIOG_CLK_ENABLE();
	GPIO_InitStruct.Pin = PINSW;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(PORTSW, &GPIO_InitStruct);

}

/**
  * @brief  Leer_Enc_Pin Funcion que devuelve el estado de los pines del enconder DT y CLK
  * @param  void
  * @return valor de los estados del encoder en formato DT CLK
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/

uint8_t Leer_Enc_Pin(void){
	uint8_t estado=0;
	estado=HAL_GPIO_ReadPin(PORTCLK,PINCLK);
	estado+=(HAL_GPIO_ReadPin(PORTDT,PINDT)<<1);
	return estado;

}


/**
  * @brief  Leer_Enc_Pin Funcion que devuelve el estado del pulsador del enconder
  * @param  void
  * @return valor del pin del enconder en crudo
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/

_Bool Leer_Enc_Sw(void){

	return !HAL_GPIO_ReadPin(PORTSW,PINSW);

}

