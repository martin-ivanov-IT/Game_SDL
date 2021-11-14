#include "manager_utils/drawing/Text.h"
#include "manager_utils/managers/ResourceMngrProxy.h"
#include "utils/Log.h"
#include "stdlib.h"
#include "string.h"

static void copyTextContent(struct Text *text, const char *textContent) {
  const size_t INPUT_TEXT_SIZE = strlen(textContent);

  // sanity check
  if (NULL != text->textContent) {
    free(text->textContent);
    text->textContent = NULL;
  }

  char *tempText = (char*)malloc(INPUT_TEXT_SIZE + 1);  //+1 for the terminator
  strncpy(tempText, textContent, INPUT_TEXT_SIZE);
  

  // strncpy should be OK, but just to be sure
  tempText[INPUT_TEXT_SIZE] = '\0';

  text->textContent = tempText;
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
    copyTextContent(self, textContent);

    params->frameRect.x = 0;
    params->frameRect.y = 0;
    params->frameRect.w = params->width;
    params->frameRect.h = params->height;

    self->widget.isCreated = true;
    self->widget.isVisible = true;
    self->widget.isAlphaModulationEnabled = true;
    self->widget.isDestroyed = false; 
    
    gResourceMngrProxy->createTextResourceMgr(self->textContent, color, fontId,
                            &params->rsrcId, &params->width, &params->height);
           

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
    self->color = COLOR_BLACK;
    self->fontId = INVALID_RSRC_ID;

    if(self->textContent){
        free(self->textContent);
        self->textContent = NULL;
    }
}

void setText(struct Text *self, const char *textContent){
    if (!self->widget.isCreated){
        LOGERR("Text with  fontId %d was not creayed  will not recreate",self->fontId);
        return;
    }
    if(!strcmp(self->textContent, textContent)){
        return;
    }
    copyTextContent(self, textContent);
    struct DrawParams* params = &self->widget.drawParams;
    gResourceMngrProxy->reloadTextResourceMgr(self->textContent, &self->color, self->fontId, params->rsrcId, &params->width, &params->height);
    params->frameRect.w = params->width;
    params->frameRect.h = params->height;

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
    gResourceMngrProxy->reloadTextResourceMgr(self->textContent, &self->color, self->fontId, params->rsrcId, &params->width, &params->height);
    params->frameRect.w = params->width;
    params->frameRect.h = params->height;
}

void drawText(struct Text* self){
    drawWidget(&self->widget);
}
