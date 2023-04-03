/*
 * API_reloj.h
 *
 *  Created on: 1 abr. 2023
 *      Author: ipave
 */

#ifndef API_INC_API_RELOJ_H_
#define API_INC_API_RELOJ_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdbool.h>

typedef enum{
	ENERO=1,FEBRERO,MARZO,ABRIL,MAYO,JUNIO,JULIO,AGOSTO,SEPTIEMBRE,OCTUBRE=0x10,NOVIEMBRE,DICIEMBRE

}meses_BCD;



typedef enum{

	PRESENTAR,
	CONFIGURAR_DIA,
	CONFIGURAR_MES,
	CONFIGURAR_ANIO,
	CONFIGURAR_HORA,
	CONFIGURAR_MIN,
	CONFIGURAR_SEG
}estado;
typedef struct{

	uint8_t seg;
	uint8_t min;
	uint8_t hora;
	uint8_t diasem;
	uint8_t dia;
	uint8_t mes;
	uint8_t anio;

}reloj;

#define POSCOMIENZAHORA 4
#define POSCOMIENZAFECHA 4
#define POSFECHA (POSCOMIENZAFECHA+1)
#define POSMES (POSFECHA+3)
#define POSANIO (POSMES+3)
#define POSHORA (POSCOMIENZAHORA+1)
#define POSMIN (POSHORA+3)
#define POSSEG (POSMIN+3)

#define DIAMAX 31
#define DIAMIN 1

#define MESMIN 1
#define MESMAX 12

#define ANIOMAX 99
#define ANIOMIN 0

#define SEGMAX 59
#define SEGMIN 0

#define MINMAX 59
#define MINMIN 0

#define HORAMAX 23
#define HORAMIN 0

typedef enum {
	LINEA_1=1,LINEA_2,LINEA_3,LINEA_4
}lineasLCD;


void RelojInit(reloj *);
void PresentaFechaLCD(reloj*,uint8_t pos,uint8_t linea);
void PresentaHoraLCD(reloj*,uint8_t pos,uint8_t linea);
void Reloj_Read(reloj* reloj1);
void Reloj_Write(reloj reloj1);
void RelojFSM_Update(reloj* reloj1);
void Decrementa(uint8_t * valor,uint8_t limiteInf,uint8_t limiteSup);
void Incrementa(uint8_t * valor,uint8_t limiteInf,uint8_t limiteSup);
uint8_t buscar_indice (uint8_t * valor,uint8_t abuscar,uint8_t limite);


void ConfiguraDia(reloj* reloj1);
void ConfiguraMes(reloj* reloj1);
void ConfiguraAnio(reloj* reloj1);
void ConfiguraHora(reloj* reloj1);
void ConfiguraMin(reloj* reloj1);
void ConfiguraSeg(reloj* reloj1);




#endif /* API_INC_API_RELOJ_H_ */
