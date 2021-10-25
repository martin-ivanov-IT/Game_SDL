#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_MANAGERHADLER_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_MANAGERHADLER_H_
#include <stdint.h>
struct ManagerHandlerCfg;

int32_t initManagerHandler(const struct ManagerHandlerCfg* cfg);
void deinitManagerHadnler(); 

#endif
