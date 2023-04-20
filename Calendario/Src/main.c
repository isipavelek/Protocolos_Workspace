/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_debounce.h"
#include "API_uart.h"
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
  * @brief  Main program
  * @param  None
  * @retval None
  */

reloj reloj1;


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

