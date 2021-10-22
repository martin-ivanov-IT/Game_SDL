#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_CONTAINERS_IMAGECONTAINER_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_CONTAINERS_IMAGECONTAINER_H_

#include "sdl_utils/config/ImageContainerCfg.h"
#include "utils/drawing/Rectangle.h"

typedef struct SDL_Texture SDL_Texture;

struct ImageContainer {
  //the textures we'll be drawing
  SDL_Texture *textures[MAX_IMAGE_SIZE];

  struct Rectangle textureFrames[MAX_IMAGE_SIZE]; //0, 0, imgWidth, imgHeight
};

int32_t initImageContainer(struct ImageContainer *self, const struct ImageContainerCfg* cfg);
void deinitImageContainer(struct ImageContainer *self);
SDL_Texture* getImageTextureImageContainer(const struct ImageContainer *self, int32_t rsrcId);
const struct Rectangle* getImageFrameImageContainer(const struct ImageContainer *self, int32_t rsrcId);

#endif