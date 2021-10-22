#include "sdl_utils/Renderer.h"
#include "sdl_utils/Texture.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include <SDL_render.h>
#include <SDL_hints.h>

static void drawImage(struct Renderer *self,const struct DrawParams* drawParams, SDL_Texture *texture){
    const SDL_Rect destRect = {.x = drawParams->pos.x, .y = drawParams->pos.y, .w = drawParams->width, .h = drawParams->height};
    int32_t errorCode = 0;
    if(drawParams->opacity == FULL_OPACITY){
        errorCode = SDL_RenderCopy(self->sdlRenderer, texture, NULL, &destRect);
    }

    else{
        if(SUCCESS != setAlphaTexture (texture, drawParams->opacity)){
            LOGERR("setAlphaTexture failed!for rsrcID %d", drawParams->rsrcId);
        }

        errorCode = SDL_RenderCopy(self->sdlRenderer, texture, NULL, &destRect);

        if(SUCCESS != setAlphaTexture (texture, FULL_OPACITY)){
            LOGERR("setAlphaTexture failed!for rsrcID %d", drawParams->rsrcId);
        }
    }
    

    if(SUCCESS != errorCode){
        LOGERR("setAlphaTexture failed!for rsrcID %d, %s", drawParams->rsrcId, SDL_GetError());
    }
}

static void drawText(struct Renderer *self,const struct DrawParams* drawParams, SDL_Texture *texture){
    const SDL_Rect destRect = {.x = drawParams->pos.x, .y = drawParams->pos.y, .w = drawParams->width, .h = drawParams->height};
    SDL_RenderCopy(self->sdlRenderer, texture, NULL, &destRect);
}

int32_t initRenderer(struct Renderer *self, SDL_Window *window){

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    LOGERR("Linear texture filtering not enabled!  SDL Error: %s", SDL_GetError());
    return FAILURE;
    }

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

void renderTexture(struct Renderer *self,const struct DrawParams* drawParams, SDL_Texture *texture){
    if(IMAGE_WIDGET == drawParams->widgetType){
        drawImage(self,drawParams, texture);
    }

    else if(TEXT_WIDGET == drawParams->widgetType){
        drawText(self,drawParams, texture);
    }

    else{
        LOGERR("Received invalid widget %d type for rsrcid %d", drawParams->widgetType, drawParams->rsrcId);
    }
    

}