#include "Game/Entities/Wheel.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
static const int64_t ROT_INTERVAL = 20;

static void processAnimation(struct Wheel *wheel){
    struct DrawParams* params = &wheel->WheelImg.widget.drawParams;
    params->rotationAngle +=10;
    const double FULL_ROTATION = 360.0;
    if(params->rotationAngle >= FULL_ROTATION){
        params->rotationAngle -= FULL_ROTATION;
    }

}

static void onTimerTimeout(void *clientProxy, int32_t timerId) {
    
  struct Wheel *wheel = (struct Wheel*) (clientProxy);

  if (timerId == wheel->rotTimerId) {
    processAnimation(wheel);
  } else {
    LOGERR("Error, received unknown timerId: [%d]", wheel->rotTimerId);
  }
}

void handleEventWheel (struct Wheel* self, struct InputEvent* e){
    if (e->type == KEYBOARD_PRESS){
        return;
    }
    struct DrawParams * params = &self->WheelImg.widget.drawParams;

    switch (e->key) {
        case KEY_Z:
            self->WheelImg.widget.drawParams.rotationAngle -= 10;
        break;

        case KEY_X:
            self->WheelImg.widget.drawParams.rotationAngle += 10;
        break;

        case KEY_C:
            self->WheelImg.widget.drawParams.rotationCenter = POINT_ZERO;
        break;

        case KEY_V:
            params->rotationCenter.x = params->frameRect.w / 2;
            params->rotationCenter.y = params->frameRect.h / 2;
            
        break;


        // case KEY_UP:
        //     self->WheelImg.widget.drawParams.pos.y -= 10;
        // break;

        // case KEY_DOWN:
        //     self->WheelImg.widget.drawParams.pos.y += 10;
        // break;

        // case KEY_RIGHT:
        //     self->WheelImg.widget.drawParams.pos.x += 10;
        // break;

        // case KEY_LEFT:
        //     self->WheelImg.widget.drawParams.pos.x -= 10;
        // break;

        // case KEY_NUMPAD_PLUS:
        //     setNextFrameImage(&self->WheelImg);
        // break;

        // case KEY_NUMPAD_MINUS:
        //     setPrevFrameImage(&self->WheelImg);
        // break;


        // case KEY_U:
        //     self->WheelImg.widget.drawParams.flipType = NONE_WIDGET_FLIP;
        // break;

        // case KEY_I:
        //     self->WheelImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        // break;

        // case KEY_O:
        //     self->WheelImg.widget.drawParams.flipType = VERTICAL_WIDGET_FLIP;
        // break;

        // case KEY_P:
        //     self->WheelImg.widget.drawParams.flipType = HORIZONTAL_AND_VERTICAL_WIDGET_FLIP;
        // break;


        default:

        break;
    }
}

int32_t initWheel (struct Wheel* self, int32_t rsrcId, int32_t rotTimerId){
    createImage(&self->WheelImg, rsrcId, &POINT_ZERO);
    self->isRotStarted = false;
    self->rotTimerId = rotTimerId;
    createTimer(&self->timerClient, (void*)self, onTimerTimeout);

    return SUCCESS;
}

void deinitWheel(struct Wheel* self){
 destroyImage(&self->WheelImg);
}

void drawWheel(struct Wheel* self){
    drawImage(&self->WheelImg);
}

void startRotationWheel(struct Wheel *wheel) {
    if (wheel->isRotStarted) {
        LOGERR("Error, rotation was already started");
        return;
    }

    wheel->isRotStarted = true;
    startTimer(&wheel->timerClient, ROT_INTERVAL, wheel->rotTimerId, PULSE_TIMER);
}

void stopRotationWheel(struct Wheel *wheel) {
    if (!wheel->isRotStarted) {
        LOGERR("Error, rotation was already stopped");
        return;
    }

    wheel->isRotStarted = false;
    stopTimer(wheel->rotTimerId);
}

