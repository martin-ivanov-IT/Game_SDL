#ifndef GAME_BATTLEFIELD_H_
#define GAME_BATTLEFIELD_H_
#include "utils/containers/Vector.h"

struct Battlefield{
    struct Vector playerArmy;
    struct Vector enemyArmy;
};

void initBattlefield(struct Battlefield* self);
void deinitBattlefield(struct Battlefield* self);
void battle(struct Battlefield* self);
void startBattle(struct Battlefield* self, int* playerMoney, int* playerXp);
#endif