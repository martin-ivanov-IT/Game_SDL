#ifndef GAME_GAMECFG_H_
#define GAME_GAMECFG_H_

#include <stdint.h>

struct ImageContainer;
struct TextContainer;


struct GameConfig {
  const struct ImageContainer* imgContainer;
  struct TextContainer* textContainer;
};


#endif 