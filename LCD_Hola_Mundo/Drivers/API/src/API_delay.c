/*
 * API_delay.c
 *
 *  Created on: 5 mar. 2023
 *      Author: ipave
 */

#include "API_delay.h"


void delayInit( delay_t * delay, tick_t duration ){
	delay->startTime=HAL_GetTick();
	delay->duration=duration;
	delay->running=false;

}
bool_t delayRead( delay_t * delay ){
	if((delay->running)==false)delay->running=true;
	else{
		if(HAL_GetTick()-delay->startTime>=delay->duration){
			delay->running=false;
			return true;
		}
	}
	return false;
}


void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration=duration;
}

