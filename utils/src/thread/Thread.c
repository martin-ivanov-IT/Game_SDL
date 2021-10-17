//Corresponding header
#include "utils/thread/Thread.h"

//C system headers
#include <errno.h>

//Other libraries headers

//Own components headers
#include "utils/time/Time.h"
#include "utils/Log.h"

void thisThreadSleepFor(int64_t sleepDurationNs) {
  if (sleepDurationNs < 0) {
    LOGERR("Error, thisThreadSleepFor() invoked with negative duration: "
        "[%ld ns]", sleepDurationNs);
  }

  struct timespec ts = { .tv_sec = sleepDurationNs / SECOND_NS,
                         .tv_nsec = sleepDurationNs % SECOND_NS };
  int32_t res = 0;
  do {
    res = nanosleep(&ts, &ts);
  } while (res && errno == EINTR);
}

