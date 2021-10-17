#include "Engine/EngineConfigLoader.h"
#include <string.h>


static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;
static void populateWindowCfg(struct MonitorWindowCfg* cfg){
    cfg->windowFlag = WINDOWS_SHOWN;
    cfg->windowWidth = SCREEN_WIDTH;
    cfg->windowHeight = SCREEN_HEIGHT;
    cfg->windowName = "Hello";
    cfg->windowPos = POINT_UNDEFINED;
}
static void populateGameCfg(struct GameConfig* cfg){
    const char *imagePaths[IMAGES_COUNT] = { "../resources/up.png",
      "../resources/down.png", "../resources/left.png",
      "../resources/right.png", "../resources/press_keys.png", "../resources/layer_2.png"};

    for (int32_t i = 0; i < IMAGES_COUNT; i++)
    {
        strcpy(cfg->imgLoadPaths[i], imagePaths[i]);
    }
}

struct EngineConfig loadEngineConfig() {

    struct EngineConfig cfg;    
    populateWindowCfg(&cfg.windowCfg);
    populateGameCfg(&cfg.gameCfg);
    
    return cfg;
}