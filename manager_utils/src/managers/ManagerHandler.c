#include "manager_utils/managers/ManagerHandler.h"
#include "manager_utils/managers/DrawMgr.h"
#include "manager_utils/managers/ResourceMngr.h"
#include "manager_utils/managers/ResourceMngrProxy.h"
#include "manager_utils/managers/DrawMgrProxy.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "stdlib.h"
#include "string.h"


#include "manager_utils/managers/config/ManagerHandlerCfg.h"


int32_t initManagerHandler(const struct ManagerHandlerCfg* cfg){
    gDrawMgr = (struct DrawMgr*)malloc(sizeof(struct DrawMgr));
    gDrawMgrProxy = (struct DrawMgrProxy*)malloc(sizeof(struct DrawMgrProxy));
    if(gDrawMgr == NULL){
        LOGERR("bad allocation for drawmgr");
        return FAILURE;
    }
    if(gDrawMgrProxy == NULL){
        LOGERR("bad allocation for gDrawMgrProxy");
        return FAILURE;
    }
    memset(gDrawMgr, 0, sizeof(struct DrawMgr));
    memset(gDrawMgrProxy, 0, sizeof(struct DrawMgrProxy));

    if (SUCCESS != initDrawMgr(gDrawMgr, &cfg->drawMgrCfg)) {
        LOGERR("initImageContainer() failed");
        return FAILURE;
    }

    gResourceMgr = (struct ResourceMgr*)malloc(sizeof(struct ResourceMgr));
    gResourceMngrProxy = (struct ResourceMngrProxy*)malloc(sizeof(struct ResourceMngrProxy));
    if(gResourceMngrProxy == NULL){
        LOGERR("bad allocation for gResourceMngrProxy");
        return FAILURE;
    }

    if(gResourceMgr == NULL){
        LOGERR("bad allocation for ResourceMgr");
        return FAILURE;
    }
    memset(gResourceMgr, 0, sizeof(struct ResourceMgr));
    memset(gResourceMngrProxy, 0, sizeof(struct ResourceMngrProxy));
    if (SUCCESS != initResourceMgr(gResourceMgr, &cfg->resourceMgrCfg)) {
        LOGERR("initResourceMgr() failed");
        return FAILURE;
    }

    return SUCCESS;
}
void deinitManagerHadnler(){
    deinitDrawMgr(gDrawMgr);
    free(gDrawMgr);
    free(gDrawMgrProxy);
    gDrawMgrProxy = NULL;
    gDrawMgr = NULL;
} 