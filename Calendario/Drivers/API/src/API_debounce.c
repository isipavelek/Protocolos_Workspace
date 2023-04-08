#include "API_debounce.h"
#include "API_delay.h"
#include "API_enc_port.h"

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;


static debounceState_t estado;
static delay_t estructura_tiempo;
static bool_t tecla=0;



void debounceFSM_init(){
	delayInit(&estructura_tiempo,DEMORA_BASE);
	estado=BUTTON_UP;
}
void debounceFSM_update(){
	switch (estado){
			case (BUTTON_UP): if(Leer_Enc_Sw()){
								estado=BUTTON_FALLING;
								delayRead(&estructura_tiempo);
							}
							  break;
			case (BUTTON_FALLING): if(delayRead(&estructura_tiempo)){
									 if(!Leer_Enc_Sw())estado=BUTTON_UP;
									 else {
										 tecla=true;
										 estado=BUTTON_DOWN;
									 }
									}
								break;
			case (BUTTON_DOWN):if(!Leer_Enc_Sw()){
									estado=BUTTON_RAISING;
									delayRead(&estructura_tiempo);
								}

								break;
			case (BUTTON_RAISING):
								if(delayRead(&estructura_tiempo)){
									 if(Leer_Enc_Sw())estado=BUTTON_DOWN;
									 else {
										 tecla=false;
										 estado=BUTTON_UP;
									 }
								 }
								break;


	}
}



bool_t readKey(void){

	if(tecla==true){
		tecla=false;
		return true;
	}
	return false;

}
