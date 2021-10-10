#ifndef UTILS_INCLUDE_UTILS_REC_H
#define UTILS_INCLUDE_UTILS_REC_H

#include <stdint.h>
#include <stdbool.h>

struct Point;

struct Rectangle {
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;

};

const struct Rectangle RECTANGLE_ZERO;
const struct Rectangle RECTANGLE_UNDEFINED;

bool isPointInsideRect( const struct Rectangle* self, const struct Point* point);
bool areRectsEqual(const struct Rectangle* left, const struct Rectangle* right);


#endif