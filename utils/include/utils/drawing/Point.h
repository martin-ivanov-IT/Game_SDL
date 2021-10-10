#ifndef UTILS_INCLUDE_UTILS_POINT_H
#define UTILS_INCLUDE_UTILS_POINT_H

#include <stdint.h>
#include <stdbool.h>

struct Point {
    int32_t x;
    int32_t y;

};

bool arePointsEqual(struct Point* left, struct Point* right);
struct Point POINT_ZERO;
struct Point POINT_UNDEFINED;

#endif