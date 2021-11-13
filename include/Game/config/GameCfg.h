#ifndef GAME_GAMECFG_H_
#define GAME_GAMECFG_H_

#include <stdint.h>

#include "Game/Entities/Hero.h"
#include "Game/Entities/Terrorist.h"

typedef enum{
  STONE_AGE,
  PRESENT,
  FUTURE,
}Epoch;

struct GameConfig {

  struct HeroCfg troll_1Cfg;
  struct HeroCfg troll_2Cfg;
  struct HeroCfg troll_3Cfg;

  struct TerroristCfg terrorist_1_Cfg;

  struct HeroBaseCfg playerTowerCfg;
  struct HeroBaseCfg enemyTowerCfg;

  int32_t trollBtnRsrcId;
  int32_t troll2BtnRsrcId;
  int32_t troll3BtnRsrcId;

  int32_t trollBtnEnemyRsrcId;
  int32_t troll2BtnEnemyRsrcId;
  int32_t troll3BtnEnemyRsrcId;

  int32_t terroristBtnRsrcId;
  int32_t terrorist2BtnRsrcId;
  int32_t terrorist3BtnRsrcId;

  int32_t terroristBtnEnemyRsrcId;
  int32_t terrorist2BtnEnemyRsrcId;
  int32_t terrorist3BtnEnemyRsrcId;

  int32_t starBtnRsrcId;
  Epoch epoch;
  int32_t playerXp;
  int32_t playerMoney;
  
};


#endif 