#ifndef UTILS_TIME_TIME_H_
#define UTILS_TIME_TIME_H_

//C system headers
#include <stdint.h>
#include <time.h>

//Other libraries headers

//Own components headers

//Forward declarations

//how many nanoseconds are there in single unit of time
typedef enum {
  SECOND_NS      = 1000000000,
  MILLISECOND_NS = 1000000,
  MICROSECOND_NS = 1000,
  NANOSECOND_NS  = 1
} TimeUnits;


struct Time {
  //used to measure time from the creation of the Time instance
  struct timespec startTime;

  //used to measure elapsed time since last getElapsed() call
  struct timespec elapsed;

  //used to help calculate the elapsed time since last getElapsed() call
  struct timespec elapsedLastCall;
};

void initTime(struct Time* time);

/** @brief used to measure elapsed time since last invoke of this method
 *         NOTE: .getElapsed() method simply measures time between 2
 *         points of time.
 * */
void advanceTime(struct Time* time);

/** @brief used to measure elapsed time since the creation of
 *                                                   the Time instance.
 * */
void getElapsedTimeFromStart(struct Time* time);

int64_t getElapsedNanoseconds(struct Time* time);
int64_t getElapsedMicroseconds(struct Time* time);
int64_t getElapsedMilliseconds(struct Time* time);
int64_t getElapsedSeconds(struct Time* time);

#endif /* UTILS_TIME_TIME_H_ */


