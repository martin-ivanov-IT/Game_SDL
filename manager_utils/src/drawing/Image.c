#include "manager_utils/drawing/Image.h"
#include "manager_utils/managers/ResourceMngrProxy.h"
#include "utils/drawing/Rectangle.h"
#include "utils/Log.h"

void createImage(struct Image *self, int32_t rsrcId, const struct Point *pos){
    if (self->widget.isCreated){
        LOGERR("image with rsrc id was already creayed  will not recreate %d", rsrcId);
        return;
    }
    resetImage(self);
    struct DrawParams* params = &self->widget.drawParams;
    params->rsrcId = rsrcId;
    params->pos = *pos;
    const struct Rectangle* rect = gResourceMngrProxy->getImageFrameResourceMgr(params->rsrcId);
    params->width = rect->w;
    params->height = rect->h;
    params->widgetType = IMAGE_WIDGET;
    self->widget.isCreated = true;
    self->widget.isDestroyed = false;

}
void destroyImage(struct Image *self){
    if (self->widget.isDestroyed){
        LOGERR("image with rsrc id was already destroyed %d",self->widget.drawParams.rsrcId);
        return;
    }
    resetImage(self);
    self->widget.isDestroyed = true;
    self->widget.isCreated = false;
}
void resetImage(struct Image *self){
    resetWidget(&self->widget);
}

void drawImage(struct Image *self){
    drawWidget(&self->widget);
}
