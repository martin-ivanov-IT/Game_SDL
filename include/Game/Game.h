#ifndef ENGINE_GAME_H_
#define ENGINE_GAME_H_


#include <stdint.h>
#include "sdl_utils/MonitorWindow.h"
#include "Game/config/GameCfg.h"
#include "utils/drawing/DrawParams.h"
#include "manager_utils/drawing/Image.h"
#include "manager_utils/drawing/Text.h"



typedef struct SDL_Texture SDL_Texture;
struct InputEvent;
struct Vector;

struct Game {
  struct Image pressKeysImg;
  struct Text pressText;
  struct Text hide;
};
void handleEventGame (struct Game* self, struct InputEvent* e);
int32_t initGame(struct Game* self, const struct GameConfig* cfg);
void deinitGame(struct Game* self);
void drawGame(struct Game* self);

#endif 
