#ifndef GAME_BATTLEFIELD_H_
#define GAME_BATTLEFIELD_H_
#include "include/containers/VectorHero.h"

struct Battlefield{
    struct VectorHero playerArmy;
    struct VectorHero enemyArmy;
};

void initBattlefield(struct Battlefield* self);
void deinitBattlefield(struct Battlefield* self);
void battle(struct Battlefield* self);
void startBattle(struct Battlefield* self);
#endif