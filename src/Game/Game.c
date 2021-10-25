#include "Game/Game.h"
#include "common/CommonDefines.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "sdl_utils/InputEvent.h"
#include "sdl_utils/config/ImageContainerCfg.h"
#include "sdl_utils/Texture.h"
#include <stdlib.h>
#include <string.h>
#include "utils/drawing/Color.h"
#include "manager_utils/drawing/Image.h"


int32_t initGame(struct Game* self, const struct GameConfig* cfg){
  UNUSED(cfg);
  createImage(&self->pressKeysImg, PRESS_KEYS_TEXTURE_ID, &POINT_ZERO);
  activateAlphaModulationWidget(&self->pressKeysImg.widget);
  struct Point textPos = {.x = 300, .y = 300};
  createText(&self->pressText, "Press M to hide", ANGELINE_VINATGE_ID, &COLOR_MAGENTA, &textPos);
  createText(&self->hide, "Press N to show", ANGELINE_VINATGE_ID, &COLOR_MAGENTA, &POINT_ZERO);
  return SUCCESS;
}

void deinitGame(struct Game* self){
    destroyText(&self->pressText);
    destroyText(&self->hide);
    destroyImage(&self->pressKeysImg);

    UNUSED(self);

}

void handleEventGame (struct Game* self, struct InputEvent* e){
  if (KEYBOARD_PRESS == e->type) {
    return;
  }
    switch (e->key) {
        case KEY_M:
        self->pressText.widget.isVisible = false;
        self->hide.widget.isVisible = true;

        break;

        case KEY_N:
        self->pressText.widget.isVisible = true;
        self->hide.widget.isVisible = false;
        break;

        case KEY_P:
        setText(&self->pressText, "Hello there");
        break;

        case KEY_J:
        setColorText(&self->pressText, &COLOR_GREEN);
        break;

        case KEY_UP:
          self->pressKeysImg.widget.drawParams.pos.y -= 10;
        break;
        // case KEY_DOWN:
        //   self->pressKeysImg.pos.y += 10;
        // break;
        // case KEY_LEFT:
        //   self->pressKeysImg.pos.x -= 10;
        // break;
        // case KEY_RIGHT:
        //   self->pressKeysImg.pos.x += 10;
        // break;

        // case KEY_Q:
        //   self->pressKeysImg.width -= 10;
        // break;
        // case KEY_W:
        //   self->pressKeysImg.width += 10;
        // break;
        // case KEY_E:
        //   self->pressKeysImg.height -= 10;
        // break;
        // case KEY_R:
        //   self->pressKeysImg.height += 10;
        // break;

        case KEY_A:
          setOpacityWidget(&self->pressKeysImg.widget, self->pressKeysImg.widget.drawParams.opacity +10);
          
        break;
        case KEY_S:
          setOpacityWidget(&self->pressKeysImg.widget, self->pressKeysImg.widget.drawParams.opacity -10);

        break;


        default:
        break;
      }
}


void drawGame(struct Game* self){
  drawImage(&self->pressKeysImg);
  drawText(&self->pressText);
  drawText(&self->hide);
}