/// @file API_delay.c
/// @version 1.0
/// @date 23/4/2023
/// @author Ing. Pavelek Israel
/// @title API de manejo de demoras no bloqueantes
/// @brief Funciones para las demoras no bloqueantes


#include "API_delay.h"

/**
  * @brief  delayInit
  * @param  delay_t * puntero a la estructura de la demora
  * @param  tick_t  duracion de la demora
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/

void delayInit( delay_t * delay, tick_t duration ){
	delay->duration=duration;
	delay->running=false;

}

/**
  * @brief  delayRead vuelve si paso o no el tiempo en caso de no haber pasado lo inicializa
  * @param  delay_t * puntero a la estructura de la demora
  * @return true si paso el tiempo false si no en caso de no estar corriendo lo inicializa
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/
bool_t delayRead( delay_t * delay ){
	if((delay->running)==false){
		delay->running=true;
		delay->startTime=HAL_GetTick();

	}
	else{
		if(HAL_GetTick()-delay->startTime>=delay->duration){
			delay->running=false;
			return true;
		}
	}
	return false;
}
/**
  * @brief  delayWrite funcion que escrbie la duracion del tiempo de la demora
  * @param  delay_t * puntero a la estructura de la demora
  * @param  tick_t  duracion de la demora
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 16/4/2023
*/

void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration=duration;
}

