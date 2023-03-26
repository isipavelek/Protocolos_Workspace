/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_debounce.h"
#include "API_uart.h"
#include "API_lcd.h"
#include "API_Lcd_port.h"
#include "API_init.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void){
  int val=0;
  HAL_Init();
  /* Configure the system clock to 180 MHz */
  SystemClock_Config();
  /* Initialize BSP Led for LED2 */
  BSP_LED_Init(LED2);
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  if(Init_Lcd()==LCD_ERROR)Error_Handler();
  while (1){
	  PosCaracHLcd(0);
	  OutTextLcd((uint8_t *)"Hola mundo");
	  PosCaracLLcd(0);
	  DatoLcd(val+'0');
	  val++;
	  if(val==10)val=0;
	  HAL_Delay(1000);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

