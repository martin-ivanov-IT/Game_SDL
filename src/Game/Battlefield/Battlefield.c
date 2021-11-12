#include "Game/Battlefield/Battlefield.h"
#include "Game/Entities/Hero.h"


#include "common/CommonDefines.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

#include "manager_utils/drawing/Widget.h"

static const int32_t FIRST_PLAYER_ENEMY_IDX = 1;

void initBattlefield(struct Battlefield* self){
      initVectorHero(&self->playerArmy, 10);
      initVectorHero(&self->enemyArmy, 10);
}
void deinitBattlefield(struct Battlefield* self){
    UNUSED(self);
}
static bool meetHeros(struct Hero* firstPlayer, struct Hero* secondPlayer){
    if(!firstPlayer || !secondPlayer){
        return false;
    }
    struct Point pointFirst = {.x = firstPlayer->heroImg.widget.drawParams.pos.x, .y = firstPlayer->heroImg.widget.drawParams.pos.y};
    
    return containsPointWidget(&secondPlayer->heroImg.widget, &pointFirst);
}

void startBattle(struct Battlefield* self){
    struct Hero* firstPlayer = getElementVectorHero(&self->playerArmy, FIRST_PLAYER_ENEMY_IDX);
    struct Hero* firstEnemy = getElementVectorHero(&self->enemyArmy, FIRST_PLAYER_ENEMY_IDX);
    struct Hero* enemyTower = getElementVectorHero(&self->enemyArmy, 0);
    struct Hero* playerTower = getElementVectorHero(&self->playerArmy, 0);
    if(firstPlayer){
        LOGY("first player x: %d", firstPlayer->heroImg.widget.drawParams.pos.x);
        LOGY("enemy tower x: %d", enemyTower->heroImg.widget.drawParams.pos.x);
    }
    

    if(firstPlayer == NULL && firstEnemy){
        if(meetHeros(firstEnemy, playerTower)){
            for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVectorHero(&self->enemyArmy); i++){
                struct Hero* currHero = getElementVectorHero(&self->enemyArmy, i);
                    if(meetHeros(currHero,playerTower )){
                        if(currHero->mode != ATACK){
                            setModeAtackHero(currHero);
                        }
                    }
                    else {
                        if(currHero->mode != RUN){
                            setModeRunHero(currHero);
                        }
                    }
                    if(currHero->mode == ATACK && currHero->heroImg.currFrame == 9){
                        currHero->heroImg.currFrame = 1;
                        int32_t damage = produceDamage(currHero);
                        LOGY("player towedamage taken")
                        takeDamage(playerTower, damage);
                    }
                }
            }
    }

    if(firstEnemy == NULL && firstPlayer){
        struct Hero towerCopy = {
            .heroImg.widget.drawParams.pos.x = enemyTower->heroImg.widget.drawParams.pos.x -120,
            .heroImg.widget.drawParams.pos.y = enemyTower->heroImg.widget.drawParams.pos.y,
            .heroImg.widget.drawParams.width = enemyTower->heroImg.widget.drawParams.width,
            .heroImg.widget.drawParams.height = enemyTower->heroImg.widget.drawParams.height,
            };
        if(meetHeros(firstPlayer, &towerCopy)){
            for (size_t i = FIRST_PLAYER_ENEMY_IDX; i < getSizeVectorHero(&self->playerArmy); i++){
                struct Hero* currHero = getElementVectorHero(&self->playerArmy, i);
                    // struct Point pointFirst = {.x = enemyTower->heroImg.widget.drawParams.pos.x -150, .y = currHero->heroImg.widget.drawParams.pos.y};
                    if(meetHeros(currHero, &towerCopy)){
                        if(currHero->mode != ATACK){
                            setModeAtackHero(currHero);
                        }
                    }
                    else {
                        if(currHero->mode != RUN){
                            setModeRunHero(currHero);
                        }
                    }
                    if(currHero->mode == ATACK && currHero->heroImg.currFrame == 9){
                        currHero->heroImg.currFrame = 1;
                        int32_t damage = produceDamage(currHero);
                        LOGY("player towedamage taken")
                        takeDamage(playerTower, damage);
                    }
                }
            }
    }

    if(firstPlayer == NULL || firstEnemy == NULL){
        return;
    }
    
    for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVectorHero(&self->playerArmy); i++)
    {
        struct Hero* currHero = getElementVectorHero(&self->playerArmy, i);
        if(meetHeros(firstPlayer, currHero)){
            if(firstPlayer->mode != RUN){
                LOGY("meet teammate player");
                setModeIdleHero(currHero);
                // currHero->heroImg.widget.drawParams.pos.x = firstPlayer->heroImg.widget.drawParams.pos.x - 15;

            }
        }
    }

    for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVectorHero(&self->enemyArmy); i++)
    {
        struct Hero* currHero = getElementVectorHero(&self->enemyArmy, i);
        if(meetHeros(firstEnemy, currHero)){
            
            if(firstEnemy->mode != RUN){
                LOGY("enemeies met")
                setModeIdleHero(currHero);
                // currHero->heroImg.widget.drawParams.pos.x = firstEnemy->heroImg.widget.drawParams.pos.x +15;
            }
        }
    }

    if(meetHeros(firstEnemy, firstPlayer)){
        
        if(firstPlayer->mode == RUN){
            setModeAtackHero(firstPlayer);
        }

        if(firstEnemy->mode == RUN){
            setModeAtackHero(firstEnemy);
        }

        if(firstPlayer->heroImg.currFrame == 9){
            firstPlayer->heroImg.currFrame = 1;
            int32_t damage = produceDamage(firstPlayer);
            LOGY("damage taken")
            takeDamage(firstEnemy, damage);
        }

        if(firstEnemy->heroImg.currFrame == 9){
            firstEnemy->heroImg.currFrame = 1;
            int32_t damage = produceDamage(firstEnemy);
            LOGY("damage taken")
            takeDamage(firstPlayer, damage);
        }

        if(!firstPlayer->isAlive){
            LOGY("firstPlayer taken")
            stopTimer(firstPlayer->moveTimerId);
            stopTimer(firstPlayer->spriteTimerId);
            
            deinitHero(firstPlayer);            
            deleteElementVectorHero(&self->playerArmy, FIRST_PLAYER_ENEMY_IDX);

            firstPlayer = NULL;

            if(firstEnemy){
                setModeRunHero(firstEnemy);
            }
        }

        if(!firstEnemy->isAlive){
            LOGY("firstEnemy taken")
            
            stopTimer(firstEnemy->moveTimerId);
            stopTimer(firstEnemy->spriteTimerId);

            deinitHero(firstEnemy);            
            deleteElementVectorHero(&self->enemyArmy, FIRST_PLAYER_ENEMY_IDX);
            firstEnemy = NULL;
            if(firstPlayer){
                setModeRunHero(firstPlayer);
            }

        }
    }

    if(!meetHeros(firstEnemy, firstPlayer)) {
        if(firstPlayer && firstPlayer->mode != RUN){
            setModeRunHero(firstPlayer);
        }

        if(firstEnemy && firstEnemy->mode != RUN){
            setModeRunHero(firstEnemy);
        }
    }

        if(firstPlayer && firstPlayer->mode == RUN){
            for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVectorHero(&self->playerArmy); i++)
            {
                struct Hero* currHero = getElementVectorHero(&self->playerArmy, i);
                if(currHero->mode != RUN){
                setModeRunHero(currHero);
                }
            }
        }

        if(firstEnemy && firstEnemy->mode == RUN){
            for (size_t i = FIRST_PLAYER_ENEMY_IDX + 1; i < getSizeVectorHero(&self->enemyArmy); i++)
            {
                struct Hero* currHero = getElementVectorHero(&self->enemyArmy, i);
                if(currHero->mode != RUN){
                setModeRunHero(currHero);
                }
            }
        }
}
