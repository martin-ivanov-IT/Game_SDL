#include "manager_utils/drawing/Image.h"
#include "manager_utils/managers/ResourceMngrProxy.h"
#include "utils/drawing/Rectangle.h"
#include "utils/containers/Vector.h"
#include "utils/Log.h"
#include "utils/ErrorCodes.h"
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
    
    self->frames = gResourceMngrProxy->getImageFramesResourceMgr(params->rsrcId);

    self->maxFrames = (int32_t)(getSizeVector(self->frames));
    const struct Rectangle* rect = (const struct Rectangle*)getElementVector(self->frames, self->currFrame);
    params->width = rect->w;
    params->height = rect->h;
    params->widgetType = IMAGE_WIDGET;
    self->widget.isCreated = true;
    self->widget.isDestroyed = false;   
    params->frameRect = *rect;

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
    self->currFrame = 0;
    self->maxFrames = 0;
}

void drawImage(struct Image *self){
    drawWidget(&self->widget);
}


void setFrameImage(struct Image *self, int32_t frameIdx) {
    if (0 > frameIdx || frameIdx >= self->maxFrames) {
        LOGERR("Error, trying to set frameIdx: %d, where maxFrames are: %d for "
            "rsrcId: %d", frameIdx, self->maxFrames,
            self->widget.drawParams.rsrcId);
        return;
    }

    self->currFrame = frameIdx;

    const struct Rectangle* rect = (const struct Rectangle*)getElementVector(self->frames, self->currFrame);
    self->widget.drawParams.frameRect = *rect;
}

void setNextFrameImage(struct Image *self) {
    ++(self->currFrame);

    if (self->maxFrames == self->currFrame) {
        self->currFrame = 0;
    }

    const struct Rectangle* rect = (const struct Rectangle*)getElementVector(self->frames, self->currFrame);
    self->widget.drawParams.frameRect = *rect;

}

void setPrevFrameImage(struct Image *self) {
    --(self->currFrame);
    
    if (-1 == self->currFrame) {
        self->currFrame = self->maxFrames - 1;
    }

    const struct Rectangle* rect = (const struct Rectangle*)getElementVector(self->frames, self->currFrame);
    self->widget.drawParams.frameRect = *rect;

}