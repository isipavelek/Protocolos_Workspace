/*
 * API_debounce.h
 *
 *  Created on: 5 mar. 2023
 *      Author: ipave
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_


#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdbool.h>

void debounceFSM_init();		// debe cargar el estado inicial
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas
void buttonPressed();			// debe togglear el LED1
void buttonReleased();		// debe togglear el LED3

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;




#endif /* API_INC_API_DEBOUNCE_H_ */
