#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_TEXTURE_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_TEXTURE_H_

#include <stdint.h>

typedef struct SDL_Surface SDL_Surface;

int32_t loadSurfaceFormFile(const char* filePath, SDL_Surface** outsurface);
void freeSurface(SDL_Surface** surface);



#endif