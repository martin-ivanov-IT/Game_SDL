#include "Engine/EngineConfigLoader.h"
#include "common/CommonDefines.h"
#include "sdl_utils/config/ImageContainerCfg.h"
#include "sdl_utils/config/TextContainerCfg.h"
#include <string.h>
#include <stdlib.h>
#include "utils/drawing/Rectangle.h"

static const int32_t SCREEN_WIDTH = 1024;
static const int32_t SCREEN_HEIGHT = 800;

static const int32_t GIRL_FRAMES_COUNT = 6;
static const int32_t GIRL_FRAME_WIDTH = 256;
static const int32_t GIRL_FRAME_HEIGHT = 220;

static const int32_t WHEEL_IMG_WIDTH_HEIGHT = 695;

static const int32_t ANGELINE_VINATGE_FONT_SIZE = 40;



static void populateResourceLocation (char* buffer, const char* relativePath){
    #ifdef RELEASE_BUILD
    strcpy(buffer,relativePath);
    #else
        strcpy(buffer, "../");
        strcat(buffer,relativePath);
        
    #endif
}
// static void popilateCameCfg( struct GameConfig* cfg){
//     cfg->heroRsrcID = RUNNING_GIRL_ID;
// }
static void populateWindowCfg(struct MonitorWindowCfg* cfg){
    cfg->windowFlag = WINDOWS_SHOWN;
    cfg->windowWidth = SCREEN_WIDTH;
    cfg->windowHeight = SCREEN_HEIGHT;
    cfg->windowName = "Hello";
    cfg->windowPos = POINT_UNDEFINED;
}

static void populateImageContainerCfg(struct ImageContainerCfg* cfg){
    struct ImageConfig imgCfg;
    initVector(&imgCfg.frames,10);
    struct Rectangle* currframe = NULL;
    for (int32_t i = 0; i < GIRL_FRAMES_COUNT; i++)
    {
        currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
        currframe->x = 0+(GIRL_FRAME_WIDTH*i);
        currframe->y = 0;
        currframe->w = GIRL_FRAME_WIDTH;
        currframe->h = GIRL_FRAME_HEIGHT;
        pushElementVector(&imgCfg.frames, currframe);
    }

    populateResourceLocation(imgCfg.location, "resources/p/sprites/running_girl.png");
    insertImageConfig(cfg, RUNNING_GIRL_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);

    currframe = (struct Rectangle*)malloc( sizeof(struct Rectangle));
    currframe->x = 0;
    currframe->y = 0;
    currframe->w = WHEEL_IMG_WIDTH_HEIGHT;
    currframe->h = WHEEL_IMG_WIDTH_HEIGHT;
    pushElementVector(&imgCfg.frames, currframe);
    populateResourceLocation(imgCfg.location, "resources/p/wheel.png");
    insertImageConfig(cfg, WHEEL_ID , &imgCfg);
    clearElementsVector(&imgCfg.frames);
    
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
    populateImageContainerCfg(&cfg->resourceMgrCfg.imgContainerCfg);
    populateTextContainerCfg(&cfg->resourceMgrCfg.textContainerCfg);
}
struct EngineConfig loadEngineConfig() {

    struct EngineConfig cfg; 
    memset(&cfg, 0, sizeof(struct EngineConfig));
    populateManagerHandlerCfg(&cfg.managerHandlerCfg);   
    
    return cfg;
}
