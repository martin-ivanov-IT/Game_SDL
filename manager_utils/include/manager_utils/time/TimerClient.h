#ifndef MANAGER_UTILS_TIME_TIMERCLIENT_H_
#define MANAGER_UTILS_TIME_TIMERCLIENT_H_

//C system headers
#include <stdint.h>
#include <stdbool.h>

//Other libraries headers

//Own components headers
#include "manager_utils/time/TimerClientStructs.h"

struct TimerClient {
  void *clientProxy;
  void (*onTimeoutCb)(void *clientProxy, int32_t timerId);
};

void createTimer(struct TimerClient *timerClient, void *clientProxy,
                 void (*onTimeoutCb)(void *clientProxy, int32_t timerId));

void startTimer(struct TimerClient *timerClient, int64_t interval,
                int32_t timerId, TimerType timerType);

void stopTimer(int32_t timerId);

bool isActiveTimerId(int32_t timerId);

#endif /* MANAGER_UTILS_TIME_TIMERCLIENT_H_ */

