#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_IMAGECONTAINERCFG_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_IMAGECONTAINERCFG_H_

#include <stdint.h>
#include <stdbool.h>
#include "utils/containers/Vector.h"


#define MAX_IMAGE_NAME_LEN 50
#define MAX_IMAGE_SIZE 200

struct ImageConfig {
  struct Vector frames;
  char location[MAX_IMAGE_NAME_LEN];
};


struct ImageContainerCfg {
  struct ImageConfig imageConfigs[MAX_IMAGE_SIZE];
  bool isConfigOccupied[MAX_IMAGE_SIZE];
};

void insertImageConfig(struct ImageContainerCfg *self, int32_t idx, const struct ImageConfig *imgCfg);

#endif