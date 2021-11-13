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
#include "Game/Entities/Terrorist.h"


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
  self->epoch = cfg->epoch;
  initBattlefield(&self->battlefield);
  struct Point widgetPos = { .x = 0, .y = 0 };
  self->troll_1Cfg = cfg->troll_1Cfg;
  self->troll_2Cfg = cfg->troll_2Cfg;
  self->troll_3Cfg = cfg->troll_3Cfg;
  self->terrorist_1_Cfg = cfg->terrorist_1_Cfg;
  resetImage(&self->gameImg);
  resetImage(&self->gameOverImg);
  resetImage(&self->gameWinImg);
  createImage(&self->gameImg, BACKGROUND_ID, &widgetPos);
  createImage(&self->gameOverImg, GAME_OVER_ID, &widgetPos);
  createImage(&self->gameWinImg, WIN_GAME_ID, &widgetPos);

  struct Point buttonTablewidgetPos = { .x = 160, .y = 35 };
  createImage(&self->buttonTableImg, BUTTON_TABLE_ID, &buttonTablewidgetPos);


  // activateAlphaModulationWidget(&self->gameImg.widget);
  activateAlphaModulationWidget(&self->gameOverImg.widget);
  activateAlphaModulationWidget(&self->gameWinImg.widget);

  self->gSpriteTimerId = 10;
  self->gAnimTimerId = 11;

  const int32_t buttonIds[WHEEL_BUTTON_COUNT] = 
    {
      cfg->trollBtnRsrcId,  cfg->trollBtnEnemyRsrcId,
      cfg->troll2BtnRsrcId, cfg->troll2BtnEnemyRsrcId,
      cfg->troll3BtnRsrcId, cfg->troll3BtnEnemyRsrcId,

      cfg->terroristBtnRsrcId,  cfg->terroristBtnEnemyRsrcId,
      cfg->terrorist2BtnRsrcId, cfg->terrorist2BtnEnemyRsrcId,
      cfg->terrorist3BtnRsrcId, cfg->terrorist3BtnEnemyRsrcId,

      cfg->starBtnRsrcId,

    };
  const struct Point buttonPos[WHEEL_BUTTON_COUNT] = {
    {.x=220, .y=50}, {.x=1000, .y=50},
    {.x=290, .y=50}, {.x=1070, .y=50},
    {.x=360, .y=50}, {.x=1140, .y=50},
    
    {.x=220, .y=50}, {.x=1000, .y=50},
    {.x=290, .y=50}, {.x=1070, .y=50},
    {.x=360, .y=50}, {.x=1140, .y=50},

    {.x=460, .y=50},
  };

  for (int32_t i = 0; i < WHEEL_BUTTON_COUNT; ++i) {
    if(SUCCESS != initWheelButton(&self->buttons[i], (void*)self, i, buttonIds[i], &buttonPos[i])){
      self->buttons[i].button.img.widget.isAlphaModulationEnabled = true;
      LOGERR("initWheelButton failed");
      return FAILURE;
    }
  }
  self->buttons[6].button.img.widget.isVisible = false;
  self->buttons[6].button.isInputUnlocked = false;
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
  drawWidget(&self->buttonTableImg.widget);
  
  // drawHero(&self->hero);
  // drawHero(&self->island_boy);
  drawWheelButton(&self->buttons[0]);
  drawWheelButton(&self->buttons[1]);
  drawWheelButton(&self->buttons[2]);
  drawWheelButton(&self->buttons[3]);
  drawWheelButton(&self->buttons[4]);
  drawWheelButton(&self->buttons[5]);
  drawWheelButton(&self->buttons[6]);

  drawWheelButton(&self->buttons[STAR_BUTTON_IDX]);
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

  else if(buttonId == TROLL_2_BUTTON_IDX){
    struct Hero* currHero = malloc(sizeof(struct Hero));

    currHero->moveTimerId = game->gAnimTimerId;
    currHero->spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos = { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TROLL_START_Y};

    initHero(&currHero->base, &game->troll_2Cfg, &widgetPos, PLAYER);

    pushElementVectorHero(&game->battlefield.playerArmy, &currHero->base);
    currHero->startAnim_func(currHero);
  }

  else if(buttonId == TROLL_2_BUTTON_ENEMY_IDX){
    struct Hero* currHero = malloc(sizeof(struct Hero));

    currHero->moveTimerId = game->gAnimTimerId;
    currHero->spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos = { .x = game->enemyTower.heroImg.widget.drawParams.pos.x + HERO_ENEMY_START_X, .y = TROLL_START_Y};
    initHero(&currHero->base, &game->troll_2Cfg, &widgetPos, ENEMY);

    pushElementVectorHero(&game->battlefield.enemyArmy, &currHero->base);
    currHero->startAnim_func(currHero);

  }

  else if(buttonId == TROLL_3_BUTTON_IDX){
    struct Hero* currHero = malloc(sizeof(struct Hero));

    currHero->moveTimerId = game->gAnimTimerId;
    currHero->spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos = { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TROLL_START_Y};

    initHero(&currHero->base, &game->troll_3Cfg, &widgetPos, PLAYER);

    pushElementVectorHero(&game->battlefield.playerArmy, &currHero->base);
    currHero->startAnim_func(currHero);
  }

  else if(buttonId == TROLL_3_BUTTON_ENEMY_IDX){
    struct Hero* currHero = malloc(sizeof(struct Hero));

    currHero->moveTimerId = game->gAnimTimerId;
    currHero->spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos = { .x = game->enemyTower.heroImg.widget.drawParams.pos.x + HERO_ENEMY_START_X, .y = TROLL_START_Y};
    initHero(&currHero->base, &game->troll_3Cfg, &widgetPos, ENEMY);

    pushElementVectorHero(&game->battlefield.enemyArmy, &currHero->base);
    currHero->startAnim_func(currHero);

  }

  else if(buttonId == STAR_BUTTON_IDX){
    if(game->epoch != PRESENT){
      game->epoch = PRESENT;
      game->buttons[6].button.img.widget.isVisible = true;
      game->buttons[6].button.isInputUnlocked = true;

      game->buttons[0].button.img.widget.isVisible = false;
      game->buttons[0].button.isInputUnlocked = false;
    }
    
  }

  // else if(buttonId == TERRORIST_1_BUTTON_IDX){
  //   if(game->buttons[6].button.isInputUnlocked == false){
  //     return;
  //   }
  //   struct Terrorist* currHero = malloc(sizeof(struct Hero));

  //   currHero->hero.moveTimerId = game->gAnimTimerId;
  //   currHero->hero.spriteTimerId = game->gSpriteTimerId;
  //   game->gAnimTimerId+=2;
  //   game->gSpriteTimerId+=2;

  //   struct Point widgetPos = { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TROLL_START_Y};

  //   initTerrorist(&currHero->hero.base, &game->terrorist_1_Cfg, &widgetPos, PLAYER);

  //   pushElementVectorHero(&game->battlefield.playerArmy, &currHero->hero.base);
  //   currHero->hero.startAnim_func(&currHero->hero);
    
  // }
   else {
    LOGERR("Received unknown buttonId: %d", buttonId);
  }
}

