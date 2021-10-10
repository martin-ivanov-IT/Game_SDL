#ifndef INCLUDE_ENGINE_EINGINE_H_
#define INCLUDE_ENGINE_EINGINE_H_

#include <stdint.h>
#include "sdl_utils/InputEvent.h"
#include "sdl_utils/MonitorWindow.h"


struct Engine {
    struct MonitorWindow window;
    SDL_Surface* image;
    struct InputEvent event;
};

int32_t initEngine(struct Engine* self);
int32_t deinitEngine(struct Engine* self);
void drawEngine(struct Engine* self);


#endif