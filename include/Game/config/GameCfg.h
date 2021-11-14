#ifndef GAME_GAMECFG_H_
#define GAME_GAMECFG_H_

#include <stdint.h>

#include "Game/Entities/Hero.h"
#include "Game/Entities/Terrorist.h"
#include "Game/Entities/Robot.h"

typedef enum{
  STONE_AGE = 0,
  PRESENT = 400,
  FUTURE = 800,
}Epoch;

struct GameConfig {

  struct HeroCfg troll_1Cfg;
  struct HeroCfg troll_2Cfg;
  struct HeroCfg troll_3Cfg;

  struct TerroristCfg terrorist_1_Cfg;
  struct TerroristCfg terrorist_2_Cfg;
  struct TerroristCfg terrorist_3_Cfg;

  RobotCfg robot_1_Cfg;
  RobotCfg robot_2_Cfg;
  RobotCfg robot_3_Cfg;

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

  int32_t robotBtnRsrcId;
  int32_t robot2BtnRsrcId;
  int32_t robot3BtnRsrcId;

  int32_t robotBtnEnemyRsrcId;
  int32_t robot2BtnEnemyRsrcId;
  int32_t robot3BtnEnemyRsrcId;

  int32_t startGameBtnRsrcId;

  bool gameStarted;

  int32_t starBtnRsrcId;

  Epoch epoch;
  int32_t playerXp;
  int32_t enemyrXp;

  int32_t playerMoney;
  
};


#endif 