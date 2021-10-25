#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_RESOURCEMGRCFG_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_RESOURCEMGRCFG_H_
#include "sdl_utils/config/ImageContainerCfg.h"
#include "sdl_utils/config/TextContainerCfg.h"
struct ResourceMgrCfg{
    struct ImageContainerCfg imgContainerCfg;
    struct TextContainerCfg textContainerCfg;
};


#endif