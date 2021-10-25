#include "manager_utils/managers/ResourceMngr.h"
#include "manager_utils/managers/ResourceMngrProxy.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "manager_utils/managers/config/ResourceMngrCfg.h"
struct ResourceMgr *gResourceMgr = NULL;
struct ResourceMngrProxy *gResourceMngrProxy = NULL;

int32_t initResourceMgr(struct ResourceMgr *self, const struct ResourceMgrCfg* cfg){
    if (NULL == self){
        LOGERR("Eroro null provided for gResourceMgr");
    }
    if (SUCCESS != initImageContainer(&self->imgContainer,&cfg->imgContainerCfg)) {
    LOGERR("initImageContainer() failed");
    return FAILURE;
    }

    if (SUCCESS != initTextContainer(&self->textContainer ,&cfg->textContainerCfg)) {
        LOGERR("initTextContainer() failed");
        return FAILURE;
    }
    gResourceMngrProxy->getImageTextureResourceMgr = getImageTextureResourceMgr;
    gResourceMngrProxy->getImageFrameResourceMgr = getImageFrameResourceMgr;
    gResourceMngrProxy->createTextResourceMgr = createTextResourceMgr;
    gResourceMngrProxy->reloadTextResourceMgr = reloadTextResourceMgr;
    gResourceMngrProxy->unloadTextResourceMgr = unloadTextResourceMgr;
    gResourceMngrProxy->getTextTextureResourceMgr = getTextTextureResourceMgr;

    return SUCCESS;
}

void deinitResourceMgr(struct ResourceMgr *self){
    deinitTextContainer(&self->textContainer);
    deinitImageContainer(&self->imgContainer);
}


SDL_Texture* getImageTextureResourceMgr( int32_t rsrcId){
    return getImageTextureImageContainer(&gResourceMgr->imgContainer, rsrcId);
}

const struct Rectangle* getImageFrameResourceMgr(int32_t rsrcId){
    return getImageFrameImageContainer(&gResourceMgr->imgContainer, rsrcId);
}

void createTextResourceMgr(const char *text, const struct Color *color,
                             int32_t rsrcId, int32_t *outTextId,
                             int32_t *outTextWidth, int32_t *outTextHeight){
    createTextTextContainer(&gResourceMgr->textContainer, text, color, rsrcId, outTextId, outTextWidth, outTextHeight);
}
                             
void reloadTextResourceMgr(const char *text, const struct Color *color,
                             int32_t rsrcId, int32_t TextId,
                             int32_t *outTextWidth, int32_t *outTextHeight){
    reloadTextTextContainer(&gResourceMgr->textContainer, text, color, rsrcId,TextId, outTextWidth, outTextHeight);
}                             

void unloadTextResourceMgr(int32_t textId){
    unloadTextTextContainer(&gResourceMgr->textContainer, textId);
}

SDL_Texture* getTextTextureResourceMgr(int32_t rsrcId){
    return getTextTextureTextContainer(&gResourceMgr->textContainer, rsrcId);
}

