#include "Game/Entities/Hero.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "common/CommonDefines.h"

void handleEventHero (struct Hero* self, struct InputEvent* e){
    UNUSED(self);
    UNUSED(e);

}
static void processSpriteAnim(struct Hero* self){
    setNextFrameImage(&self->heroImg);
}

static void processMoveAnim(struct Hero* self){
    if(!self->isMovingHor){
        return;
    }
    if(self->playerType == PLAYER){
        self->currAnimStep++;
        moveRight(&self->heroImg.widget, self->heroCfg.deltaMovePx);

    }

    else if(self->playerType == ENEMY){
        self->currAnimStep++;
        moveLeft(&self->heroImg.widget, self->heroCfg.deltaMovePx);
    }
}

static void onTimerTimeout(void* proxy, int32_t timerId){
    struct Hero* self = (struct Hero*) proxy;
    if (timerId == self->heroCfg.heroChangeAnimTimerId)
    {
        processSpriteAnim(self);
    }

    else if (timerId == self->heroCfg.heroMoveTimerId)
    {
        processMoveAnim(self);
    }

    else{
        LOGERR("Recieved unsuported timer id: %d", timerId);
    }
    
}
int32_t initHero (struct Hero* self,const struct HeroCfg* cfg, struct Point* pos){
    self->heroCfg = *cfg;

    struct Point widgetPos = *pos;
    createImage(&self->heroRunImg, cfg->runRsrcId, &widgetPos);
    createImage(&self->heroDieImg, cfg->dieRsrcId, &widgetPos);
    createImage(&self->heroHurtImg, cfg->hurtRsrcId, &widgetPos);
    createImage(&self->heroIdleImg, cfg->idleRsrcId, &widgetPos);
    createImage(&self->heroAtackImg, cfg->atackRsrcId, &widgetPos);

    if(self->playerType == ENEMY){
        self->heroRunImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        self->heroDieImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        self->heroHurtImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        self->heroAtackImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        self->heroIdleImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
        self->heroImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;

    }

    // createImage(&self->heroImg, cfg->rsrcId, &widgetPos);
    self->heroImg = self->heroRunImg;

    self->currAnimStep = 0;
    self->isMovingHor = true;
    self->isMovingRight = true;
    self->isMovingUp = true;
    self->mode = cfg->mode;
    self->health = cfg->health;
    self->atackDamage = cfg->atackDamage;
    self->isAlive = true;
    self->heroType = HERO;
    
    createTimer(&self->TimerClient, self, onTimerTimeout);
    return SUCCESS;
}

int32_t initTower(struct Hero* self, const struct HeroCfg* cfg){
    self->heroCfg = *cfg;
    self->heroType = cfg->playerType;
    self->isAlive = true;
    self->health = cfg->health;


    struct Point widgetPos = { .x = 0, .y = 150 };
    if(cfg->playerType == ENEMY){
        widgetPos.x = 2400;
        widgetPos.y = 150;
    }
    createImage(&self->heroImg, cfg->rsrcId, &widgetPos);
    
    
    return SUCCESS;

}

void deinitHero(struct Hero* self){
 destroyImage(&self->heroImg);
}

void drawHero(struct Hero* self){
    drawImage(&self->heroImg);
}

void startAnim(struct Hero* self){
    startTimer(&self->TimerClient, 100, self->heroCfg.heroChangeAnimTimerId, PULSE_TIMER);
    startTimer(&self->TimerClient, 100, self->heroCfg.heroMoveTimerId, PULSE_TIMER);
}

int32_t produceDamage(struct Hero* self){
    return self->atackDamage;
}

int32_t takeDamage(struct Hero* self, int32_t damage){
    self->health -= damage;
    if (self->health < 0){
        self->isAlive = false;
    }
    return self->atackDamage;
}

void setModeAtackHero(struct Hero* self){
    self->isMovingHor = false;
    self->heroAtackImg.widget.drawParams.pos.x = self->heroImg.widget.drawParams.pos.x;
    self->heroAtackImg.widget.drawParams.pos.y = self->heroImg.widget.drawParams.pos.y;
    self->heroImg = self->heroAtackImg;
    self->mode = ATACK;
}

void setModeIdleHero(struct Hero* self){
    self->isMovingHor = false;
    self->heroIdleImg.widget.drawParams.pos.x = self->heroImg.widget.drawParams.pos.x;
    self->heroIdleImg.widget.drawParams.pos.y = self->heroImg.widget.drawParams.pos.y;
    self->heroImg = self->heroIdleImg;
    self->mode = IDLE;
}

void setModeHurtHero(struct Hero* self){
    self->isMovingHor = false;
    self->heroHurtImg.widget.drawParams.pos.x = self->heroImg.widget.drawParams.pos.x;
    self->heroHurtImg.widget.drawParams.pos.y = self->heroImg.widget.drawParams.pos.y;
    self->heroImg = self->heroHurtImg;
    self->mode = HURT;
}

void setModeRunHero(struct Hero* self){
    self->isMovingHor = true;
    self->heroRunImg.widget.drawParams.pos.x = self->heroImg.widget.drawParams.pos.x;
    self->heroRunImg.widget.drawParams.pos.y = self->heroImg.widget.drawParams.pos.y;
    self->heroImg = self->heroRunImg;
    self->mode = RUN;
}

void setModeDieHero(struct Hero* self){
    self->isMovingHor = true;
    self->heroDieImg.widget.drawParams.pos.x = self->heroImg.widget.drawParams.pos.x;
    self->heroDieImg.widget.drawParams.pos.y = self->heroImg.widget.drawParams.pos.y;
    self->heroImg = self->heroDieImg;
    self->mode = DIE;
}