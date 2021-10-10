#include "sdl_utils/MonitorWindow.h"
#include "utils/ErrorCodes.h"
#include <SDL_video.h>
#include  "utils/Log.h"
int32_t initMonitorWindow(struct MonitorWindow* self, struct MonitorWindowCfg* cfg){

    int32_t windowX = 0;
    int32_t windowY = 0;
    if(arePointsEqual(&cfg->pos , &POINT_UNDEFINED)){
        windowX = SDL_WINDOWPOS_UNDEFINED;
        windowY = SDL_WINDOWPOS_UNDEFINED;
    }
    else{
        windowX = cfg->pos.x;
        windowY = cfg->pos.y;
    }

    self->sdlWindow = SDL_CreateWindow(cfg->name, windowX, windowY, cfg->width, cfg->hight, cfg->mode);

    if (NULL == self->sdlWindow){
        LOGERR("SDL_CreateWindow( failed) Reason: %s",SDL_GetError());
        return FAILURE;
    }

    self->windowSurface = SDL_GetWindowSurface(self->sdlWindow);
    if (NULL == self->windowSurface){
        LOGERR("SDL_GetWindowSurface( failed) Reason: %s",SDL_GetError());
        return FAILURE;
    }

    return SUCCESS;
}
void deinitMonitorWindow(struct MonitorWindow* self){
    if (self->sdlWindow)
    {
        SDL_DestroyWindow(self->sdlWindow);
        self->sdlWindow = NULL;
    }
}

void updateMonitorWindowSurface(struct MonitorWindow* self){
    if(SUCCESS != SDL_UpdateWindowSurface(self->sdlWindow)){
        LOGERR("SDL_UpdateWindowSurface( failed) Reason: %s",SDL_GetError());
    }
}
