#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_MANAGERHADNLERCFG_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_MANAGERHADNLERCFG_H_

#include "manager_utils/managers/config/DrawMgrCfg.h"
#include "manager_utils/managers/config/ResourceMngrCfg.h"


struct ManagerHandlerCfg {
    struct DrawMgrCfg drawMgrCfg;
    struct ResourceMgrCfg resourceMgrCfg;
};

#endif