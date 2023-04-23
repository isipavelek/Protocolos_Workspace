/// @file API_encoder.c
/// @version 1.0
/// @date 23/4/2023
/// @author Ing. Pavelek Israel
/// @title API de manejo del en encoder
/// @brief funciones API_enconder.c

#include "API_encoder.h"
#include "API_enc_port.h"

static uint8_t estado;
static uint8_t giro=NOGIRA;
static delay_t encoder_time;

/**
  * @brief  Init_Enc
  * @param  void
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/


void Init_Enc(void){
	Init_Enc_port();
    delayInit(&encoder_time,DEMORA_BASE);
    estado=INI;
}
/**
  * @brief  EncFSM_Update funcion que realiza la FSM del enconder
  * @param  void
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/

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

/**
  * @brief  LeerEncoder funciòn que devuelve el estado del enconder si esta girando y en que sentido
  * @param  void
  * @return giro_encoder_t el sentido de giro IZQ DER o no GIRA
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/

giro_encoder_t LeerEncoder(){
	uint8_t aux=0;
	aux=giro;
	giro=NOGIRA;
	return aux;

}
