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


static const int32_t SCREEN_WIDTH = 1400;
static const int32_t SCREEN_HEIGHT = 750;

static const int32_t TROLL_1_ID_FRAMES_COUNT = 10;
static const int32_t TROLL_1_FRAME_WIDTH = 200;
static const int32_t TROLL_1_FRAME_HEIGHT = 300;
static const int32_t TROLL_1_BUTTON_FRAME_WIDTH_HEIGHT = 50;

static const int32_t TROLL_1_HEALTH = 50;
static const int32_t TROLL_1_ATACK_DEMAGE = 25;

static const int32_t TOWER_HEALTH = 50;
static const int32_t TOWER_FRAMES_COUNT= 50;
static const int32_t TOWER_FRAME_WIDTH_HEIGHT = 600;

static const int32_t BUTTON_COUNT = 2;

static const int32_t BACKGROUND_IMG_WIDTH = 3000;
static const int32_t BACKGROUND_IMG_HEIGHT= 750;

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

static void popilateCameCfg( struct GameConfig* cfg){
    UNUSED(cfg);
    cfg->heroCfg.rsrcId = TROLL_1_RUN_ID;
    cfg->heroCfg.runRsrcId = TROLL_1_RUN_ID;
    cfg->heroCfg.atackRsrcId = TROLL_1_ATACK_ID;
    cfg->heroCfg.dieRsrcId = TROLL_1_DIE_ID;
    cfg->heroCfg.hurtRsrcId = TROLL_1_HURT_ID;
    cfg->heroCfg.idleRsrcId = TROLL_1_IDLE_ID;
    cfg->heroCfg.health = TROLL_1_HEALTH;
    cfg->heroCfg.atackDamage = TROLL_1_ATACK_DEMAGE;
    cfg->heroCfg.mode = RUN;
    cfg->heroCfg.horSteps = 40;
    cfg->heroCfg.verSteps = 20;
    cfg->heroCfg.deltaMovePx = 40;

    cfg->playerTowerCfg.health = TOWER_HEALTH;
    cfg->playerTowerCfg.rsrcId = PLAYER_TOWER_ID;
    cfg->playerTowerCfg.playerType = PLAYER;

    cfg->enemyTowerCfg.health = TOWER_HEALTH;
    cfg->enemyTowerCfg.rsrcId = ENEMY_TOWER_ID;
    cfg->enemyTowerCfg.playerType = ENEMY;

    cfg->trollBtnRsrcId = TROLL_1_BUTTON_ID;
    cfg->trollBtnEnemyRsrcId = TROLL_1_BUTTON_ENEMY_ID;
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
    
    //Troll die sprite
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
    //end Troll die sprite

    //Troll run sprite
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

    populateResourceLocation(imgCfg.location, "resources/p/sprites/troll_1_sprite_run.png");
    insertImageConfig(cfg, TROLL_1_RUN_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    //end Troll run sprite

    //Troll idle sprite
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
    //end Troll idle sprite

    //Troll atack sprite
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
    //end Troll atack sprite

    //Troll hurt sprite
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
    //end Troll hurt sprite

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

//buttons
    const char* buttonPaths[2] = {"resources/p/buttons/island_boy_face.png", "resources/p/buttons/troll_1_face.png"};
    const int32_t buttonRsrcIds[2] = { TROLL_1_BUTTON_ID, TROLL_1_BUTTON_ENEMY_ID};

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
