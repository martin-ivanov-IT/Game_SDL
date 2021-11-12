#ifndef GAME_HEROBASE_H_
#define GAME_HEROBASE_H_
#include <stdint.h>
#include "manager_utils/drawing/Image.h"
struct HeroBaseCfg{
    int32_t rsrcId;
    int32_t health;
    bool isAlive;
    HeroType heroType;
};

typedef enum PlayerType{
    ENEMY,
    PLAYER,
}PlayerType;

typedef enum HeroType{
    TROLL,
}HeroType;
struct HeroBase{
    struct Image heroImg;
    int32_t rsrcId;
    int32_t health;
    int32_t heroChangeAnimTimerId;
    PlayerType playerType;
    bool isAlive;
    HeroType heroType;
    int32_t (*init_func)(struct HeroBase* self,const struct HeroCfg* cfg, struct Point* pos);
    void (*deinit_func)(struct HeroBase* self);
    void (*draw_func)(struct HeroBase* self);
    void (*takeDamage_func)(struct HeroBase* self, int32_t damage); 
};

int32_t initBase (struct HeroBase* self,const struct HeroBaseCfg* cfg, struct Point* pos, PlayerType playerType);
#endif
// int32_t takeDamage(struct HeroBase* self, int32_t damage)
// void handleEventHero (struct Hero* self, struct InputEvent* e);
// int32_t initHero(struct Hero* self,const struct HeroCfg* cfg, struct Point* pos);
// void deinitHero(struct Hero* self);
// void drawHero(struct Hero* self);
// void startAnim(struct Hero* self);
// int32_t produceDamage(struct Hero* self);
// int32_t takeDamage(struct Hero* self, int32_t damage);
// void setModeAtackHero(struct Hero* self);
// void setModeIdleHero(struct Hero* self);
// void setModeHurtHero(struct Hero* self);
// void setModeRunHero(struct Hero* self);
// void setModeDieHero(struct Hero* self);
// int32_t initTower(struct Hero* self, const struct HeroCfg* cfg);