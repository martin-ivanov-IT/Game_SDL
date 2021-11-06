#include "Game/Entities/Hero.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "common/CommonDefines.h"



void handleEventHero (struct Hero* self, struct InputEvent* e){
    if (e->type == KEYBOARD_PRESS){
        return;
    }
    switch (e->key) {
        case KEY_M:

        break;

        case KEY_N:

        break;

        case KEY_J:

        break;

        case KEY_UP:
            self->heroImg.widget.drawParams.pos.y -= 10;
        break;

        case KEY_DOWN:
            self->heroImg.widget.drawParams.pos.y += 10;
        break;

        case KEY_RIGHT:
            self->heroImg.widget.drawParams.pos.x += 10;
        break;

        case KEY_LEFT:
            self->heroImg.widget.drawParams.pos.x -= 10;
        break;

        case KEY_NUMPAD_PLUS:
            setNextFrameImage(&self->heroImg);
        break;

        case KEY_NUMPAD_MINUS:
            setPrevFrameImage(&self->heroImg);
        break;


          case KEY_U:
            self->heroImg.widget.drawParams.flipType = NONE_WIDGET_FLIP;
        break;

        case KEY_I:
            self->heroImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        break;

        case KEY_O:
            self->heroImg.widget.drawParams.flipType = VERTICAL_WIDGET_FLIP;
        break;

        case KEY_P:
            self->heroImg.widget.drawParams.flipType = HORIZONTAL_AND_VERTICAL_WIDGET_FLIP;
        break;


        default:

        break;
    }
}
static void processSpriteAnim(struct Hero* self){
    setNextFrameImage(&self->heroImg);
}

static void processMoveAnim(struct Hero* self){
    if(self->playerType == PLAYER){
        self->currAnimStep++;
        moveRight(&self->heroImg.widget, self->heroCfg.deltaMovePx);
    }

    else if(self->playerType == ENEMY){
        self->currAnimStep++;
        self->heroImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        moveLeft(&self->heroImg.widget, self->heroCfg.deltaMovePx);
    }
    
    
    // if(self->isMovingHor){
    //     if(self->isMovingRight){
    //         moveRight(&self->heroImg.widget, self->heroCfg.deltaMovePx);
    //     }
    //     else{
    //         moveLeft(&self->heroImg.widget, self->heroCfg.deltaMovePx);
    //     }

    //     if (self->currAnimStep == self->heroCfg.horSteps){
    //         self->currAnimStep = 0;
    //         self->isMovingHor = false;
    //         self->isMovingUp = false;
    //     }
    // }
    // else {
    //     if(self->isMovingUp){
    //         moveUp(&self->heroImg.widget, self->heroCfg.deltaMovePx);
    //     }
    //     else{
    //         moveDown(&self->heroImg.widget, self->heroCfg.deltaMovePx);
    //     }

    //     if (self->currAnimStep == self->heroCfg.verSteps){
    //         self->currAnimStep = 0;
    //         self->isMovingHor = true;
    //         self->isMovingUp = true;
    //         self->isMovingRight = false;
    //         self->heroImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
    //     }

    // }

}

static void onTimerTimeout(void* proxy, int32_t timerId){
    struct Hero* self = (struct Hero*) proxy;
    if (timerId == self->heroCfg.heroChangeAnimTimerId)
    {
        processSpriteAnim(self);
    }

    else if (timerId == self->heroCfg.heroMoveTimerId)
    {
        processMoveAnim(self);
    }

    else{
        LOGERR("Recieved unsuported timer id: %d", timerId);
    }
    
}
int32_t initHero (struct Hero* self, const struct HeroCfg* cfg){
    struct Point widgetPos = { .x = 0, .y = 150 };
    if(self->playerType == ENEMY){
        widgetPos.x = 1200;
        widgetPos.y = 150;
    }

    createImage(&self->heroImg, cfg->rsrcId, &widgetPos);
    self->heroCfg = *cfg;
    self->currAnimStep = 0;
    self->isMovingHor = true;
    self->isMovingRight = true;
    self->isMovingUp = true;
    
    createTimer(&self->TimerClient, self, onTimerTimeout);
    return SUCCESS;
}

void deinitHero(struct Hero* self){
 destroyImage(&self->heroImg);
}

void drawHero(struct Hero* self){
    drawImage(&self->heroImg);
}

void startAnim(struct Hero* self){
    startTimer(&self->TimerClient, 100, self->heroCfg.heroChangeAnimTimerId, PULSE_TIMER);
    startTimer(&self->TimerClient, 100, self->heroCfg.heroMoveTimerId, PULSE_TIMER);
}
