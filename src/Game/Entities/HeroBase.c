#include "Game/Entities/HeroBase.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "include/containers/VectorHero.h"
#include <stdlib.h>


static void draw(struct HeroBase* self);
static void takeDamage(struct HeroBase* self, int32_t damage);
static void deinit(struct HeroBase* self);

int32_t initBase (struct HeroBase* self,const struct HeroBaseCfg* cfg, struct Point* pos, PlayerType playerType){
    self->playerType = playerType;
    self->rsrcId = cfg->rsrcId;
    self->health = cfg->health;
    self->isAlive = cfg->isAlive;
    self->heroType = cfg->heroType;
    self->draw_func = draw;
    self->takeDamage_func = takeDamage;
    self->deinit_func = deinit;
    createImage(&self->heroImg, cfg->rsrcId, pos);
    return SUCCESS;

}

static void draw(struct HeroBase* self){
    drawImage(&self->heroImg);
}

static void takeDamage(struct HeroBase* self, int32_t damage){
    self->health -= damage;
    if (self->health < 0){
        self->isAlive = false;
    }
}
static void deinit(struct HeroBase* self){
    UNUSED(self);
}
