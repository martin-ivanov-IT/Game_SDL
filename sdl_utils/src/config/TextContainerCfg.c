#include "sdl_utils/config/TextContainerCfg.h"
#include <string.h>
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

void insertFontConfig(struct TextContainerCfg *self, int32_t idx, const struct FontConfig *fontCfg){
    if(0 > idx || idx >= MAX_TEXT_SIZE){
        LOGERR("Error, foIndex: %d is out of range: fontPath %s", idx, fontCfg->location);
    }

    if (self->isConfigOccupied[idx]){
        LOGERR("Error, imgIndex: %d is already occupied: imgPath %s", idx, fontCfg->location);

    }
    self->isConfigOccupied[idx] = true;
    self->fontConfigs[idx].fontSize = fontCfg->fontSize;
    strcpy( self->fontConfigs[idx].location, fontCfg->location);
}
