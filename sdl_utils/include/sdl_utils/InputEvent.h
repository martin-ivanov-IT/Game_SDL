#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_INPUTEVENT_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_INPUTEVENT_H_

#include <stdint.h>
#include "utils/drawing/Point.h"
#include "utils/input/EventDefines.h"




typedef union SDL_Event SDL_Event;

struct InputEvent {
  /* Holds event position on the screen */
  struct Point pos;

  /* See EventDefines.h for more information */
  int32_t key;
  uint8_t mouseButton;
  TouchEvent type;

  /** Holds the OS communication event system */
  SDL_Event *sdlEvent;
};

int32_t initInputEvent(struct InputEvent* e);

void deinitInputEvent(struct InputEvent* e);
bool pollInputEvent(struct InputEvent* e);
bool checkForExitRequest(const struct InputEvent* e);

#endif
// SDL_UTILS_INCLUDE_SDL_UTILS_SDLLOADER_H_