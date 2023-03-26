/*
 * API_debounce.c
 *
 *  Created on: 5 mar. 2023
 *      Author: ipave
 */

#include "API_debounce.h"
#include "API_delay.h"
#include "API_uart.h"

unsigned char estado=BUTTON_UP;
delay_t estructura;
#define DEMORA_BASE 40


void debounceFSM_init(){
    delayInit(&estructura,DEMORA_BASE);


}
void debounceFSM_update(){

	switch (estado){
		case (BUTTON_UP): if(BSP_PB_GetState(BUTTON_USER))estado=BUTTON_FALLING;
						  break;
		case (BUTTON_FALLING):if(!BSP_PB_GetState(BUTTON_USER))estado=BUTTON_UP;
							 else {
								 buttonPressed();
								 estado=BUTTON_DOWN;
							 }
							break;
		case (BUTTON_DOWN):if(!BSP_PB_GetState(BUTTON_USER))estado=BUTTON_RAISING;
							break;
		case (BUTTON_RAISING):if(BSP_PB_GetState(BUTTON_USER))estado=BUTTON_DOWN;
							 else {

								 buttonReleased();
								 estado=BUTTON_UP;
							 }
							break;


		}

}

void buttonPressed(){
	 uartSendString((uint8_t * )"Flanco Descendente detectado");


}
void buttonReleased(){

	 uartSendString((uint8_t * )"Flanco Ascendente detectado");

}
