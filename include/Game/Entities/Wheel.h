#ifndef GAME_WHEEL_H_
#define GAME_WHEELH_
#include <stdint.h>
#include <stdbool.h>
#include "manager_utils/drawing/Image.h"
struct InputEvent;

struct WheelCfg{
    int32_t rsrcId;
};
struct Wheel{
    struct Image WheelImg;
     bool isRotStarted;
};
void handleEventWheel (struct Wheel* self, struct InputEvent* e);
int32_t initWheel(struct Wheel* self, int32_t rsrcId);
void deinitWheel(struct Wheel* self);
void drawWheel(struct Wheel* self);
void startRotationWheel(struct Wheel *wheel);
void stopRotationWheel(struct Wheel *wheel);

#endif
