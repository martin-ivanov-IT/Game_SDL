#ifndef GAME_HERO_H_
#define GAME_HERO_H_

#include <stdint.h>
#include "manager_utils/drawing/Image.h"

struct InputEvent;
struct HeroCfg{
    int32_t rsrcId;
};
struct Hero{
    struct Image heroImg;
};
void handleEventHero (struct Hero* self, struct InputEvent* e);
int32_t initHero(struct Hero* self, int32_t rsrcId);
void deinitHero(struct Hero* self);
void drawHero(struct Hero* self);
#endif