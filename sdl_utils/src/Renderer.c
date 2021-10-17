#include "sdl_utils/Renderer.h"
#include "sdl_utils/Texture.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include <SDL_render.h>

int32_t initRenderer(struct Renderer *self, SDL_Window *window){
    const int32_t unspecifiesDriverId = -1;
    self->sdlRenderer = SDL_CreateRenderer(window, unspecifiesDriverId, SDL_RENDERER_ACCELERATED);
    if (NULL ==  self->sdlRenderer)
    {
        LOGERR("SDL_CreateRenderer could not be created! SDL Error: %s", SDL_GetError());
        return FAILURE;
    }

    if(SUCCESS != SDL_SetRenderDrawColor(self->sdlRenderer, 0,0,255,SDL_ALPHA_OPAQUE)){
        LOGERR("SDL_SetRenderDrawColor failed! SDL Error: %s", SDL_GetError());
        return FAILURE;
    }

    setRenderer(self->sdlRenderer);

    return SUCCESS;
}
void deinitRenderer(struct Renderer *self){
    if(self->sdlRenderer){
        SDL_DestroyRenderer(self->sdlRenderer);
        self->sdlRenderer = NULL;
    }
}
void clearScreenRenderer(struct Renderer *self){
    if(SUCCESS != SDL_RenderClear(self->sdlRenderer)){
        LOGERR("SDL_SetRenderDrawColor failed! SDL Error: %s", SDL_GetError());
    }

}
void finishFrameRenderer(struct Renderer *self){
    SDL_RenderPresent(self->sdlRenderer);
}

void renderTexture(struct Renderer *self, SDL_Texture *texture){
    const int32_t errorCode =SDL_RenderCopy(self->sdlRenderer, texture, NULL, NULL);
    if(SUCCESS != errorCode){
        LOGERR("SDL_RenderCopy failed! SDL Error: %s", SDL_GetError());
    }
}