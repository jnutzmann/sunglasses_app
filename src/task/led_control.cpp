
#include "led_control.h"


#include "hw/stm32f3xx/gpio.h"
#include "hw/stm32f3xx/spi.h"

#include "freertos/ticks.hpp"
#include "freertos/src/CMSIS_RTOS_V2/cmsis_os.h"


#include "hw/tps92518.h"

#include "pin_definitions.h"


using namespace hw::stm32f3xx;


namespace task {

//typedef struct {
//    uint8_t on_hour    : 5;
//    uint8_t on_min     : 3;
//    uint8_t off_hour   : 5;
//    uint8_t off_min    : 3;
//    uint8_t brightness : 8;
//    uint8_t fade       : 8;
//} LedConfig;
//


LedControlTask::LedControlTask(hw::stm32f3xx::Rtc& rtc)
  : freertos::Thread("LED", 128*2, osPriorityAboveNormal1), _rtc(rtc) {
  Start();
};


void LedControlTask::Run() {

  uint16_t brightness = 210;
  uint8_t hour_on = 6;
  uint8_t minute_on = 0;
  uint8_t hour_off = 10+12;
  uint8_t minute_off = 0;

  // Slave Select Pins
  GpioPin led0_ss(LED0_SS_GPIO_Port, LED0_SS_Pin,
                  GpioPin::Mode::kOutput,
                  GpioPin::OutputType::kPushPull,
                  GpioPin::OutputSpeed::kHigh,
                  GpioPin::Pull::kNoPull,
                  GpioPin::State::kSet);

  GpioPin led1_ss(LED1_SS_GPIO_Port, LED1_SS_Pin,
                  GpioPin::Mode::kOutput,
                  GpioPin::OutputType::kPushPull,
                  GpioPin::OutputSpeed::kHigh,
                  GpioPin::Pull::kNoPull,
                  GpioPin::State::kSet);

  // PWM Pins (Enables)
  GpioPin led0_pwm_a(LED0_PWM_A_GPIO_Port, LED0_PWM_A_Pin,
                     GpioPin::Mode::kOutput,
                     GpioPin::OutputType::kPushPull,
                     GpioPin::OutputSpeed::kLow,
                     GpioPin::Pull::kNoPull,
                     GpioPin::State::kReset);

  GpioPin led0_pwm_b(LED0_PWM_B_GPIO_Port, LED0_PWM_B_Pin,
                     GpioPin::Mode::kOutput,
                     GpioPin::OutputType::kPushPull,
                     GpioPin::OutputSpeed::kLow,
                     GpioPin::Pull::kNoPull,
                     GpioPin::State::kReset);

  GpioPin led1_pwm_a(LED1_PWM_A_GPIO_Port, LED1_PWM_A_Pin,
                     GpioPin::Mode::kOutput,
                     GpioPin::OutputType::kPushPull,
                     GpioPin::OutputSpeed::kLow,
                     GpioPin::Pull::kNoPull,
                     GpioPin::State::kReset);

  GpioPin led1_pwm_b(LED1_PWM_B_GPIO_Port, LED1_PWM_B_Pin,
                     GpioPin::Mode::kOutput,
                     GpioPin::OutputType::kPushPull,
                     GpioPin::OutputSpeed::kLow,
                     GpioPin::Pull::kNoPull,
                     GpioPin::State::kReset);

  SpiMaster spi1(16,
                 GPIOA, GPIO_PIN_6,
                 GPIOA, GPIO_PIN_7,
                 GPIOA, GPIO_PIN_5);

  hw::Tps92518 led0(&spi1, &led0_ss);
  hw::Tps92518 led1(&spi1, &led1_ss);

//  hw::tps92618ReadRsp rsp0[17];
//  hw::tps92618ReadRsp rsp1[17];

  hw::tps92618WriteRsp cmdresp;

  led0.Write(hw::Tps92518::Register::RESET, 0x0C3, &cmdresp);
  led1.Write(hw::Tps92518::Register::RESET, 0x0C3, &cmdresp);

//  for (int i=0; i <= 0x10; i++) {
//    led0.Read((hw::Tps92518::Register)i, &rsp0[i]);
//    led1.Read((hw::Tps92518::Register)i, &rsp1[i]);
//  }

  led0.Write(hw::Tps92518::Register::LED1_TOFF_DAC, 42, &cmdresp);
  led0.Write(hw::Tps92518::Register::LED2_TOFF_DAC, 42, &cmdresp);
  led1.Write(hw::Tps92518::Register::LED1_TOFF_DAC, 42, &cmdresp);
  led1.Write(hw::Tps92518::Register::LED2_TOFF_DAC, 42, &cmdresp);

  led0.Write(hw::Tps92518::Register::LED1_PKTH_DAC, brightness, &cmdresp);
  led0.Write(hw::Tps92518::Register::LED2_PKTH_DAC, brightness, &cmdresp);
  led1.Write(hw::Tps92518::Register::LED1_PKTH_DAC, brightness, &cmdresp);
  led1.Write(hw::Tps92518::Register::LED2_PKTH_DAC, brightness, &cmdresp);

  uint8_t hours, minutes, seconds;
  _rtc.GetTime(hours, minutes, seconds);

  bool isOn = true;
  //bool isOn = ((hours > hour_on || (hours == hour_on && minutes >= minute_on))
  //    & (hours < hour_off || (hours == hour_off && minutes < minute_off)));

  led0_pwm_a.Write(isOn ? GpioPin::State::kSet : GpioPin::State::kReset);
  led0_pwm_b.Write(isOn ? GpioPin::State::kSet : GpioPin::State::kReset);
  led1_pwm_a.Write(isOn ? GpioPin::State::kSet : GpioPin::State::kReset);
  led1_pwm_b.Write(isOn ? GpioPin::State::kSet : GpioPin::State::kReset);

  led0.Write(hw::Tps92518::Register::CONTROL, 0b11, &cmdresp);
  led1.Write(hw::Tps92518::Register::CONTROL, 0b11, &cmdresp);

//  for (int i=0; i <= 0x10; i++) {
//    led0.Read((hw::Tps92518::Register)i, &rsp0[i]);
//    led1.Read((hw::Tps92518::Register)i, &rsp1[i]);
//  }


  while (true) {

//    _rtc.GetTime(hours, minutes, seconds);
//
//    isOn = ((hours > hour_on || (hours == hour_on && minutes >= minute_on))
//        & (hours < hour_off || (hours == hour_off && minutes < minute_off)));
//
//    led0_pwm_a.Write(isOn ? GpioPin::State::kSet : GpioPin::State::kReset);
//    led0_pwm_b.Write(isOn ? GpioPin::State::kSet : GpioPin::State::kReset);
//    led1_pwm_a.Write(isOn ? GpioPin::State::kSet : GpioPin::State::kReset);
//    led1_pwm_b.Write(isOn ? GpioPin::State::kSet : GpioPin::State::kReset);

    Delay(1000*20); // check every 20 seconds

        //if (increasing) { brightness++; if (brightness == 32) increasing = false; }
        //else { brightness--; if (brightness == 16) increasing = true; }

        //led1.Write(hw::Tps92518::Register::LED1_PKTH_DAC, brightness, &cmdresp);

        //Delay(50);
  }
}

} // namespace task
