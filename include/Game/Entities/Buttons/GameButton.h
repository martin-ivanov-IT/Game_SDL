#ifndef GAME_BUTTONS_GameButton_H_
#define GAME_BUTTONS_GameButton_H_

#include <stdint.h>
#include "manager_utils/input/Button.h"

struct InputEvent;

struct GameButton {
  struct Button button;

  void *gameProxy;
  int32_t buttonId;
};

int32_t initGameButton(struct GameButton *GameButton, void *gameProxy, int32_t buttonId, int32_t rsrcId, const struct Point *pos);

void handleEventGameButton(struct GameButton *GameButton,
                            const struct InputEvent *e);

void drawGameButton(struct GameButton *GameButton);

void deinitGameButton(struct GameButton *GameButton);

#endif /* GAME_BUTTONS_GameButton_H_ */
