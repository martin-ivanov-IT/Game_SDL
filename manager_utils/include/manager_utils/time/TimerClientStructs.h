#ifndef MANAGER_UTILS_TIME_TIMERCLIENTSTRUCTS_H_
#define MANAGER_UTILS_TIME_TIMERCLIENTSTRUCTS_H_

//C system headers
#include <stdint.h>

//Other libraries headers

//Own components headers

//Forward declarations
struct TimerClient;

typedef enum {
  ONESHOT_TIMER, PULSE_TIMER, UNKNOWN_TIMER_TYPE = 255
} TimerType;

struct TimerData {
  int64_t interval;
  int64_t remaining;
  TimerType timerType;
  struct TimerClient *tcInstance;
};

void resetTimerData(struct TimerData *timerData);

#endif /* MANAGER_UTILS_TIME_TIMERCLIENTSTRUCTS_H_ */

