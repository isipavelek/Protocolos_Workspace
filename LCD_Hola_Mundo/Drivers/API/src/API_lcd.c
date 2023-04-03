/*
 * API_lcd.c
 *
 *  Created on: 14 mar. 2023
 *      Author: ipave
 */


#include "API_lcd.h"
#include "API_Lcd_port.h"
#include "API_delay.h"

static const uint8_t LCD_INIT_CMD[]={
		_4BIT_MODE,DISPLAY_CONTROL,RETURN_HOME,ENTRY_MODE+AUTOINCREMENT,DISPLAY_CONTROL+DISPLAY_ON,CLR_LCD
};

_Bool Init_Lcd(void){

   if(LCD_HW_init()==LCD_ERROR)return LCD_ERROR;
   DelayLcd(DELAY20ms);
   Send4bitsLcd(COMANDO_INI1,CONTROL);
   DelayLcd(DELAY10ms);
   Send4bitsLcd(COMANDO_INI1,CONTROL);
   DelayLcd(DELAY1ms);
   Send4bitsLcd(COMANDO_INI1,CONTROL);
   Send4bitsLcd(COMANDO_INI2,CONTROL);
   for(uint8_t i=0;i<sizeof(LCD_INIT_CMD);i++)ControlLcd(LCD_INIT_CMD[i]);
   DelayLcd(DELAY2ms);
   return LCD_OK;

}

void DelayLcd(uint32_t demora){
	  HAL_Delay(demora);
}


void ControlLcd(uint8_t valor){
	Send8bitsLcd(valor,CONTROL);
}

void DatoLcd (uint8_t dato){
	Send8bitsLcd(dato,DATOS);
}

void DatoAsciiLcd (uint8_t dato){
	Send8bitsLcd(dato+ '0',DATOS);
}

void DatoBCD (uint8_t dato){

	  DatoAsciiLcd((((dato)&0xf0)>>4));
	  DatoAsciiLcd(((dato)&0x0f));

}

void Send8bitsLcd (uint8_t valor,_Bool tipo){
	Send4bitsLcd(valor&HIGH_NIBBLE,tipo); 		//me con quedo y envio los 4 bits más significaticos.
	Send4bitsLcd(valor<<LOW_NIBBLE,tipo);   	//me quedo y envio los 4 bits menos significativos.
}

void Send4bitsLcd (uint8_t valor,_Bool tipo){

	LCD_Write_Byte(valor+tipo+EN+BL);
	DelayLcd(DelayTime);
	LCD_Write_Byte(valor+tipo+BL);
	DelayLcd(DelayTime);
}


void OutTextLcd (int8_t *texto){
	while(*texto)DatoLcd(*texto++);
}

void ClrLcd(void){
   ControlLcd(CLR_LCD);				//	Display Clear.
   DelayLcd(DELAY2ms);

}


void PosCaracHLcd(uint8_t posH){
	ControlLcd(posH | LINEA1);
}

void PosCaracLLcd(uint8_t posL){
	ControlLcd(posL | LINEA2);
}

void CursorOffLcd(void){
	ControlLcd(DISPLAY_CONTROL+DISPLAY_ON);
}

void CursorOnLcd(void){
	ControlLcd(DISPLAY_CONTROL+CURSOR_ON+DISPLAY_ON+CURSOR_BLINK);
}