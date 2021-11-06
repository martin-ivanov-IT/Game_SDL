#include "Game/Entities/Buttons/IslandBoyButton.h"
#include "Game/proxies/GameInterface.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

int32_t initIslandBoyButton(struct IslandBoyButton *IslandBoyButton, void *gameProxy, int32_t buttonId, int32_t rsrcId, const struct Point *pos) {
  if (NULL == gameProxy) {
    LOGERR("NULL GameProxy provided for for IslandBoyButton Id: %d", buttonId);
    return FAILURE;
  }
  createButton(&IslandBoyButton->button, rsrcId, pos);

  IslandBoyButton->gameProxy = gameProxy;
  IslandBoyButton->buttonId = buttonId;

  return SUCCESS;
}

void handleEventIslandBoyButton(struct IslandBoyButton *IslandBoyButton, const struct InputEvent *e) {
  if (TOUCH_PRESS == e->type) {
    setFrameImage(&IslandBoyButton->button.img, CLICKED);
  } else if (TOUCH_RELEASE == e->type) {
    setFrameImage(&IslandBoyButton->button.img, UNCLICKED);
    onButtonPressedGameProxy(IslandBoyButton->gameProxy, IslandBoyButton->buttonId);
  }
}

void drawIslandBoyButton(struct IslandBoyButton *IslandBoyButton) {
  drawButton(&IslandBoyButton->button);
}

void deinitIslandBoyButton(struct IslandBoyButton *IslandBoyButton) {
  destroyImage(&IslandBoyButton->button.img);
}



