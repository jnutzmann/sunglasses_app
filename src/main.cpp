#include "main.h"
#include "rcc.h"
#include "error.h"

#include "hw/stm32f3xx/gpio.h"
#include "hw/stm32f3xx/spi.h"

#include "hw/tps92518.h"

#include "pin_definitions.h"

#include "freertos/src/CMSIS_RTOS_V2/cmsis_os.h"

#include "freertos/thread.hpp"
#include "freertos/ticks.hpp"

using namespace hw::stm32f3xx;


class DefaultThread : public freertos::Thread {

  public:
    DefaultThread(void)
      : freertos::Thread("default", 128*4, osPriorityAboveNormal) {
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

      // Slave Select Pins
      GpioPin led0_ss(LED0_SS_GPIO_Port,
                      LED0_SS_Pin,
                      GpioPin::Mode::kOutput,
                      GpioPin::OutputType::kPushPull,
                      GpioPin::OutputSpeed::kHigh,
                      GpioPin::Pull::kNoPull,
                      GpioPin::State::kSet);

      GpioPin led1_ss(LED1_SS_GPIO_Port,
                      LED1_SS_Pin,
                      GpioPin::Mode::kOutput,
                      GpioPin::OutputType::kPushPull,
                      GpioPin::OutputSpeed::kHigh,
                      GpioPin::Pull::kNoPull,
                      GpioPin::State::kSet);

      // PWM Pins (Enables)
      GpioPin led0_pwm_a(LED0_PWM_A_GPIO_Port,
                         LED0_PWM_A_Pin,
                         GpioPin::Mode::kOutput,
                         GpioPin::OutputType::kPushPull,
                         GpioPin::OutputSpeed::kHigh,
                         GpioPin::Pull::kNoPull,
                         GpioPin::State::kReset);

      GpioPin led0_pwm_b(LED0_PWM_B_GPIO_Port,
                         LED0_PWM_B_Pin,
                         GpioPin::Mode::kOutput,
                         GpioPin::OutputType::kPushPull,
                         GpioPin::OutputSpeed::kHigh,
                         GpioPin::Pull::kNoPull,
                         GpioPin::State::kReset);

      GpioPin led1_pwm_a(LED1_PWM_A_GPIO_Port,
                         LED1_PWM_A_Pin,
                         GpioPin::Mode::kOutput,
                         GpioPin::OutputType::kPushPull,
                         GpioPin::OutputSpeed::kHigh,
                         GpioPin::Pull::kNoPull,
                         GpioPin::State::kReset);

      GpioPin led1_pwm_b(LED1_PWM_B_GPIO_Port,
                         LED1_PWM_B_Pin,
                         GpioPin::Mode::kOutput,
                         GpioPin::OutputType::kPushPull,
                         GpioPin::OutputSpeed::kHigh,
                         GpioPin::Pull::kNoPull,
                         GpioPin::State::kReset);

      SpiMaster spi1(16,
                     GPIOA, GPIO_PIN_6,
                     GPIOA, GPIO_PIN_7,
                     GPIOA, GPIO_PIN_5);

      hw::Tps92518 led0(spi1, led0_ss);
      hw::Tps92518 led1(spi1, led1_ss);

      hw::tps92618ReadRsp rsp0[17];
      hw::tps92618ReadRsp rsp1[17];

      hw::tps92618WriteRsp cmdresp;

      led0.Write(hw::Tps92518::Register::RESET, 0x0C3, &cmdresp);
      led1.Write(hw::Tps92518::Register::RESET, 0x0C3, &cmdresp);

      for (int i=0; i <= 0x10; i++) {
        led0.Read((hw::Tps92518::Register)i, &rsp0[i]);
        led1.Read((hw::Tps92518::Register)i, &rsp1[i]);
      }

      led0.Write(hw::Tps92518::Register::LED1_TOFF_DAC, 42, &cmdresp);
      led0.Write(hw::Tps92518::Register::LED2_TOFF_DAC, 42, &cmdresp);
      led1.Write(hw::Tps92518::Register::LED1_TOFF_DAC, 42, &cmdresp);
      led1.Write(hw::Tps92518::Register::LED2_TOFF_DAC, 42, &cmdresp);

      led0.Write(hw::Tps92518::Register::LED1_PKTH_DAC, 24, &cmdresp);
      led0.Write(hw::Tps92518::Register::LED2_PKTH_DAC, 24, &cmdresp);
      led1.Write(hw::Tps92518::Register::LED1_PKTH_DAC, 24, &cmdresp);
      led1.Write(hw::Tps92518::Register::LED2_PKTH_DAC, 24, &cmdresp);

      led0_pwm_a.Write(GpioPin::State::kSet);
      led0_pwm_b.Write(GpioPin::State::kSet);
      led1_pwm_a.Write(GpioPin::State::kSet);
      led1_pwm_b.Write(GpioPin::State::kSet);

      led0.Write(hw::Tps92518::Register::CONTROL, 0b11, &cmdresp);
      led1.Write(hw::Tps92518::Register::CONTROL, 0b11, &cmdresp);

      for (int i=0; i <= 0x10; i++) {
        led0.Read((hw::Tps92518::Register)i, &rsp0[i]);
        led1.Read((hw::Tps92518::Register)i, &rsp1[i]);
      }

//      int brightness = 0;
//      bool increasing = true;
      while (true) {

//        if (increasing) { brightness++; if (brightness == 32) increasing = false; }
//        else { brightness--; if (brightness == 16) increasing = true; }
//
//        led1.Write(hw::Tps92518::Register::LED1_PKTH_DAC, brightness, &cmdresp);
//
//        Delay(50);

        red_led.Toggle();
        Delay(freertos::Ticks::MsToTicks(500));
        blue_led.Toggle();
      }
    };
};

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



  DefaultThread dThread;

  freertos::Thread::StartScheduler();

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
