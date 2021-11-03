#include "manager_utils/managers/DrawMgr.h"
#include <stdlib.h>
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "manager_utils/managers/config/DrawMgrCfg.h"
#include "manager_utils/managers/ResourceMngr.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "sdl_utils/Texture.h"
#include "manager_utils/managers/DrawMgrProxy.h"




struct DrawMgr* gDrawMgr = NULL;
struct DrawMgrProxy *gDrawMgrProxy = NULL;

static SDL_Texture* getTexture(const struct DrawParams* drawParams){
   if(IMAGE_WIDGET == drawParams->widgetType){
     return getImageTextureResourceMgr(drawParams->rsrcId);
    }

    if(TEXT_WIDGET == drawParams->widgetType){
        return getTextTextureResourceMgr(drawParams->rsrcId);
    }

    LOGERR("Received invalid widget %d type for rsrcid %d", drawParams->widgetType, drawParams->rsrcId);
    return NULL;

}

int32_t initDrawMgr(struct DrawMgr *self, const struct DrawMgrCfg* cfg){

    if (NULL == self){
        LOGERR("Eroro null provided for gDrawMgr");
    }

  if (SUCCESS != initMonitorWindow(&gDrawMgr->window, &cfg->windowCfg)) {
    LOGERR("initMonitorWindow() failed");
    return FAILURE;
  }

  if (SUCCESS != initRenderer(&gDrawMgr->renderer, self->window.sdlWindow)) {
    LOGERR("initRenderer() failed");
    return FAILURE;
  }
  self->maxFrames = cfg->maxFrames;
  gDrawMgrProxy->maxFrames = cfg->maxFrames;
  gDrawMgrProxy->addDrawCmdDrawMgr = addDrawCmdDrawMgr;
  gDrawMgrProxy->clearScreenDrawMgr = clearScreenDrawMgr;
  gDrawMgrProxy->finishFrameDrawMgr = finishFrameDrawMgr;
  gDrawMgrProxy->setWidgetBlendModeDrawMgr = setWidgetBlendModeDrawMgr;
  gDrawMgrProxy->setWidgetOpacityDrawMgr = setWidgetOpacityDrawMgr;

  return SUCCESS;
}

void deinitDrawMgr(struct DrawMgr *self){
  deinitRenderer(&self->renderer);
  deinitMonitorWindow(&self->window);
}

void clearScreenDrawMgr(){
  clearScreenRenderer(&gDrawMgr->renderer);
  
}

void finishFrameDrawMgr(){
  finishFrameRenderer(&gDrawMgr->renderer);
  
}

void addDrawCmdDrawMgr( const struct DrawParams *drawParams){
  SDL_Texture* texture = getTexture(drawParams);
  renderTexture(&gDrawMgr->renderer, drawParams, texture); 
}

void setWidgetBlendModeDrawMgr(const struct DrawParams *drawParams, BlendMode blendmode){
  SDL_Texture* texture = getTexture(drawParams);
  if (SUCCESS != setBlendModeTexture(texture, blendmode)){
      LOGERR("setBlendModeTexture() failed for rsrcId %d", drawParams->rsrcId);
             
  }
}

void setWidgetOpacityDrawMgr(const struct DrawParams *drawParams){
  if(drawParams->widgetType == IMAGE_WIDGET){
    return;
  }
  SDL_Texture* texture = getTexture(drawParams);
  if (SUCCESS != setAlphaTexture(texture, drawParams->opacity)){
    LOGERR("setWidgetOpacityDrawMgr() failed for rsrcId %d", drawParams->rsrcId);
  }
}
