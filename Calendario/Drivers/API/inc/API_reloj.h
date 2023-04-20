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
#define ERROR -1
typedef enum{
	ENERO=1,FEBRERO,MARZO,ABRIL,MAYO,JUNIO,JULIO,AGOSTO,SEPTIEMBRE,OCTUBRE=0x10,NOVIEMBRE,DICIEMBRE

}meses_BCD;




typedef enum{

	PRESENTARTEMP,
	PRESENTARHORA,
	CONFIGURAR_DIA_ESP,
	CONFIGURAR_DIA_ENG,
	CONFIGURAR_MES_ESP,
	CONFIGURAR_MES_ENG,
	CONFIGURAR_ANIO,
	CONFIGURAR_HORA,
	CONFIGURAR_MIN,
	CONFIGURAR_SEG,
	CONFIGURAR_IDIOMA_INI,
	CONFIGURAR_IDIOMA
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

#define GRADOS 223   //valor ASCII del simbolo de º en el LCD

#define POSIDIOMA 5
#define POSIDIOMA1 1
#define POSIDIOMA2 10
#define POSTEMPTIT 2
#define POSTEMP 5
#define POSCOMIENZAHORA 4
#define POSCOMIENZAFECHA 2
#define POSFECHA (POSCOMIENZAFECHA+5)
#define POSMES (POSFECHA+3)
#define POSMESENG POSFECHA
#define POSFECHAENG POSMES
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


#define bit7 (1<<7)
#define bit6 (1<<6)

typedef enum {
	LINEA_1=1,LINEA_2,LINEA_3,LINEA_4
}lineasLCD;


void RelojInit(reloj *);
void Reloj_Read(reloj* reloj1);
void Reloj_Write(reloj reloj1);
void RelojFSM_Update(reloj* reloj1);



#endif /* API_INC_API_RELOJ_H_ */
