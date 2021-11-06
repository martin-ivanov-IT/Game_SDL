#include "manager_utils/drawing/Widget.h"
#include "manager_utils/managers/DrawMgrProxy.h"
#include "utils/drawing/Rectangle.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"



void drawWidget(struct Widget *widget){
    if (widget->isVisible){
       gDrawMgrProxy->addDrawCmdDrawMgr(&widget->drawParams);
    }
}

void resetWidget(struct Widget *widget){
    resetDrawParams(&widget->drawParams);
    widget->isCreated = false;
    widget->isDestroyed = false;
    widget->isVisible = true;
    widget->isAlphaModulationEnabled = false;
}

bool containsPointWidget(const struct Widget *widget, const struct Point *point){
    const struct DrawParams* params = &widget->drawParams;
    const struct Rectangle rect = {.x = params->pos.x, .y = params->pos.y, .w = params->width, .h = params->height};

    return isPointInsideRect(&rect,point);
}

void setOpacityWidget(struct Widget *widget, int32_t opacity){
    if(!widget->isAlphaModulationEnabled){
        LOGERR("Eroro alpha modulation was not activated for widget with rsrc id %d will not change opacity to \
             %d", widget->drawParams.rsrcId, opacity);
        return;
    }
    widget->drawParams.opacity = opacity;
    gDrawMgrProxy->setWidgetOpacityDrawMgr(&widget->drawParams);
}

void activateAlphaModulationWidget(struct Widget *widget){
    if(widget->isAlphaModulationEnabled){
        LOGERR("Eroro alpha modulation already activated for widget with rsrc id %d", widget->drawParams.rsrcId);
        return;
    }
    widget->isAlphaModulationEnabled =true;
    gDrawMgrProxy->setWidgetBlendModeDrawMgr(&widget->drawParams, BLEND_BLEND);
}

void deactivateAlphaModulationWidget(struct Widget *widget){
    if(widget->isAlphaModulationEnabled){
        LOGERR("Eroro alpha modulation already deactivated for widget with rsrc id %d", widget->drawParams.rsrcId);
        return;
    }
    widget->isAlphaModulationEnabled = false;
    gDrawMgrProxy->setWidgetBlendModeDrawMgr(&widget->drawParams, BLEND_NONE);

}

void hideWidget(struct Widget* widget){
    widget->isVisible = false;
}

void showWidget(struct Widget* widget){
    widget->isVisible = true;
}

void moveRight(struct Widget* widget, int32_t delta){
    widget->drawParams.pos.x += delta;
}
void moveLeft(struct Widget* widget, int32_t delta){
    widget->drawParams.pos.x -= delta;

}
void moveUp(struct Widget* widget, int32_t delta){
    widget->drawParams.pos.y -= delta;

}
void moveDown(struct Widget* widget, int32_t delta){
    widget->drawParams.pos.y += delta;
}