#include "Game/Battlefield/Battlefield.h"
#include "Game/Entities/Hero.h"


#include "common/CommonDefines.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

#include "manager_utils/drawing/Widget.h"


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
    struct Hero* firstPlayer = getElementVectorHero(&self->playerArmy, 0);
    struct Hero* firstEnemy = getElementVectorHero(&self->enemyArmy, 0);
    if(firstPlayer == NULL || firstEnemy == NULL){
        return;
    }
    
    for (size_t i = 1; i < getSizeVectorHero(&self->playerArmy); i++)
    {
        struct Hero* currHero = getElementVectorHero(&self->playerArmy, i);
        if(meetHeros(firstPlayer, currHero)){
            if(firstPlayer->mode != RUN){
                setModeIdleHero(currHero);
                currHero->heroImg.widget.drawParams.pos.x = firstPlayer->heroImg.widget.drawParams.pos.x -30;

            }
        }
    }

    for (size_t i = 1; i < getSizeVectorHero(&self->enemyArmy); i++)
    {
        struct Hero* currHero = getElementVectorHero(&self->enemyArmy, i);
        if(meetHeros(firstEnemy, currHero)){
            if(firstEnemy->mode != RUN){
                setModeIdleHero(currHero);
                currHero->heroImg.widget.drawParams.pos.x = firstEnemy->heroImg.widget.drawParams.pos.x +30;
            }
        }
    }

    if(meetHeros(firstEnemy, firstPlayer)){
        LOGY("meet opposite");
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
            deleteElementVectorHero(&self->playerArmy, 0);

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
            deleteElementVectorHero(&self->enemyArmy, 0);
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
            for (size_t i = 1; i < getSizeVectorHero(&self->playerArmy); i++)
            {
                struct Hero* currHero = getElementVectorHero(&self->playerArmy, i);
                setModeRunHero(currHero);
            }
        }

        if(firstEnemy && firstEnemy->mode == RUN){
            for (size_t i = 1; i < getSizeVectorHero(&self->enemyArmy); i++)
            {
                struct Hero* currHero = getElementVectorHero(&self->enemyArmy, i);
                setModeRunHero(currHero);
            }
        }
}
