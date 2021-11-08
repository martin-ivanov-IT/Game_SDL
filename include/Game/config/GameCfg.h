#ifndef GAME_GAMECFG_H_
#define GAME_GAMECFG_H_

#include <stdint.h>

#include "Game/Entities/Hero.h"


struct GameConfig {

  struct HeroCfg heroCfg;
  struct HeroCfg playerTowerCfg;
  struct HeroCfg enemyTowerCfg;
  int32_t trollBtnRsrcId;
  int32_t trollBtnEnemyRsrcId;
  
};


#endif 