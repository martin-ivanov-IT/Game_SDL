#ifndef GAME_HERO_H_
#define GAME_HERO_H_

#include <stdint.h>
#include "manager_utils/drawing/Image.h"
#include "manager_utils/time/TimerClient.h"
#include "Game/Entities/HeroBase.h"


struct InputEvent;


typedef enum HeroMode{
    RUN,
    ATACK,
    HURT,
    DIE,
    IDLE,
}HeroMode;

typedef enum HeroType{
    HERO,
    TOWER,
}HeroType;


struct HeroCfg{
    
    int32_t rsrcId;
    int32_t runRsrcId;
    int32_t atackRsrcId;
    int32_t dieRsrcId;
    int32_t idleRsrcId;
    int32_t hurtRsrcId;

    enum HeroMode mode;

    int32_t health;
    int32_t atackDamage;
    
    int32_t heroChangeAnimTimerId;
    int32_t heroMoveTimerId;
    int32_t horSteps;
    int32_t verSteps;
    int32_t deltaMovePx;

    PlayerType playerType;
};


struct Hero{
    struct TimerClient TimerClient;
    
    int32_t moveTimerId;
    int32_t spriteTimerId;

    struct Image heroImg;
    struct Image heroRunImg;
    struct Image heroAtackImg;
    struct Image heroHurtImg;
    struct Image heroDieImg;
    struct Image heroIdleImg;
    struct HeroCfg heroCfg;
    int32_t health;
    int32_t atackDamage;
    bool isAlive;
    PlayerType playerType;
    HeroType heroType;
    enum HeroMode mode;
    int32_t currAnimStep;
    bool isMovingHor;
    bool isMovingRight;
    bool isMovingUp;
};
void handleEventHero (struct Hero* self, struct InputEvent* e);
int32_t initHero(struct Hero* self,const struct HeroCfg* cfg, struct Point* pos);
void deinitHero(struct Hero* self);
void drawHero(struct Hero* self);
void startAnim(struct Hero* self);
int32_t produceDamage(struct Hero* self);
int32_t takeDamage(struct Hero* self, int32_t damage);
void setModeAtackHero(struct Hero* self);
void setModeIdleHero(struct Hero* self);
void setModeHurtHero(struct Hero* self);
void setModeRunHero(struct Hero* self);
void setModeDieHero(struct Hero* self);
int32_t initTower(struct Hero* self, const struct HeroCfg* cfg);
#endif