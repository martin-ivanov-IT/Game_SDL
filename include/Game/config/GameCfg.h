#ifndef GAME_GAMECFG_H_
#define GAME_GAMECFG_H_

#include <stdint.h>

#include "Game/Entities/Hero.h"


struct GameConfig {

  struct HeroCfg troll_1Cfg;
  struct HeroCfg troll_2Cfg;
  struct HeroBaseCfg playerTowerCfg;
  struct HeroBaseCfg enemyTowerCfg;

  int32_t trollBtnRsrcId;
  int32_t troll2BtnRsrcId;
  int32_t trollBtnEnemyRsrcId;
  int32_t troll2BtnEnemyRsrcId;
  
};


#endif 