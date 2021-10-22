#ifndef ENGINE_GAME_H_
#define ENGINE_GAME_H_


#include <stdint.h>
#include "sdl_utils/MonitorWindow.h"
#include "Game/config/GameCfg.h"
#include "utils/drawing/DrawParams.h"


typedef struct SDL_Texture SDL_Texture;
struct InputEvent;
struct Vector;

struct Game {
  struct DrawParams pressKeysImg;
  struct DrawParams pressText;
  struct DrawParams hide;
  const struct ImageContainer* imgContainer;
  struct TextContainer* textContaoner;

  bool isTextShown;
};
void handleEventGame (struct Game* self, struct InputEvent* e);
int32_t initGame(struct Game* self, const struct GameConfig* cfg);
void deinitGame(struct Game* self);
void drawGame(struct Game* self, struct Vector* images);

#endif 
