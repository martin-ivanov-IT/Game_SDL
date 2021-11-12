#include "Game/Entities/Tower.h"

int32_t initTower (Tower* self,const struct HeroBaseCfg* cfg, struct Point* pos, PlayerType playerType){

    initBase(self, cfg, pos, playerType);
    self->health = 500;
}