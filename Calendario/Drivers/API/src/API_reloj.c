/*
 * API_reloj.c
 *
 *  Created on: 1 abr. 2023
 *      Author: ipave
 */

#include "API_reloj.h"
#include "API_lcd.h"
#include "API_lcd_port.h"
#include "API_rtc.h"
#include "API_debounce.h"
#include "API_encoder.h"

static uint8_t estado_reloj;


static const uint8_t mes31[]={ENERO,MARZO,MAYO,JULIO,AGOSTO,OCTUBRE,DICIEMBRE};

static void PresentaFechaLCD(reloj*,uint8_t pos,uint8_t linea);
static void PresentaHoraLCD(reloj*,uint8_t pos,uint8_t linea);
static void Decrementa(uint8_t * valor,uint8_t limiteInf,uint8_t limiteSup);
static void Incrementa(uint8_t * valor,uint8_t limiteInf,uint8_t limiteSup);
static uint8_t buscar_indice (uint8_t * valor,uint8_t abuscar,uint8_t limite);

static void ConfiguraDia(reloj* reloj1);
static void ConfiguraMes(reloj* reloj1);
static void ConfiguraAnio(reloj* reloj1);
static void ConfiguraHora(reloj* reloj1);
static void ConfiguraMin(reloj* reloj1);
static void ConfiguraSeg(reloj* reloj1);

/********************************************************************************
 *Funcion:PresentaFechaLCD
 * Acción: Función que presenta en el LCD la fecha
 * Recibe: el reloj con el que se trabaje, posición donde colocarlo y linea
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

static void PresentaFechaLCD(reloj* reloj1,uint8_t pos,uint8_t linea){

	  if(linea==1)PosCaracHLcd(pos);
	  else PosCaracLLcd(pos);
	  DatoBCD (reloj1->dia);
	  DatoLcd('/');
	  DatoBCD (reloj1->mes);
	  DatoLcd('/');
	  DatoBCD (reloj1->anio);

}

/********************************************************************************
 *Funcion: PresentaHoraLCD
 * Acción: Función que presenta en el LCD la hora
 * Recibe: el reloj con el que se trabaje, posición donde colocarlo y linea
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

static void PresentaHoraLCD(reloj* reloj1,uint8_t pos,uint8_t linea){

	  if(linea==1)PosCaracHLcd(pos);
	  else PosCaracLLcd(pos);
	  DatoBCD (reloj1->hora);
	  DatoLcd(':');
	  DatoBCD (reloj1->min);
	  DatoLcd(':');
	  DatoBCD (reloj1->seg);

}
/********************************************************************************
 *Funcion: RelojInit
 * Acción: Función que inicializa la MEF del reloj
 * Recibe: el reloj a inicializar
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/
void RelojInit(reloj* reloj1){
	estado_reloj=PRESENTAR;
	/*reloj1->seg=0;
	reloj1->min=0;
	reloj1->hora=0;
	reloj1->diasem=0;
	reloj1->dia=1;
	reloj1->mes=1;
	reloj1->anio=0;*/

}

/********************************************************************************
 *Funcion: Reloj_Read
 * Acción: Función que interfacea con el HW del RTC y lee el calendario
 * Recibe:  Puntero a donde dejar los datos del reloj
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

void Reloj_Read(reloj* reloj1){

	RTC_Read_Cal(reloj1);

}

/********************************************************************************
 *Funcion: Reloj_Write
 * Acción: Función que interfacea con el HW del RTC y escribe  el calendario
 * Recibe:  Puntero a donde estan los datos a grabar en el reloj
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

void Reloj_Write(reloj reloj1){
	RTC_Write_Cal(reloj1);

}

/********************************************************************************
 *Funcion: RelojFSM_Update
 * Acción: Función que actauliza la MEF del reloj
 * Recibe: Reloj con el que trabaja
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

void RelojFSM_Update(reloj* reloj1){

	switch(estado_reloj){
		case PRESENTAR: Reloj_Read(reloj1);
						PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
						PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
     					if(readKey()==true){
     						CursorOnLcd();
     						estado_reloj=CONFIGURAR_DIA;
     					}
						break;
		case CONFIGURAR_DIA:
						ConfiguraDia(reloj1);
						break;
		case CONFIGURAR_MES:
						ConfiguraMes(reloj1);
						break;
		case CONFIGURAR_ANIO:
						ConfiguraAnio(reloj1);
						break;
		case CONFIGURAR_HORA:
						ConfiguraHora(reloj1);
						break;
		case CONFIGURAR_MIN:
						ConfiguraMin(reloj1);
						break;
		case CONFIGURAR_SEG:
						ConfiguraSeg(reloj1);
						break;
	}


}

/********************************************************************************
 *Funcion:ConfiguraDia
 * Acción: Función que configura el dia en el reloj y lo presenta en pantalla.
 * Recibe: Puntero al reloj que trabaja
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

static void ConfiguraDia(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracHLcd(POSFECHA);
	if(readKey()==true)estado_reloj=CONFIGURAR_MES;
	encoder=ReadEncoder();
	if(encoder==IZQ){
		Decrementa(&(reloj1->dia),DIAMIN,DIAMAX);
		if(reloj1->dia==0x30 && reloj1->mes==FEBRERO)reloj1->mes=MARZO;
		if(reloj1->dia==0x31 && (reloj1->mes==FEBRERO || reloj1->mes==ABRIL || reloj1->mes==JUNIO || reloj1->mes==SEPTIEMBRE || reloj1->mes==NOVIEMBRE))(reloj1->mes)--;
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}
	if(encoder==DER){
		Incrementa(&(reloj1->dia),DIAMIN,DIAMAX);

		if(reloj1->dia==0x30 && reloj1->mes==FEBRERO)reloj1->mes=MARZO;
		if(reloj1->dia==0x31 && (reloj1->mes==FEBRERO || reloj1->mes==ABRIL || reloj1->mes==JUNIO || reloj1->mes==SEPTIEMBRE || reloj1->mes==NOVIEMBRE))(reloj1->mes)++;
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}

}


/********************************************************************************
 *Funcion ConfiguraMes
 * Acción: Función que configura el mes en el reloj y lo presenta en pantalla.
 * 			tiene en cuenta segun el dìa ingresado los limites del mes en cuestion
 * Recibe: Puntero al reloj que trabaja
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

static void ConfiguraMes(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracHLcd(POSMES);
	if(readKey()==true)estado_reloj=CONFIGURAR_ANIO;
	encoder=ReadEncoder();
	if(encoder==IZQ){
		if((reloj1->dia)!=0x31)Decrementa(&(reloj1->mes),MESMIN,MESMAX);	//si el mes no tiene 31, lo dejo decrementar libremente
		else{
			uint8_t indice=buscar_indice((uint8_t *)mes31,reloj1->mes,sizeof(mes31));  //busco el limite
			if(indice==0)reloj1->mes=mes31[sizeof(mes31)-1];
			else reloj1->mes=mes31[indice-1];
		}
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}
	if(encoder==DER){
		if((reloj1->dia)!=0x31)Incrementa(&(reloj1->mes),MESMIN,MESMAX); //si el mes no tiene 31, lo dejo incrementar  libremente
		else{
			uint8_t indice=buscar_indice((uint8_t *)mes31,reloj1->mes,sizeof(mes31)); //busco el limite
			if(indice==sizeof(mes31)-1)reloj1->mes=mes31[0];
			else reloj1->mes=mes31[indice+1];
		}
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}
}

/********************************************************************************
 *Funcion: ConfiguraAnio
 * Acción: Función que configura el año en el reloj y lo presenta en pantalla.
 * Recibe: Puntero al reloj que trabaja
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

static void ConfiguraAnio(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracHLcd(POSANIO);
	if(readKey()==true)estado_reloj=CONFIGURAR_HORA;
	encoder=ReadEncoder();
	if(encoder==IZQ){
		if(reloj1->mes==FEBRERO && reloj1->dia==0x29){
			do{
				Decrementa(&(reloj1->anio),ANIOMIN,ANIOMAX);
			}while((reloj1->anio)%4);
		}
		else Decrementa(&(reloj1->anio),ANIOMIN,ANIOMAX);

		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}
	if(encoder==DER){
		if(reloj1->mes==FEBRERO && reloj1->dia==0x29){
			do{
				Incrementa(&(reloj1->anio),ANIOMIN,ANIOMAX);
			}while((reloj1->anio)%4);
		}
		else Incrementa(&(reloj1->anio),ANIOMIN,ANIOMAX);
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}
}

/********************************************************************************
 *Funcion: ConfiguraHora
 * Acción: Función que configura el hora en el reloj y lo presenta en pantalla.
 * Recibe: Puntero al reloj que trabaja
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

static void ConfiguraHora(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracLLcd(POSHORA);
	if(readKey()==true)estado_reloj=CONFIGURAR_MIN;
	encoder=ReadEncoder();
	if(encoder==IZQ){
		Decrementa(&(reloj1->hora),HORAMIN,HORAMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}
	if(encoder==DER){
		Incrementa(&(reloj1->hora),HORAMIN,HORAMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}
}

/********************************************************************************
 *Funcion: ConfiguraMin
 * Acción: Función que configura los minutos en el reloj y lo presenta en pantalla.
 * Recibe: Puntero al reloj que trabaja
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

static void ConfiguraMin(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracLLcd(POSMIN);
	if(readKey()==true)estado_reloj=CONFIGURAR_SEG;
	encoder=ReadEncoder();
	if(encoder==IZQ){
		Decrementa(&(reloj1->min),MINMIN,MINMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}
	if(encoder==DER){
		Incrementa(&(reloj1->min),MINMIN,MINMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}
}

/********************************************************************************
 *Funcion: ConfiguraSeg
 * Acción: Función que configura los segundos en el reloj y lo presenta en pantalla.
 * Recibe: Puntero al reloj que trabaja
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/
static void ConfiguraSeg(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracLLcd(POSSEG);
	if(readKey()==true){
		CursorOffLcd();
		Reloj_Write(*reloj1);
		estado_reloj=PRESENTAR;
	}
	encoder=ReadEncoder();
	if(encoder==IZQ){
		Decrementa(&(reloj1->seg),SEGMIN,SEGMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}
	if(encoder==DER){
		Incrementa(&(reloj1->seg),SEGMIN,SEGMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}

}

/********************************************************************************
 *Funcion:  Decrementa
 * Acción: Función que se encarga de decrementar un variable y mantenerla entre los limites
 * Recibe: puntero a la variable a decrementar, limite inferior, y limite superior.
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/
static void Decrementa(uint8_t * valor,uint8_t limiteInf,uint8_t limiteSup){

	uint8_t aux;
	aux=(*valor&0x0f)+(((*valor&0xf0)>>4)*10);
	if(aux==limiteInf)aux=limiteSup;
	else aux--;
	*valor=((aux/10)<<4)|(aux%10);

}

/********************************************************************************
 *Funcion:  Incrementa
 * Acción: Función que se encarga de incrementar  un variable y mantenerla entre los limites
 * Recibe: puntero a la variable a incrementar, limite inferior, y limite superior.
 * Devuelve: nada
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/
static void Incrementa(uint8_t * valor,uint8_t limiteInf,uint8_t limiteSup){
	uint8_t aux;
	aux=(*valor&0x0f)+(((*valor&0xf0)>>4)*10);
	aux++;
	if(aux>limiteSup)aux=limiteInf;
	*valor=((aux/10)<<4)|(aux%10);

}

/********************************************************************************
 *Funcion: buscar_indice
 * Acción: Función que busca el limite de acuerdo al día ingresado
 * Recibe: el puntero donde buscarlo, el valor a buscar, y el limite de datos donde buscarlo
 * Devuelve: el indice donde se encuentra o ERROR si no lo encuentra
 *
 * Realizada por:Israel Pavelek
 * Version: 1.0
 * Fecha 13/4/23
  *
 **********************************************************************************/

static uint8_t buscar_indice (uint8_t * valor,uint8_t abuscar,uint8_t limite){

	for(int i=0;i<limite;i++)if(valor[i]==abuscar)return i;
	return ERROR;


}
