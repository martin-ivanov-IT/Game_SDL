#ifndef GAME_TROLL1_H_
#define GAME_TROLL1_H_
#include "Game/Entities/Hero.h"

#include "utils/ErrorCodes.h"
#include "utils/ContainerOf.h"
#include "utils/Log.h"
#include "common/CommonDefines.h"


typedef struct Hero Troll_1;
int32_t initTroll_1 (struct HeroBase* base,const struct HeroCfg* cfg, struct Point* pos, PlayerType playerType);


#endif