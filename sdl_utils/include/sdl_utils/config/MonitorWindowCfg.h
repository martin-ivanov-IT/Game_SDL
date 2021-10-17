#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_MONITORWINDOWCFG_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_MONITORWINDOWCFG_H_

#include <stdint.h>
#include "utils/drawing/Point.h"

typedef enum {
    WINDOWS_SHOWN = 4,
    WINDOW_FULLSCREEN_DESKTOP = 4097,
}WindowFlags;

struct MonitorWindowCfg {
  int32_t windowWidth;
  int32_t windowHeight;
  struct Point windowPos;
  char *windowName;
  WindowFlags windowFlag;
};



#endif