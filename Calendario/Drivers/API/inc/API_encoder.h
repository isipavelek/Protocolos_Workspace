/*
 * API_encoder.h
 *
 *  Created on: 1 abr. 2023
 *      Author: ipave
 */

#ifndef API_INC_API_ENCODER_H_
#define API_INC_API_ENCODER_H_


#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdbool.h>
#include "API_delay.h"

#define DEMORA_BASE 40

typedef enum {
	NOGIRA,IZQ,DER

}giro_encoder_t;

typedef enum{
	INI,
	E00,
	E11,
	E01Der,
	E10Der,
	E01Izq,
	E10Izq,



} EncState_t;

_Bool Init_Enc(void);
void EncFSM_Update();
giro_encoder_t LeerEncoder();

#endif /* API_INC_API_ENCODER_H_ */
