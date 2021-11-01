#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_RESPURCEMANAGERPROXY_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_RESPURCEMANAGERPROXY_H_
#include <stdint.h>
typedef struct SDL_Texture SDL_Texture;
struct Rectangle;
struct Color;
struct Vector;
struct ResourceMngrProxy {
    SDL_Texture* (*getImageTextureResourceMgr)(int32_t rsrcId);

    const struct Vector* (*getImageFramesResourceMgr)(int32_t rsrcId);

    void (*createTextResourceMgr)(const char *text, const struct Color *color,
                             int32_t rsrcId, int32_t *outTextId,
                             int32_t *outTextWidth, int32_t *outTextHeight);

    void (*reloadTextResourceMgr)(const char *text, const struct Color *color,
                             int32_t rsrcId, int32_t TextId,
                             int32_t *outTextWidth, int32_t *outTextHeight);
                             
    void (*unloadTextResourceMgr)(int32_t textId);

    SDL_Texture* (*getTextTextureResourceMgr)(int32_t rsrcId);
};
extern struct ResourceMngrProxy *gResourceMngrProxy;

#endif
