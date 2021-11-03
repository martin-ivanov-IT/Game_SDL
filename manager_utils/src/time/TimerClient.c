//Corresponding header
#include "manager_utils/time/TimerClient.h"

//C system headers

//Other libraries headers

//Own components headers
#include "manager_utils/managers/TimerMgr.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

static const int64_t MIN_TIMER_INTERNAL = 20;

void createTimer(struct TimerClient *timerClient, void *clientProxy, void (*onTimeoutCb)(void *clientProxy, int32_t timerId)) {
  timerClient->clientProxy = clientProxy;
  timerClient->onTimeoutCb = onTimeoutCb;
}

void startTimer(struct TimerClient *timerClient, int64_t interval, int32_t timerId, TimerType timerType) {
  //if timer already exists -> do not start it
  if (isActiveTimerIdTimerMgr(gTimerMgr, timerId)) {
    LOGERR("Warning, timer with Id: [%d] already exist. Will not start new "
           "timer", timerId);
    return;
  }

  if (interval < MIN_TIMER_INTERNAL) {
    LOGERR("Warning, timer with Id: [%d] requested startTimer() with interval "
           "[%ld], while minimum interval is [%ld]. Timer will not be started.",
           timerId, interval, MIN_TIMER_INTERNAL);
    return;
  }

  startTimerTimerMgr(gTimerMgr, timerClient, interval, timerId, timerType);
}

void stopTimer(int32_t timerId) {
  stopTimerTimerMgr(gTimerMgr, timerId);
}

bool isActiveTimerId(int32_t timerId) {
  return isActiveTimerIdTimerMgr(gTimerMgr, timerId);
}

