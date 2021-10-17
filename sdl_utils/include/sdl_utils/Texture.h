#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_TEXTURE_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_TEXTURE_H_

#include <stdint.h>

typedef struct SDL_Surface SDL_Surface;
typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;

int32_t loadSurfaceFormFile(const char* filePath, SDL_Surface** outsurface);
int32_t loadTextureFormFile(const char* path, SDL_Texture** outTexture);
int32_t loadTextureFormSurface(SDL_Surface* surface, SDL_Texture** outTexture);

void freeSurface(SDL_Surface** surface);
void freeTexture(SDL_Texture** texture );
void setRenderer(SDL_Renderer* renderer);




#endif