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
//   const size_t xValueStrLen = snprintf(NULL, 0, "%d", pos->x);
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

static const int32_t FIRST_PLAYER_ENEMY_IDX = 1;

static void cameraMotion(struct Game* self){
  if(self->camaraMotionLeftOn){

      if(self->gameImg.widget.drawParams.pos.x != 0){
        self->gameImg.widget.drawParams.pos.x += 2;
        for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVectorHero(&self->battlefield.playerArmy); i++)
        {
          struct Hero* currHero = getElementVectorHero(&self->battlefield.playerArmy, i);
          if(currHero){
            currHero->heroImg.widget.drawParams.pos.x +=2;
          } 
        }

        for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVectorHero(&self->battlefield.enemyArmy); i++)
        {
          struct Hero* currHero = getElementVectorHero(&self->battlefield.enemyArmy, i);
          if(currHero){
            currHero->heroImg.widget.drawParams.pos.x +=2;
          } 
        }

      }
      if(self->enemyTower.heroImg.widget.drawParams.pos.x+2 <= 2400){
        self->enemyTower.heroImg.widget.drawParams.pos.x += 2;
      }

      if(self->playerTower.heroImg.widget.drawParams.pos.x != 0){
        self->playerTower.heroImg.widget.drawParams.pos.x += 2;
      }

      
  }
  else if(self->camaraMotionRightOn){
    if(self->gameImg.widget.drawParams.pos.x-2 >= -1600){
        self->gameImg.widget.drawParams.pos.x -= 2;
        for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVectorHero(&self->battlefield.playerArmy); i++)
        {
          struct Hero* currHero = getElementVectorHero(&self->battlefield.playerArmy, i);
          if(currHero){
            currHero->heroImg.widget.drawParams.pos.x -=2;
          } 
        }

        for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVectorHero(&self->battlefield.enemyArmy); i++)
        {
          struct Hero* currHero = getElementVectorHero(&self->battlefield.enemyArmy, i);
          if(currHero){
            currHero->heroImg.widget.drawParams.pos.x -=2;
          } 
        }
    }

    if(self->playerTower.heroImg.widget.drawParams.pos.x >= -1600){ 
        self->playerTower.heroImg.widget.drawParams.pos.x -= 2;
    }

    if(self->enemyTower.heroImg.widget.drawParams.pos.x >= 800){
        self->enemyTower.heroImg.widget.drawParams.pos.x -= 2;
    }
   
  }
}


int32_t initGame(struct Game* self, const struct GameConfig* cfg){
  self->camaraMotionLeftOn = false;
  self->camaraMotionRightOn = false;
  initBattlefield(&self->battlefield);
  struct Point widgetPos = { .x = 0, .y = 0 };
  self->heroCfg = cfg->heroCfg;
  resetImage(&self->gameImg);
  resetImage(&self->gameOverImg);
  resetImage(&self->gameWinImg);
  createImage(&self->gameImg, TEXTURE_BACKGROUND, &widgetPos);
  createImage(&self->gameOverImg, TEXTURE_GAME_OVER, &widgetPos);
  createImage(&self->gameWinImg, TEXTURE_WIN_GAME, &widgetPos);
  activateAlphaModulationWidget(&self->gameImg.widget);
  activateAlphaModulationWidget(&self->gameOverImg.widget);
  activateAlphaModulationWidget(&self->gameWinImg.widget);

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

  if (SUCCESS != initTower(&self->playerTower, &cfg->playerTowerCfg)) {
    LOGERR("Error, initTower() failed");
    return FAILURE;
  }
  self->playerTower.heroImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;

  if (SUCCESS != initTower(&self->enemyTower, &cfg->enemyTowerCfg)) {
    LOGERR("Error, initTower() failed");
    return FAILURE;
  }
  pushElementVectorHero(&self->battlefield.enemyArmy, &self->enemyTower);
  pushElementVectorHero(&self->battlefield.playerArmy, &self->playerTower);

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
  if(MOUSE_MOTION == e->type){
    if(e->pos.x>=1200){
      self->camaraMotionRightOn = true;
      self->camaraMotionLeftOn = false;
    }

    else if(e->pos.x<=200){
      self->camaraMotionLeftOn = true;
      self->camaraMotionRightOn = false;
    }
    else {
      self->camaraMotionRightOn = false;
      self->camaraMotionLeftOn = false;
    }
    // LOGY("x: %d  y: %d", e->pos.x , e->pos.y );
  }
  for (int32_t i = 0; i < WHEEL_BUTTON_COUNT; ++i) {
    if (&self->buttons[i].button.isInputUnlocked && containsEventButton(&self->buttons[i].button, e)){
      handleEventWheelButton(&self->buttons[i], e);
      break;
    }
  }
}


void drawGame(struct Game* self){
  if(!self->playerTower.isAlive){
     drawWidget(&self->gameOverImg.widget);
     return;
  }

  if(!self->enemyTower.isAlive){
     drawWidget(&self->gameWinImg.widget);
     return;
  }
  // drawWheel(&self->wheel);
  cameraMotion(self);
  drawWidget(&self->gameImg.widget);
  
  // drawHero(&self->hero);
  // drawHero(&self->island_boy);
  drawWheelButton(&self->buttons[0]);
  drawWheelButton(&self->buttons[1]);
  startBattle(&self->battlefield);
  drawHero(&self->playerTower);
  drawHero(&self->enemyTower);
  for (size_t i = 0; i < getSizeVectorHero(&self->battlefield.playerArmy); i++)
  {
    struct Hero* hero = getElementVectorHero(&self->battlefield.playerArmy, i);
    drawHero(hero);

  }

  for (size_t i = 0; i < getSizeVectorHero(&self->battlefield.enemyArmy); i++)
  {
    struct Hero* hero = getElementVectorHero(&self->battlefield.enemyArmy, i);
    drawHero(hero);

  }
  
}

void onButtonPressedGameProxy (void* gameProxy, int32_t buttonId){
  struct Game *game = (struct Game*)gameProxy;
  if(buttonId == TROLL_1_BUTTON_IDX){
    struct Hero* currHero = malloc(sizeof(struct Hero));
    currHero->playerType = PLAYER;
    struct HeroCfg cfg;
    cfg = game->heroCfg;
    currHero->moveTimerId = game->gAnimTimerId;
    currHero->spriteTimerId = game->gSpriteTimerId;
    
    cfg.heroMoveTimerId = game->gSpriteTimerId;
    cfg.heroChangeAnimTimerId = game->gAnimTimerId;
  
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;
    struct Point widgetPos = { .x = game->playerTower.heroImg.widget.drawParams.pos.x + 620, .y = 450};
    initHero(currHero, &cfg, &widgetPos);

    pushElementVectorHero(&game->battlefield.playerArmy, currHero);
    startAnim(currHero);
  }

  else if(buttonId == TROLL_1_BUTTON_ENEMY_IDX){
    struct Hero* currHero = malloc(sizeof(struct Hero));
    currHero->playerType = ENEMY;
    struct HeroCfg cfg;
    cfg = game->heroCfg;

    currHero->moveTimerId = game->gAnimTimerId;
    currHero->spriteTimerId = game->gSpriteTimerId;
    
    cfg.heroMoveTimerId = game->gSpriteTimerId;
    cfg.heroChangeAnimTimerId = game->gAnimTimerId;
  
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;
    struct Point widgetPos = { .x = game->enemyTower.heroImg.widget.drawParams.pos.x -300, .y = 450};
    initHero(currHero, &cfg, &widgetPos);

    pushElementVectorHero(&game->battlefield.enemyArmy, currHero);
    startAnim(currHero);
  }

   else {
    LOGERR("Received unknown buttonId: %d", buttonId);
  }
}

