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
#include "Game/Entities/Buttons/GameButton.h"
#include "include/containers/VectorHero.h"
#include "manager_utils/drawing/Text.h"
#include "Game/Battlefield/Battlefield.h"


enum GameButtons {
  TROLL_1_BUTTON_IDX,
  TROLL_2_BUTTON_IDX,
  TROLL_3_BUTTON_IDX,

  TROLL_1_BUTTON_ENEMY_IDX,
  TROLL_2_BUTTON_ENEMY_IDX,
  TROLL_3_BUTTON_ENEMY_IDX,
  
  TERRORIST_1_BUTTON_IDX,
  TERRORIST_2_BUTTON_IDX,
  TERRORIST_3_BUTTON_IDX,

  TERRORIST_1_BUTTON_ENEMY_IDX,
  TERRORIST_2_BUTTON_ENEMY_IDX,
  TERRORIST_3_BUTTON_ENEMY_IDX,

  ROBOT_1_BUTTON_IDX,
  ROBOT_2_BUTTON_IDX,
  ROBOT_3_BUTTON_IDX,
  ROBOT_1_BUTTON_ENEMY_IDX,
  ROBOT_2_BUTTON_ENEMY_IDX,
  ROBOT_3_BUTTON_ENEMY_IDX,

  STAR_BUTTON_IDX,
  
  START_GAME_BUTTON_IDX,

  GAME_BUTTON_COUNT,

};

typedef struct SDL_Texture SDL_Texture;
struct InputEvent;
struct Vector;

struct Game {
  struct Image gameImg;
  struct Image gameStartImg;
  struct Image gameOverImg;
  struct Image gameWinImg;
  struct Image buttonTableImg;
  struct Image CoinImg;

  struct Text moneyText;
  struct Text playerXpText;

  struct HeroBase playerTower;
  struct HeroBase enemyTower;

  struct GameButton buttons [GAME_BUTTON_COUNT];
  // struct WheelButton startGamebuttons [WHEEL_BUTTON_COUNT];
  struct Battlefield battlefield;

  struct HeroCfg troll_1Cfg;
  struct HeroCfg troll_2Cfg;
  struct HeroCfg troll_3Cfg;

  struct TerroristCfg terrorist_1_Cfg;
  struct TerroristCfg terrorist_2_Cfg;
  struct TerroristCfg terrorist_3_Cfg;

   RobotCfg robot_1_Cfg;
   RobotCfg robot_2_Cfg;
   RobotCfg robot_3_Cfg;

  int32_t gSpriteTimerId;
  int32_t gAnimTimerId;

  int32_t playerMoney;
  int32_t playerXp;
  int32_t enemyXp;
  Epoch epoch;

  bool gameStarted;

  bool camaraMotionRightOn;
  bool camaraMotionLeftOn;
};
void handleEventGame (struct Game* self, struct InputEvent* e);
int32_t initGame(struct Game* self, const struct GameConfig* cfg);
void deinitGame(struct Game* self);
void drawGame(struct Game* self);

#endif 
