
#ifndef LED_CONTROL_TASK_H_
#define LED_CONTROL_TASK_H_

#include "freertos/thread.hpp"
#include "hw/stm32f3xx/rtc.h"
#include "shell/cli.h"

namespace task {

class LedControlTask : public freertos::Thread {

  public:
    LedControlTask(hw::stm32f3xx::Rtc& rtc);

  protected:
    virtual void Run(void);

  private:
    hw::stm32f3xx::Rtc& _rtc;

};

class LedCommand : public shell::Command {
  public:
    LedCommand(hw::stm32f3xx::Rtc& rtc);
    void Callback(char* commandInput);
  private:
    hw::stm32f3xx::Rtc& _rtc;
};


} // namespace task


#endif /* LED_CONTROL_TASK_H_ */
