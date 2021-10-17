#ifndef ENGINE_ENGINECFG_H_
#define ENGINE_ENGINECFG_H_

#include <stdint.h>
#include "sdl_utils/config/MonitorWindowCfg.h"
#include "Game/config/GameCfg.h"


struct EngineConfig {
    struct MonitorWindowCfg windowCfg;
    struct GameConfig gameCfg;
};

#endif 
