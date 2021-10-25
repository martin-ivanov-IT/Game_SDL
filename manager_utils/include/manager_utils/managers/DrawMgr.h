#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_DRAWMGR_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_DRAWMGR_H_
#include <stdint.h>
#include "sdl_utils/MonitorWindow.h"
#include "sdl_utils/Renderer.h"
struct DrawMgrCfg;


struct DrawMgr {
  struct Renderer renderer;

  struct MonitorWindow window;

  //Hold maximum frame rate cap
  int64_t maxFrames;
};

extern struct DrawMgr *gDrawMgr;

int32_t initDrawMgr(struct DrawMgr *self, const struct DrawMgrCfg* cfg);

void deinitDrawMgr(struct DrawMgr *self);

void clearScreenDrawMgr();

void finishFrameDrawMgr();

void addDrawCmdDrawMgr(const struct DrawParams *drawParams);

void setWidgetBlendModeDrawMgr(const struct DrawParams *drawParams, BlendMode blendmode);

void setWidgetOpacityDrawMgr(const struct DrawParams *drawParams);



#endif