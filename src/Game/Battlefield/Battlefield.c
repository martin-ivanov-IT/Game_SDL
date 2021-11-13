#include "Game/Battlefield/Battlefield.h"
#include "Game/Entities/Hero.h"


#include "common/CommonDefines.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "utils/ContainerOf.h"

#include "manager_utils/drawing/Widget.h"

static const int32_t FIRST_PLAYER_ENEMY_IDX = 1;

void initBattlefield(struct Battlefield* self){
      initVectorHero(&self->playerArmy, 10);
      initVectorHero(&self->enemyArmy, 10);
}
void deinitBattlefield(struct Battlefield* self){
    UNUSED(self);
}
static bool meetHeros(struct HeroBase* firstPlayer, struct HeroBase* secondPlayer){
    if(!firstPlayer || !secondPlayer){
        return false;
    }
    struct Point pointFirst = {.x = firstPlayer->heroImg.widget.drawParams.pos.x, .y = firstPlayer->heroImg.widget.drawParams.pos.y};
    
    return containsPointWidget(&secondPlayer->heroImg.widget, &pointFirst);
}

void startBattle(struct Battlefield* self){
    struct Hero* firstPlayer =
     container_of(getElementVectorHero(&self->playerArmy, FIRST_PLAYER_ENEMY_IDX), struct Hero, base);
    
    struct Hero* firstEnemy =
     container_of(getElementVectorHero(&self->enemyArmy, FIRST_PLAYER_ENEMY_IDX), struct Hero, base);

    struct HeroBase* enemyTower = getElementVectorHero(&self->enemyArmy, 0);
    struct HeroBase* playerTower = getElementVectorHero(&self->playerArmy, 0);
    
    if(firstPlayer){
        LOGY("first player x: %d rsrcId%d", firstPlayer->base.heroImg.widget.drawParams.pos.x, firstPlayer->base.playerType);
        LOGY("enemy tower x: %d", enemyTower->heroImg.widget.drawParams.pos.x);
    }

    if(firstEnemy){
        LOGY("firstEnemy x: %d rsrcId%d", firstEnemy->base.heroImg.widget.drawParams.pos.x, firstEnemy->base.playerType);
        LOGY("enemy tower x: %d", enemyTower->heroImg.widget.drawParams.pos.x);
    }
    

    if(firstPlayer == NULL && firstEnemy){
        if(meetHeros(&firstEnemy->base, playerTower)){
            for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVectorHero(&self->enemyArmy); i++){
                struct Hero* currHero =
                    container_of(getElementVectorHero(&self->enemyArmy, i), struct Hero, base);
                    if(meetHeros(&currHero->base,playerTower )){
                        if(currHero->mode != ATACK){
                            currHero->setModeAtackHero_func(currHero);
                        }
                    }
                    else {
                        if(currHero->mode != RUN){
                            currHero->setModeRunHero_func(currHero);
                        }
                    }
                    if(currHero->mode == ATACK && currHero->base.heroImg.currFrame == 9){
                        currHero->base.heroImg.currFrame = 1;
                        int32_t damage = currHero->produceDamage_func(currHero);
                        LOGY("player towedamage taken")
                        playerTower->takeDamage_func(playerTower, damage);
                    }
                }
            }
    }

    if(firstEnemy == NULL && firstPlayer){
        struct HeroBase towerCopy = {
            .heroImg.widget.drawParams.pos.x = enemyTower->heroImg.widget.drawParams.pos.x -120,
            .heroImg.widget.drawParams.pos.y = enemyTower->heroImg.widget.drawParams.pos.y,
            .heroImg.widget.drawParams.width = enemyTower->heroImg.widget.drawParams.width,
            .heroImg.widget.drawParams.height = enemyTower->heroImg.widget.drawParams.height,
            };
        if(meetHeros(&firstPlayer->base, &towerCopy)){
            for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVectorHero(&self->playerArmy); i++){
                    struct Hero* currHero =
                        container_of(getElementVectorHero(&self->playerArmy, i), struct Hero, base);
                    // struct Point pointFirst = {.x = enemyTower->heroImg.widget.drawParams.pos.x -150, .y = currHero->base.heroImg.widget.drawParams.pos.y};
                    if(meetHeros(&currHero->base, &towerCopy)){
                        if(currHero->mode != ATACK){
                            currHero->setModeAtackHero_func(currHero);
                        }
                    }
                    else {
                        if(currHero->mode != RUN){
                            currHero->setModeRunHero_func(currHero);
                        }
                    }
                    if(currHero->mode == ATACK && currHero->base.heroImg.currFrame == 9){
                        currHero->base.heroImg.currFrame = 1;
                        int32_t damage = currHero->produceDamage_func(currHero);
                        LOGY("player towedamage taken")
                        enemyTower->takeDamage_func(enemyTower, damage);
                    }
                }
            }
    }

    if(firstPlayer == NULL || firstEnemy == NULL){
        return;
    }
    
    for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVectorHero(&self->playerArmy); i++)
    {
        struct Hero* currHero =
                        container_of(getElementVectorHero(&self->playerArmy, i), struct Hero, base);

        if(meetHeros(&firstPlayer->base, &currHero->base)){
            if(firstPlayer->mode != RUN){
                LOGY("meet teammate player");
                currHero->setModeIdleHero_func(currHero);
                // currHero->base.heroImg.widget.drawParams.pos.x = firstPlayer->base.heroImg.widget.drawParams.pos.x - 15;

            }
        }
    }

    for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVectorHero(&self->enemyArmy); i++)
    {   
        struct Hero* currHero =
                        container_of(getElementVectorHero(&self->enemyArmy, i), struct Hero, base);

        if(meetHeros(&firstEnemy->base,  &currHero->base)){
            
            if(firstEnemy->mode != RUN){
                LOGY("enemeies met")
                currHero->setModeIdleHero_func(currHero);
                // currHero->base.heroImg.widget.drawParams.pos.x = firstEnemy->base.heroImg.widget.drawParams.pos.x +15;
            }
        }
    }

    if(meetHeros(&firstEnemy->base, &firstPlayer->base)){
        
        if(firstPlayer->mode == RUN){
            firstPlayer->setModeAtackHero_func(firstPlayer);
        }

        if(firstEnemy->mode == RUN){
            firstEnemy->setModeAtackHero_func(firstEnemy);
        }

        if(firstPlayer->base.heroImg.currFrame == 9){
            firstPlayer->base.heroImg.currFrame = 1;
            int32_t damage = firstPlayer->produceDamage_func(firstPlayer);
            LOGY("damage taken")
            firstEnemy->base.takeDamage_func(&firstEnemy->base, damage);
        }

        if(firstEnemy->base.heroImg.currFrame == 9){
            firstEnemy->base.heroImg.currFrame = 1;
            int32_t damage = firstPlayer->produceDamage_func(firstEnemy);
            LOGY("damage taken")
            firstEnemy->base.takeDamage_func(&firstPlayer->base, damage);
        }

        if(!firstPlayer->base.isAlive){
            LOGY("firstPlayer taken")
            stopTimer(firstPlayer->moveTimerId);
            stopTimer(firstPlayer->spriteTimerId);
            
            firstPlayer->base.deinit_func(&firstPlayer->base);         
            deleteElementVectorHero(&self->playerArmy, FIRST_PLAYER_ENEMY_IDX);

            firstPlayer = NULL;

            if(firstEnemy){
                firstEnemy->setModeRunHero_func(firstEnemy);
            }
        }

        if(!firstEnemy->base.isAlive){
            LOGY("firstEnemy taken")
            
            stopTimer(firstEnemy->moveTimerId);
            stopTimer(firstEnemy->spriteTimerId);

            firstEnemy->base.deinit_func(&firstEnemy->base);            
            deleteElementVectorHero(&self->enemyArmy, FIRST_PLAYER_ENEMY_IDX);
            firstEnemy = NULL;
            if(firstPlayer){
                firstPlayer->setModeRunHero_func(firstPlayer);
            }

        }
    }

    if(!meetHeros(&firstEnemy->base, &firstPlayer->base)) {
        if(firstPlayer && firstPlayer->mode != RUN){
            firstPlayer->setModeRunHero_func(firstPlayer);
        }

        if(firstEnemy && firstEnemy->mode != RUN){
            firstEnemy->setModeRunHero_func(firstEnemy);
        }
    }

        if(firstPlayer && firstPlayer->mode == RUN){
            for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVectorHero(&self->playerArmy); i++)
            {
                struct Hero* currHero =
                    container_of(getElementVectorHero(&self->playerArmy, i), struct Hero, base);
                if(currHero->mode != RUN){
                    currHero->setModeRunHero_func(currHero);
                }
            }
        }

        if(firstEnemy && firstEnemy->mode == RUN){
            for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVectorHero(&self->enemyArmy); i++)
            {   
                struct Hero* currHero =
                    container_of(getElementVectorHero(&self->enemyArmy, i), struct Hero, base);
                if(currHero->mode != RUN){
                    currHero->setModeRunHero_func(currHero);
                }
            }
        }
}
