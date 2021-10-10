#include <stdio.h>
#include <stdint.h>

struct Point {
    int32_t x;
    int32_t y;

};

void swap(struct Point **const point, struct Point **  point2){
    (*point)->x = 20;
        *point = *point2;
}

void changeValue(struct Point * const point){
 point->x = 5;
}

int32_t main(int32_t argc, char **argv) {

    struct Point point;
    point.x = 0;
    point.y = 0;

    struct Point* pointPtr = &point;
    struct Point point2;
    struct Point* point2Ptr = &point2;
    point2.x = 0;
    point2.y = 10;
    changeValue(&point);
    printf("%d\n",pointPtr->y);
    swap(&pointPtr, &point2Ptr);
    printf("%d\n",pointPtr->y);
    // setPtrNull(&point);
    // printf("%d\n",point.x);


    return 0;
}

