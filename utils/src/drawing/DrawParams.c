
#include "utils/drawing/DrawParams.h"

const int32_t INVALID_RSRC_ID = -1;

const int32_t FULL_OPACITY = 255;
const int32_t ZERO_OPACITY = 0;

void resetDrawParams(struct DrawParams* drawParams){
    drawParams->pos = POINT_UNDEFINED;
    drawParams->frameRect = RECTANGLE_ZERO;
    drawParams->width = 0;
    drawParams->height = 0;
    drawParams->rsrcId = INVALID_RSRC_ID;
    drawParams->opacity = FULL_OPACITY;
    drawParams->blendMode = BLEND_NONE;
    drawParams->widgetType = UNKNOWN_WIDGET_TYPE;
    drawParams->flipType = NONE_WIDGET_FLIP;
    drawParams->rotationCenter = POINT_ZERO;
    drawParams->rotationAngle = 0.0;
}


