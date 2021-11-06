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
#include "common/CommonDefines.h"
#include "common/TimerDefines.h"


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
  struct Point widgetPos = { .x = 0, .y = 0 };
  resetImage(&self->gameImg);
  createImage(&self->gameImg, TEXTURE_BACKGROUND, &widgetPos);
  activateAlphaModulationWidget(&self->gameImg.widget);
  initVectorHero(&self->playerArmy, 10);
  self->gSpriteTimerId = 10;
  self->gAnimTimerId = 11;

  const int32_t buttonIds[WHEEL_BUTTON_COUNT] = {cfg->trollBtnRsrcId,cfg->trollBtnEnemyRsrcId};
  const struct Point buttonPos[WHEEL_BUTTON_COUNT] = {
    {.x=680, .y=100}, {.x=630, .y=100}
  };

  for (int32_t i = 0; i < WHEEL_BUTTON_COUNT; ++i) {
    if(SUCCESS != initWheelButton(&self->buttons[i], (void*)self, i, buttonIds[i], &buttonPos[i])){
      LOGERR("initWheelButton failed");
      return FAILURE;
    }
  }
  return SUCCESS;
}

void deinitGame(struct Game* self){
  destroyImage(&self->gameImg);
  // deinitWheel(&self->wheel);
  // for (int32_t i = 0; i < WHEEL_BUTTON_COUNT; ++i) {
  //   deinitWheelButton(&self->wheelBtns[i]);
  // }

}

void handleEventGame (struct Game* self, struct InputEvent* e){
  for (int32_t i = 0; i < WHEEL_BUTTON_COUNT; ++i) {
    if (&self->buttons[i].button.isInputUnlocked && containsEventButton(&self->buttons[i].button, e)){
      handleEventWheelButton(&self->buttons[i], e);
      break;
    }
  }
}


void drawGame(struct Game* self){
  // drawWheel(&self->wheel);
  drawWidget(&self->gameImg.widget);
  // drawHero(&self->hero);
  // drawHero(&self->island_boy);
  drawWheelButton(&self->buttons[0]);
  drawWheelButton(&self->buttons[1]);
  
  for (size_t i = 0; i < getSizeVectorHero(&self->playerArmy); i++)
  {
    struct Hero* hero = getElementVectorHero(&self->playerArmy, i);
    drawHero(hero);

  }

  for (size_t i = 0; i < getSizeVectorHero(&self->enemyArmy); i++)
  {
    struct Hero* hero = getElementVectorHero(&self->enemyArmy, i);
    drawHero(hero);

  }
  
}

void onButtonPressedGameProxy (void* gameProxy, int32_t buttonId){
  struct Game *game = (struct Game*)gameProxy;
  if(buttonId == TROLL_1_BUTTON_IDX){
    struct Hero* currHero = malloc(sizeof(struct Hero));
    currHero->playerType = PLAYER;
    struct HeroCfg cfg;
    cfg.rsrcId = TROLL_1_ID;
    cfg.heroMoveTimerId = game->gSpriteTimerId;
    cfg.heroChangeAnimTimerId = game->gAnimTimerId;
  
    

    game->gAnimTimerId+=2;

    game->gSpriteTimerId+=2;

    cfg.horSteps = 40;
    cfg.verSteps = 20;
    cfg.deltaMovePx = 5;

    initHero(currHero, &cfg);

    pushElementVectorHero(&game->playerArmy, currHero);
    startAnim(currHero);
  }

  else if(buttonId == TROLL_1_BUTTON_ENEMY_IDX){
    struct Hero* currHero = malloc(sizeof(struct Hero));
    struct HeroCfg cfg;
    cfg.rsrcId = TROLL_1_ID;
    cfg.heroMoveTimerId = game->gSpriteTimerId;
    cfg.heroChangeAnimTimerId = game->gAnimTimerId;
    currHero->playerType = ENEMY;
    
    game->gAnimTimerId+=2;

    game->gSpriteTimerId+=2;

    cfg.horSteps = 40;
    cfg.verSteps = 20;
    cfg.deltaMovePx = 5;

    initHero(currHero, &cfg);

    pushElementVectorHero(&game->enemyArmy, currHero);
    startAnim(currHero);
  }

   else {
    LOGERR("Received unknown buttonId: %d", buttonId);
  }
}