#ifndef ENGINE_GAME_H_
#define ENGINE_GAME_H_


#include <stdint.h>
#include "sdl_utils/MonitorWindow.h"
#include "Game/config/GameCfg.h"
#include "utils/drawing/DrawParams.h"
#include "manager_utils/drawing/Image.h"
#include "manager_utils/drawing/Text.h"
#include "Game/Entities/Hero.h"
#include "Game/Entities/Tower.h"
#include "Game/Entities/Wheel.h"
#include "Game/Entities/Buttons/WheelButton.h"
#include "include/containers/VectorHero.h"
#include "Game/Battlefield/Battlefield.h"


enum WheelButtons {
  TROLL_1_BUTTON_IDX,
  TROLL_1_BUTTON_ENEMY_IDX,

  TROLL_2_BUTTON_IDX,
  TROLL_2_BUTTON_ENEMY_IDX,
  
  TROLL_3_BUTTON_IDX,
  TROLL_3_BUTTON_ENEMY_IDX,
 

  TERRORIST_1_BUTTON_IDX,
  TERRORIST_1_BUTTON_ENEMY_IDX,

  TERRORIST_2_BUTTON_IDX,
  TERRORIST_2_BUTTON_ENEMY_IDX,

  TERRORIST_3_BUTTON_IDX,
  TERRORIST_3_BUTTON_ENEMY_IDX,

  STAR_BUTTON_IDX,
  
  WHEEL_BUTTON_COUNT
};



typedef enum Game_Mode {
  DEMO,
  EASY,
  HARD,
  IMPOSSIBLE,
}Game_Mode;

typedef struct SDL_Texture SDL_Texture;
struct InputEvent;
struct Vector;

struct Game {
  struct Image gameImg;
  struct Image gameOverImg;
  struct Image gameWinImg;
  struct Image buttonTableImg;

  struct HeroBase playerTower;
  struct HeroBase enemyTower;

  struct WheelButton buttons [WHEEL_BUTTON_COUNT];
  struct Battlefield battlefield;

  struct HeroCfg troll_1Cfg;
  struct HeroCfg troll_2Cfg;
  struct HeroCfg troll_3Cfg;

  struct TerroristCfg terrorist_1_Cfg;

  int32_t gSpriteTimerId;
  int32_t gAnimTimerId;

  int32_t playerMoney;
  int32_t playerXp;
  Epoch epoch;

  bool camaraMotionRightOn;
  bool camaraMotionLeftOn;
};
void handleEventGame (struct Game* self, struct InputEvent* e);
int32_t initGame(struct Game* self, const struct GameConfig* cfg);
void deinitGame(struct Game* self);
void drawGame(struct Game* self);

#endif 
