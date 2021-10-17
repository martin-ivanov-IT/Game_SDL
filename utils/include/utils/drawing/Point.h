#ifndef UTILS_DRAWING_POINT_H_
#define UTILS_DRAWING_POINT_H_

//C system headers
#include <stdint.h>
#include <stdbool.h>

//Other libraries headers

//Own components headers

//Forward declarations

struct Point {
  int32_t x;
  int32_t y;
};

bool arePointsEqual(const struct Point* left, const struct Point* right);

bool arePointsDifferent(const struct Point* left, const struct Point* right);

extern const struct Point POINT_ZERO;
extern const struct Point POINT_UNDEFINED;

#endif /* UTILS_DRAWING_POINT_H_ */
