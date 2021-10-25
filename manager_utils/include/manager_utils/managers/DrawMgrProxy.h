#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_DRAWMGRVTABLE_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_DRAWMGRVTABLE_H_
struct DrawParams;
struct BlendMode;
struct DrawMgrProxy {
    void (*clearScreenDrawMgr)();
    void (*finishFrameDrawMgr)();
    void (*addDrawCmdDrawMgr)(const struct DrawParams *drawParams);
    void (*setWidgetBlendModeDrawMgr)(const struct DrawParams *drawParams, BlendMode blendmode);
    void (*setWidgetOpacityDrawMgr)(const struct DrawParams *drawParams);
};

extern struct DrawMgrProxy *gDrawMgrProxy;

// void clearScreenDrawMgr(struct DrawMgr *self);

// void finishFrameDrawMgr(struct DrawMgr *self);

// void addDrawCmdDrawMgr(struct DrawMgr *self, const struct DrawParams *drawParams);

// void setWidgetBlendModeDrawMgr(struct DrawMgr *self, const struct DrawParams *drawParams, BlendMode blendmode);

// void setWidgetOpacityDrawMgr(struct DrawMgr *self, const struct DrawParams *drawParams);
#endif