#include "Game/Game.h"
#include "common/CommonDefines.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "sdl_utils/InputEvent.h"
#include "utils/containers/Vector.h"
#include "sdl_utils/config/ImageContainerCfg.h"
#include "sdl_utils/Texture.h"
#include "sdl_utils/containers/ImageContainer.h"
#include "sdl_utils/containers/TextContainer.h"
#include <stdlib.h>
#include <string.h>
#include "utils/drawing/Color.h"


int32_t initGame(struct Game* self, const struct GameConfig* cfg){
  
  if(NULL == cfg->imgContainer) {
    LOGERR("Error, NULL imgContainer privided");
    return FAILURE;
  }
  self->imgContainer = cfg->imgContainer;

  if(NULL == cfg->textContainer) {
    LOGERR("Error, NULL textContainer privided");
    return FAILURE;
  }
  self->textContaoner = cfg->textContainer;

  resetDrawParams(&self->pressKeysImg);
  self->pressKeysImg.rsrcId = PRESS_KEYS_TEXTURE_ID;
  self->pressKeysImg.pos = POINT_ZERO;
  const struct Rectangle* rect = getImageFrameImageContainer(self->imgContainer, self->pressKeysImg.rsrcId);
  self->pressKeysImg.width = rect->w;
  self->pressKeysImg.height = rect->h;
  self->pressKeysImg.widgetType = IMAGE_WIDGET;

  resetDrawParams(&self->pressText);
  self->pressText.pos.x = 300;
  self->pressText.pos.y = 300;
  self->pressText.widgetType = TEXT_WIDGET;

  createTextTextContainer(self->textContaoner, "Press M to hide", &COLOR_MAGENTA, ANGELINE_VINATGE_ID,
                          &self->pressText.rsrcId, &self->pressText.width, &self->pressText.height);   
  
  resetDrawParams(&self->hide);
  self->hide.pos = POINT_ZERO;
  self->hide.widgetType = TEXT_WIDGET;

  createTextTextContainer(self->textContaoner, "Press N to show", &COLOR_MAGENTA, ANGELINE_VINATGE_ID,
                          &self->hide.rsrcId, &self->hide.width, &self->hide.height); 

  self->isTextShown = true;
  return SUCCESS;
}

void deinitGame(struct Game* self){
    UNUSED(self);

}

void handleEventGame (struct Game* self, struct InputEvent* e){
  if (KEYBOARD_PRESS == e->type) {
    return;
  }
    switch (e->key) {
        case KEY_M:
        self->isTextShown = false;  
        break;

        case KEY_N:
        self->isTextShown = true;  
        break;

        case KEY_UP:
          self->pressKeysImg.pos.y -= 10;
        break;
        case KEY_DOWN:
          self->pressKeysImg.pos.y += 10;
        break;
        case KEY_LEFT:
          self->pressKeysImg.pos.x -= 10;
        break;
        case KEY_RIGHT:
          self->pressKeysImg.pos.x += 10;
        break;

        case KEY_Q:
          self->pressKeysImg.width -= 10;
        break;
        case KEY_W:
          self->pressKeysImg.width += 10;
        break;
        case KEY_E:
          self->pressKeysImg.height -= 10;
        break;
        case KEY_R:
          self->pressKeysImg.height += 10;
        break;

        case KEY_A:
          self->pressKeysImg.opacity += 10;
        break;
        case KEY_S:
          self->pressKeysImg.opacity -= 10;
        break;


        default:
        break;
      }
}


void drawGame(struct Game* self, struct Vector* images){
  pushElementVector(images, &self->pressKeysImg);
  if (self->isTextShown){
    pushElementVector(images, &self->pressText);
  }
  else {
    pushElementVector(images, &self->hide);

  }
}