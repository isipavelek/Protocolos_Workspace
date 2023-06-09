/*
 * API_enc_port.h
 *
 *  Created on: 1 abr. 2023
 *      Author: ipave
 */

#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdbool.h>

#ifndef API_INC_API_ENC_PORT_H_
#define API_INC_API_ENC_PORT_H_

#define NOENC 0
#define PINCLK GPIO_PIN_0
#define PORTCLK GPIOD
#define PINDT GPIO_PIN_1
#define PORTDT GPIOD
#define PINSW	GPIO_PIN_0
#define PORTSW	GPIOG


void Init_Enc_port(void);
uint8_t Leer_Enc_Pin(void);
_Bool Leer_Enc_Sw(void);


#endif /* API_INC_API_ENC_PORT_H_ */
