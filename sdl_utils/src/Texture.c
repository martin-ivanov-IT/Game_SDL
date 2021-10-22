#include "sdl_utils/Texture.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include <SDL_surface.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include "utils/drawing/Color.h"


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

int32_t loadTextureFormSurface(SDL_Surface** outsurface, SDL_Texture** outTexture){
    if(*outTexture){
        LOGERR("Error, outTexture is already populated. Memory leak prvented");
        return FAILURE;
    }
    *outTexture = SDL_CreateTextureFromSurface(gRenderer, *outsurface);
    if(*outTexture == NULL){
        LOGERR("SDL_CreateTextureFromSurface failed Reason: %s",SDL_GetError());
        return FAILURE;
    }
    freeSurface(outsurface);
    return SUCCESS;
}

int32_t loadTextureFormFile(const char* path, SDL_Texture** outTexture){
    SDL_Surface* surface = NULL;
    if(SUCCESS != loadSurfaceFormFile(path, &surface)){
        LOGERR("loadSurfaceFormFile failed ");
    }

    if(SUCCESS != loadTextureFormSurface(&surface, outTexture)){
        LOGERR("loadSurfaceFormFile failed ");
    }
    return SUCCESS;
}

void setRenderer(SDL_Renderer* renderer){
    gRenderer = renderer;
}

int32_t setBlendModeTexture(SDL_Texture *texture, BlendMode blendMode){
    if(SUCCESS != SDL_SetTextureBlendMode(texture, (SDL_BlendMode)blendMode)){
        LOGERR("Error SDL_SetTextureBlendMode failed Resaon %s", SDL_GetError());
        return FAILURE;
    }
    return SUCCESS;
}

int32_t setAlphaTexture(SDL_Texture *texture, int32_t alpha){
    if (0>alpha || alpha > FULL_OPACITY){
        LOGERR("Error invalid alpha value of %d whlie accepted range is [%d - %d]", alpha, ZERO_OPACITY, FULL_OPACITY);
        return FAILURE;

    }
    if(SUCCESS != SDL_SetTextureAlphaMod(texture, (uint8_t)alpha)){
        LOGERR("Error SDL_SetTextureAlphaMod failed Resaon %s", SDL_GetError());
        return FAILURE;
    }
    return SUCCESS;
}

int32_t loadSurfaceFromText(const char* text , TTF_Font* font, const struct Color* color, SDL_Surface **outsurface){
    const SDL_Color* sdlColor = (const SDL_Color*)&color->rgba;
    *outsurface = TTF_RenderText_Blended(font, text, *sdlColor);
    if(outsurface == NULL){
        LOGERR("TTF_RenderText_Blended failed %s", SDL_GetError());
    }
 return SUCCESS;
}
int32_t loadTextureFromText(const char* text , TTF_Font* font, const struct Color* color, 
                        SDL_Texture **outTextue, int32_t* outTextWidth, int32_t* outTextHeight){
    SDL_Surface* textSurface = NULL;

    if(SUCCESS != loadSurfaceFromText(text, font, color, &textSurface)){
        LOGERR("loadSurfaceFromText failed for text %s", text);
        return FAILURE;
    }
    *outTextWidth = textSurface->w;
    *outTextHeight = textSurface->h;

    if(SUCCESS != loadTextureFormSurface(&textSurface, outTextue)){
        LOGERR("loadTextureFormSurface failed for text %s", text);
        return FAILURE;
    }
    return SUCCESS;
}




