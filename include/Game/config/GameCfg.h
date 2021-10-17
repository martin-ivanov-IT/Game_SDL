#ifndef GAME_GAMECFG_H_
#define GAME_GAMECFG_H_

#include <stdint.h>

#define MAX_IMG_NAME_LEN 50

enum GameImages {
  UP, DOWN, LEFT, RIGHT, PRESS_KEYS, LAYER_2, IMAGES_COUNT
};

struct GameConfig {
  char imgLoadPaths[IMAGES_COUNT][MAX_IMG_NAME_LEN];
};


#endif 