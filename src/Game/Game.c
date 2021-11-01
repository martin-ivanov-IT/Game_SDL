#include "Game/Game.h"
#include "common/CommonDefines.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "sdl_utils/InputEvent.h"
#include "sdl_utils/config/ImageContainerCfg.h"
#include "sdl_utils/Texture.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils/drawing/Color.h"
#include "manager_utils/drawing/Image.h"

static void updateMouseTargetText(struct Text *text, const struct Point *pos) {
  const char initialStr[] = "X: ";
  const size_t initialStrLen = strlen(initialStr);
  char textContent[50];
  memset(textContent, 0, sizeof (textContent));
  size_t usedSize = 0;

  //append initial string
  strncpy(&textContent[usedSize], initialStr, initialStrLen);
  usedSize += initialStrLen;

  //append X value:
  const size_t xValueStrLen = snprintf(NULL, 0, "%d", pos->x);
  snprintf(&textContent[usedSize], xValueStrLen + 1, "%d", pos->x);
  usedSize += xValueStrLen;

  const char YStr[] = "nY: ";
  const size_t YStrStrLen = strlen(YStr);
  strncpy(&textContent[usedSize], YStr, YStrStrLen);
  usedSize += YStrStrLen;


  const size_t yValueStrLen = snprintf(NULL, 0, "%d", pos->y);
  snprintf(&textContent[usedSize], yValueStrLen + 1, "%d", pos->y);
  usedSize += yValueStrLen;
  setText(text, textContent);
  
  //...
}

int32_t initGame(struct Game* self, const struct GameConfig* cfg){
  if(SUCCESS != initHero(&self->hero, cfg->heroRsrcID)){
    LOGERR("initHero failed");
    return FAILURE;
  }
  createText(&self->mousePosText, "-", ANGELINE_VINATGE_ID, &COLOR_YELLOW, &POINT_ZERO);
  hideWidget(&self->mousePosText.widget);
  return SUCCESS;
}

void deinitGame(struct Game* self){
  deinitHero(&self->hero);
  destroyText(&self->mousePosText);

  UNUSED(self);

}

void handleEventGame (struct Game* self, struct InputEvent* e){
  handleEventHero(&self->hero, e);

  if (TOUCH_PRESS == e->type && e->mouseButton == MOUSE_LEFT_BUTTON) {
    updateMouseTargetText(&self->mousePosText, &e->pos);
    showWidget(&self->mousePosText.widget);
    self->mousePosText.widget.drawParams.pos = e->pos;
    return;
  }

  
}


void drawGame(struct Game* self){
  drawHero(&self->hero);
  drawText(&self->mousePosText);
}