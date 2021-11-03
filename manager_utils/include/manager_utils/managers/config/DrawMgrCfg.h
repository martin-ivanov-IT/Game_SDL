#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_DRAWMGRCFG_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_DRAWMGRCFG_H_
#include "sdl_utils/config/MonitorWindowCfg.h"
struct DrawMgrCfg{
    struct MonitorWindowCfg windowCfg;
    int64_t maxFrames;
};




#endif