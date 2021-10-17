#ifndef SDL_UTILS_MONITORWINDOW_H_
#define SDL_UTILS_MONITORWINDOW_H_

//C system headers
#include <stdint.h>

//Other libraries headers

//Own components headers
#include "utils/drawing/Point.h"
#include "utils/drawing/Rectangle.h"
#include "sdl_utils/config/MonitorWindowCfg.h"

//Forward declarations
typedef struct SDL_Window SDL_Window;


struct MonitorWindow {
  SDL_Window *sdlWindow;
  struct Rectangle windowRect;
};

int32_t initMonitorWindow(struct MonitorWindow *window,
                          const struct MonitorWindowCfg *cfg);

void deinitMonitorWindow(struct MonitorWindow *window);

#endif /* SDL_UTILS_MONITORWINDOW_H_ */
