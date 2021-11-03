//Corresponding header
#include "manager_utils/managers/TimerMgr.h"

//C system headers
#include <stdlib.h>
#include <string.h>

//Other libraries headers

//Own components headers
#include "manager_utils/managers/config/TimerMgrConfig.h"
#include "manager_utils/time/TimerClient.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

struct TimerMgr *gTimerMgr = NULL;

static void onTimerTimeoutTimerMgr(struct TimerMgr *timerMgr, int32_t timerId,struct TimerData *timerData) {

  timerData->tcInstance->onTimeoutCb(timerData->tcInstance->clientProxy, timerId);

  if (ONESHOT_TIMER == timerData->timerType) {
    //If timer was on TimerType::ONESHOT it should close on it's own
    timerMgr->stoppedFrameTimers[timerId] = true;
    return;
  }
  timerData->remaining += timerData->interval;
}

static void removeTimersInternalTimerMgr(struct TimerMgr *timerMgr) {
  for (int32_t timerId = 0; timerId < MAX_SUPPORTED_TIMERS; ++timerId) {
    if (!timerMgr->stoppedFrameTimers[timerId]) {
      continue;
    }

    resetTimerData(&timerMgr->timerStorage[timerId]);
    timerMgr->stoppedFrameTimers[timerId] = false;
  }
}

int32_t initTimerMgr(struct TimerMgr *timerMgr) {
  initTime(&timerMgr->elapsedTime);
  return SUCCESS;
}

void deinitTimerMgr(struct TimerMgr *timerMgr) {
  UNUSED(timerMgr);
}

void processTimerMgr(struct TimerMgr *timerMgr) {
  const int64_t msElapsed = getElapsedMilliseconds(&timerMgr->elapsedTime);
  struct TimerData *currTimerData = NULL;

  for (int32_t timerId = 0; timerId < MAX_SUPPORTED_TIMERS; ++timerId) {
    currTimerData = &timerMgr->timerStorage[timerId];

    if (NULL == currTimerData->tcInstance) {
      continue;
    }

    currTimerData->remaining -= msElapsed;
    if (0 >= currTimerData->remaining) {
      onTimerTimeoutTimerMgr(timerMgr, timerId, currTimerData);
    }
  }

  removeTimersInternalTimerMgr(timerMgr);
}

void startTimerTimerMgr(struct TimerMgr *timerMgr, struct TimerClient *tcInstance, int64_t interval, int32_t timerId, TimerType timerType) {
  //The check for isActiveTimerId is invoked from TimerClient class
  if (isActiveTimerIdTimerMgr(timerMgr, timerId)){
    LOGERR("Error, timer with Id: %d is already active will  not start twice", timerId);
    return;
  }
  struct TimerData *currTimerData = &timerMgr->timerStorage[timerId];
  currTimerData->interval = interval;     //original interval
  currTimerData->remaining = interval;    //remaining interval
  currTimerData->timerType = timerType;   //ONESHOT or PULSE
  currTimerData->tcInstance = tcInstance; //TimerClient instance
}

void stopTimerTimerMgr(struct TimerMgr *timerMgr, int32_t timerId) {

  if (isActiveTimerIdTimerMgr(timerMgr, timerId)) {
    timerMgr->stoppedFrameTimers[timerId] = true;
  } 
  else {
    LOGERR("Warning, trying to remove a non-existing timer with Id: [%d]. "
           "Be sure to check your timerId with 'isActiveTimerId(timerId)' "
           "before calling 'stopTimer(timerId)'", timerId);
  }
}

bool isActiveTimerIdTimerMgr(struct TimerMgr *timerMgr, int32_t timerId) {
  const bool isUnsupportedTimerId = (0 > timerId || timerId >= MAX_SUPPORTED_TIMERS);
  if (isUnsupportedTimerId) {
    LOGERR("Warning, 'isActiveTimerIdTimerMgr()' invoked with non supported "
           "timerId: [%d]. Valid Ids are in the range [%d-%d]",
           timerId, 0, MAX_SUPPORTED_TIMERS);
    return false;
  }

  const bool isActive = (false == timerMgr->stoppedFrameTimers[timerId]) && (NULL != timerMgr->timerStorage[timerId].tcInstance);

  return isActive;
}

void onInitEndTimerMgr(struct TimerMgr *timerMgr) {
  //reset the timer so it can clear the "stored" time since the creation
  //of the TimerMgr instance and this function call
  advanceTime(&timerMgr->elapsedTime);
}

int32_t getActiveTimersCountTimerMgr(struct TimerMgr *timerMgr) {
  int32_t count = 0;
  for (int32_t timerId = 0; timerId < MAX_SUPPORTED_TIMERS; ++timerId) {
    if (NULL != timerMgr->timerStorage[timerId].tcInstance) {
      ++count;
    }
  }

  return count;
}

