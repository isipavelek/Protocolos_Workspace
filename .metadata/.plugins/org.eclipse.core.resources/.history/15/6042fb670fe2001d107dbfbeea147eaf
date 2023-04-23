/// @file main.c
/// @version 1.0
/// @date 23/4/2023
/// @author Ing. Pavelek Israel
/// @title funcion principal
/// @brief archivo que maneja el main princial del dispositivo

/*! \mainpage Calendario Perpetuo
 *
 *	Trabajo realizado como integrador de la asignatura Protocolos de microcontroladores y programacion de microcontroladores del posgrado Especializacion en sistemas embebidos de la UBA
 *
 * \section intro_sec Autor:
 *
 * Ing. Israel Pavelek
 *
 * \section install_sec Proposito
 *
 * El dispositivo desarrollado es un Reloj Calendario perpetuo (utiliza la congruencia de Zeller para calcular el día de la semana). El mismo indica en pantalla la hora y fecha completa y alterna con la indicación de la temperatura ambiente. Además se puede visualizar la fecha en ingles o español.
 *
 *\section install_sec Docentes
 *
 * Mg. Ing. Patricio Bos (Programacion de microcontroladores)
 * Mg. Ing. Gonzalo Sanchez (Protocolos de microcontroladores)
 *
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_debounce.h"
#include "API_lcd.h"
#include "API_Lcd_port.h"
#include "API_init.h"
#include "API_reloj.h"
#include "API_encoder.h"
#include "API_enc_port.h"
#include "API_debounce.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**
  * @brief  reloj principal de todo el sistema
*/

reloj reloj1;

/**
  * @brief  Funcion Main
  * @param  void
  * @retval int
  */

int main(void){
  HAL_Init();
  /* Configure the system clock to 180 MHz */
  SystemClock_Config();
  /* Initialize BSP Led for LED2 */
  BSP_LED_Init(LED2);
  //BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  if(Init_Lcd()==LCD_ERROR)Error_Handler();
  RelojInit(&reloj1);			//inicializo el reloj
  ClrLcd();
  Init_Enc();					//inicializo el encoder
  debounceFSM_init();			//inicializo el debounce del pulsador del enconder
  while (true){

	  RelojFSM_Update(&reloj1);		//actualizo la MEF del reloj
  	  EncFSM_Update();				//actualizo la MEF del enconder
  	  debounceFSM_update();			//actualizo la MEF del putlsador del enconder*/

  }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

