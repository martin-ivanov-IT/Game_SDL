#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_MONITORWINDOW_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_MONITORWINDOW_H_

#include <stdint.h>
#include "utils/drawing/Rectangle.h"
#include "utils/drawing/Point.h"


typedef struct SDL_Window SDL_Window;
typedef struct SDL_Surface SDL_Surface;
typedef enum {
    WINDOW_SHOWN = 4,
    WINDOW_FULLSCREEN_DESKTOP = 4097
}WindowMode;

struct MonitorWindowCfg{
 struct Point pos;
 const char* name;
 int32_t width;
 int32_t hight;
 WindowMode mode;
};

 struct MonitorWindow {
     SDL_Surface* windowSurface; 
     SDL_Window *sdlWindow;
 }; 

int32_t initMonitorWindow(struct MonitorWindow* self,  struct MonitorWindowCfg* cfg);
void deinitMonitorWindow(struct MonitorWindow* self);
void updateMonitorWindowSurface(struct MonitorWindow* self);
#endif
