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
  WHEEL_BUTTON_COUNT
};

typedef struct SDL_Texture SDL_Texture;
struct InputEvent;
struct Vector;

struct Game {
  struct Image gameImg;
  struct Image gameOverImg;
  struct Image gameWinImg;
  struct Hero playerTower;
  struct Hero enemyTower;
  struct WheelButton buttons [WHEEL_BUTTON_COUNT];
  struct Battlefield battlefield;

  struct HeroCfg heroCfg;
  struct HeroBaseCfg herobaseCfg;
  int32_t gSpriteTimerId;
  int32_t gAnimTimerId;

  bool camaraMotionRightOn;
  bool camaraMotionLeftOn;
};
void handleEventGame (struct Game* self, struct InputEvent* e);
int32_t initGame(struct Game* self, const struct GameConfig* cfg);
void deinitGame(struct Game* self);
void drawGame(struct Game* self);

#endif 
