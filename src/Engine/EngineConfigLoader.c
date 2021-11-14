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
  TERRORIST_1_PRISE = 50,

} Terorist_1_defines;

typedef enum {
    TERRORIST_2_HEALTH = 120,
    TERRORIST_2_SHORT_ATACK_DEMAGE = 75,
    TERRORIST_2_LONG_ATACK_DEMAGE = 125,
    TERRORIST_2_PRISE = 75,


} Terorist_2_defines;

typedef enum {
    TERRORIST_3_HEALTH = 200,
    TERRORIST_3_SHORT_ATACK_DEMAGE = 150,
    TERRORIST_3_LONG_ATACK_DEMAGE = 150,
    TERRORIST_3_SPRITE_FRAMES = 6,
    TERRORIST_3_PRISE = 100,


} Terorist_3_defines;

typedef enum {
  ROBOT_1_HEALTH = 75,
  ROBOT_1_SHORT_ATACK_DEMAGE = 50,
  ROBOT_1_LONG_ATACK_DEMAGE = 100,
  ROBOT_1_SPRITE_FRAMES = 9,
  ROBOT_1_PRISE = 100,

} Robot_1_defines;

typedef enum {
  ROBOT_2_HEALTH = 120,
  ROBOT_2_SHORT_ATACK_DEMAGE = 75,
  ROBOT_2_LONG_ATACK_DEMAGE = 125,
  ROBOT_2_SPRITE_FRAMES = 6,
  ROBOT_2_PRISE = 150,


} Robot_2_defines;

typedef enum {
  ROBOT_3_HEALTH = 200,
  ROBOT_3_SHORT_ATACK_DEMAGE = 150,
  ROBOT_3_LONG_ATACK_DEMAGE = 150,
  ROBOT_3_SPRITE_FRAMES = 6,
  ROBOT_3_PRISE = 150,


} Robot_3_defines;


static const int32_t SCREEN_WIDTH = 1400;
static const int32_t SCREEN_HEIGHT = 750;

static const int32_t MOVE_SPPED = 10;

static const int32_t TROLL_FRAMES_COUNT = 10;
static const int32_t TROLL_FRAME_WIDTH = 200;
static const int32_t TROLL_FRAME_HEIGHT = 300;

static const int32_t TERRORIST_FRAMES_COUNT = 6;
static const int32_t TERRORIST_FRAME_WIDTH = 120;
static const int32_t TERRORIST_FRAME_HEIGHT = 150;

static const int32_t ROBOT_FRAMES_COUNT = 9;
static const int32_t ROBOT_FRAME_WIDTH = 120;
static const int32_t ROBOT_FRAME_HEIGHT = 150;

static const int32_t BUTTON_FRAME_WIDTH_HEIGHT = 50;

static const int32_t START_GAME_BUTTON_FRAME_WIDTH = 200;
static const int32_t START_GAME_BUTTON_FRAME_HEIGHT = 60;

static const int32_t BUTTON_TABLE_FRAME_WIDTH = 300;
static const int32_t BUTTON_TABLE_FRAME_HEIGHT = 90;

static const int32_t TROLL_1_HEALTH = 50;
static const int32_t TROLL_1_ATACK_DEMAGE = 25;
static const int32_t TROLL_1_PRISE= 25;


static const int32_t TROLL_2_HEALTH = 75;
static const int32_t TROLL_2_ATACK_DEMAGE = 50;
static const int32_t TROLL_2_PRISE= 65;


static const int32_t TROLL_3_HEALTH = 120;
static const int32_t TROLL_3_ATACK_DEMAGE = 75;
static const int32_t TROLL_3_PRISE= 75;

static const int32_t TOWER_HEALTH = 1000;
static const int32_t TOWER_FRAMES_COUNT= 3;
static const int32_t TOWER_FRAME_WIDTH_HEIGHT = 600;

static const int32_t COIN_WIDTH_HEIGHT = 25;

static const int32_t BUTTON_COUNT = 19;
static const int32_t START_GAME_BUTTON_COUNT = 1;

static const int32_t BACKGROUND_IMG_WIDTH = 3000;
static const int32_t BACKGROUND_IMG_HEIGHT= 750;

static const int32_t START_GAME_IMG_WIDTH = 1400;
static const int32_t START_GAME_IMG_HEIGHT= 750;

static const int32_t GAME_OVER_IMG_WIDTH = 1400;
static const int32_t GAME_OVER_IMG_HEIGHT= 750;

static const int32_t ANGELINE_VINATGE_FONT_SIZE = 40;
static const int32_t BUTTON_FRAMES = 2;
static const int32_t ENGINE_TARGET_FRAMES = 120;

static const int32_t TROLL_ATACK_FRAME_IDX= 9;
static const int32_t TERRORIST_ATACK_FRAME_IDX= 5;
static const int32_t ROBOT_ATACK_FRAME_IDX= 8;

static void populateResourceLocation (char* buffer, const char* relativePath){
    #ifdef RELEASE_BUILD
    strcpy(buffer,relativePath);
    #else
        strcpy(buffer, "../");
        strcat(buffer,relativePath);
        
    #endif
}

void createSprite (struct ImageConfig* imgCfg, struct Rectangle** currframe, int32_t framesCount,
                     int32_t Frame_Width,int32_t Frame_Height, char* path)
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
    }
    

}

static void popilateCameCfg( struct GameConfig* cfg){
    cfg->epoch = STONE_AGE;
    cfg->playerMoney = 500;
    cfg->playerXp =0;
    cfg->enemyrXp =0;
    cfg->gameStarted = false;

    cfg->troll_1Cfg.baseCfg.rsrcId = TROLL_1_RUN_ID;
    cfg->troll_1Cfg.runRsrcId = TROLL_1_RUN_ID;
    cfg->troll_1Cfg.atackRsrcId = TROLL_1_ATACK_ID;
    cfg->troll_1Cfg.hurtRsrcId = TROLL_1_HURT_ID;
    cfg->troll_1Cfg.dieRsrcId = TROLL_1_DIE_ID;
    cfg->troll_1Cfg.idleRsrcId = TROLL_1_IDLE_ID;
    cfg->troll_1Cfg.baseCfg.health = TROLL_1_HEALTH;
    cfg->troll_1Cfg.atackDamage = TROLL_1_ATACK_DEMAGE;
    cfg->troll_1Cfg.mode = RUN;
    cfg->troll_1Cfg.deltaMovePx  = MOVE_SPPED;
    cfg->troll_1Cfg.baseCfg.isAlive = true;
    cfg->troll_1Cfg.baseCfg.heroType = TROLL;
    cfg->troll_1Cfg.prise = TROLL_1_PRISE;
    cfg->troll_1Cfg.atackFrame = TROLL_ATACK_FRAME_IDX;

    cfg->troll_2Cfg.baseCfg.rsrcId = TROLL_2_RUN_ID;
    cfg->troll_2Cfg.runRsrcId = TROLL_2_RUN_ID;
    cfg->troll_2Cfg.atackRsrcId = TROLL_2_ATACK_ID;
    cfg->troll_2Cfg.hurtRsrcId = TROLL_2_HURT_ID;
    cfg->troll_2Cfg.dieRsrcId = TROLL_2_DIE_ID;
    cfg->troll_2Cfg.idleRsrcId = TROLL_2_IDLE_ID;
    cfg->troll_2Cfg.baseCfg.health = TROLL_2_HEALTH;
    cfg->troll_2Cfg.atackDamage = TROLL_2_ATACK_DEMAGE;
    cfg->troll_2Cfg.mode = RUN;
    cfg->troll_2Cfg.deltaMovePx  = MOVE_SPPED;
    cfg->troll_2Cfg.baseCfg.isAlive = true;
    cfg->troll_2Cfg.baseCfg.heroType = TROLL;
    cfg->troll_2Cfg.prise = TROLL_2_PRISE;
    cfg->troll_2Cfg.atackFrame = TROLL_ATACK_FRAME_IDX;



    cfg->troll_3Cfg.baseCfg.rsrcId = TROLL_3_RUN_ID;
    cfg->troll_3Cfg.runRsrcId = TROLL_3_RUN_ID;
    cfg->troll_3Cfg.atackRsrcId = TROLL_3_ATACK_ID;
    cfg->troll_3Cfg.hurtRsrcId = TROLL_3_HURT_ID;
    cfg->troll_3Cfg.dieRsrcId = TROLL_3_DIE_ID;
    cfg->troll_3Cfg.idleRsrcId = TROLL_3_IDLE_ID;
    cfg->troll_3Cfg.baseCfg.health = TROLL_3_HEALTH;
    cfg->troll_3Cfg.atackDamage = TROLL_3_ATACK_DEMAGE;
    cfg->troll_3Cfg.mode = RUN;
    cfg->troll_3Cfg.deltaMovePx  = MOVE_SPPED;
    cfg->troll_3Cfg.baseCfg.isAlive = true;
    cfg->troll_3Cfg.baseCfg.heroType = TROLL;
    cfg->troll_3Cfg.prise = TROLL_3_PRISE;
    cfg->troll_3Cfg.atackFrame = TROLL_ATACK_FRAME_IDX;



    cfg->terrorist_1_Cfg.heroCfg.baseCfg.rsrcId = TERRORIST_1_RUN_ID;
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
    cfg->terrorist_1_Cfg.heroCfg.deltaMovePx = MOVE_SPPED;
    cfg->terrorist_1_Cfg.heroCfg.mode = RUN;
    cfg->terrorist_1_Cfg.heroCfg.prise = TERRORIST_1_PRISE ;
    cfg->terrorist_1_Cfg.heroCfg.baseCfg.heroType = TERRORIST;
    cfg->terrorist_1_Cfg.heroCfg.atackFrame = TERRORIST_ATACK_FRAME_IDX;

    cfg->terrorist_2_Cfg.heroCfg.baseCfg.rsrcId = TERRORIST_2_RUN_ID;
    cfg->terrorist_2_Cfg.heroCfg.runRsrcId = TERRORIST_2_RUN_ID;
    cfg->terrorist_2_Cfg.heroCfg.atackRsrcId = TERRORIST_2_ATACK_ID;
    cfg->terrorist_2_Cfg.heroCfg.idleRsrcId = TERRORIST_2_IDLE_ID;
    cfg->terrorist_2_Cfg.heroCfg.dieRsrcId = TERRORIST_2_DIE_ID;
    cfg->terrorist_2_Cfg.heroCfg.hurtRsrcId = TERRORIST_2_HURT_ID;
    cfg->terrorist_2_Cfg.longAtackRsrcId = TERRORIST_2_LONG_ATACK_ID;
    cfg->terrorist_2_Cfg.heroCfg.atackDamage = TERRORIST_2_SHORT_ATACK_DEMAGE;
    cfg->terrorist_2_Cfg.longAtackDamage = TERRORIST_2_LONG_ATACK_DEMAGE;
    cfg->terrorist_2_Cfg.heroCfg.baseCfg.health = TERRORIST_2_HEALTH;
    cfg->terrorist_2_Cfg.heroCfg.baseCfg.isAlive = true;
    cfg->terrorist_2_Cfg.heroCfg.deltaMovePx = MOVE_SPPED;
    cfg->terrorist_2_Cfg.heroCfg.mode = RUN;
    cfg->terrorist_2_Cfg.heroCfg.baseCfg.heroType = TERRORIST;
    cfg->terrorist_2_Cfg.heroCfg.prise = TERRORIST_2_PRISE ;
    cfg->terrorist_2_Cfg.heroCfg.atackFrame = TERRORIST_ATACK_FRAME_IDX;



    cfg->terrorist_3_Cfg.heroCfg.baseCfg.rsrcId = TERRORIST_3_RUN_ID;
    cfg->terrorist_3_Cfg.heroCfg.runRsrcId = TERRORIST_3_RUN_ID;
    cfg->terrorist_3_Cfg.heroCfg.atackRsrcId = TERRORIST_3_ATACK_ID;
    cfg->terrorist_3_Cfg.heroCfg.idleRsrcId = TERRORIST_3_IDLE_ID;
    cfg->terrorist_3_Cfg.heroCfg.dieRsrcId = TERRORIST_3_DIE_ID;
    cfg->terrorist_3_Cfg.heroCfg.hurtRsrcId = TERRORIST_3_HURT_ID;
    cfg->terrorist_3_Cfg.longAtackRsrcId = TERRORIST_3_LONG_ATACK_ID;
    cfg->terrorist_3_Cfg.heroCfg.atackDamage = TERRORIST_3_SHORT_ATACK_DEMAGE;
    cfg->terrorist_3_Cfg.longAtackDamage = TERRORIST_3_LONG_ATACK_DEMAGE;
    cfg->terrorist_3_Cfg.heroCfg.baseCfg.health = TERRORIST_3_HEALTH;
    cfg->terrorist_3_Cfg.heroCfg.baseCfg.isAlive = true;
    cfg->terrorist_3_Cfg.heroCfg.deltaMovePx = MOVE_SPPED;
    cfg->terrorist_3_Cfg.heroCfg.mode = RUN;
    cfg->terrorist_3_Cfg.heroCfg.baseCfg.heroType = TERRORIST;
    cfg->terrorist_3_Cfg.heroCfg.prise = TERRORIST_3_PRISE ;
    cfg->terrorist_3_Cfg.heroCfg.atackFrame = TERRORIST_ATACK_FRAME_IDX;



    cfg->robot_1_Cfg.heroCfg.baseCfg.rsrcId = ROBOT_1_RUN_ID;
    cfg->robot_1_Cfg.heroCfg.runRsrcId = ROBOT_1_RUN_ID;
    cfg->robot_1_Cfg.heroCfg.atackRsrcId = ROBOT_1_ATACK_ID;
    cfg->robot_1_Cfg.heroCfg.idleRsrcId = ROBOT_1_IDLE_ID;
    cfg->robot_1_Cfg.heroCfg.dieRsrcId = ROBOT_1_DIE_ID;
    cfg->robot_1_Cfg.heroCfg.hurtRsrcId = ROBOT_1_HURT_ID;
    cfg->robot_1_Cfg.longAtackRsrcId = ROBOT_1_LONG_ATACK_ID;
    cfg->robot_1_Cfg.heroCfg.atackDamage = ROBOT_1_SHORT_ATACK_DEMAGE;
    cfg->robot_1_Cfg.longAtackDamage = ROBOT_1_LONG_ATACK_DEMAGE;
    cfg->robot_1_Cfg.heroCfg.baseCfg.health = ROBOT_1_HEALTH;
    cfg->robot_1_Cfg.heroCfg.baseCfg.isAlive = true;
    cfg->robot_1_Cfg.heroCfg.deltaMovePx = MOVE_SPPED;
    cfg->robot_1_Cfg.heroCfg.mode = RUN;
    cfg->robot_1_Cfg.heroCfg.baseCfg.heroType = ROBOT;
    cfg->robot_1_Cfg.heroCfg.prise = ROBOT_1_PRISE;
    cfg->robot_1_Cfg.heroCfg.atackFrame = ROBOT_ATACK_FRAME_IDX;



    cfg->robot_2_Cfg.heroCfg.baseCfg.rsrcId = ROBOT_2_RUN_ID;
    cfg->robot_2_Cfg.heroCfg.runRsrcId = ROBOT_2_RUN_ID;
    cfg->robot_2_Cfg.heroCfg.atackRsrcId = ROBOT_2_ATACK_ID;
    cfg->robot_2_Cfg.heroCfg.idleRsrcId = ROBOT_2_IDLE_ID;
    cfg->robot_2_Cfg.heroCfg.dieRsrcId = ROBOT_2_DIE_ID;
    cfg->robot_2_Cfg.heroCfg.hurtRsrcId = ROBOT_2_HURT_ID;
    cfg->robot_2_Cfg.longAtackRsrcId = ROBOT_2_LONG_ATACK_ID;
    cfg->robot_2_Cfg.heroCfg.atackDamage = ROBOT_2_SHORT_ATACK_DEMAGE;
    cfg->robot_2_Cfg.longAtackDamage = ROBOT_2_LONG_ATACK_DEMAGE;
    cfg->robot_2_Cfg.heroCfg.baseCfg.health = ROBOT_2_HEALTH;
    cfg->robot_2_Cfg.heroCfg.baseCfg.isAlive = true;
    cfg->robot_2_Cfg.heroCfg.deltaMovePx = MOVE_SPPED;
    cfg->robot_2_Cfg.heroCfg.mode = RUN;
    cfg->robot_2_Cfg.heroCfg.baseCfg.heroType = ROBOT;
    cfg->robot_2_Cfg.heroCfg.prise = ROBOT_2_PRISE;
    cfg->robot_2_Cfg.heroCfg.atackFrame = ROBOT_ATACK_FRAME_IDX;

    cfg->robot_3_Cfg.heroCfg.baseCfg.rsrcId = ROBOT_3_RUN_ID;
    cfg->robot_3_Cfg.heroCfg.runRsrcId = ROBOT_3_RUN_ID;
    cfg->robot_3_Cfg.heroCfg.atackRsrcId = ROBOT_3_ATACK_ID;
    cfg->robot_3_Cfg.heroCfg.idleRsrcId = ROBOT_3_IDLE_ID;
    cfg->robot_3_Cfg.heroCfg.dieRsrcId = ROBOT_3_DIE_ID;
    cfg->robot_3_Cfg.heroCfg.hurtRsrcId = ROBOT_3_HURT_ID;
    cfg->robot_3_Cfg.longAtackRsrcId = ROBOT_3_LONG_ATACK_ID;
    cfg->robot_3_Cfg.heroCfg.atackDamage = ROBOT_3_SHORT_ATACK_DEMAGE;
    cfg->robot_3_Cfg.longAtackDamage = ROBOT_3_LONG_ATACK_DEMAGE;
    cfg->robot_3_Cfg.heroCfg.baseCfg.health = ROBOT_3_HEALTH;
    cfg->robot_3_Cfg.heroCfg.baseCfg.isAlive = true;
    cfg->robot_3_Cfg.heroCfg.deltaMovePx = MOVE_SPPED;
    cfg->robot_3_Cfg.heroCfg.mode = RUN;
    cfg->robot_3_Cfg.heroCfg.baseCfg.heroType = ROBOT;
    cfg->robot_3_Cfg.heroCfg.prise = ROBOT_3_PRISE;
    cfg->robot_3_Cfg.heroCfg.atackFrame = ROBOT_ATACK_FRAME_IDX;

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

    cfg->robotBtnRsrcId = ROBOT_1_BUTTON_ID;
    cfg->robotBtnEnemyRsrcId = ROBOT_1_BUTTON_ENEMY_ID;
    cfg->robot2BtnRsrcId = ROBOT_2_BUTTON_ID;
    cfg->robot2BtnEnemyRsrcId = ROBOT_2_BUTTON_ENEMY_ID;
    cfg->robot3BtnRsrcId = ROBOT_3_BUTTON_ID;
    cfg->robot3BtnEnemyRsrcId = ROBOT_3_BUTTON_ENEMY_ID;

    cfg->startGameBtnRsrcId = START_GAME_BUTTON_ID;

    cfg->starBtnRsrcId = STAR_BUTTON_ID;
}

static void populateWindowCfg(struct MonitorWindowCfg* cfg){
    cfg->windowFlag = WINDOWS_SHOWN;
    cfg->windowWidth = SCREEN_WIDTH;
    cfg->windowHeight = SCREEN_HEIGHT;
    cfg->windowName = "Age of war :)";
    cfg->windowPos = POINT_UNDEFINED;
}

static void populateImageContainerCfg(struct ImageContainerCfg* cfg){
    struct Rectangle* currframe = NULL;
    struct ImageConfig imgCfg;

    //Troll_1 die sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_1_sprite_die.png");
    insertImageConfig(cfg, TROLL_1_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);
    
    //Troll_2 die sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_2_sprite_die.png");                  
    insertImageConfig(cfg, TROLL_2_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_3 die sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_3_sprite_die.png");
    insertImageConfig(cfg, TROLL_3_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_1  run sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_1_sprite_run.png");
    insertImageConfig(cfg, TROLL_1_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_2  run sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_2_sprite_run.png");
    insertImageConfig(cfg, TROLL_2_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_3  run sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_3_sprite_run.png");
    insertImageConfig(cfg, TROLL_3_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_1  idle sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_1_sprite_idle.png");
    insertImageConfig(cfg, TROLL_1_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_2  idle sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_2_sprite_idle.png");
    insertImageConfig(cfg, TROLL_2_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_3  idle sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_3_sprite_idle.png");
    insertImageConfig(cfg, TROLL_3_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_1  atack sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_1_sprite_atack.png");
    insertImageConfig(cfg, TROLL_1_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_2  atack sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_2_sprite_atack.png");
    insertImageConfig(cfg, TROLL_2_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_3  atack sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_3_sprite_atack.png");
    insertImageConfig(cfg, TROLL_3_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_1  hurt sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_1_sprite_hurt.png");
    insertImageConfig(cfg, TROLL_1_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Troll_2  hurt sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_2_sprite_hurt.png");
    insertImageConfig(cfg, TROLL_2_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

     //Troll_3  hurt sprite
    createSprite(&imgCfg, &currframe, TROLL_FRAMES_COUNT, TROLL_FRAME_WIDTH, TROLL_FRAME_HEIGHT,
                    "resources/p/sprites/troll_3_sprite_hurt.png");          
    insertImageConfig(cfg, TROLL_3_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 1 run
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_1_sprite_run.png");
    insertImageConfig(cfg, TERRORIST_1_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 1 idle
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_1_sprite_idle.png");
    insertImageConfig(cfg, TERRORIST_1_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 1 die
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_1_sprite_die.png");
    insertImageConfig(cfg, TERRORIST_1_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 1 atack
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_1_sprite_atack.png");
    insertImageConfig(cfg, TERRORIST_1_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 1 hurt
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_1_sprite_hurt.png");
    insertImageConfig(cfg, TERRORIST_1_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);


    //Terrorist 1 atack long
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_1_sprite_atack.png");
    insertImageConfig(cfg, TERRORIST_1_LONG_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //----Terrorist 2-----
    //Terrorist 2 run
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_2_sprite_run.png");
    insertImageConfig(cfg, TERRORIST_2_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 2 idle
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_2_sprite_idle.png");
    insertImageConfig(cfg, TERRORIST_2_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 2 die
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_2_sprite_die.png");
    insertImageConfig(cfg, TERRORIST_2_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 2 atack
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_2_sprite_atack.png");
    insertImageConfig(cfg, TERRORIST_2_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 2 hurt
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_2_sprite_hurt.png");
    insertImageConfig(cfg, TERRORIST_2_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 2 atack long
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_2_sprite_atack.png");
    insertImageConfig(cfg, TERRORIST_2_LONG_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 3 ----

    //Terrorist 3 run
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_3_sprite_run.png");
    insertImageConfig(cfg, TERRORIST_3_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 3 idle
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_3_sprite_idle.png");
    insertImageConfig(cfg, TERRORIST_3_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 3 die
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_3_sprite_die.png");
    insertImageConfig(cfg, TERRORIST_3_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 3 atack
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_3_sprite_atack.png");
    insertImageConfig(cfg, TERRORIST_3_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 3 hurt
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_3_sprite_hurt.png");
    insertImageConfig(cfg, TERRORIST_3_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Terrorist 3 atack long
    createSprite(&imgCfg, &currframe, TERRORIST_FRAMES_COUNT, TERRORIST_FRAME_WIDTH, TERRORIST_FRAME_HEIGHT,
                    "resources/p/sprites/terrorist_3_sprite_atack.png");
    insertImageConfig(cfg, TERRORIST_3_LONG_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    // ------ROBOT 1------

    //Robot 1 run
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_1_sprite_run.png");
    insertImageConfig(cfg, ROBOT_1_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 1 idle
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_1_sprite_idle.png");
    insertImageConfig(cfg, ROBOT_1_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 1 die
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_1_sprite_die.png");
    insertImageConfig(cfg, ROBOT_1_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 1 atack
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_1_sprite_atack.png");
    insertImageConfig(cfg, ROBOT_1_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 1 hurt
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_1_sprite_hurt.png");
    insertImageConfig(cfg, ROBOT_1_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 1 atack long
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_1_sprite_atack.png");
    insertImageConfig(cfg, ROBOT_1_LONG_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    // ------ROBOT 2------

    //Robot 2 run
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_2_sprite_run.png");
    insertImageConfig(cfg, ROBOT_2_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 2 idle
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_2_sprite_idle.png");
    insertImageConfig(cfg, ROBOT_2_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 2 die
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_2_sprite_die.png");
    insertImageConfig(cfg, ROBOT_2_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 2 atack
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_2_sprite_atack.png");
    insertImageConfig(cfg, ROBOT_2_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 2 hurt
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_2_sprite_hurt.png");
    insertImageConfig(cfg, ROBOT_2_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 2 atack long
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_2_sprite_atack.png");
    insertImageConfig(cfg, ROBOT_2_LONG_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);


    // ------ROBOT 3 ------

    //Robot 3 run
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_3_sprite_run.png");
    insertImageConfig(cfg, ROBOT_3_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 3 idle
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_3_sprite_idle.png");
    insertImageConfig(cfg, ROBOT_3_IDLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 3 die
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_3_sprite_die.png");
    insertImageConfig(cfg, ROBOT_3_DIE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 3 atack
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_3_sprite_atack.png");
    insertImageConfig(cfg, ROBOT_3_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 3 hurt
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_3_sprite_hurt.png");
    insertImageConfig(cfg, ROBOT_3_HURT_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Robot 3 atack long
    createSprite(&imgCfg, &currframe, ROBOT_FRAMES_COUNT, ROBOT_FRAME_WIDTH, ROBOT_FRAME_HEIGHT,
                    "resources/p/sprites/robot_3_sprite_atack.png");
    insertImageConfig(cfg, ROBOT_3_LONG_ATACK_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);


    //Catsle player sprite
    createSprite(&imgCfg, &currframe, TOWER_FRAMES_COUNT, TOWER_FRAME_WIDTH_HEIGHT, TOWER_FRAME_WIDTH_HEIGHT,
                    "resources/p/sprites/castle_1_sprite.png");          
    insertImageConfig(cfg, PLAYER_TOWER_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //Catsle enemy sprite
    createSprite(&imgCfg, &currframe, TOWER_FRAMES_COUNT, TOWER_FRAME_WIDTH_HEIGHT, TOWER_FRAME_WIDTH_HEIGHT,
                    "resources/p/sprites/castle_2_sprite.png");          
    insertImageConfig(cfg, ENEMY_TOWER_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);
    
    //Background
    createSprite(&imgCfg, &currframe, 1, BACKGROUND_IMG_WIDTH, BACKGROUND_IMG_HEIGHT,
                    "resources/p/background_1_3000x750.png");          
    insertImageConfig(cfg, BACKGROUND_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);
    free(getElementVector(&imgCfg.frames, 0));

    //Start game img
    createSprite(&imgCfg, &currframe, 1, START_GAME_IMG_WIDTH, START_GAME_IMG_HEIGHT,
                    "resources/p/background_1400x750.png");          
    insertImageConfig(cfg, START_GAME_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //button table
    createSprite(&imgCfg, &currframe, 1, BUTTON_TABLE_FRAME_WIDTH, BUTTON_TABLE_FRAME_HEIGHT,
                    "resources/p/button_table.png");          
    insertImageConfig(cfg, BUTTON_TABLE_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    //game over img
    createSprite(&imgCfg, &currframe, 1, GAME_OVER_IMG_WIDTH, GAME_OVER_IMG_HEIGHT,
                    "resources/p/game_over.png");          
    insertImageConfig(cfg, GAME_OVER_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    // win game img
    createSprite(&imgCfg, &currframe, 1, GAME_OVER_IMG_WIDTH, GAME_OVER_IMG_HEIGHT,
                    "resources/p/win_game_screen.png");          
    insertImageConfig(cfg, WIN_GAME_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

    // coin img
    createSprite(&imgCfg, &currframe, 1, COIN_WIDTH_HEIGHT, COIN_WIDTH_HEIGHT,
                    "resources/p/coin.png");          
    insertImageConfig(cfg, COIN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }
    freeVector(&imgCfg.frames);

//buttons
    char* buttonPaths[19] = 
    {
        "resources/p/buttons/troll_1_face.png", "resources/p/buttons/troll_1_face.png",
        "resources/p/buttons/troll_2_face.png", "resources/p/buttons/troll_2_face.png",
        "resources/p/buttons/troll_3_face.png", "resources/p/buttons/troll_3_face.png",
        
        "resources/p/buttons/terrorist_1_face.png", "resources/p/buttons/terrorist_1_face.png",
        "resources/p/buttons/terrorist_2_face.png", "resources/p/buttons/terrorist_2_face.png",
        "resources/p/buttons/terrorist_3_face.png", "resources/p/buttons/terrorist_3_face.png",

        "resources/p/buttons/robot_1_face.png", "resources/p/buttons/robot_1_face.png",
        "resources/p/buttons/robot_2_face.png", "resources/p/buttons/robot_2_face.png",
        "resources/p/buttons/robot_3_face.png", "resources/p/buttons/robot_3_face.png",

        "resources/p/buttons/star_button.png",
        };
    const int32_t buttonRsrcIds[19] = 
            {
                TROLL_1_BUTTON_ID, TROLL_1_BUTTON_ENEMY_ID,
                TROLL_2_BUTTON_ID, TROLL_2_BUTTON_ENEMY_ID,
                TROLL_3_BUTTON_ID, TROLL_3_BUTTON_ENEMY_ID,
                
                TERRORIST_1_BUTTON_ID, TERRORIST_1_BUTTON_ENEMY_ID,
                TERRORIST_2_BUTTON_ID, TERRORIST_2_BUTTON_ENEMY_ID,
                TERRORIST_3_BUTTON_ID, TERRORIST_3_BUTTON_ENEMY_ID,

                ROBOT_1_BUTTON_ID, ROBOT_1_BUTTON_ENEMY_ID,
                ROBOT_2_BUTTON_ID, ROBOT_2_BUTTON_ENEMY_ID,
                ROBOT_3_BUTTON_ID, ROBOT_3_BUTTON_ENEMY_ID,

                STAR_BUTTON_ID,
            };

    for (int32_t buttonId = 0; buttonId < BUTTON_COUNT; ++buttonId) {
        strcpy(imgCfg.location, buttonPaths[buttonId]);

        createSprite(&imgCfg, &currframe, BUTTON_FRAMES, BUTTON_FRAME_WIDTH_HEIGHT, BUTTON_FRAME_WIDTH_HEIGHT,
                    buttonPaths[buttonId]);
        populateResourceLocation(imgCfg.location, buttonPaths[buttonId]);
        insertImageConfig(cfg, buttonRsrcIds[buttonId] , &imgCfg);
        clearElementsVector(&imgCfg.frames);
        for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
        {
            free(getElementVector(&imgCfg.frames, i));
        }
        freeVector(&imgCfg.frames);
    }

// start game buttons
    const int32_t start_game_buttonRsrcIds[1] = 
            {
                START_GAME_BUTTON_ID,
            };
    
    char* start_game_buttonPaths[1] = 
    {
        "resources/p/buttons/start_button.png",
        };

    for (int32_t buttonId = 0; buttonId < START_GAME_BUTTON_COUNT; ++buttonId) {
        strcpy(imgCfg.location, start_game_buttonPaths[buttonId]);

        createSprite(&imgCfg, &currframe, BUTTON_FRAMES, START_GAME_BUTTON_FRAME_WIDTH,
                     START_GAME_BUTTON_FRAME_HEIGHT, start_game_buttonPaths[buttonId]);

        populateResourceLocation(imgCfg.location, start_game_buttonPaths[buttonId]);
        insertImageConfig(cfg, start_game_buttonRsrcIds[buttonId] , &imgCfg);
        clearElementsVector(&imgCfg.frames);
        for (size_t i = 0; i < getSizeVector(&imgCfg.frames); i++)
    {
        free(getElementVector(&imgCfg.frames, i));

    }

freeVector(&imgCfg.frames);    }


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
