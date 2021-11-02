#ifndef ENGINE_GAME_H_
#define ENGINE_GAME_H_


#include <stdint.h>
#include "sdl_utils/MonitorWindow.h"
#include "Game/config/GameCfg.h"
#include "utils/drawing/DrawParams.h"
#include "manager_utils/drawing/Image.h"
#include "manager_utils/drawing/Text.h"
#include "Game/Entities/Hero.h"
#include "Game/Entities/Wheel.h"
#include "Game/Entities/Buttons/WheelButton.h"

enum WheelButtons {
  START_WHEEL_BTN_IDX,
  STOP_WHEEL_BTN_IDX,
  WHEEL_BUTTON_COUNT
};

typedef struct SDL_Texture SDL_Texture;
struct InputEvent;
struct Vector;

struct Game {
  struct Hero hero;
  struct Wheel wheel;
  struct WheelButton wheelBtns[WHEEL_BUTTON_COUNT];
};
void handleEventGame (struct Game* self, struct InputEvent* e);
int32_t initGame(struct Game* self, const struct GameConfig* cfg);
void deinitGame(struct Game* self);
void drawGame(struct Game* self);

#endif 
