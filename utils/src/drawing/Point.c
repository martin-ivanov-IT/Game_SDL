#include "utils/drawing/Point.h"

struct Point POINT_ZERO = {.x = 0, .y = 0};
struct Point POINT_UNDEFINED = {.x = 10000, .y = 10000};

bool arePointsEqual(struct Point* left, struct Point* right){
    return (left->x == right->x && left->y && right->y);
}