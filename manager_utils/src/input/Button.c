#include "manager_utils/input/Button.h"
#include "sdl_utils/InputEvent.h"
#include "utils/drawing/Rectangle.h"


void createButton(struct Button *button, int32_t rsrcId, const struct Point *pos) {
    resetButton(button);
    createImage(&button->img, rsrcId, pos);
    button->isInputUnlocked = true;
}

void resetButton(struct Button *button) {
    resetImage(&button->img);
    button->isInputUnlocked = true;
}

void drawButton(struct Button *button) {
    drawImage(&button->img);
}

void lockInputButton(struct Button *button) {
    button->isInputUnlocked = false;
    setFrameImage(&button->img, DISABLED);
}

void unlockInputButton(struct Button *button) {
    button->isInputUnlocked = true;
    setFrameImage(&button->img, UNCLICKED);
}

bool containsEventButton(struct Button *button, const struct InputEvent *e) {
    if (!button->img.widget.isVisible)
    {
        return false;
    }
    
  const struct DrawParams *drawParams = &button->img.widget.drawParams;
  const struct Rectangle bounds = { .x = drawParams->pos.x, .y =
      drawParams->pos.y, .w = drawParams->width, .h = drawParams->height };
  return isPointInRect(&e->pos, &bounds );
}