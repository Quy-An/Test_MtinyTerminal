#include "kxnTask.h"

void kxnTask::kDelay(unsigned long paTime){
    interval = paTime;
  }

  uint8_t kxnTask::getState(){
    return taskState;
  }

  bool kxnTask::isStateStop(){
    return taskState == KXN_TASK_STATE_STOP;
  }

  bool kxnTask::isStateStart(){
    return taskState == KXN_TASK_STATE_START;
  }

  bool kxnTask::isStateIdle(){
    return taskState == KXN_TASK_STATE_IDLE;
  }

  void kxnTask::setState(uint8_t pa_state){
    lastTaskState = taskState;
    taskState = pa_state;
  }

  void kxnTask::setStateStop(){
    setState(KXN_TASK_STATE_STOP);
  }

  void kxnTask::setStateIdle(){
    taskState = KXN_TASK_STATE_IDLE;
  }

  void kxnTask::run(unsigned long pa_ulCurrentTime) {
    runFast();
    unsigned long currentTime = pa_ulCurrentTime;

    if (currentTime - previousTime >= interval) {
      previousTime = currentTime;
      switch (taskState) {
      case KXN_TASK_STATE_IDLE:
        kxnTaskManager.remove(this);
        break;
      default:
        loop();
      }
      
    }
  }

  kxnTaskManagerClass kxnTaskManager;

#ifdef EN_KXNTASK_YIELD
  void yield(){
    kxnTaskManager.run(millis());
  }
#endif