#include "Game/Entities/HeroBase.h"
struct HeroBaseCfg{
    int32_t rsrcId;
    int32_t health;
    bool isAlive;
    HeroType heroType;
};

int32_t initBase (struct HeroBase* self,const struct HeroBaseCfg* cfg, struct Point* pos, PlayerType playerType){
    self->playerType = playerType;
    self->rsrcId = cfg->rsrcId;
    self->health = cfg->health;
    self->isAlive = cfg->isAlive;
    self->heroType = cfg->heroType;
    self->draw_func = draw;
    self->takeDamage_func = takeDamage;
    self->deinit_func = deinit;
}

static void draw(struct HeroBase* self){
    drawImage(&self->heroImg);
}

static int32_t takeDamage(struct HeroBase* self, int32_t damage){
    self->health -= damage;
    if (self->health < 0){
        self->isAlive = false;
    }
}
static void deinit(struct HeroBase* self){
 destroyImage(&self->heroImg);
}
