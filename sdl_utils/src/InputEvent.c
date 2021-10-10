 #include "sdl_utils/InputEvent.h"
#include "utils/input/EventDefines.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include <SDL_events.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static void setEventTypeInternal(struct InputEvent *e) {
    SDL_Event* event = e->sdlEvent;
    switch (e->sdlEvent->type) {

        case KEYBOARD_PRESS_TYPE:
            e->key = event->key.keysym.sym;
            e->mouseButton = MOUSE_UNKNOWN;
            e->type = KEYBOARD_PRESS;
            break;

        case KEYBOARD_RELEASE_TYPE:
            e->key = event->key.keysym.sym;
            e->mouseButton = MOUSE_UNKNOWN;
            e->type = KEYBOARD_RELEASE;
            break;

        case MOUSE_PRESS_TYPE:
            e->key = KEY_UNKNOWN;
            e->mouseButton = event->button.button;
            e->type = TOUCH_PRESS;
            break;

        case FINGER_PRESS_TYPE:
            e->key = KEY_UNKNOWN;
            e->mouseButton = MOUSE_UNKNOWN;
            e->type = TOUCH_PRESS;
            break;

        case MOUSE_RELEASE_TYPE:
            e->key = KEY_UNKNOWN;
            e->mouseButton = event->button.button;
            e->type = TOUCH_RELEASE;
            break;
        case FINGER_RELEASE_TYPE:
            e->key = KEY_UNKNOWN;
            e->mouseButton = MOUSE_UNKNOWN;
            e->type = TOUCH_RELEASE;
            break;

            //X is pressed on the window (or CTRL-C signal is sent)
        case QUIT_TYPE:
        case WINDOW_TYPE:
        case OS_TEXTEDITING_TYPE:
        case MOUSE_MOTION_TYPE:
        case AUDIO_DEVICE_ADDED_TYPE:
        case TEXT_INPUT_TYPE:
        case MOUSE_WHEEL_MOTION_TYPE:
            e->key = KEY_UNKNOWN;
            e->mouseButton = MOUSE_UNKNOWN;
            e->type = TOUCH_EVENT_UNKNOWN;
            break;

        default:
            LOGERR("Error, received unsupported eventTypeL %d",e->sdlEvent->type);
            break;
  }
}

int32_t initInputEvent(struct InputEvent* e){
    e->pos = POINT_UNDEFINED;
    e->key = KEY_UNKNOWN;
    e->mouseButton = MOUSE_UNKNOWN;
    e->type =UNKNOWN_TYPE;
    e->sdlEvent= (SDL_Event*)malloc(sizeof(SDL_Event));
    if (NULL == e->sdlEvent){
        LOGERR("bad alloc sdl_event ");
        return FAILURE;
    }
    memset(e->sdlEvent, 0, sizeof(SDL_Event));
    return SUCCESS;
}

void deinitInputEvent(struct InputEvent* e){
    if(e->sdlEvent){
        free(e->sdlEvent);
        e->sdlEvent = NULL;
    }
}

bool pollInputEvent(struct InputEvent* e){
     if(0 == SDL_PollEvent(e->sdlEvent)){
        return false;
    }

    SDL_GetMouseState(&e->pos.x, &e->pos.y);
    setEventTypeInternal(e);

    return true;
}

bool checkForExitRequest(const struct InputEvent* e){
    return ( e->sdlEvent->type == QUIT_TYPE) || (e->type==KEYBOARD_PRESS && KEY_ESCAPE == e->key);

}
