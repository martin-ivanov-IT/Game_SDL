#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_TEXTURE_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_TEXTURE_H_

#include <stdint.h>
#include "utils/drawing/DrawParams.h"

typedef struct SDL_Surface SDL_Surface;
typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct _TTF_Font TTF_Font;
struct Color;

int32_t loadSurfaceFormFile(const char* filePath, SDL_Surface** outsurface);
int32_t loadTextureFormFile(const char* path, SDL_Texture** outTexture);
int32_t loadTextureFormSurface(SDL_Surface** outsurface, SDL_Texture** outTexture);

int32_t loadSurfaceFromText(const char* text , TTF_Font* font, const struct Color* color, SDL_Surface **outsurface);
int32_t loadTextureFromText(const char* text , TTF_Font* font, const struct Color* color,
                            SDL_Texture **outTextue, int32_t* outTextWidth, int32_t* outTextHeight);


void freeSurface(SDL_Surface** surface);
void freeTexture(SDL_Texture** texture );
void setRenderer(SDL_Renderer* renderer);

int32_t setBlendModeTexture(SDL_Texture *texture, BlendMode blendMode);
int32_t setAlphaTexture(SDL_Texture *texture, int32_t alpha);




#endif