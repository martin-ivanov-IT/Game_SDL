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
#include "utils/ContainerOf.h"



static const int32_t FIRST_PLAYER_ENEMY_IDX = 1;

static void cameraMotion(struct Game* self){
  if(self->camaraMotionLeftOn){

      if(self->gameImg.widget.drawParams.pos.x != 0){
        self->gameImg.widget.drawParams.pos.x += 2;
        for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVectorHero(&self->battlefield.playerArmy); i++)
        {
          struct Hero* currHero =
                    container_of(getElementVectorHero(&self->battlefield.playerArmy, i), struct Hero, base);
          if(currHero){
            currHero->base.heroImg.widget.drawParams.pos.x +=2;
          } 
        }

        for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVectorHero(&self->battlefield.enemyArmy); i++)
        {
           struct Hero* currHero =
                    container_of(getElementVectorHero(&self->battlefield.enemyArmy, i), struct Hero, base);
          if(currHero){
            currHero->base.heroImg.widget.drawParams.pos.x +=2;
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
          struct Hero* currHero =
                    container_of(getElementVectorHero(&self->battlefield.playerArmy, i), struct Hero, base);
          if(currHero){
            currHero->base.heroImg.widget.drawParams.pos.x -=2;
          } 
        }

        for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVectorHero(&self->battlefield.enemyArmy); i++)
        {
          struct Hero* currHero =
                    container_of(getElementVectorHero(&self->battlefield.enemyArmy, i), struct Hero, base);
          if(currHero){
            currHero->base.heroImg.widget.drawParams.pos.x -=2;
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
  self->troll_1Cfg = cfg->troll_1Cfg;
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
    {.x=220, .y=50}, {.x=1000, .y=50}
  };

  for (int32_t i = 0; i < WHEEL_BUTTON_COUNT; ++i) {
    if(SUCCESS != initWheelButton(&self->buttons[i], (void*)self, i, buttonIds[i], &buttonPos[i])){
      LOGERR("initWheelButton failed");
      return FAILURE;
    }
  }

  struct Point playerTowerPos = { .x = 0, .y = 150 };
  if (SUCCESS != initBase(&self->playerTower, &cfg->playerTowerCfg, &playerTowerPos, PLAYER)) {
    LOGERR("Error, initTower() failed");
    return FAILURE;
  }
  self->playerTower.heroImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;

  struct Point enemyTowerPos = { .x = 2400, .y = 150 };
  if (SUCCESS != initBase(&self->enemyTower, &cfg->enemyTowerCfg,&enemyTowerPos, ENEMY)) {
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
  LOGY("playertowe health: %d", self->playerTower.health);

  if(self->playerTower.health<200 && self->playerTower.heroImg.currFrame == 1){
    self->playerTower.heroImg.currFrame = 2;
    const struct Rectangle* rect =
                          (const struct Rectangle*)getElementVector
                            (self->playerTower.heroImg.frames, self->playerTower.heroImg.currFrame);

    self->playerTower.heroImg.widget.drawParams.frameRect = *rect; 
  }

  else if(self->playerTower.health<600 && self->playerTower.heroImg.currFrame == 0){
    self->playerTower.heroImg.currFrame = 1;
    const struct Rectangle* rect =
                          (const struct Rectangle*)getElementVector
                            (self->playerTower.heroImg.frames, self->playerTower.heroImg.currFrame);

    self->playerTower.heroImg.widget.drawParams.frameRect = *rect;
  }

  // drawWheel(&self->wheel);
  cameraMotion(self);
  drawWidget(&self->gameImg.widget);
  
  // drawHero(&self->hero);
  // drawHero(&self->island_boy);
  drawWheelButton(&self->buttons[0]);
  drawWheelButton(&self->buttons[1]);
  startBattle(&self->battlefield);

  self->playerTower.draw_func(&self->playerTower);
  self->enemyTower.draw_func(&self->enemyTower);
  for (size_t i = 0; i < getSizeVectorHero(&self->battlefield.playerArmy); i++)
  {
    struct Hero* hero =
                    container_of(getElementVectorHero(&self->battlefield.playerArmy, i), struct Hero, base);
    hero->base.draw_func(&hero->base);
  }

  for (size_t i = 0; i < getSizeVectorHero(&self->battlefield.enemyArmy); i++)
  {
    struct Hero* hero =
                    container_of(getElementVectorHero(&self->battlefield.enemyArmy, i), struct Hero, base);
    hero->base.draw_func(&hero->base);
  }
  
}

void onButtonPressedGameProxy (void* gameProxy, int32_t buttonId){
  struct Game *game = (struct Game*)gameProxy;
  if(buttonId == TROLL_1_BUTTON_IDX){
    struct Hero* currHero = malloc(sizeof(struct Hero));

    currHero->moveTimerId = game->gAnimTimerId;
    currHero->spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos = { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TROLL_START_Y};

    initHero(&currHero->base, &game->troll_1Cfg, &widgetPos, PLAYER);

    pushElementVectorHero(&game->battlefield.playerArmy, &currHero->base);
    currHero->startAnim_func(currHero);
  }

  else if(buttonId == TROLL_1_BUTTON_ENEMY_IDX){
    struct Hero* currHero = malloc(sizeof(struct Hero));

    currHero->moveTimerId = game->gAnimTimerId;
    currHero->spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos = { .x = game->enemyTower.heroImg.widget.drawParams.pos.x + HERO_ENEMY_START_X, .y = TROLL_START_Y};
    initHero(&currHero->base, &game->troll_1Cfg, &widgetPos, ENEMY);

    pushElementVectorHero(&game->battlefield.enemyArmy, &currHero->base);
    currHero->startAnim_func(currHero);

  }

   else {
    LOGERR("Received unknown buttonId: %d", buttonId);
  }
}

