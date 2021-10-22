#ifndef SDL_UTILS_RENDERER_H_
#define SDL_UTILS_RENDERER_H_

#include <stdint.h>
#include "utils/drawing/DrawParams.h"


typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Window SDL_Window;

struct Renderer {
  SDL_Renderer *sdlRenderer;
};

int32_t initRenderer(struct Renderer *self, SDL_Window *window);
void deinitRenderer(struct Renderer *self);
void clearScreenRenderer(struct Renderer *self);
void finishFrameRenderer(struct Renderer *self);
void renderTexture(struct Renderer *self,const struct DrawParams* drawParams, SDL_Texture *texture);
 
#endif 
