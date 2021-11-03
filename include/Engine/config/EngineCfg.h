#ifndef ENGINE_ENGINECFG_H_
#define ENGINE_ENGINECFG_H_

#include <stdint.h>
#include "sdl_utils/config/MonitorWindowCfg.h"
#include "sdl_utils/config/ImageContainerCfg.h"
#include "sdl_utils/config/TextContainerCfg.h"
#include "Game/config/GameCfg.h"
#include "manager_utils/managers/config/DrawMgrCfg.h"
#include "manager_utils/managers/config/ManagerHandlerCfg.h"
#include "Game/config/GameCfg.h"

struct EngineConfig {
    struct ManagerHandlerCfg managerHandlerCfg;
    struct GameConfig gameCfg;
    int32_t debugConsoleFontId;

};

#endif 
