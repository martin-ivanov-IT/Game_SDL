#include "sdl_utils/containers/ImageContainer.h"
#include "sdl_utils/Texture.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "utils/drawing/Rectangle.h"
#include <stddef.h>
#include <stdlib.h>

static struct Vector EMPTY_FRAMES;

SDL_Texture* getImageTextureImageContainer(const struct ImageContainer *self, int32_t rsrcId){
    if (0 > rsrcId || rsrcId >= MAX_IMAGE_SIZE){
        return NULL;
    }
    return self->textures[rsrcId];
}

const struct Vector* getImageFramesImageContainer(const struct ImageContainer *self, int32_t rsrcId){
    if (0 > rsrcId || rsrcId >= MAX_IMAGE_SIZE){
         LOGERR(
        "Error, invalid rsrcId: %d provided. getImageFrameImageContainer() "
        "returning EMPTY_FRAMES Vector", rsrcId);
        return &EMPTY_FRAMES;
    }
    return &self->textureFrames[rsrcId];
}

int32_t initImageContainer(struct ImageContainer *self, const struct ImageContainerCfg* cfg){
    for(int32_t textureid = 0; textureid < MAX_IMAGE_SIZE; textureid++){
        if (!cfg->isConfigOccupied[textureid]){
            initVector(&self->textureFrames[textureid], 0);
            continue;
        }
        const struct ImageConfig* currImgCfg = & cfg->imageConfigs[textureid];
        if (SUCCESS != loadTextureFormFile(currImgCfg->location, & (self->textures[textureid]))) {
            LOGERR("loadTextureFormFile() failed for filePath %s", currImgCfg->location);
            return FAILURE;
        }
        shallowCopyVector(&cfg->imageConfigs[textureid].frames, &self->textureFrames[textureid]); 
    }

    initVector(&EMPTY_FRAMES, 1);
#pragma GCC diagnostic push  // require GCC 4.6
#pragma GCC diagnostic ignored "-Wcast-qual"
  pushElementVector(&EMPTY_FRAMES, (void*)&RECTANGLE_ZERO);
#pragma GCC diagnostic pop   // require GCC 4.6
    return SUCCESS;
}
void deinitImageContainer(struct ImageContainer *self){
    for (int32_t i = 0; i < MAX_IMAGE_SIZE; ++i) {
        if(self->textures[i]){
            freeTexture(&self->textures[i]);
        }
        const size_t size = getSizeVector(&self->textureFrames[i]);
        for (size_t el = 0; el < size; el++)
        {   
            free(getElementVector(&self->textureFrames[i], el));
        }
        freeVector(&self->textureFrames[i]);
    }
    freeVector(&EMPTY_FRAMES);
}