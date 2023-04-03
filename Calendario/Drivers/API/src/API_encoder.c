/*
 * API_encoder.c
 *
 *  Created on: 1 abr. 2023
 *      Author: ipave
 */

#include "API_encoder.h"
#include "API_enc_port.h"


static uint8_t estado;

uint8_t giro=NOGIRA;

delay_t encoder_time;

_Bool Init_Enc(void){
	Init_Enc_port();
    delayInit(&encoder_time,DEMORA_BASE);
    estado=E00;
	return 0;
}

void EncFSM_Update(){

	uint8_t estados_pines=Leer_Enc_Pin();

	switch (estado){
			case (E00):	if(estados_pines!=E00 && estados_pines!=E11)estado=estados_pines;
						break;
			case (E01):	if(estados_pines!=E01){
							if(estados_pines==E00)giro=IZQ;
							else giro=DER;
							estado=E00;
						}
						break;
			case (E10): if(estados_pines!=E10){
							if(estados_pines==E00)giro=DER;
							else giro=IZQ;
							estado=E00;
						}
						break;

	}
}

giro_encoder_t ReadEncoder(){
	uint8_t aux=0;
	aux=giro;
	giro=NOGIRA;
	return aux;

}