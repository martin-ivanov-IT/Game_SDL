#include "sdl_utils/Texture.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include <SDL_surface.h>
#include <SDL_image.h>

int32_t loadSurfaceFormFile(const char* filePath, SDL_Surface** outsurface){
    *outsurface = IMG_Load(filePath);
    
    if (NULL == *outsurface){
         LOGERR("loadResources( failed) Reason: %s",SDL_GetError());
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
