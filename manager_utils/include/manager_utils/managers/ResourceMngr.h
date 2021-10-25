#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_RESOURCEMGR_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_RESOURCEMGR_H_
#include <stdint.h>
#include "sdl_utils/containers/ImageContainer.h"
#include "sdl_utils/containers/TextContainer.h"


struct ResourceMgrCfg;

struct ResourceMgr {
    struct ImageContainer imgContainer;
    struct TextContainer textContainer;
};

extern struct ResourceMgr *gResourceMgr;

int32_t initResourceMgr(struct ResourceMgr *self, const struct ResourceMgrCfg* cfg);

void deinitResourceMgr(struct ResourceMgr *self);

SDL_Texture* getImageTextureResourceMgr(int32_t rsrcId);

const struct Rectangle* getImageFrameResourceMgr( int32_t rsrcId);

void createTextResourceMgr(const char *text, const struct Color *color,
                        int32_t rsrcId, int32_t *outTextId,
                        int32_t *outTextWidth, int32_t *outTextHeight);
                             
void reloadTextResourceMgr(const char *text, const struct Color *color,
                        int32_t rsrcId, int32_t TextId,
                        int32_t *outTextWidth, int32_t *outTextHeight);                             

void unloadTextResourceMgr(int32_t textId);

SDL_Texture* getTextTextureResourceMgr( int32_t rsrcId);


#endif