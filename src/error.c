/*
 * error.c
 *
 *  Created on: Feb 26, 2021
 *      Author: jnutzmann
 */

#include "error.h"
#include "stm32f3_hal/stm32f3xx_hal.h"


void error_handle(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


