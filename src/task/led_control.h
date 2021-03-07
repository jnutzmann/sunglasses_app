
#ifndef LED_CONTROL_TASK_H_
#define LED_CONTROL_TASK_H_

#include "freertos/thread.hpp"


namespace task {

class LedControlTask : public freertos::Thread {

  public:
    LedControlTask(void);

  protected:
    virtual void Run(void);

};


} // namespace task


#endif /* LED_CONTROL_TASK_H_ */
