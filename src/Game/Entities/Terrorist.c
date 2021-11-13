#include "Game/Entities/Terrorist.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/ContainerOf.h"
#include "utils/Log.h"
#include "common/CommonDefines.h"

static void setModelongAtackHero(struct Terrorist* self);

int32_t initTerrorist (struct HeroBase* heroBase,const struct TerroristCfg* cfg, struct Point* pos, PlayerType playerType){
    initHero(heroBase, &cfg->heroCfg, pos, playerType);
    struct Hero* hero = container_of(heroBase, struct Hero, base);
    struct Terrorist* self = container_of(hero, struct Terrorist, hero);
    self->longAtackDamage = cfg->longAtackDamage;
    createImage(&self->longAtackDamage, cfg->longAtackRsrcId, pos);
    if(self->hero.base.playerType == ENEMY){
        self->heroLongAtackImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
    }
    self->setModeLongAtackHero_func = setModelongAtackHero;
}
static void setModelongAtackHero(struct Terrorist* self){
    self->hero.isMovingHor = false;
    self->heroLongAtackImg.widget.drawParams.pos.x = self->hero.base.heroImg.widget.drawParams.pos.x;
    self->heroLongAtackImg.widget.drawParams.pos.y = self->hero.base.heroImg.widget.drawParams.pos.y;
    self->hero.base.heroImg = self->heroLongAtackImg;
    self->hero.mode = ATACK;
}
