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
#include "Game/Entities/Terrorist.h"
#include "Game/Entities/Robot.h"


static const int32_t FIRST_PLAYER_ENEMY_IDX = 1;

static void cameraMotion(struct Game* self){
  if(self->camaraMotionLeftOn){

      if(self->gameImg.widget.drawParams.pos.x != 0){
        self->gameImg.widget.drawParams.pos.x += 2;
        for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVector(&self->battlefield.playerArmy); i++)
        {
          struct Hero* currHero =
                  (struct Hero*)getElementVector(&self->battlefield.playerArmy, i);
          if(currHero){
            currHero->base.heroImg.widget.drawParams.pos.x +=2;
          } 
        }

        for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVector(&self->battlefield.enemyArmy); i++)
        {
           struct Hero* currHero =
                  (struct Hero*)getElementVector(&self->battlefield.enemyArmy, i);
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
        for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVector(&self->battlefield.playerArmy); i++)
        {
          struct Hero* currHero =
                  (struct Hero*)getElementVector(&self->battlefield.playerArmy, i);
          if(currHero){
            currHero->base.heroImg.widget.drawParams.pos.x -=2;
          } 
        }

        for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVector(&self->battlefield.enemyArmy); i++)
        {
          struct Hero* currHero =
                  (struct Hero*)getElementVector(&self->battlefield.enemyArmy, i);
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
  self->gameStarted = cfg->gameStarted;

  self->epoch = cfg->epoch;
  self->playerXp = cfg->playerXp;
  self->enemyXp = cfg->enemyrXp;
  self->playerMoney = cfg->playerMoney;
  initBattlefield(&self->battlefield);
  struct Point widgetPos = { .x = 0, .y = 0 };
  self->troll_1Cfg = cfg->troll_1Cfg;
  self->troll_2Cfg = cfg->troll_2Cfg;
  self->troll_3Cfg = cfg->troll_3Cfg;

  self->terrorist_1_Cfg = cfg->terrorist_1_Cfg;
  self->terrorist_2_Cfg = cfg->terrorist_2_Cfg;
  self->terrorist_3_Cfg = cfg->terrorist_3_Cfg;

  self->robot_1_Cfg = cfg->robot_1_Cfg;
  self->robot_2_Cfg = cfg->robot_2_Cfg;
  self->robot_3_Cfg = cfg->robot_3_Cfg;

  resetImage(&self->gameImg);
  resetImage(&self->gameOverImg);
  resetImage(&self->gameWinImg);
  createImage(&self->gameImg, BACKGROUND_ID, &widgetPos);
  createImage(&self->gameOverImg, GAME_OVER_ID, &widgetPos);
  createImage(&self->gameWinImg, WIN_GAME_ID, &widgetPos);
  createImage(&self->gameStartImg, START_GAME_ID, &widgetPos);

  widgetPos.x = 5; widgetPos.y = 10; 
  createImage(&self->CoinImg, COIN_ID, &widgetPos);

  widgetPos.x = 160; widgetPos.y = 35; 
  createImage(&self->buttonTableImg, BUTTON_TABLE_ID, &widgetPos);

  widgetPos.x = 40; widgetPos.y = -45;
  char* textContent = "empty";
  resetText(&self->moneyText);
  createText(&self->moneyText, textContent, ANGELINE_VINATGE_ID,
      &COLOR_BLACK, &widgetPos);
  self->moneyText.widget.isVisible = true;

  widgetPos.x = 100; widgetPos.y = -45;
  resetText(&self->playerXpText);
  createText(&self->playerXpText, textContent, ANGELINE_VINATGE_ID,
      &COLOR_BLACK, &widgetPos);
  self->playerXpText.widget.isVisible = true;

  // activateAlphaModulationWidget(&self->gameImg.widget);
  activateAlphaModulationWidget(&self->gameOverImg.widget);
  activateAlphaModulationWidget(&self->gameWinImg.widget);

  self->gSpriteTimerId = 10;
  self->gAnimTimerId = 11;

  const int32_t buttonIds[GAME_BUTTON_COUNT] = 
    {
      cfg->trollBtnRsrcId,  
      cfg->troll2BtnRsrcId, 
      cfg->troll3BtnRsrcId, 

      cfg->trollBtnEnemyRsrcId,
      cfg->troll2BtnEnemyRsrcId,
      cfg->troll3BtnEnemyRsrcId,

      cfg->terroristBtnRsrcId,  
      cfg->terrorist2BtnRsrcId, 
      cfg->terrorist3BtnRsrcId,

      cfg->terroristBtnEnemyRsrcId,
      cfg->terrorist2BtnEnemyRsrcId,
      cfg->terrorist3BtnEnemyRsrcId,

      cfg->robotBtnRsrcId,  
      cfg->robot2BtnRsrcId, 
      cfg->robot3BtnRsrcId,

      cfg->robotBtnEnemyRsrcId,
      cfg->robot2BtnEnemyRsrcId,
      cfg->robot3BtnEnemyRsrcId,  

      cfg->starBtnRsrcId,
      cfg->startGameBtnRsrcId,

    };
  const struct Point buttonPos[GAME_BUTTON_COUNT] = {
    {.x=220, .y=50}, 
    {.x=290, .y=50}, 
    {.x=360, .y=50},

    {.x=1000, .y=50},
    {.x=1070, .y=50},
    {.x=1140, .y=50}, 
    
    {.x=220, .y=50}, 
    {.x=290, .y=50}, 
    {.x=360, .y=50}, 

    {.x=1000, .y=50},
    {.x=1070, .y=50},
    {.x=1140, .y=50},

    {.x=220, .y=50}, 
    {.x=290, .y=50}, 
    {.x=360, .y=50}, 

    {.x=1000, .y=50},
    {.x=1070, .y=50},
    {.x=1140, .y=50},

    {.x=460, .y=50},
    {.x=600, .y=600},
  };

  for (int32_t i = 0; i < GAME_BUTTON_COUNT; ++i) {
    if(SUCCESS != initGameButton(&self->buttons[i], (void*)self, i, buttonIds[i], &buttonPos[i])){
      self->buttons[i].button.img.widget.isAlphaModulationEnabled = true;
      LOGERR("initGameButton failed");
      return FAILURE;
    }
  }

  for (int32_t i = TERRORIST_1_BUTTON_IDX; i < STAR_BUTTON_IDX; ++i) {
    self->buttons[i].button.img.widget.isVisible = false;
    self->buttons[i].button.isInputUnlocked = false;
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

  pushElementVector(&self->battlefield.enemyArmy, &self->enemyTower);
  pushElementVector(&self->battlefield.playerArmy, &self->playerTower);

  return SUCCESS;
}

void deinitGame(struct Game* self){
  UNUSED(self);
  deinitBattlefield(&self->battlefield);
  destroyImage(&self->gameImg);
  destroyImage(&self->buttonTableImg);
  destroyImage(&self->gameWinImg);
  destroyImage(&self->gameOverImg);

  destroyText(&self->playerXpText);
  destroyText(&self->moneyText);
  // deinitWheel(&self->wheel);
  for (int32_t i = 0; i < GAME_BUTTON_COUNT; ++i) {
    deinitGameButton(&self->buttons[i]);
  }
  deinitBattlefield(&self->battlefield);

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
  for (int32_t i = 0; i < GAME_BUTTON_COUNT; ++i) {
    if (&self->buttons[i].button.isInputUnlocked && containsEventButton(&self->buttons[i].button, e)){
      handleEventGameButton(&self->buttons[i], e);
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

  if(self->playerXp < (int32_t)self->epoch){
    self->buttons[STAR_BUTTON_IDX].button.isInputUnlocked = false;
  }
  else{
    self->buttons[STAR_BUTTON_IDX].button.isInputUnlocked = true;

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

  if(self->enemyTower.health<200 && self->enemyTower.heroImg.currFrame == 1){
    self->enemyTower.heroImg.currFrame = 2;
    const struct Rectangle* rect =
                          (const struct Rectangle*)getElementVector
                            (self->enemyTower.heroImg.frames, self->enemyTower.heroImg.currFrame);

    self->enemyTower.heroImg.widget.drawParams.frameRect = *rect; 
  }

  else if(self->enemyTower.health<600 && self->enemyTower.heroImg.currFrame == 0){
    self->enemyTower.heroImg.currFrame = 1;
    const struct Rectangle* rect =
                          (const struct Rectangle*)getElementVector
                            (self->enemyTower.heroImg.frames, self->enemyTower.heroImg.currFrame);

    self->enemyTower.heroImg.widget.drawParams.frameRect = *rect;
  }


  cameraMotion(self);
  drawWidget(&self->gameImg.widget);
  drawWidget(&self->buttonTableImg.widget);
  drawWidget(&self->CoinImg.widget);
  // LOGY("wtf text x: y: %s %d %d %d",self->wtfText.textContent, self->wtfText.widget.drawParams.pos.x, self->wtfText.widget.drawParams.pos.y);
  char strC[10] ;
  sprintf(strC, "%d", self->playerMoney);
  setText(&self->moneyText, strC);
  
  sprintf(strC, "Xp: %d", self->playerXp);
  setText(&self->playerXpText, strC);

  drawWidget(&self->moneyText.widget);
  drawWidget(&self->playerXpText.widget);


  for (int i = TROLL_1_BUTTON_IDX; i <= STAR_BUTTON_IDX; i++)
  {
    drawGameButton(&self->buttons[i]);
  }

   
  startBattle(&self->battlefield, &self->playerMoney, &self->playerXp);

  self->playerTower.draw_func(&self->playerTower);
  self->enemyTower.draw_func(&self->enemyTower);
  for (size_t i = 0; i < getSizeVector(&self->battlefield.playerArmy); i++)
  {
    struct Hero* hero =
                  (struct Hero*)getElementVector(&self->battlefield.playerArmy, i);
    hero->base.draw_func(&hero->base);
  }

  for (size_t i = 0; i < getSizeVector(&self->battlefield.enemyArmy); i++)
  {
    struct Hero* hero =
                  (struct Hero*)getElementVector(&self->battlefield.enemyArmy, i);
    hero->base.draw_func(&hero->base);
  }

  if(!self->gameStarted){

    drawWidget(&self->gameStartImg.widget);
    drawGameButton(&self->buttons[START_GAME_BUTTON_IDX]);
  }

}

void onButtonPressedGameProxy (void* gameProxy, int32_t buttonId){
  
  struct Game *game = (struct Game*)gameProxy;
  if(buttonId == TROLL_1_BUTTON_IDX){
    if(game->playerMoney < game->troll_1Cfg.prise){
      return;
    }
    game->playerMoney -= game->troll_1Cfg.prise;

    struct Hero* currHero = malloc(sizeof(struct Hero));

    currHero->moveTimerId = game->gAnimTimerId;
    currHero->spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos = { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TROLL_START_Y};

    initHero(&currHero->base, &game->troll_1Cfg, &widgetPos, PLAYER);

    pushElementVector(&game->battlefield.playerArmy, &currHero->base);
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

    pushElementVector(&game->battlefield.enemyArmy, &currHero->base);
    currHero->startAnim_func(currHero);

  }

  else if(buttonId == TROLL_2_BUTTON_IDX){
    if(game->playerMoney < game->troll_2Cfg.prise){
      return;
    }
    game->playerMoney -= game->troll_2Cfg.prise;

    struct Hero* currHero = malloc(sizeof(struct Hero));

    currHero->moveTimerId = game->gAnimTimerId;
    currHero->spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos = { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TROLL_START_Y};

    initHero(&currHero->base, &game->troll_2Cfg, &widgetPos, PLAYER);

    pushElementVector(&game->battlefield.playerArmy, &currHero->base);
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

    pushElementVector(&game->battlefield.enemyArmy, &currHero->base);
    currHero->startAnim_func(currHero);

  }

  else if(buttonId == TROLL_3_BUTTON_IDX){
    if(game->playerMoney < game->troll_3Cfg.prise){
      return;
    }
    game->playerMoney -= game->troll_3Cfg.prise;

    struct Hero* currHero = malloc(sizeof(struct Hero));

    currHero->moveTimerId = game->gAnimTimerId;
    currHero->spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos = { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TROLL_START_Y};

    initHero(&currHero->base, &game->troll_3Cfg, &widgetPos, PLAYER);

    pushElementVector(&game->battlefield.playerArmy, &currHero->base);
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

    pushElementVector(&game->battlefield.enemyArmy, &currHero->base);
    currHero->startAnim_func(currHero);
  }

  else if(buttonId == STAR_BUTTON_IDX){
    if(game->buttons[STAR_BUTTON_IDX].button.isInputUnlocked == false){
      return;
    }

    if(game->epoch == STONE_AGE){
      game->epoch = PRESENT;
      for (int32_t i = TROLL_1_BUTTON_IDX; i <= TROLL_3_BUTTON_IDX; i++)
      {
         game->buttons[i].button.img.widget.isVisible = false;
         game->buttons[i].button.isInputUnlocked = false;
      }

      for (int32_t i = TERRORIST_1_BUTTON_IDX; i <= TERRORIST_3_BUTTON_IDX; i++)
      {
         game->buttons[i].button.img.widget.isVisible = true;
         game->buttons[i].button.isInputUnlocked = true;
      }


    }
    else if(game->epoch == PRESENT ){
      game->epoch = FUTURE;
      for (int32_t i = TERRORIST_1_BUTTON_IDX; i <= TERRORIST_3_BUTTON_IDX; i++)
      {
         game->buttons[i].button.img.widget.isVisible = false;
         game->buttons[i].button.isInputUnlocked = false;
      }

      for (int32_t i = ROBOT_1_BUTTON_IDX; i <= ROBOT_3_BUTTON_IDX; i++)
      {
         game->buttons[i].button.img.widget.isVisible = true;
         game->buttons[i].button.isInputUnlocked = true;
      }

    }

  }

  else if(buttonId == TERRORIST_1_BUTTON_IDX){
    if(game->buttons[TERRORIST_1_BUTTON_IDX].button.isInputUnlocked == false){
      return;
    }

    if(game->playerMoney < game->terrorist_1_Cfg.heroCfg.prise){
      return;
    }
    game->playerMoney -= game->terrorist_1_Cfg.heroCfg.prise;

    struct Terrorist* currHero = (struct Terrorist*)malloc(sizeof(struct Terrorist));

    currHero->hero.moveTimerId = game->gAnimTimerId;
    currHero->hero.spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos =
     { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TERRORIST_START_Y};

    initTerrorist(&currHero->hero.base, &game->terrorist_1_Cfg, &widgetPos, PLAYER);

    pushElementVector(&game->battlefield.playerArmy, &currHero->hero.base);
    currHero->hero.startAnim_func(&currHero->hero);
    
  }


  else if(buttonId == TERRORIST_2_BUTTON_IDX){
    if(game->buttons[TERRORIST_2_BUTTON_IDX].button.isInputUnlocked == false){
      return;
    }

    if(game->playerMoney < game->terrorist_2_Cfg.heroCfg.prise){
      return;
    }
    game->playerMoney -= game->terrorist_2_Cfg.heroCfg.prise;
    struct Terrorist* currHero = (struct Terrorist*)malloc(sizeof(struct Terrorist));

    currHero->hero.moveTimerId = game->gAnimTimerId;
    currHero->hero.spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos =
     { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TERRORIST_START_Y};

    initTerrorist(&currHero->hero.base, &game->terrorist_2_Cfg, &widgetPos, PLAYER);

    pushElementVector(&game->battlefield.playerArmy, &currHero->hero.base);
    currHero->hero.startAnim_func(&currHero->hero);
    
  }

  else if(buttonId == TERRORIST_3_BUTTON_IDX){
    if(game->buttons[TERRORIST_3_BUTTON_IDX].button.isInputUnlocked == false){
      return;
    }

    if(game->playerMoney < game->terrorist_3_Cfg.heroCfg.prise){
      return;
    }
    game->playerMoney -= game->terrorist_3_Cfg.heroCfg.prise;
    struct Terrorist* currHero = (struct Terrorist*)malloc(sizeof(struct Terrorist));

    currHero->hero.moveTimerId = game->gAnimTimerId;
    currHero->hero.spriteTimerId = game->gSpriteTimerId;
    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos =
     { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TERRORIST_START_Y};

    initTerrorist(&currHero->hero.base, &game->terrorist_3_Cfg, &widgetPos, PLAYER);

    pushElementVector(&game->battlefield.playerArmy, &currHero->hero.base);
    currHero->hero.startAnim_func(&currHero->hero);
    
  }

  else if(buttonId == ROBOT_1_BUTTON_IDX){
    if(game->buttons[ROBOT_1_BUTTON_IDX].button.isInputUnlocked == false){
      return;
    }

    if(game->playerMoney < game->robot_1_Cfg.heroCfg.prise){
      return;
    }
    game->playerMoney -= game->robot_1_Cfg.heroCfg.prise;
    LOGY("ROBOT 1")

    Robot* currHero = (Robot*)malloc(sizeof( Robot));

    currHero->hero.moveTimerId = game->gAnimTimerId;
    currHero->hero.spriteTimerId = game->gSpriteTimerId;

    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos =
     { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TERRORIST_START_Y};

    initTerrorist(&currHero->hero.base, &game->robot_1_Cfg, &widgetPos, PLAYER);

    pushElementVector(&game->battlefield.playerArmy, &currHero->hero.base);
    currHero->hero.startAnim_func(&currHero->hero);
  }

  else if(buttonId == ROBOT_2_BUTTON_IDX){
    if(game->buttons[ROBOT_2_BUTTON_IDX].button.isInputUnlocked == false){
      return;
    }

    if(game->playerMoney < game->robot_2_Cfg.heroCfg.prise){
      return;
    }
    game->playerMoney -= game->robot_2_Cfg.heroCfg.prise;


    Robot* currHero = (Robot*)malloc(sizeof( Robot));

    currHero->hero.moveTimerId = game->gAnimTimerId;
    currHero->hero.spriteTimerId = game->gSpriteTimerId;

    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos =
     { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TERRORIST_START_Y};

    initTerrorist(&currHero->hero.base, &game->robot_2_Cfg, &widgetPos, PLAYER);

    pushElementVector(&game->battlefield.playerArmy, &currHero->hero.base);
    currHero->hero.startAnim_func(&currHero->hero);
  }

  else if(buttonId == ROBOT_3_BUTTON_IDX){
    if(game->buttons[ROBOT_3_BUTTON_IDX].button.isInputUnlocked == false){
      return;
    }
    if(game->playerMoney < game->robot_3_Cfg.heroCfg.prise){
      return;
    }
    game->playerMoney -= game->robot_3_Cfg.heroCfg.prise;


    Robot* currHero = (Robot*)malloc(sizeof( Robot));

    currHero->hero.moveTimerId = game->gAnimTimerId;
    currHero->hero.spriteTimerId = game->gSpriteTimerId;

    game->gAnimTimerId+=2;
    game->gSpriteTimerId+=2;

    struct Point widgetPos =
     { .x = game->playerTower.heroImg.widget.drawParams.pos.x + HERO_PLAYER_START_X, .y = TERRORIST_START_Y};

    initTerrorist(&currHero->hero.base, &game->robot_3_Cfg, &widgetPos, PLAYER);

    pushElementVector(&game->battlefield.playerArmy, &currHero->hero.base);
    currHero->hero.startAnim_func(&currHero->hero);
  }

  else if(buttonId == START_GAME_BUTTON_IDX){
    LOGY("start Game");
    game->gameStarted = true;
    game->buttons[START_GAME_BUTTON_IDX].button.img.widget.isVisible = false;
    game->buttons[START_GAME_BUTTON_IDX].button.isInputUnlocked = false;
    game->gameStartImg.widget.isVisible = false;
    game->gameStartImg.widget.isDestroyed = true;

  }

   else {
    LOGERR("Received unknown buttonId: %d", buttonId);
  }
}

