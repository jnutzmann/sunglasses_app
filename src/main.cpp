#include "main.h"
#include "rcc.h"
#include "error.h"

#include "hw/stm32f3xx/gpio.h"

#include "pin_definitions.h"

#include "freertos/src/CMSIS_RTOS_V2/cmsis_os.h"

#include "freertos/thread.hpp"
#include "freertos/ticks.hpp"


class DefaultThread : public freertos::Thread {

  public:
    DefaultThread(void)
      : freertos::Thread("default", 128*4, osPriorityAboveNormal) {
      Start();
    };

  protected:

    virtual void Run() {

      hw::stm32f3xx::GpioPin red_led(LED_RED_GPIO_Port,
                                     LED_RED_Pin,
                                     hw::stm32f3xx::GpioPin::Mode::kOutput,
                                     hw::stm32f3xx::GpioPin::OutputType::kPushPull,
                                     hw::stm32f3xx::GpioPin::OutputSpeed::kLow,
                                     hw::stm32f3xx::GpioPin::Pull::kNoPull);
      red_led.ConfigureOutput();

      while (true) {
        red_led.Toggle();
        Delay(freertos::Ticks::MsToTicks(500));
      }
    };
};

//
//static void MX_GPIO_Init(void)
//{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//  /* GPIO Ports Clock Enable */
//  __HAL_RCC_GPIOC_CLK_ENABLE();
//  __HAL_RCC_GPIOF_CLK_ENABLE();
//  __HAL_RCC_GPIOA_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOA, LED_BLUE_Pin|LED0_PWM_A_Pin|LED0_PWM_B_Pin|LED1_PWM_A_Pin
//                          |LED1_PWM_B_Pin, GPIO_PIN_RESET);
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOB, LED0_SS_Pin|LED1_SS_Pin, GPIO_PIN_SET);
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOB, MAT0_EN_Pin|MAT1_EN_Pin|SOIL0_EN_Pin|SOIL1_EN_Pin, GPIO_PIN_RESET);
//
//  /*Configure GPIO pin : LED_RED_Pin */
//  GPIO_InitStruct.Pin = LED_RED_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(LED_RED_GPIO_Port, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : LED_BLUE_Pin LED0_PWM_A_Pin LED0_PWM_B_Pin LED1_PWM_A_Pin
//                           LED1_PWM_B_Pin */
//  GPIO_InitStruct.Pin = LED_BLUE_Pin|LED0_PWM_A_Pin|LED0_PWM_B_Pin|LED1_PWM_A_Pin
//                          |LED1_PWM_B_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : LED0_SS_Pin LED1_SS_Pin */
//  GPIO_InitStruct.Pin = LED0_SS_Pin|LED1_SS_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : MAT0_EN_Pin MAT1_EN_Pin SOIL0_EN_Pin SOIL1_EN_Pin */
//  GPIO_InitStruct.Pin = MAT0_EN_Pin|MAT1_EN_Pin|SOIL0_EN_Pin|SOIL1_EN_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//}


int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  rcc_init();

  /* Initialize all configured peripherals */
  //MX_GPIO_Init();
//  MX_ADC1_Init();
// MX_CAN_Init();
//  MX_I2C1_Init();
//  MX_RTC_Init();
//  MX_SPI1_Init();
//  MX_TIM3_Init();
//  MX_TIM17_Init();
//  MX_USART3_UART_Init();

  /* Init scheduler */
  //osKernelInitialize();

  DefaultThread dThread;

  freertos::Thread::StartScheduler();


//  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);


  /* Start scheduler */
//  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  while (1) { }

}


//void StartDefaultTask(void *argument)
//{
//  /* Infinite loop */
//  for(;;)
//  {
//	  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
//	  	osDelay(500);
//	  	HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
//  }
//}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
