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
