#ifndef GAME_WHEEL_H_
#define GAME_WHEEL_H_
#include <stdint.h>
#include <stdbool.h>
#include "manager_utils/drawing/Image.h"
#include "manager_utils/time/TimerClient.h"

struct InputEvent;

struct WheelCfg{
    int32_t rsrcId;
};
struct Wheel{
    struct TimerClient timerClient;
    struct Image WheelImg;
    int32_t rotTimerId;
    bool isRotStarted;
};
void handleEventWheel (struct Wheel* self, struct InputEvent* e);
int32_t initWheel(struct Wheel* self, int32_t rsrcId, int32_t rotTimerId);
void deinitWheel(struct Wheel* self);
void drawWheel(struct Wheel* self);
void startRotationWheel(struct Wheel *wheel);
void stopRotationWheel(struct Wheel *wheel);


#endif
