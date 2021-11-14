#ifndef MANAGER_UTILS_MANAGERS_TIMERMGR_H_
#define MANAGER_UTILS_MANAGERS_TIMERMGR_H_

//C system headers
#include <stdint.h>
#include <stdbool.h>

//Other libraries headers

//Own components headers
#include "manager_utils/time/TimerClientStructs.h"
#include "utils/time/Time.h"

#define MAX_SUPPORTED_TIMERS 1000000

//Forward declarations
struct TimerMgrConfig;
struct TimerClient;

struct TimerMgr {
  struct Time elapsedTime;
  struct TimerData timerStorage[MAX_SUPPORTED_TIMERS];
  bool stoppedFrameTimers[MAX_SUPPORTED_TIMERS];
};

int32_t initTimerMgr(struct TimerMgr *timerMgr);

void deinitTimerMgr(struct TimerMgr *timerMgr);

void processTimerMgr(struct TimerMgr *timerMgr);

void startTimerTimerMgr(struct TimerMgr *timerMgr, struct TimerClient *tcInstance, int64_t interval, int32_t timerId, TimerType timerType);

void stopTimerTimerMgr(struct TimerMgr *timerMgr, int32_t timerId);

bool isActiveTimerIdTimerMgr(struct TimerMgr *timerMgr, int32_t timerId);

void onInitEndTimerMgr(struct TimerMgr *timerMgr);

int32_t getActiveTimersCountTimerMgr(struct TimerMgr *timerMgr);

extern struct TimerMgr *gTimerMgr;

#endif /* MANAGER_UTILS_MANAGERS_TIMERMGR_H_ */

