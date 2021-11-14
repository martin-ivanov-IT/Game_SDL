#include "Game/Battlefield/Battlefield.h"
#include "Game/Entities/Hero.h"

#include "common/CommonDefines.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

#include "manager_utils/drawing/Widget.h"
#include "Game/Entities/Troll.h"
#include "Game/Entities/Robot.h"
#include <stdlib.h>



static const int32_t FIRST_PLAYER_ENEMY_IDX = 1;

void initBattlefield(struct Battlefield* self){
      initVector(&self->playerArmy, 10);
      initVector(&self->enemyArmy, 10);
}
void deinitBattlefield(struct Battlefield* self){
    int32_t enemyArmySize = self->enemyArmy.size;
    for (int32_t i = FIRST_PLAYER_ENEMY_IDX; i < enemyArmySize; i++)
    {
        free(getElementVector(&self->enemyArmy, i));
    }
    
    int32_t playerArmySize = self->playerArmy.size;
    for (int32_t i = FIRST_PLAYER_ENEMY_IDX; i < playerArmySize; i++)
    {   
        if(getElementVector(&self->playerArmy, i)){
            free(getElementVector(&self->playerArmy, i));
        }
    }
    freeVector(&self->playerArmy);
    freeVector(&self->enemyArmy);

    
}
// void battle(struct Battlefield* self){
//     struct Hero* firstPlayer =
//      container_of(getElementVector(&self->playerArmy, FIRST_PLAYER_ENEMY_IDX), struct Hero, base);
    
//     struct Hero* firstEnemy =
//      container_of(getElementVector(&self->enemyArmy, FIRST_PLAYER_ENEMY_IDX), struct Hero, base);
//     struct HeroBase* enemyTower = getElementVector(&self->enemyArmy, 0);
//     struct HeroBase* playerTower = getElementVector(&self->playerArmy, 0);

//      if(firstPlayer == NULL && firstEnemy){
//          if(meetHeros(&firstEnemy->base, playerTower){

//          }
//      }

// }
static bool meetHeros(struct HeroBase* firstPlayer, struct HeroBase* secondPlayer){
    if(!firstPlayer || !secondPlayer){
        return false;
    }
    struct Point pointFirst = {.x = firstPlayer->heroImg.widget.drawParams.pos.x, .y = firstPlayer->heroImg.widget.drawParams.pos.y};
    
    return pointFirst.x >= secondPlayer->heroImg.widget.drawParams.pos.x;
}

void startBattle(struct Battlefield* self, int* playerMoney, int* playerXp){
    struct Hero* firstPlayer =
                  (struct Hero*)getElementVector(&self->playerArmy, FIRST_PLAYER_ENEMY_IDX);

    struct Hero* firstEnemy =
                  (struct Hero*)getElementVector(&self->enemyArmy, FIRST_PLAYER_ENEMY_IDX);            
    
    struct HeroBase* enemyTower = getElementVector(&self->enemyArmy, 0);
    struct HeroBase* playerTower = getElementVector(&self->playerArmy, 0);
    
    if(firstPlayer == NULL && firstEnemy){
        if(meetHeros(playerTower,&firstEnemy->base)){
            for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVector(&self->enemyArmy); i++){
                struct Hero* currHero =
                  (struct Hero*)getElementVector(&self->enemyArmy, i);
                    if(meetHeros(playerTower, &currHero->base )){
                        if(currHero->mode != ATACK){
                            currHero->setModeAtackHero_func(currHero);
                        }
                    }
                    else {
                        if(currHero->mode != RUN){
                            currHero->setModeRunHero_func(currHero);
                        }
                    }
                    if(currHero->mode == ATACK && currHero->base.heroImg.currFrame == currHero->atackFrame){
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
            for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVector(&self->playerArmy); i++){
                struct Hero* currHero =
                  (struct Hero*)getElementVector(&self->playerArmy, i);
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
                    if(currHero->mode == ATACK && currHero->base.heroImg.currFrame == currHero->atackFrame){
                        currHero->base.heroImg.currFrame = 1;
                        int32_t damage = currHero->produceDamage_func(currHero);
                        enemyTower->takeDamage_func(enemyTower, damage);
                    }
                }
            }
    }

    if(firstPlayer == NULL || firstEnemy == NULL){
        return;
    }
    
    for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVector(&self->playerArmy); i++)
    {
        struct Hero* currHero =
                  (struct Hero*)getElementVector(&self->playerArmy, i);

        if(meetHeros(&firstPlayer->base, &currHero->base)){
            if(firstPlayer->mode != RUN){
                currHero->setModeIdleHero_func(currHero);

            }
        }
    }

    for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVector(&self->enemyArmy); i++)
    {   
        struct Hero* currHero =
                  (struct Hero*)getElementVector(&self->enemyArmy, i);

        if(meetHeros(&firstEnemy->base, &currHero->base)){
            
            if(firstEnemy->mode != RUN){
                currHero->setModeIdleHero_func(currHero);
            }
        }
    }

    if(meetHeros(&firstPlayer->base, &firstEnemy->base )){
        if(firstPlayer->mode == RUN){
            firstPlayer->setModeAtackHero_func(firstPlayer);
        }

        if(firstEnemy->mode == RUN){
            firstEnemy->setModeAtackHero_func(firstEnemy);
        }

        if(firstPlayer->base.heroImg.currFrame == firstPlayer->atackFrame){
            firstPlayer->base.heroImg.currFrame = 1;
            int32_t damage = firstPlayer->produceDamage_func(firstPlayer);
            firstEnemy->base.takeDamage_func(&firstEnemy->base, damage);
        }

        if(firstEnemy->base.heroImg.currFrame == firstEnemy->atackFrame){
            firstEnemy->base.heroImg.currFrame = 1;
            int32_t damage = firstPlayer->produceDamage_func(firstEnemy);
            firstEnemy->base.takeDamage_func(&firstPlayer->base, damage);
        }

        if(!firstPlayer->base.isAlive){
            stopTimer(firstPlayer->moveTimerId);
            stopTimer(firstPlayer->spriteTimerId);
            
            firstPlayer->base.deinit_func(&firstPlayer->base);         
            deleteElementVector(&self->playerArmy, FIRST_PLAYER_ENEMY_IDX);
            free(firstPlayer);
            firstPlayer = NULL;

            if(firstEnemy){
                firstEnemy->setModeRunHero_func(firstEnemy);
            }
        }

        if(!firstEnemy->base.isAlive){
            stopTimer(firstEnemy->moveTimerId);
            stopTimer(firstEnemy->spriteTimerId);
            *playerXp += firstEnemy->prise;
            *playerMoney += firstEnemy->prise;
            
            firstEnemy->base.deinit_func(&firstEnemy->base);            
            deleteElementVector(&self->enemyArmy, FIRST_PLAYER_ENEMY_IDX);
            free(firstEnemy);
            firstEnemy = NULL;
            if(firstPlayer){
                firstPlayer->setModeRunHero_func(firstPlayer);
            }

        }
    }
    
    if(!meetHeros(&firstPlayer->base, &firstEnemy->base )) {
        if(firstPlayer && firstPlayer->mode != RUN){
            firstPlayer->setModeRunHero_func(firstPlayer);
        }

        if(firstEnemy && firstEnemy->mode != RUN){
            firstEnemy->setModeRunHero_func(firstEnemy);
        }
    }

        if(firstPlayer && firstPlayer->mode == RUN){
            for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVector(&self->playerArmy); i++)
            {
                struct Hero* currHero =
                  (struct Hero*)getElementVector(&self->playerArmy, i);
                if(currHero->mode != RUN){
                    currHero->setModeRunHero_func(currHero);
                }
            }
        }

        if(firstEnemy && firstEnemy->mode == RUN){
            for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVector(&self->enemyArmy); i++)
            {   
                struct Hero* currHero =
                  (struct Hero*)getElementVector(&self->enemyArmy, i);
                if(currHero->mode != RUN){
                    currHero->setModeRunHero_func(currHero);
                }
            }
        }
}