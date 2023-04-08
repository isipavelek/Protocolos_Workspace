/*
 * API_encoder.c
 *
 *  Created on: 1 abr. 2023
 *      Author: ipave
 */

#include "API_encoder.h"
#include "API_enc_port.h"

static uint8_t estado;
static uint8_t giro=NOGIRA;
static delay_t encoder_time;

_Bool Init_Enc(void){
	Init_Enc_port();
    delayInit(&encoder_time,DEMORA_BASE);
    estado=INI;
	return 0;
}

void EncFSM_Update(){

	uint8_t estados_pines=Leer_Enc_Pin();
	switch (estado){
		case INI: if(estados_pines==PINDT+PINCLK)estado=E11;
				  if(estados_pines==NOENC)estado=E00;
				  break;
		case E00:if(estados_pines==PINCLK)estado=E01Der;
				  if(estados_pines==PINDT)estado=E10Izq;
				  break;
		case E01Izq:if(estados_pines==PINDT+PINCLK)estado=E11;
				  if(estados_pines==NOENC){
					  giro=IZQ;
					  estado=E00;
				  }
				  break;
		case E10Der:
				  if(estados_pines==NOENC){
					  giro=DER;
					  estado=E00;
				  }
				  if(estados_pines==PINDT+PINCLK)estado=E11;
				  break;

		case E01Der:if(estados_pines==PINDT+PINCLK){
						giro=DER;
						estado=E11;
					}
				  if(estados_pines==NOENC)estado=E00;
				  break;
		case E10Izq:if(estados_pines==PINDT+PINCLK){
					giro=IZQ;
					estado=E11;
				  }
				  if(estados_pines==NOENC)estado=E00;
				  break;
		case E11: if(estados_pines==PINCLK)estado=E01Izq;
				  if(estados_pines==PINDT)estado=E10Der;
				  break;

	}
}

giro_encoder_t ReadEncoder(){
	uint8_t aux=0;
	aux=giro;
	giro=NOGIRA;
	return aux;

}
