#include "Game/Entities/Hero.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"


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

int32_t initHero (struct Hero* self, int32_t rsrcId){
    createImage(&self->heroImg, rsrcId, &POINT_ZERO);
    return SUCCESS;
}

void deinitHero(struct Hero* self){
 destroyImage(&self->heroImg);
}

void drawHero(struct Hero* self){
    drawImage(&self->heroImg);
}