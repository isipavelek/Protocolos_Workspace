/// @file API_debounce.c
/// @version 1.0
/// @date 23/4/2023
/// @author Ing. Pavelek Israel
/// @title API de manejo de antirebote
/// @brief funciones debounce.c


#include "API_debounce.h"
#include "API_delay.h"
#include "API_enc_port.h"

/**
  * @brief  Enun sobre el estado de la FSM del boton del Encoder
*/
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

static debounceState_t estado;
static delay_t tiempo1,tiempo2;
static uint8_t tecla=false;

/**
  * @brief  debounceFSM_init
  * @param  void
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/



void debounceFSM_init(){
	delayInit(&tiempo1,DEMORA_BASE);
	delayInit(&tiempo2,DEMORA_LARGA);

	estado=BUTTON_UP;

}


/**
  * @brief  debounceFSM_update
  * @param  void
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/


void debounceFSM_update(){
	switch (estado){
			case (BUTTON_UP): if(Leer_Enc_Sw()==true){
								estado=BUTTON_FALLING;
								delayRead(&tiempo1);
							  }
							  break;
			case (BUTTON_FALLING): if(delayRead(&tiempo1)){
									 if(Leer_Enc_Sw()==false)estado=BUTTON_UP;
									 else {
										 estado=BUTTON_DOWN;
										 delayRead(&tiempo2);
									 }
									}
									break;
			case (BUTTON_DOWN):if(Leer_Enc_Sw()==false){
									estado=BUTTON_RAISING;
									delayRead(&tiempo1);


								}
			 	 	 	 	 	if(delayRead(&tiempo2))tecla=PRES_LARGO_TIEMPO;
								break;
			case (BUTTON_RAISING):
								if(delayRead(&tiempo1)){
									 if(Leer_Enc_Sw()==true)estado=BUTTON_DOWN;
									 else {
										 if(tecla!=PRES_LARGO_TIEMPO)tecla=PRESIONADO;
										 else tecla=SUELTO;
										 estado=BUTTON_UP;
									 }

								}
								break;


	}
}



/**
  * @brief  LeerSW funcion que devuelve el estado del boton del encoder
  * @param  void
  * @return estado_boton
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/


estado_boton LeerSW(void){

	if(tecla==PRESIONADO){
		tecla=SUELTO;
		return PRESIONADO;
	}
	if(tecla==PRES_LARGO_TIEMPO){
		return PRES_LARGO_TIEMPO;
	}

	return SUELTO;

}
