#include "sdl_utils/Texture.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include <SDL_surface.h>
#include <SDL_image.h>
#include <SDL_render.h>

static SDL_Renderer* gRenderer = NULL;

int32_t loadSurfaceFormFile(const char* filePath, SDL_Surface** outsurface){
    freeSurface(outsurface);

    *outsurface = IMG_Load(filePath);
    
    if (NULL == *outsurface){
         LOGERR("loadResources( failed) Reason: %s",IMG_GetError());
         return FAILURE;
     }
    return SUCCESS;

}
void freeSurface(SDL_Surface** surface){
    if(*surface){
        SDL_FreeSurface(*surface);
        *surface = NULL;
    }
}

void freeTexture(SDL_Texture** texture ){
    if(*texture){
        SDL_DestroyTexture(*texture);
        *texture = NULL;
    }
}

int32_t loadTextureFormSurface(SDL_Surface* surface, SDL_Texture** outTexture){
    if(*outTexture){
        LOGERR("Error, outTexture is already populated. Memory leak prvented");
        return FAILURE;
    }
    *outTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
    if(*outTexture == NULL){
        LOGERR("SDL_CreateTextureFromSurface failed Reason: %s",SDL_GetError());
        return FAILURE;
    }
    freeSurface(&surface);
    return SUCCESS;
}

int32_t loadTextureFormFile(const char* path, SDL_Texture** outTexture){
    SDL_Surface* surface = NULL;
    if(SUCCESS != loadSurfaceFormFile(path, &surface)){
        LOGERR("loadSurfaceFormFile failed ");
    }

    if(SUCCESS != loadTextureFormSurface(surface, outTexture)){
        LOGERR("loadSurfaceFormFile failed ");
    }
    return SUCCESS;
}

void setRenderer(SDL_Renderer* renderer){
    gRenderer = renderer;
}



