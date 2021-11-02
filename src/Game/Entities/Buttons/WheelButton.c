#include "Game/Entities/Buttons/WheelButton.h"
#include "Game/proxies/GameInterface.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

int32_t initWheelButton(struct WheelButton *wheelButton, void *gameProxy, int32_t buttonId, int32_t rsrcId, const struct Point *pos) {
  if (NULL == gameProxy) {
    LOGERR("NULL GameProxy provided for for WheelButton Id: %d", buttonId);
    return FAILURE;
  }
  createButton(&wheelButton->button, rsrcId, pos);

  wheelButton->gameProxy = gameProxy;
  wheelButton->buttonId = buttonId;

  return SUCCESS;
}

void handleEventWheelButton(struct WheelButton *wheelButton, const struct InputEvent *e) {
  if (TOUCH_PRESS == e->type) {
    setFrameImage(&wheelButton->button.img, CLICKED);
  } else if (TOUCH_RELEASE == e->type) {
    setFrameImage(&wheelButton->button.img, UNCLICKED);
    onButtonPressedGameProxy(wheelButton->gameProxy, wheelButton->buttonId);
  }
}

void drawWheelButton(struct WheelButton *wheelButton) {
  drawButton(&wheelButton->button);
}

void deinitWheelButton(struct WheelButton *wheelButton) {
  destroyImage(&wheelButton->button.img);
}



