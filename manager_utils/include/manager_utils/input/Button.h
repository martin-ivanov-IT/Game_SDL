#ifndef MANAGER_UTILS_INPUT_BUTTON_H_
#define MANAGER_UTILS_INPUT_BUTTON_H_
#include <stdbool.h>
#include "manager_utils/drawing/Image.h"

struct InputEvent;

enum ButtonStates {
  UNCLICKED, CLICKED, DISABLED
};

struct Button {
  struct Image img;
  bool isInputUnlocked;
};

void createButton(struct Button *button, int32_t rsrcId,
                  const struct Point *pos);

void resetButton(struct Button *button);

void drawButton(struct Button *button);

void lockInputButton(struct Button *button);

void unlockInputButton(struct Button *button);

bool containsEventButton(struct Button *button, const struct InputEvent *e);

#endif