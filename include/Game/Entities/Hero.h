#ifndef GAME_HERO_H_
#define GAME_HERO_H_

#include <stdint.h>
#include "manager_utils/drawing/Image.h"
#include "manager_utils/time/TimerClient.h"


struct InputEvent;
typedef enum PlayerType{
    ENEMY,
    PLAYER,
}PlayerType;
struct HeroCfg{
    int32_t rsrcId;
    int32_t heroChangeAnimTimerId;
    int32_t heroMoveTimerId;
    int32_t horSteps;
    int32_t verSteps;
    int32_t deltaMovePx;
};
struct Hero{
    struct TimerClient TimerClient;
    struct Image heroImg;
    struct Image heroRunImg;
    struct Image heroAtackImg;
    struct Image heroHurtImg;
    struct Image heroDieImg;
    struct HeroCfg heroCfg;
    PlayerType playerType;
    int32_t currAnimStep;
    bool isMovingHor;
    bool isMovingRight;
    bool isMovingUp;
};
void handleEventHero (struct Hero* self, struct InputEvent* e);
int32_t initHero(struct Hero* self,const struct HeroCfg* cfg);
void deinitHero(struct Hero* self);
void drawHero(struct Hero* self);
void startAnim(struct Hero* self);
#endif