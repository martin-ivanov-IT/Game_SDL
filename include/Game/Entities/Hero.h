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


typedef enum HeroDefines{
    HERO_PLAYER_START_X = 620,
    TROLL_START_Y = 450,
    HERO_ENEMY_START_X = -300,

}HeroDefines;


struct HeroCfg{
    struct HeroBaseCfg baseCfg;
    int32_t runRsrcId;
    int32_t atackRsrcId;
    int32_t dieRsrcId;
    int32_t idleRsrcId;
    int32_t hurtRsrcId;
    enum HeroMode mode;
    int32_t atackDamage;
    int32_t deltaMovePx;

};

struct Hero{
    struct HeroBase base;
    struct TimerClient TimerClient;
    
    int32_t moveTimerId;
    int32_t spriteTimerId;

    struct Image heroRunImg;
    struct Image heroAtackImg;
    struct Image heroHurtImg;
    struct Image heroDieImg;
    struct Image heroIdleImg;

    int32_t atackDamage;
    enum HeroMode mode;

    int32_t currAnimStep;
    int32_t deltaMovePx;
    bool isMovingHor;

    int32_t (*produceDamage_func)(struct Hero* self);
    void (*setModeAtackHero_func)(struct Hero* self);
    void (*setModeIdleHero_func)(struct Hero* self);
    void (*setModeHurtHero_func)(struct Hero* self);
    void (*setModeRunHero_func)(struct Hero* self);
    void (*setModeDieHero_func)(struct Hero* self);
    void (*startAnim_func)(struct Hero* self);

};
void handleEventHero (struct Hero* self, struct InputEvent* e);
int32_t initHero (struct HeroBase* base,const struct HeroCfg* cfg, struct Point* pos, PlayerType playerType);

#endif