#include "utils/drawing/Rectangle.h"
#include "utils/drawing/Point.h"

const struct Rectangle RECTANGLE_ZERO = {.x = 0, .y = 0, .w = 0, .h = 0};
const struct Rectangle RECTANGLE_UNDEFINED = {.x = 10000, .y = 10000, .w = 10000, .h = 10000};

bool isPointInsideRect( const struct Rectangle* self, const struct Point* point){
    const bool isInsideXAxis = (self->x <= point->x) && (point->x <(self->x+self->w));
    const bool isInsideYAxis = (self->y <= point->y) && (point->y <(self->y+self->w));

    return isInsideXAxis && isInsideYAxis;
}

bool areRectsEqual(const struct Rectangle* left, const struct Rectangle* right){
    return (
            (left->x == right->x)
            && (left->y == right->y)
            && (left->h == right->h)
            && (left->w == right->w)
    );

}
