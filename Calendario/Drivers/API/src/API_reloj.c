/// @file API_reloj.c
/// @version 1.0
/// @date 23/4/2023
/// @author Ing. Pavelek Israel
/// @title API_Reloj.c
/// @brief Funciones Reloj.c

#include "API_reloj.h"
#include "API_lcd.h"
#include "API_rtc.h"
#include "API_debounce.h"
#include "API_encoder.h"



typedef enum{
	ESP,
	ENG,
	CANT_IDIOMAS



}idioma_t;
static bool_t idioma=ESP;
static const uint8_t POSIDIOMA_SELEC[]={1,10};			//Posicion del idioma indices
/******************************/

static uint8_t estado_reloj;

static const uint8_t dia[][7][4]={{"Dom","Lun","Mar","Mie","Jue","Vie","Sab"},
								{"Sun","Mon","Thu","Wed","Tue","Fri","Sat"}};

static const uint8_t mes31[]={ENERO,MARZO,MAYO,JULIO,AGOSTO,OCTUBRE,DICIEMBRE};

static void PresentaFechaLCD(reloj*,uint8_t pos,uint8_t linea);
static void PresentaHoraLCD(reloj*,uint8_t pos,uint8_t linea);
static void PresentaTempLCD(uint8_t pos);
static void Decrementa(uint8_t * valor,uint8_t limiteInf,uint8_t limiteSup);
static void Incrementa(uint8_t * valor,uint8_t limiteInf,uint8_t limiteSup);
static uint8_t buscar_indice (uint8_t * valor,uint8_t abuscar,uint8_t limite);
static void calcula_dia_semana(reloj* reloj1);
static void Configuro_idioma_ini(void);
static void Configuro_idioma(void);
static void PresentarHoraYFecha(reloj* reloj1);
static void PresentarTempe(reloj* reloj1);

static uint8_t BCD_a_Dec (uint8_t dato);

static void ConfiguraDiaEsp(reloj* reloj1);
static void ConfiguraMesEsp(reloj* reloj1);
static void ConfiguraDiaEng(reloj* reloj1);
static void ConfiguraMesEng(reloj* reloj1);
static void ConfiguraAnio(reloj* reloj1);
static void ConfiguraHora(reloj* reloj1);
static void ConfiguraMin(reloj* reloj1);
static void ConfiguraSeg(reloj* reloj1);


 /// @brief PresentaTempLCD
 /// Acción: Función que presenta en el LCD la temperatura
 /// @param uint8_t pos posición donde colocarlo en la linea inferior
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23



static void PresentaTempLCD(uint8_t pos){

	temp_t temp=RTC_Read_Temp();
	PosCaracHLcd(POSTEMPTIT);
	if(idioma==ESP)SacaTextoLcd((uint8_t*)"Temperatura:");
	else SacaTextoLcd((uint8_t*)"Temperature:");
	PosCaracLLcd(POSTEMP);
	DatoAsciiLcd(temp.temp_ent/10);				//me quedo con las decenas y presento
	DatoAsciiLcd(temp.temp_ent%10);				//me quedo con las unidades  y presento
	DatoLcd('.');
	temp.temp_dec=((temp.temp_dec&bit7)>>7)*50+((temp.temp_dec&bit6)>>6)*25;  //como los bits mas significativos de esta posicion
																	//representan los bits luego de la coma de acuerdo
																	//a si están en 1 o 0resicion de .25ºC)
																	//me quedo con  es el peso que representan en el formato de
																	//coma fija .50 o .25 (pcada bit y lo llevo al peso que corresponde
	DatoAsciiLcd(temp.temp_dec/10);				//me quedo con las decenas  y presento
	DatoAsciiLcd(temp.temp_dec%10);				//me quedo con las unidades  y presento
	DatoLcd(GRADOS);
	DatoLcd('C');

}

/// @brief PresentaFechaLCD
 /// Acción: Función que presenta en el LCD la Fecha
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @param uint8_t pos Posicion donde presentar en el LCD
 /// @param lineasLCD linea Linea en donde presentar LINEA_1....
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23



static void PresentaFechaLCD(reloj* reloj1,uint8_t pos,lineasLCD linea){

	  if(linea==LINEA_1)PosCaracHLcd(pos);
	  else PosCaracLLcd(pos);
	  calcula_dia_semana(reloj1);
	  SacaTextoLcd((uint8_t *)dia[idioma][(reloj1->diasem)-1]);
	  DatoLcd(' ');
	  if(idioma==ENG){
		  DatoBCD (reloj1->mes);
		  DatoLcd('/');
		  DatoBCD (reloj1->dia);

	  }else{
		  DatoBCD (reloj1->dia);
		  DatoLcd('/');
		  DatoBCD (reloj1->mes);
	  }
	  DatoLcd('/');
	  DatoBCD (reloj1->anio);

}



/// @brief PresentaHoraLCD
 /// Acción: Función que presenta en el LCD la Hora
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @param uint8_t pos Posicion donde presentar en el LCD
 /// @param lineasLCD linea Linea en donde presentar LINEA_1....
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23

static void PresentaHoraLCD(reloj* reloj1,uint8_t pos,uint8_t linea){

	  if(linea==1)PosCaracHLcd(pos);
	  else PosCaracLLcd(pos);
	  DatoBCD (reloj1->hora);
	  DatoLcd(':');
	  DatoBCD (reloj1->min);
	  DatoLcd(':');
	  DatoBCD (reloj1->seg);

}


/// @brief RelojInit
 /// Acción: Función que Inicializa la FSM del reloj
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23


void RelojInit(reloj* reloj1){
	estado_reloj=PRESENTARHORA;
	/*reloj1->seg=0;
	reloj1->min=0;
	reloj1->hora=0;
	reloj1->diasem=0;
	reloj1->dia=1;
	reloj1->mes=1;
	reloj1->anio=0;*/

}


/// @brief Reloj_Read
 /// Acción: Función que lee el reloj
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23

void Reloj_Read(reloj* reloj1){

	RTC_Read_Cal(reloj1);

}

/// @brief Reloj_Write
 /// Acción: Función que escribe el reloj
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23
void Reloj_Write(reloj reloj1){
	RTC_Write_Cal(reloj1);

}

/// @brief RelojFSM_Update
 /// Acción: Función que actualiza la FSM del reloj
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23

void RelojFSM_Update(reloj* reloj1){
	switch(estado_reloj){
		case PRESENTARHORA:
						PresentarHoraYFecha(reloj1);
						break;
		case PRESENTARTEMP:
						PresentarTempe(reloj1);
						break;
		case CONFIGURAR_DIA_ESP:
						ConfiguraDiaEsp(reloj1);
						break;
		case CONFIGURAR_DIA_ENG:
						ConfiguraDiaEng(reloj1);
						break;
		case CONFIGURAR_MES_ESP:
						ConfiguraMesEsp(reloj1);
						break;
		case CONFIGURAR_MES_ENG:
						ConfiguraMesEng(reloj1);
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
		case CONFIGURAR_IDIOMA_INI:
						Configuro_idioma_ini();
						break;
		case CONFIGURAR_IDIOMA:
						Configuro_idioma();
						break;

	}


}
/// @brief PresentarTempe
 /// Acción: Funciòn que presenta la temperatura en el LCD
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23

static void PresentarTempe(reloj* reloj1){
	uint8_t SW;
	Reloj_Read(reloj1);
	PresentaTempLCD(POSTEMP);
	SW=LeerSW();
	if(SW==PRESIONADO){
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
		CursorOnLcd();
		if(idioma==ESP)estado_reloj=CONFIGURAR_DIA_ESP;
		else estado_reloj=CONFIGURAR_MES_ENG;
	}else if(SW==PRES_LARGO_TIEMPO){

		estado_reloj=CONFIGURAR_IDIOMA_INI;
	}
	if(((reloj1->seg)&0x0f)==9){
		ClrLcd();
		estado_reloj=PRESENTARHORA;
	}


}

/// @brief PresentarHoraYFecha
 /// Acción: Funciòn que presenta la hora y fecha en el LCD
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23

static void PresentarHoraYFecha(reloj* reloj1){
	uint8_t SW;
	Reloj_Read(reloj1);
	PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	SW=LeerSW();
	if(SW==PRESIONADO){
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
		CursorOnLcd();
		if(idioma==ESP)estado_reloj=CONFIGURAR_DIA_ESP;
		else estado_reloj=CONFIGURAR_MES_ENG;
	}else if(SW==PRES_LARGO_TIEMPO){

		estado_reloj=CONFIGURAR_IDIOMA_INI;
	}
	if(((reloj1->seg)&0x0f)==4){
		ClrLcd();
		estado_reloj=PRESENTARTEMP;
	}
}

/// @brief ConfiguraDiaEsp
 /// Acción: Funciòn que configura el dia en español
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23

static void ConfiguraDiaEsp(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracHLcd(POSFECHA);
	if(LeerSW()==PRESIONADO){
		if(reloj1->dia==0x30 && reloj1->mes==FEBRERO)reloj1->mes=MARZO;
		if(reloj1->dia==0x31 && (reloj1->mes==FEBRERO || reloj1->mes==ABRIL || reloj1->mes==JUNIO || reloj1->mes==SEPTIEMBRE || reloj1->mes==NOVIEMBRE))(reloj1->mes)++;
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
		estado_reloj=CONFIGURAR_MES_ESP;
	}
	encoder=LeerEncoder();
	if(encoder==IZQ){
		Decrementa(&(reloj1->dia),DIAMIN,DIAMAX);
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}
	if(encoder==DER){
		Incrementa(&(reloj1->dia),DIAMIN,DIAMAX);
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}

}


/// @brief ConfiguraMesEng
 /// Acción: Funciòn que configura el mes en ingles
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23


static void ConfiguraMesEng(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracHLcd(POSMESENG);
	if(LeerSW()==PRESIONADO){
		if((reloj1->mes==FEBRERO || reloj1->mes==ABRIL || reloj1->mes==JUNIO || reloj1->mes==SEPTIEMBRE || reloj1->mes==NOVIEMBRE) && reloj1->dia==0x31)(reloj1->dia)--;
		if(reloj1->mes==FEBRERO && reloj1->dia==0x30)(reloj1->dia)--;
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
		estado_reloj=CONFIGURAR_DIA_ENG;
	}
	encoder=LeerEncoder();
	if(encoder==IZQ){
		Decrementa(&(reloj1->mes),MESMIN,MESMAX);

		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}
	if(encoder==DER){
		Incrementa(&(reloj1->mes),MESMIN,MESMAX);
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}

}
/// @brief ConfiguraDiaEng
 /// Acción: Funciòn que configura el dia en ingles
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23

static void ConfiguraDiaEng(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracHLcd(POSFECHAENG);
	if(LeerSW()==PRESIONADO){
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
		estado_reloj=CONFIGURAR_ANIO;
	}
	encoder=LeerEncoder();
	if(encoder==IZQ){

		if(reloj1->mes==ENERO || reloj1->mes==MARZO || reloj1->mes==MAYO || reloj1->mes==JULIO || reloj1->mes==AGOSTO || reloj1->mes==OCTUBRE || reloj1->mes==DICIEMBRE)
			Decrementa(&(reloj1->dia),DIAMIN,DIAMAX);
		else if(reloj1->mes==FEBRERO)Decrementa(&(reloj1->dia),DIAMIN,DIAMAX-2);
		else Decrementa(&(reloj1->dia),DIAMIN,DIAMAX-1);
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}
	if(encoder==DER){

		if(reloj1->mes==ENERO || reloj1->mes==MARZO || reloj1->mes==MAYO || reloj1->mes==JULIO || reloj1->mes==AGOSTO || reloj1->mes==OCTUBRE || reloj1->mes==DICIEMBRE)
			Incrementa(&(reloj1->dia),DIAMIN,DIAMAX);
		else if(reloj1->mes==FEBRERO)Incrementa(&(reloj1->dia),DIAMIN,DIAMAX-2);
		else Incrementa(&(reloj1->dia),DIAMIN,DIAMAX-1);

		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}
}

/// @brief ConfiguraMesEsp
 /// Acción: Funciòn que configura el mes en español
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23

static void ConfiguraMesEsp(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracHLcd(POSMES);
	if(LeerSW()==PRESIONADO){
		if(reloj1->mes==FEBRERO && reloj1->dia==0x29){
			do Incrementa(&(reloj1->anio),ANIOMIN,ANIOMAX);
			while((reloj1->anio)%4);
		}
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);

		estado_reloj=CONFIGURAR_ANIO;

	}
	encoder=LeerEncoder();
	/*
	 * Como el limite del mes depende del dia ingresado al decrementar
	 * o incrementar tengo que tener en cuenta lo ingresado en el dia.
	 * Si el dia fue 31 solo tengo unos meses
	 * si el dia tenia 30 solo queda exceptuado febrero
	 * en cualquier otro caso puedo ingresar cualquier mes
	 * */
	if(encoder==IZQ){
		if((reloj1->dia)<0x31){
		    Decrementa(&(reloj1->mes),MESMIN,MESMAX);	//si el mes no tiene 31, lo dejo decrementar libremente
			if((reloj1->dia)==0x30)if(reloj1->mes==0x02)reloj1->mes--;
		}
		else{
			uint8_t indice=buscar_indice((uint8_t *)mes31,reloj1->mes,sizeof(mes31));  //busco el limite
			if(indice==0)reloj1->mes=mes31[sizeof(mes31)-1];
			else reloj1->mes=mes31[indice-1];
		}
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}
	if(encoder==DER){
		if((reloj1->dia)<0x31){
			Incrementa(&(reloj1->mes),MESMIN,MESMAX); //si el mes no tiene 31, lo dejo incrementar  libremente
			if((reloj1->dia)==0x30)if(reloj1->mes==0x02)reloj1->mes++;;
		}
		else{
			uint8_t indice=buscar_indice((uint8_t *)mes31,reloj1->mes,sizeof(mes31)); //busco el limite
			if(indice==sizeof(mes31)-1)reloj1->mes=mes31[0];
			else reloj1->mes=mes31[indice+1];
		}
		PresentaFechaLCD(reloj1,POSCOMIENZAFECHA,LINEA_1);
	}
}

/// @brief ConfiguraAnio
 /// Acción: Funciòn que configura el anio
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23


static void ConfiguraAnio(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracHLcd(POSANIO);
	if(LeerSW()==PRESIONADO)estado_reloj=CONFIGURAR_HORA;
	encoder=LeerEncoder();
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

/// @brief ConfiguraHora
 /// Acción: Funciòn que configura la hora
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23


static void ConfiguraHora(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracLLcd(POSHORA);
	if(LeerSW()==PRESIONADO)estado_reloj=CONFIGURAR_MIN;
	encoder=LeerEncoder();
	if(encoder==IZQ){
		Decrementa(&(reloj1->hora),HORAMIN,HORAMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}
	if(encoder==DER){
		Incrementa(&(reloj1->hora),HORAMIN,HORAMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}
}

/// @brief ConfiguraMin
 /// Acción: Funciòn que configura los minutos
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23


static void ConfiguraMin(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracLLcd(POSMIN);
	if(LeerSW()==PRESIONADO)estado_reloj=CONFIGURAR_SEG;
	encoder=LeerEncoder();
	if(encoder==IZQ){
		Decrementa(&(reloj1->min),MINMIN,MINMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}
	if(encoder==DER){
		Incrementa(&(reloj1->min),MINMIN,MINMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}
}

/// @brief ConfiguraSeg
 /// Acción: Funciòn que configura los segundos
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23

static void ConfiguraSeg(reloj* reloj1){
	uint8_t encoder=0;

	PosCaracLLcd(POSSEG);
	if(LeerSW()==PRESIONADO){
		CursorOffLcd();
		Reloj_Write(*reloj1);
		estado_reloj=PRESENTARHORA;
	}
	encoder=LeerEncoder();
	if(encoder==IZQ){
		Decrementa(&(reloj1->seg),SEGMIN,SEGMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}
	if(encoder==DER){
		Incrementa(&(reloj1->seg),SEGMIN,SEGMAX);
		PresentaHoraLCD(reloj1,POSCOMIENZAHORA,LINEA_2);
	}

}
/// @brief Configuro_idioma_ini
 /// Acción: Funciòn que presenta la posibilidad de cambiar el idioma
 /// @param nada
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23


static void Configuro_idioma_ini(void){
	ClrLcd();
	PosCaracHLcd(POSIDIOMA);
	SacaTextoLcd((uint8_t *)"IDIOMA");
	PosCaracLLcd(0);
	SacaTextoLcd((uint8_t *)"  ESP      ENG  ");
	PosCaracLLcd(POSIDIOMA_SELEC[idioma]);
	DatoLcd('>');
	estado_reloj=CONFIGURAR_IDIOMA;

}

/// @brief Configuro_idioma
 /// Acción: Funciòn que cambia el idioma
 /// @param nada
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23


static void Configuro_idioma(void){

	if(LeerSW()==PRESIONADO){
			CursorOffLcd();
				ClrLcd();
			estado_reloj=PRESENTARHORA;
	}
	uint8_t encoder=LeerEncoder();
	if(encoder==IZQ){
		Decrementa((uint8_t *)&idioma,0,CANT_IDIOMAS-1);

		for(int i=0;i<sizeof(POSIDIOMA_SELEC);i++){
			PosCaracLLcd(POSIDIOMA_SELEC[i]);
			if(i==idioma)DatoLcd('>');
			else DatoLcd(' ');
		}
	}
	if(encoder==DER){
		Incrementa((uint8_t *)&idioma,0,CANT_IDIOMAS-1);
		for(int i=0;i<sizeof(POSIDIOMA_SELEC);i++){
			PosCaracLLcd(POSIDIOMA_SELEC[i]);
			if(i==idioma)DatoLcd('>');
			else DatoLcd(' ');
		}

	}

}

/// @brief Decrementa
 /// Acción: Función que se encarga de decrementar un variable y mantenerla entre los limites
 /// @param uint8_t * puntero a la variable a decrementar,
 /// @param uint8_t limite inferior
 /// @param uint8_t liminte superior
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23


static void Decrementa(uint8_t * valor,uint8_t limiteInf,uint8_t limiteSup){

	uint8_t aux;
	aux=(*valor&0x0f)+(((*valor&0xf0)>>4)*10);
	if(aux==limiteInf)aux=limiteSup;
	else aux--;
	*valor=((aux/10)<<4)|(aux%10);

}


/// @brief Incrementa
 /// Acción: Función que se encarga de Incrementar un variable y mantenerla entre los limites
 /// @param uint8_t * puntero a la variable a incrementar,
 /// @param uint8_t limite inferior
 /// @param uint8_t liminte superior
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23

static void Incrementa(uint8_t * valor,uint8_t limiteInf,uint8_t limiteSup){
	uint8_t aux;
	aux=(*valor&0x0f)+(((*valor&0xf0)>>4)*10);
	aux++;
	if(aux>limiteSup)aux=limiteInf;
	*valor=((aux/10)<<4)|(aux%10);

}


/// @brief buscar_indice
 /// Acción: Función que busca el limite de acuerdo al día ingresado

/// @param uint8_t * puntero al vector donde buscar,
 /// @param uint8_t valor a buscar
 /// @param uint8_t limite hasta donde buscar
 /// @return uint8_t posicion donde estaba en elemento o ERROR en caso de no encontrarlo
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23


static uint8_t buscar_indice (uint8_t * valor,uint8_t abuscar,uint8_t limite){

	for(int i=0;i<limite;i++)if(valor[i]==abuscar)return i;
	return ERROR;

}


/// @brief calcula_dia_semana
 /// Acción: Funciòn que implementa el algoritmo de Zeller para determinar el dia de la semana
 /// Referncia de la congruencia de Zeller: https://es.wikipedia.org/wiki/Congruencia_de_Zeller
 /// @param reloj* reloj1 Puntero al reloj a trabajar
 /// @return nada
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23


static void calcula_dia_semana(reloj* reloj1){
	int dia,n,anio,mes;
	dia=BCD_a_Dec(reloj1->dia);
	mes=BCD_a_Dec(reloj1->mes);
	anio=BCD_a_Dec(reloj1->anio)+2000 ; 		//supone que todos los calendarios que se utilizaran son a partir del 2000
	n = ((14 - mes) / 12);
	anio = (anio - n);
	mes = (mes + (12 * n) - 2);
	reloj1->diasem=(((dia + anio + (anio / 4) - (anio / 100) + (anio / 400) + ((31 * mes) / 12))%7 )+1);

}



/// @brief BCD_a_Dec
 /// Acción: Funcion que pasa un numero de BCD a decimal
 /// @param uint8_t  el valor en BCD a convertir
 /// @return uint8_t valor convertido en binario puro
 ///
 /// @author Realizada por:Israel Pavelek
 /// @version 1.0
 /// @date Fecha 16/4/23


static uint8_t BCD_a_Dec (uint8_t dato){
	return ((((dato&0xf0)>>4)*10) + (dato&0x0f));

}
