//Corresponding header
#include "sdl_utils/MonitorWindow.h"

//C system headers

//Other libraries headers
#include <SDL_video.h>

//Own components headers
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

int32_t initMonitorWindow(struct MonitorWindow *window,
                          const struct MonitorWindowCfg *cfg) {
  struct Point initWindowPos = cfg->windowPos;

  if (arePointsEqual(&POINT_UNDEFINED, &cfg->windowPos)) {
    initWindowPos.x = SDL_WINDOWPOS_UNDEFINED;
    initWindowPos.y = SDL_WINDOWPOS_UNDEFINED;
  }

  window->windowRect.w = cfg->windowWidth;
  window->windowRect.h = cfg->windowHeight;

  //Create window
  window->sdlWindow = SDL_CreateWindow(cfg->windowName, initWindowPos.x,
      initWindowPos.y, window->windowRect.w, window->windowRect.h,
      cfg->windowFlag);

  if (NULL == window->sdlWindow) {
    LOGERR("Window could not be created! SDL Error: %s", SDL_GetError());
    return FAILURE;
  }

  //obtain real window coordinates after creation
  SDL_GetWindowPosition(window->sdlWindow, &window->windowRect.x,
      &window->windowRect.y);

  return SUCCESS;
}

void deinitMonitorWindow(struct MonitorWindow *window) {
  if (window) { //sanity check
    SDL_DestroyWindow(window->sdlWindow);
    window->sdlWindow = NULL;
  }
}
