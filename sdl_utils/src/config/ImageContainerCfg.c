#include "sdl_utils/config/ImageContainerCfg.h"
#include <string.h>
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

void insertImageConfig(struct ImageContainerCfg *self, int32_t idx, const struct ImageConfig *imgCfg){
    if(0 > idx || idx >= MAX_IMAGE_SIZE){
        LOGERR("Error, imgIndex: %d is out of range: imgPath %s", idx, imgCfg[idx].location);
    }

    if (self->isConfigOccupied[idx]){
        LOGERR("Error, imgIndex: %d is already occupied: imgPath %s", idx, imgCfg[idx].location);

    }
    self->isConfigOccupied[idx] = true;
    deepCopyVector(&imgCfg->frames, &self->imageConfigs[idx].frames);
    strcpy( self->imageConfigs[idx].location, imgCfg->location);
}
