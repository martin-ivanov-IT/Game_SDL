//Corresponding header
#include "manager_utils/time/TimerClientStructs.h"

//C system headers
#include <stddef.h>

//Other libraries headers

//Own components headers

void resetTimerData(struct TimerData *timerData) {
  timerData->interval = 0;
  timerData->remaining = 0;
  timerData->timerType = UNKNOWN_TIMER_TYPE;
  timerData->tcInstance = NULL;
}

