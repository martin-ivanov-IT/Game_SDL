#include "Engine/EngineConfigLoader.h"
#include "common/CommonDefines.h"
#include "sdl_utils/config/ImageContainerCfg.h"
#include "sdl_utils/config/TextContainerCfg.h"
#include <string.h>
#include <stdlib.h>
#include "utils/drawing/Rectangle.h"
#include "common/TimerDefines.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

typedef enum {
  TERRORIST_1_HEALTH = 75,
  TERRORIST_1_SHORT_ATACK_DEMAGE = 50,
  TERRORIST_1_LONG_ATACK_DEMAGE = 100,
  TERRORIST_1_SPRITE_FRAMES = 6,

} Terorist_1_defines;

static const int32_t SCREEN_WIDTH = 1400;
static const int32_t SCREEN_HEIGHT = 750;

static const int32_t TROLL_1_ID_FRAMES_COUNT = 10;
static const int32_t TROLL_1_FRAME_WIDTH = 200;
static const int32_t TROLL_1_FRAME_HEIGHT = 300;
static const int32_t TROLL_1_BUTTON_FRAME_WIDTH_HEIGHT = 50;

static const int32_t BUTTON_TABLE_FRAME_WIDTH = 300;
static const int32_t BUTTON_TABLE_FRAME_HEIGHT = 90;

static const int32_t TROLL_1_HEALTH = 50;
static const int32_t TROLL_1_ATACK_DEMAGE = 25;

static const int32_t TROLL_2_HEALTH = 75;
static const int32_t TROLL_2_ATACK_DEMAGE = 50;

static const int32_t TROLL_3_HEALTH = 120;
static const int32_t TROLL_3_ATACK_DEMAGE = 75;

static const int32_t TOWER_HEALTH = 1000;
static const int32_t TOWER_FRAMES_COUNT= 3;
static const int32_t TOWER_FRAME_WIDTH_HEIGHT = 600;

static const int32_t BUTTON_COUNT = 13;

static const int32_t BACKGROUND_IMG_WIDTH = 3000;
static const int32_t BACKGROUND_IMG_HEIGHT= 750;

static const int32_t GAME_OVER_IMG_WIDTH = 1400;
static const int32_t GAME_OVER_IMG_HEIGHT= 750;

static const int32_t ANGELINE_VINATGE_FONT_SIZE = 40;
static const int32_t BUTTON_FRAMES = 2;
static const int32_t ENGINE_TARGET_FRAMES = 120;

static void populateResourceLocation (char* buffer, const char* relativePath){
    #ifdef RELEASE_BUILD
    strcpy(buffer,relativePath);
    #else
        strcpy(buffer, "../");
        strcat(buffer,relativePath);
        
    #endif
}
// //Troll_1  run sprite
//     initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
//     for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
//     {
//         currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
//         currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
//         currframe->y = 0;
//         currframe->w = TROLL_1_FRAME_WIDTH;
//         currframe->h = TROLL_1_FRAME_HEIGHT;
//         pushElementVector(&imgCfg.frames, currframe);
//     }

//     populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_1_sprite_run.png");
//     insertImageConfig(cfg, TROLL_1_RUN_ID , &imgCfg);
//     clearElementsVector(&imgCfg.frames);
//     //end Troll_1  run sprite

// struct ImageConfig imgCfg;
// struct Rectangle* currframe = NULL;
void createSprite (struct ImageConfig* imgCfg, struct Rectangle** currframe, int32_t framesCount,
                     int32_t Frame_Width,int32_t Frame_Height, char* path, struct ImageContainerCfg* cfg, int32_t rsrcId)
{
    initVector(&imgCfg->frames,framesCount);
    for (int32_t i = 0; i < framesCount; i++)
    {
        *currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        (*currframe)->x = 0+(Frame_Width*i);
        (*currframe)->y = 0;
        (*currframe)->w = Frame_Width;
        (*currframe)->h = Frame_Height;
        pushElementVector(&imgCfg->frames, *currframe);

    populateResourceLocation(imgCfg->location, path);
    insertImageConfig(cfg, rsrcId , imgCfg);
    clearElementsVector(&imgCfg->frames);
    }
    

}

static void popilateCameCfg( struct GameConfig* cfg){
    cfg->epoch = STONE_AGE;
    cfg->playerMoney = 500;
    cfg->playerXp =0;

    cfg->troll_1Cfg.baseCfg.rsrcId = TROLL_1_RUN_ID;
    cfg->troll_1Cfg.runRsrcId = TROLL_1_RUN_ID;
    cfg->troll_1Cfg.atackRsrcId = TROLL_1_ATACK_ID;
    cfg->troll_1Cfg.hurtRsrcId = TROLL_1_HURT_ID;
    cfg->troll_1Cfg.dieRsrcId = TROLL_1_DIE_ID;
    cfg->troll_1Cfg.idleRsrcId = TROLL_1_IDLE_ID;
    cfg->troll_1Cfg.baseCfg.health = TROLL_1_HEALTH;
    cfg->troll_1Cfg.atackDamage = TROLL_1_ATACK_DEMAGE;
    cfg->troll_1Cfg.mode = RUN;
    cfg->troll_1Cfg.deltaMovePx  = 25;
    cfg->troll_1Cfg.baseCfg.isAlive = true;
    cfg->troll_1Cfg.baseCfg.heroType = TROLL_1;

    cfg->troll_2Cfg.baseCfg.rsrcId = TROLL_2_RUN_ID;
    cfg->troll_2Cfg.runRsrcId = TROLL_2_RUN_ID;
    cfg->troll_2Cfg.atackRsrcId = TROLL_2_ATACK_ID;
    cfg->troll_2Cfg.hurtRsrcId = TROLL_2_HURT_ID;
    cfg->troll_2Cfg.dieRsrcId = TROLL_2_DIE_ID;
    cfg->troll_2Cfg.idleRsrcId = TROLL_2_IDLE_ID;
    cfg->troll_2Cfg.baseCfg.health = TROLL_2_HEALTH;
    cfg->troll_2Cfg.atackDamage = TROLL_2_ATACK_DEMAGE;
    cfg->troll_2Cfg.mode = RUN;
    cfg->troll_2Cfg.deltaMovePx  = 25;
    cfg->troll_2Cfg.baseCfg.isAlive = true;
    cfg->troll_2Cfg.baseCfg.heroType = TROLL_2;

    cfg->troll_3Cfg.baseCfg.rsrcId = TROLL_3_RUN_ID;
    cfg->troll_3Cfg.runRsrcId = TROLL_3_RUN_ID;
    cfg->troll_3Cfg.atackRsrcId = TROLL_3_ATACK_ID;
    cfg->troll_3Cfg.hurtRsrcId = TROLL_3_HURT_ID;
    cfg->troll_3Cfg.dieRsrcId = TROLL_3_DIE_ID;
    cfg->troll_3Cfg.idleRsrcId = TROLL_3_IDLE_ID;
    cfg->troll_3Cfg.baseCfg.health = TROLL_3_HEALTH;
    cfg->troll_3Cfg.atackDamage = TROLL_3_ATACK_DEMAGE;
    cfg->troll_3Cfg.mode = RUN;
    cfg->troll_3Cfg.deltaMovePx  = 25;
    cfg->troll_3Cfg.baseCfg.isAlive = true;
    cfg->troll_3Cfg.baseCfg.heroType = TROLL_3;

    cfg->terrorist_1_Cfg.heroCfg.baseCfg.rsrcId = TERRORIST_1_ID;
    cfg->terrorist_1_Cfg.heroCfg.runRsrcId = TERRORIST_1_RUN_ID;
    cfg->terrorist_1_Cfg.heroCfg.atackRsrcId = TERRORIST_1_ATACK_ID;
    cfg->terrorist_1_Cfg.heroCfg.idleRsrcId = TERRORIST_1_IDLE_ID;
    cfg->terrorist_1_Cfg.heroCfg.dieRsrcId = TERRORIST_1_DIE_ID;
    cfg->terrorist_1_Cfg.heroCfg.hurtRsrcId = TERRORIST_1_HURT_ID;
    cfg->terrorist_1_Cfg.longAtackRsrcId = TERRORIST_1_LONG_ATACK_ID;
    cfg->terrorist_1_Cfg.heroCfg.atackDamage = TERRORIST_1_SHORT_ATACK_DEMAGE;
    cfg->terrorist_1_Cfg.longAtackDamage = TERRORIST_1_LONG_ATACK_DEMAGE;
    cfg->terrorist_1_Cfg.heroCfg.baseCfg.health = TERRORIST_1_HEALTH;
    cfg->terrorist_1_Cfg.heroCfg.baseCfg.isAlive = true;
    cfg->terrorist_1_Cfg.heroCfg.deltaMovePx = 25;
    cfg->terrorist_1_Cfg.heroCfg.mode = RUN;
    cfg->terrorist_1_Cfg.heroCfg.baseCfg.heroType = TERRORIST_1;

    cfg->playerTowerCfg.health = TOWER_HEALTH;
    cfg->playerTowerCfg.rsrcId = PLAYER_TOWER_ID;
    cfg->playerTowerCfg.isAlive = true;

    cfg->enemyTowerCfg.health = TOWER_HEALTH;
    cfg->enemyTowerCfg.rsrcId = ENEMY_TOWER_ID;
    cfg->enemyTowerCfg.isAlive = true;      

    cfg->trollBtnRsrcId = TROLL_1_BUTTON_ID;
    cfg->trollBtnEnemyRsrcId = TROLL_1_BUTTON_ENEMY_ID;

    cfg->troll2BtnRsrcId = TROLL_2_BUTTON_ID;
    cfg->troll2BtnEnemyRsrcId = TROLL_2_BUTTON_ENEMY_ID;

    cfg->troll3BtnRsrcId = TROLL_3_BUTTON_ID;
    cfg->troll3BtnEnemyRsrcId = TROLL_3_BUTTON_ENEMY_ID;

    cfg->trollBtnRsrcId = TROLL_1_BUTTON_ID;
    cfg->trollBtnEnemyRsrcId = TROLL_1_BUTTON_ENEMY_ID;

    cfg->troll2BtnRsrcId = TROLL_2_BUTTON_ID;
    cfg->troll2BtnEnemyRsrcId = TROLL_2_BUTTON_ENEMY_ID;

    cfg->troll3BtnRsrcId = TROLL_3_BUTTON_ID;
    cfg->troll3BtnEnemyRsrcId = TROLL_3_BUTTON_ENEMY_ID;

    cfg->terroristBtnRsrcId = TERRORIST_1_BUTTON_ID;
    cfg->terroristBtnEnemyRsrcId = TERRORIST_1_BUTTON_ENEMY_ID;

    cfg->terrorist2BtnRsrcId = TERRORIST_2_BUTTON_ID;
    cfg->terrorist2BtnEnemyRsrcId = TERRORIST_2_BUTTON_ENEMY_ID;

    cfg->terrorist3BtnRsrcId = TERRORIST_3_BUTTON_ID;
    cfg->terrorist3BtnEnemyRsrcId = TERRORIST_3_BUTTON_ENEMY_ID;

    cfg->terroristBtnRsrcId = TERRORIST_1_BUTTON_ID;
    cfg->terroristBtnEnemyRsrcId = TERRORIST_1_BUTTON_ENEMY_ID;

    cfg->terrorist2BtnRsrcId = TERRORIST_2_BUTTON_ID;
    cfg->terrorist2BtnEnemyRsrcId = TERRORIST_2_BUTTON_ENEMY_ID;

    cfg->terrorist3BtnRsrcId = TERRORIST_3_BUTTON_ID;
    cfg->terrorist3BtnEnemyRsrcId = TERRORIST_3_BUTTON_ENEMY_ID;


    cfg->starBtnRsrcId = STAR_BUTTON_ID;
}

static void populateWindowCfg(struct MonitorWindowCfg* cfg){
    cfg->windowFlag = WINDOWS_SHOWN;
    cfg->windowWidth = SCREEN_WIDTH;
    cfg->windowHeight = SCREEN_HEIGHT;
    cfg->windowName = "Hello";
    cfg->windowPos = POINT_UNDEFINED;
}

static void populateImageContainerCfg(struct ImageContainerCfg* cfg){
    struct ImageConfig imgCfg;
    struct Rectangle* currframe = NULL;
    
    //Troll_1 die sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_1_sprite_die.png");
    insertImageConfig(cfg, TROLL_1_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_1  die sprite

    //Troll_2 die sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_2_sprite_die.png");
    insertImageConfig(cfg, TROLL_2_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_2  die sprite

    //Troll_2 die sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_3_sprite_die.png");
    insertImageConfig(cfg, TROLL_3_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_2  die sprite

    createSprite(&imgCfg, &currframe, TROLL_1_ID_FRAMES_COUNT, TROLL_1_FRAME_WIDTH, TROLL_1_FRAME_HEIGHT,
                    "resources/p/sprites/troll_1_sprite_run.png",cfg, TROLL_1_RUN_ID);
    // //Troll_1  run sprite
    // initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    // for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    // {
    //     currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
    //     currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
    //     currframe->y = 0;
    //     currframe->w = TROLL_1_FRAME_WIDTH;
    //     currframe->h = TROLL_1_FRAME_HEIGHT;
    //     pushElementVector(&imgCfg.frames, currframe);
    // }

    // populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_1_sprite_run.png");
    // insertImageConfig(cfg, TROLL_1_RUN_ID , &imgCfg);
    // clearElementsVector(&imgCfg.frames);
    // //end Troll_1  run sprite

    //Troll_2  run sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_2_sprite_run.png");
    insertImageConfig(cfg, TROLL_2_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_2  run sprite

    //Troll_3  run sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_3_sprite_run.png");
    insertImageConfig(cfg, TROLL_3_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_3  run sprite

    //Troll_1  idle sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_1_sprite_idle.png");
    insertImageConfig(cfg, TROLL_1_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_1  idle sprite

    //Troll_2  idle sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_2_sprite_idle.png");
    insertImageConfig(cfg, TROLL_2_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_2  idle sprite

    //Troll_3  idle sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_3_sprite_idle.png");
    insertImageConfig(cfg, TROLL_3_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_3  idle sprite

    //Troll_1  atack sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_1_sprite_atack.png");
    insertImageConfig(cfg, TROLL_1_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_1  atack sprite

    //Troll_2  atack sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_2_sprite_atack.png");
    insertImageConfig(cfg, TROLL_2_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_2  atack sprite

    //Troll_3  atack sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_3_sprite_atack.png");
    insertImageConfig(cfg, TROLL_3_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_3  atack sprite

    //Troll_1  hurt sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_1_sprite_hurt.png");
    insertImageConfig(cfg, TROLL_1_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_1  hurt sprite

    //Troll_2  hurt sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_2_sprite_hurt.png");
    insertImageConfig(cfg, TROLL_2_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_2  hurt sprite

     //Troll_3  hurt sprite
    initVector(&imgCfg.frames,TROLL_1_ID_FRAMES_COUNT);
    for (int32_t i = 0; i < TROLL_1_ID_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TROLL_1_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = TROLL_1_FRAME_WIDTH;
        currframe->h = TROLL_1_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_3_sprite_hurt.png");
    insertImageConfig(cfg, TROLL_3_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll_3  hurt sprite

    //Catsle player sprite
    initVector(&imgCfg.frames,TOWER_FRAMES_COUNT);
    for (int32_t i = 0; i < TOWER_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TOWER_FRAME_WIDTH_HEIGHT*i);
        currframe->y = 0;
        currframe->w = TOWER_FRAME_WIDTH_HEIGHT;
        currframe->h = TOWER_FRAME_WIDTH_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/castle_1_sprite.png");
    insertImageConfig(cfg, PLAYER_TOWER_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Catsle player sprite

    //Catsle enemy sprite
    initVector(&imgCfg.frames,TOWER_FRAMES_COUNT);
    for (int32_t i = 0; i < TOWER_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(TOWER_FRAME_WIDTH_HEIGHT*i);
        currframe->y = 0;
        currframe->w = TOWER_FRAME_WIDTH_HEIGHT;
        currframe->h = TOWER_FRAME_WIDTH_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/castle_2_sprite.png");
    insertImageConfig(cfg, ENEMY_TOWER_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Catsle enemy sprite

    currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
    currframe->x = 0;
    currframe->y = 0;
    currframe->w = BACKGROUND_IMG_WIDTH;
    currframe->h = BACKGROUND_IMG_HEIGHT;
    pushElementVector(&imgCfg.frames, currframe);
    populateResourceLocation(imgCfg.location, "resources/p/background_1_3000x750.png");
    insertImageConfig(cfg, BACKGROUND_ID, &imgCfg);
    clearElementsVector(&imgCfg.frames);

    currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
    currframe->x = 0;
    currframe->y = 0;
    currframe->w = BUTTON_TABLE_FRAME_WIDTH;
    currframe->h = BUTTON_TABLE_FRAME_HEIGHT;
    pushElementVector(&imgCfg.frames, currframe);
    populateResourceLocation(imgCfg.location, "resources/p/button_table.png");
    insertImageConfig(cfg, BUTTON_TABLE_ID, &imgCfg);
    clearElementsVector(&imgCfg.frames);

    currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
    currframe->x = 0;
    currframe->y = 0;
    currframe->w = GAME_OVER_IMG_WIDTH;
    currframe->h = GAME_OVER_IMG_HEIGHT;
    pushElementVector(&imgCfg.frames, currframe);
    populateResourceLocation(imgCfg.location, "resources/p/game_over.png");
    insertImageConfig(cfg, GAME_OVER_ID, &imgCfg);
    clearElementsVector(&imgCfg.frames);

    currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
    currframe->x = 0;
    currframe->y = 0;
    currframe->w = GAME_OVER_IMG_WIDTH;
    currframe->h = GAME_OVER_IMG_HEIGHT;
    pushElementVector(&imgCfg.frames, currframe);
    populateResourceLocation(imgCfg.location, "resources/p/win-game-screen .png");
    insertImageConfig(cfg, WIN_GAME_ID, &imgCfg);
    clearElementsVector(&imgCfg.frames);
//buttons
    const char* buttonPaths[13] = 
    {
        "resources/p/buttons/troll_1_face.png", "resources/p/buttons/troll_1_face.png",
        "resources/p/buttons/troll_2_face.png", "resources/p/buttons/troll_2_face.png",
        "resources/p/buttons/troll_3_face.png", "resources/p/buttons/troll_3_face.png",
        
        "resources/p/buttons/terrorist_1_face.png", "resources/p/buttons/terrorist_1_face.png",
        "resources/p/buttons/terrorist_2_face.png", "resources/p/buttons/terrorist_2_face.png",
        "resources/p/buttons/terrorist_3_face.png", "resources/p/buttons/terrorist_3_face.png",

        "resources/p/buttons/star_button.png",
        };
    const int32_t buttonRsrcIds[13] = 
            {
                TROLL_1_BUTTON_ID, TROLL_1_BUTTON_ENEMY_ID,
                TROLL_2_BUTTON_ID, TROLL_2_BUTTON_ENEMY_ID,
                TROLL_3_BUTTON_ID, TROLL_3_BUTTON_ENEMY_ID,
                
                TERRORIST_1_BUTTON_ID, TERRORIST_1_BUTTON_ENEMY_ID,
                TERRORIST_2_BUTTON_ID, TERRORIST_2_BUTTON_ENEMY_ID,
                TERRORIST_3_BUTTON_ID, TERRORIST_3_BUTTON_ENEMY_ID,

                STAR_BUTTON_ID,
            };

    for (int32_t buttonId = 0; buttonId < BUTTON_COUNT; ++buttonId) {
        strcpy(imgCfg.location, buttonPaths[buttonId]);
        clearElementsVector(&imgCfg.frames);
        for (int32_t i = 0; i < BUTTON_FRAMES; i++)
        {
            currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));

            currframe->x = i * TROLL_1_BUTTON_FRAME_WIDTH_HEIGHT;
            currframe->y = 0;
            currframe->w = TROLL_1_BUTTON_FRAME_WIDTH_HEIGHT;
            currframe->h = TROLL_1_BUTTON_FRAME_WIDTH_HEIGHT;
            pushElementVector(&imgCfg.frames, currframe);
        }

        populateResourceLocation(imgCfg.location, buttonPaths[buttonId]);
        insertImageConfig(cfg, buttonRsrcIds[buttonId] , &imgCfg);
        clearElementsVector(&imgCfg.frames);
    }

    freeVector(&imgCfg.frames);
}

static void populateTextContainerCfg(struct TextContainerCfg* cfg){
    struct FontConfig fontCfg;
    fontCfg.fontSize = ANGELINE_VINATGE_FONT_SIZE;
    populateResourceLocation(fontCfg.location, "resources/f/AngelineVintage.ttf");
    insertFontConfig(cfg, ANGELINE_VINATGE_ID , &fontCfg);
}
static void populateManagerHandlerCfg(struct ManagerHandlerCfg* cfg){
    populateWindowCfg(&cfg->drawMgrCfg.windowCfg);
    cfg->drawMgrCfg.maxFrames =ENGINE_TARGET_FRAMES;
    populateImageContainerCfg(&cfg->resourceMgrCfg.imgContainerCfg);
    populateTextContainerCfg(&cfg->resourceMgrCfg.textContainerCfg);
}
struct EngineConfig loadEngineConfig() {

    struct EngineConfig cfg; 
    memset(&cfg, 0, sizeof(struct EngineConfig));
    populateManagerHandlerCfg(&cfg.managerHandlerCfg);
    popilateCameCfg(&cfg.gameCfg);   
    cfg.debugConsoleFontId = ANGELINE_VINATGE_ID;

    
    return cfg;
}
