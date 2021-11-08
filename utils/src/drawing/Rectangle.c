#include "utils/drawing/Rectangle.h"
#include "utils/drawing/Point.h"

const struct Rectangle RECTANGLE_ZERO = {.x = 0, .y = 0, .w = 0, .h = 0};
const struct Rectangle RECTANGLE_UNDEFINED = {.x = 10000, .y = 10000, .w = 10000, .h = 10000};

bool isPointInRect(const struct Point *point, const struct Rectangle *rect) {
  return (point->x >= rect->x) && (point->x < (rect->x + rect->w))
         && (point->y >= rect->y) && (point->y < (rect->y + rect->h));
}

bool areRectsEqual(const struct Rectangle* left, const struct Rectangle* right){
    return left->x == right->x && left->y == right->y && left->w == right->w
         && left->h == right->h;

}
