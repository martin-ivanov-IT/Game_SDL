#ifndef GAME_ISLAND_BOY_H_
#define GAME_ISLAND_BOY_H_
#include "Game/Entities/Hero.h"
#include "manager_utils/drawing/Image.h"
#include "manager_utils/time/TimerClient.h"


struct InputEvent;

struct Island_BoyCfg{
    struct HeroCfg;
};

struct Island_Boy
{
    struct Hero;
};
void handleEventIslandBoy (struct Hero* self, struct InputEvent* e);
int32_t initIslandBoy(struct Hero* self,const struct HeroCfg* cfg);
void deinitIslandBoy(struct Hero* self);
void drawIslandBoy(struct Hero* self);
void startAnim(struct Hero* self);

#endif