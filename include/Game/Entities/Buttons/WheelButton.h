#ifndef GAME_BUTTONS_WHEELBUTTON_H_
#define GAME_BUTTONS_WHEELBUTTON_H_

#include <stdint.h>
#include "manager_utils/input/Button.h"

struct InputEvent;

struct WheelButton {
  struct Button button;

  void *gameProxy;
  int32_t buttonId;
};

int32_t initWheelButton(struct WheelButton *wheelButton, void *gameProxy, int32_t buttonId, int32_t rsrcId, const struct Point *pos);

void handleEventWheelButton(struct WheelButton *wheelButton,
                            const struct InputEvent *e);

void drawWheelButton(struct WheelButton *wheelButton);

void deinitWheelButton(struct WheelButton *wheelButton);

#endif /* GAME_BUTTONS_WHEELBUTTON_H_ */
