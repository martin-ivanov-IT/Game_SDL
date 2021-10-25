#include "Engine/EngineConfigLoader.h"
#include "common/CommonDefines.h"
#include "sdl_utils/config/ImageContainerCfg.h"
#include "sdl_utils/config/TextContainerCfg.h"
#include <string.h>


static const int32_t SCREEN_WIDTH = 640;
static const int32_t SCREEN_HEIGHT = 480;

static const int32_t PRESS_KEYS_IMG_WIDTH = 640;
static const int32_t PRESS_KEYS_IMG_HEIGHT = 480;

static const int32_t LAYER2_IMG_WIDTH_HEIGHT = 150;

static const int32_t ANGELINE_VINATGE_FONT_SIZE = 40;

static void populateResourceLocation (char* buffer, const char* relativePath){
    #ifdef RELEASE_BUILD
    strcpy(buffer,relativePath);
    #else
        strcpy(buffer, "../");
        strcat(buffer,relativePath);
        
    #endif
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
    imgCfg.width = PRESS_KEYS_IMG_WIDTH;
    imgCfg.height = PRESS_KEYS_IMG_HEIGHT;
    populateResourceLocation(imgCfg.location, "resources/p/press_keys.png");
    insertImageConfig(cfg, PRESS_KEYS_TEXTURE_ID , &imgCfg);

    imgCfg.width = LAYER2_IMG_WIDTH_HEIGHT;
    imgCfg.height = LAYER2_IMG_WIDTH_HEIGHT;
    populateResourceLocation(imgCfg.location, "resources/p/layer_2.png");
    insertImageConfig(cfg, LAYER2_TEXTURE_ID , &imgCfg);
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
