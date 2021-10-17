//Corresponding header
#include "utils/drawing/Point.h"

//C system headers

//Other libraries headers

//Own components headers

bool arePointsEqual(const struct Point* left, const struct Point* right) {
  return (left->x == right->x && left->y == right->y);
}

bool arePointsDifferent(const struct Point* left, const struct Point* right) {
  return !arePointsEqual(left, right);
}

const struct Point POINT_ZERO = { .x = 0, .y = 0 };
const struct Point POINT_UNDEFINED = { .x = 100000, .y = 100000 };

