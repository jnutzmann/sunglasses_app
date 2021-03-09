#include "main.h"
#include "rcc.h"
#include "error.h"

#include "hw/stm32f3xx/gpio.h"

#include "task/led_control.h"

#include "pin_definitions.h"

#include "freertos/src/CMSIS_RTOS_V2/cmsis_os.h"

#include "freertos/thread.hpp"
#include "freertos/ticks.hpp"

#include "hw/stm32f3xx/uart_shell.h"

using namespace hw::stm32f3xx;






class DefaultThread : public freertos::Thread {

  public:
    DefaultThread(void)
      : freertos::Thread("dft", 128*1, osPriorityNormal) {
      Start();
    };

  protected:

    virtual void Run() {

      // LED Pins
      GpioPin red_led(LED_RED_GPIO_Port,
                      LED_RED_Pin,
                      GpioPin::Mode::kOutput,
                      GpioPin::OutputType::kPushPull,
                      GpioPin::OutputSpeed::kLow,
                      GpioPin::Pull::kNoPull,
                      GpioPin::State::kReset);

      GpioPin blue_led(LED_BLUE_GPIO_Port,
                       LED_BLUE_Pin,
                       GpioPin::Mode::kOutput,
                       GpioPin::OutputType::kPushPull,
                       GpioPin::OutputSpeed::kLow,
                       GpioPin::Pull::kNoPull,
                       GpioPin::State::kReset);


      while (true) {
        red_led.Toggle();
        Delay(freertos::Ticks::MsToTicks(500));
        blue_led.Toggle();
      }
    };
};




static constexpr UartShell::Config debugShellConfig = {
    .uartIndex = 3,
    .baudrate = 115200,
    .txPort = GPIOB, .txPin = GPIO_PIN_10,
    .rxPort = GPIOB, .rxPin = GPIO_PIN_11
};

static UartShell debugShell(debugShellConfig);
extern "C" { void USART3_IRQHandler(void) { debugShell.ServiceInterrupt(); } }





int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  rcc_init();

  // Enable all the GPIO clocks.
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();


  //shell = &dbgShell;

  task::LedControlTask ledControlTask;
  DefaultThread dThread;

  freertos::Thread::StartScheduler();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  while (1) { }

}




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
