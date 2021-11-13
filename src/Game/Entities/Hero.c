#include "Game/Entities/Hero.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/ContainerOf.h"
#include "utils/Log.h"
#include "common/CommonDefines.h"

static void deinit(struct HeroBase* heroBase);
static void startAnim(struct Hero* self);
static int32_t produceDamage(struct Hero* self);
static void setModeAtackHero(struct Hero* self);
static void setModeIdleHero(struct Hero* self);
static void setModeHurtHero(struct Hero* self);
void setModeRunHero(struct Hero* self);
void setModeDieHero(struct Hero* self);

void handleEventHero (struct Hero* self, struct InputEvent* e){
    UNUSED(self);
    UNUSED(e);

}
static void processSpriteAnim(struct Hero* self){
    setNextFrameImage(&self->base.heroImg);
}

static void processMoveAnim(struct Hero* self){
    if(!self->isMovingHor){
        return;
    }
    if(self->base.playerType == PLAYER){
        self->currAnimStep++;
        moveRight(&self->base.heroImg.widget, self->deltaMovePx);

    }

    else if(self->base.playerType == ENEMY){
        self->currAnimStep++;
        moveLeft(&self->base.heroImg.widget, self->deltaMovePx);
    }
}

static void onTimerTimeout(void* proxy, int32_t timerId){
    struct Hero* self = (struct Hero*) proxy;
    if (timerId == self->spriteTimerId)
    {
        processSpriteAnim(self);
    }

    else if (timerId == self->moveTimerId)
    {
        processMoveAnim(self);
    }

    else{
        LOGERR("Recieved unsuported timer id: %d", timerId);
    }
    
}
int32_t initHero (struct HeroBase* heroBase,const struct HeroCfg* cfg, struct Point* pos, PlayerType playerType){
    initBase(heroBase, &cfg->baseCfg, pos, playerType); 
    struct Hero* self = container_of(heroBase, struct Hero, base);
    heroBase->deinit_func = deinit;

    self->setModeAtackHero_func = setModeAtackHero;
    self->setModeDieHero_func = setModeDieHero;
    self->setModeHurtHero_func = setModeHurtHero;
    self->setModeIdleHero_func = setModeIdleHero;
    self->setModeRunHero_func = setModeRunHero;
    self->startAnim_func = startAnim;
    self->produceDamage_func = produceDamage;
    
    createImage(&self->heroRunImg, cfg->runRsrcId, pos);
    createImage(&self->heroDieImg, cfg->dieRsrcId, pos);
    createImage(&self->heroHurtImg, cfg->hurtRsrcId, pos);
    createImage(&self->heroIdleImg, cfg->idleRsrcId, pos);
    createImage(&self->heroAtackImg, cfg->atackRsrcId, pos);

    if(self->base.playerType == ENEMY){
        self->heroRunImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        self->heroDieImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        self->heroHurtImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        self->heroAtackImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        self->heroIdleImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        self->base.heroImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;

    }
    self->base.heroImg = self->heroRunImg;
    self->currAnimStep = 0;
    self->isMovingHor = true;
    self->mode = cfg->mode;
    self->base.health = cfg->baseCfg.health;
    self->atackDamage = cfg->atackDamage;
    self->deltaMovePx = cfg->deltaMovePx;

    createTimer(&self->TimerClient, self, onTimerTimeout);

    return SUCCESS;
}

static void deinit(struct HeroBase* heroBase){
    struct Hero* self = container_of(heroBase, struct Hero, base);
    destroyImage(&self->base.heroImg);
    destroyImage(&self->heroHurtImg);
    destroyImage(&self->heroDieImg);
    destroyImage(&self->heroRunImg);
    destroyImage(&self->heroAtackImg);
    destroyImage(&self->heroIdleImg);
}

static void startAnim(struct Hero* self){

    startTimer(&self->TimerClient, 100, self->spriteTimerId, PULSE_TIMER);
    startTimer(&self->TimerClient, 100, self->moveTimerId, PULSE_TIMER);
}

static int32_t produceDamage(struct Hero* self){
    return self->atackDamage;
}

static void setModeAtackHero(struct Hero* self){
    self->isMovingHor = false;
    self->heroAtackImg.widget.drawParams.pos.x = self->base.heroImg.widget.drawParams.pos.x;
    self->heroAtackImg.widget.drawParams.pos.y = self->base.heroImg.widget.drawParams.pos.y;
    self->base.heroImg = self->heroAtackImg;
    self->mode = ATACK;
}

static void setModeIdleHero(struct Hero* self){
    self->isMovingHor = false;
    self->heroIdleImg.widget.drawParams.pos.x = self->base.heroImg.widget.drawParams.pos.x;
    self->heroIdleImg.widget.drawParams.pos.y = self->base.heroImg.widget.drawParams.pos.y;
    self->base.heroImg = self->heroIdleImg;
    self->mode = IDLE;
}

static void setModeHurtHero(struct Hero* self){
    self->isMovingHor = false;
    self->heroHurtImg.widget.drawParams.pos.x = self->base.heroImg.widget.drawParams.pos.x;
    self->heroHurtImg.widget.drawParams.pos.y = self->base.heroImg.widget.drawParams.pos.y;
    self->base.heroImg = self->heroHurtImg;
    self->mode = HURT;
}

void setModeRunHero(struct Hero* self){
    self->isMovingHor = true;
    self->heroRunImg.widget.drawParams.pos.x = self->base.heroImg.widget.drawParams.pos.x;
    self->heroRunImg.widget.drawParams.pos.y = self->base.heroImg.widget.drawParams.pos.y;
    self->base.heroImg = self->heroRunImg;
    self->mode = RUN;
}

void setModeDieHero(struct Hero* self){
    self->isMovingHor = true;
    self->heroDieImg.widget.drawParams.pos.x = self->base.heroImg.widget.drawParams.pos.x;
    self->heroDieImg.widget.drawParams.pos.y = self->base.heroImg.widget.drawParams.pos.y;
    self->base.heroImg = self->heroDieImg;
    self->mode = DIE;
}