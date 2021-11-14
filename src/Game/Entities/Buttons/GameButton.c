#include "Game/Entities/Buttons/GameButton.h"
#include "Game/proxies/GameInterface.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

int32_t initGameButton(struct GameButton *gameButton, void *gameProxy, int32_t buttonId, int32_t rsrcId, const struct Point *pos) {
  if (NULL == gameProxy) {
    LOGERR("NULL GameProxy provided for for WheelButton Id: %d", buttonId);
    return FAILURE;
  }
  createButton(&gameButton->button, rsrcId, pos);

  gameButton->gameProxy = gameProxy;
  gameButton->buttonId = buttonId;

  return SUCCESS;
}

void handleEventGameButton(struct GameButton *gameButton, const struct InputEvent *e) {
  if (TOUCH_PRESS == e->type) {
    setFrameImage(&gameButton->button.img, CLICKED);
  } else if (TOUCH_RELEASE == e->type) {
    setFrameImage(&gameButton->button.img, UNCLICKED);
    onButtonPressedGameProxy(gameButton->gameProxy, gameButton->buttonId);
  }
}

void drawGameButton(struct GameButton *gameButton) {
  drawButton(&gameButton->button);
}

void deinitGameButton(struct GameButton *gameButton) {
  destroyImage(&gameButton->button.img);
}



