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
#include "Game/proxies/GameInterface.h"

// static void updateMouseTargetText(struct Text *text, const struct Point *pos) {
//   const char initialStr[] = "X: ";
//   const size_t initialStrLen = strlen(initialStr);
//   char textContent[50];
//   memset(textContent, 0, sizeof (textContent));
//   size_t usedSize = 0;

//   //append initial string
//   strncpy(&textContent[usedSize], initialStr, initialStrLen);
//   usedSize += initialStrLen;

//   //append X value:
//   const size_t xValueStrLen = snprintf(NULL, 0, "%d", pos->x);z
//   snprintf(&textContent[usedSize], xValueStrLen + 1, "%d", pos->x);
//   usedSize += xValueStrLen;

//   const char YStr[] = "nY: ";
//   const size_t YStrStrLen = strlen(YStr);
//   strncpy(&textContent[usedSize], YStr, YStrStrLen);
//   usedSize += YStrStrLen;


//   const size_t yValueStrLen = snprintf(NULL, 0, "%d", pos->y);
//   snprintf(&textContent[usedSize], yValueStrLen + 1, "%d", pos->y);
//   usedSize += yValueStrLen;
//   setText(text, textContent);
  
//   //...
// }

int32_t initGame(struct Game* self, const struct GameConfig* cfg){
  if(SUCCESS != initHero(&self->hero, cfg->heroRsrcID)){
    LOGERR("initHero failed");
    return FAILURE;
  }

  if(SUCCESS != initWheel(&self->wheel, cfg->wheelRsrcID)){
    LOGERR("initWheel failed");
    return FAILURE;
  }

  const int32_t buttonIds[WHEEL_BUTTON_COUNT] = {cfg->wheelStartBtnRsrcId, cfg->wheelStopBtnRsrcId};
  const struct Point buttonPos[WHEEL_BUTTON_COUNT] = {
    {.x=680, .y=100}, {.x = 850, .y=100}
  };

  for (int32_t i = 0; i < WHEEL_BUTTON_COUNT; ++i) {
    if(SUCCESS != initWheelButton(&self->wheelBtns[i], (void*)self, i, buttonIds[i], &buttonPos[i])){
      LOGERR("initWheelButton failed");
      return FAILURE;
    }
  }

  lockInputButton(&self->wheelBtns[STOP_WHEEL_BTN_IDX].button);

  return SUCCESS;
}

void deinitGame(struct Game* self){
  deinitHero(&self->hero);
  deinitWheel(&self->wheel);
  for (int32_t i = 0; i < WHEEL_BUTTON_COUNT; ++i) {
    deinitWheelButton(&self->wheelBtns[i]);
  }

}

void handleEventGame (struct Game* self, struct InputEvent* e){
  handleEventHero(&self->hero, e);
  handleEventWheel(&self->wheel, e);
  for (int32_t i = 0; i < WHEEL_BUTTON_COUNT; ++i) {
    if (&self->wheelBtns[i].button.isInputUnlocked && containsEventButton(&self->wheelBtns[i].button, e)){
      handleEventWheelButton(&self->wheelBtns[i], e);
      break;
    }
  }
}


void drawGame(struct Game* self){
  drawWheel(&self->wheel);
  drawHero(&self->hero);
  for (int32_t i = START_WHEEL_BTN_IDX; i < WHEEL_BUTTON_COUNT; ++i) {
    drawWheelButton(&self->wheelBtns[i]);
  }

}

void onButtonPressedGameProxy (void* gameProxy, int32_t buttonId){
  struct Game *game = (struct Game*)gameProxy;
  if (START_WHEEL_BTN_IDX == buttonId) {
    startRotationWheel(&game->wheel);
    lockInputButton(&game->wheelBtns[START_WHEEL_BTN_IDX].button);
    unlockInputButton(&game->wheelBtns[STOP_WHEEL_BTN_IDX].button);
  } else if (STOP_WHEEL_BTN_IDX == buttonId) {
    stopRotationWheel(&game->wheel);
    lockInputButton(&game->wheelBtns[STOP_WHEEL_BTN_IDX].button);
    unlockInputButton(&game->wheelBtns[START_WHEEL_BTN_IDX].button);
  } else {
    LOGERR("Received unknown buttonId: %d", buttonId);
  }
}
