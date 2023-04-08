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
#include "API_delay.h"

#define DEMORA_BASE 40

void debounceFSM_init();
void debounceFSM_update();

bool_t readKey(void);


#endif /* API_INC_API_DEBOUNCE_H_ */
