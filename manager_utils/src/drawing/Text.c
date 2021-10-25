#include "manager_utils/drawing/Text.h"
#include "manager_utils/managers/ResourceMngrProxy.h"
#include "utils/Log.h"
#include "stdlib.h"
#include "string.h"

static void copyTextContent(char** currText, const char* newText){
    if(*currText != NULL){
        free(*currText);
    }
    *currText =  (char*)malloc(strlen(newText) + 1);
    strcpy(*currText, newText);
}
void createText(struct Text *self, const char *textContent, int32_t fontId,
                const struct Color *color, const struct Point *pos){

    if (self->widget.isCreated){
        LOGERR("Text with rsrc id %d and fontId %dwas already creayed  will not recreate"
        ,self->widget.drawParams.rsrcId,fontId );
        return;
    }

    resetWidget(&self->widget);

    struct DrawParams* params = &self->widget.drawParams;
    params->pos = *pos;
    params->widgetType = TEXT_WIDGET;

    self->fontId = fontId;
    self->color = *color;
    self->textContent = NULL;
    copyTextContent(&self->textContent, textContent);

    gResourceMngrProxy->createTextResourceMgr(self->textContent, color, fontId,
                            &params->rsrcId, &params->width, &params->height);
    self->widget.isCreated = true;
    self->widget.isDestroyed = false;        

}

void destroyText(struct Text *self){
    if (self->widget.isDestroyed){
        LOGERR("text with rsrc id was already destroyed %d",self->widget.drawParams.rsrcId);
        return;
    }
    resetText(self);
    self->widget.isDestroyed = true;
    self->widget.isCreated = false;
}

void resetText(struct Text *self){
    resetWidget(&self->widget);
    self->textContent = NULL;
    self->color = COLOR_BLACK;
    self->fontId = INVALID_RSRC_ID;
}

void setText(struct Text *self, const char *textContent){
    if (!self->widget.isCreated){
        LOGERR("Text with  fontId %d was not creayed  will not recreate",self->fontId);
        return;
    }
    if(strcmp(self->textContent, textContent)){
        return;
    }
    copyTextContent(&self->textContent, textContent);
    struct DrawParams* params = &self->widget.drawParams;
    gResourceMngrProxy->reloadTextResourceMgr(self->textContent, &self->color, self->fontId,
                            params->rsrcId, &params->width, &params->height);
}

void setColorText(struct Text *self, const struct Color *color){
    if (!self->widget.isCreated){
        LOGERR("Text with  fontId %d was not creayed  will not recreate",self->fontId);
        return;
    }
    if(areColorsEqual(&self->color, color)){
        return;
    }
    self->color = *color;
    struct DrawParams* params = &self->widget.drawParams;
    gResourceMngrProxy->reloadTextResourceMgr(self->textContent, &self->color, self->fontId,
                            params->rsrcId, &params->width, &params->height);
}

void drawText(struct Text* self){
    drawWidget(&self->widget);
}
