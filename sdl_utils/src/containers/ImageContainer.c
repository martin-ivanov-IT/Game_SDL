#include "sdl_utils/containers/ImageContainer.h"
#include "sdl_utils/Texture.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include <stddef.h>
SDL_Texture* getImageTextureImageContainer(const struct ImageContainer *self, int32_t rsrcId){
    if (0 > rsrcId || rsrcId >= MAX_IMAGE_SIZE){
        return NULL;
    }
    return self->textures[rsrcId];
}

const struct Rectangle* getImageFrameImageContainer(const struct ImageContainer *self, int32_t rsrcId){
    if (0 > rsrcId || rsrcId >= MAX_IMAGE_SIZE){
        return NULL;
    }
    return &self->textureFrames[rsrcId];
}

int32_t initImageContainer(struct ImageContainer *self, const struct ImageContainerCfg* cfg){
    for(int32_t i = 0; i < MAX_IMAGE_SIZE; i++){
        if (!cfg->isConfigOccupied[i]){
            continue;
        }
        const struct ImageConfig* currImgCfg = & cfg->imageConfigs[i];
        if (SUCCESS != loadTextureFormFile(currImgCfg->location, & (self->textures[i]))) {
            LOGERR("loadTextureFormFile() failed for filePath %s", currImgCfg->location);
            return FAILURE;
        }
        self->textureFrames[i].x = 0;
        self->textureFrames[i].y = 0;
        self->textureFrames[i].w = currImgCfg->width;
        self->textureFrames[i].h = currImgCfg->height;

    }
    return SUCCESS;
}
void deinitImageContainer(struct ImageContainer *self){
    for (int32_t i = 0; i < MAX_IMAGE_SIZE; ++i) {
        if(self->textures[i]){
            freeTexture(&self->textures[i]);
        }
    }
}