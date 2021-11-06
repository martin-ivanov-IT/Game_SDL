#ifndef GAME_BUTTONS_IslandBoyButtonH_
#define GAME_BUTTONS_IslandBoyButtonH_

#include <stdint.h>
#include "manager_utils/input/Button.h"

struct InputEvent;

struct IslandBoyButton {
  struct Button button;

  void *gameProxy;
  int32_t buttonId;
};

int32_t initIslandBoyButton(struct IslandBoyButton *self, void *gameProxy, int32_t buttonId, int32_t rsrcId, const struct Point *pos);

void handleEventIslandBoyButton(struct IslandBoyButton *self,
                            const struct InputEvent *e);

void drawIslandBoyButton(struct IslandBoyButton *self);

void deinitIslandBoyButton(struct IslandBoyButton *self);

#endif 
