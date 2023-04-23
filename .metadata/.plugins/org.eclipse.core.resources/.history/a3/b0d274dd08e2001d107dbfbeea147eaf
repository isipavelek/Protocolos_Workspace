/*
 * API_uart.c
 *
 *  Created on: 7 mar. 2023
 *      Author: ipave
 */

#include "API_uart.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdbool.h>
#include "main.h"

#define TIMEOUT 100
static UART_HandleTypeDef huart1;
static uint8_t TXT_INI[]="UART INICIALIZADA EN 115200 8N1";

/********************************************************************************
 *Funcion:uartInit
 * Acción: Funciòn que inicializa la UART
 * Recibe: Nada
 * Devuelve: true si hubo un error, false si todo ok
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

bool uartInit(){

	  huart1.Instance = USARTx;
	  huart1.Init.BaudRate = USART_BAUD;
	  huart1.Init.WordLength = UART_WORDLENGTH_8B;
	  huart1.Init.StopBits = UART_STOPBITS_1;
	  huart1.Init.Parity = UART_PARITY_NONE;
	  huart1.Init.Mode = UART_MODE_TX_RX;
	  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	  HAL_UART_MspInit(&huart1);
	  if (HAL_UART_Init(&huart1) != HAL_OK)return true;
      uartSendString(TXT_INI);
	  return false;

}
/********************************************************************************
 *Funcion:uartSendString
 * Acción: Función que envia un strig por UART
 * Recibe: Puntero al string a enviar
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

void uartSendString(uint8_t * pstring){

	while(*pstring)uartSendStringSize(pstring++,1);

}
/********************************************************************************
 *Funcion:uartSendStringSize
 * Acción: Función que envia un strig  (solo la cantidad de bytes que quiera)
 * Recibe: Puntero al string a enviar, cantidad de datos datos a enviar (size)
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/
void uartSendStringSize(uint8_t * pstring, uint16_t size){

	HAL_UART_Transmit(&huart1,pstring,size,TIMEOUT);


}
/********************************************************************************
 *Funcion:uartReceiveStringSize
 * Acción: Función que recibe un strig (solo la cantidad de bytes que quiera)
 * Recibe: Puntero al string a recibir, cantidad de datos datos a enviar (size)
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/
void uartReceiveStringSize(uint8_t * pstring, uint16_t size){
	HAL_UART_Receive(&huart1,pstring,size,TIMEOUT);
}
