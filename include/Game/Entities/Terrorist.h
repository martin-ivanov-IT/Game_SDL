#ifndef GAME_TERRORIST_H_
#define GAME_TERRORIST_H_

#include <stdint.h>
#include "manager_utils/drawing/Image.h"
#include "manager_utils/time/TimerClient.h"
#include "Game/Entities/Hero.h"
struct TerroristCfg{
    struct HeroCfg heroCfg;
    int32_t longAtackDamage;
    int32_t longAtackRsrcId;
};
struct Terrorist{
    struct Hero hero;
    int32_t longAtackDamage;
    struct Image heroLongAtackImg;
    void (*setModeLongAtackHero_func)(struct Terrorist* self);

};
int32_t initTerrorist (struct HeroBase* base,const struct TerroristCfg* cfg, struct Point* pos, PlayerType playerType);

#endif