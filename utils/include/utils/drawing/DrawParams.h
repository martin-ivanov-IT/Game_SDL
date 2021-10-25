#ifndef UTILS_DRAWING_DRAWPARAMS_H_
#define UTILS_DRAWING_DRAWPARAMS_H_

#include <stdint.h>
#include <stdbool.h>
#include "utils/drawing/Point.h"


typedef enum {
  BLEND_NONE  = 0, //value for SDL_BLENDMODE_NONE
  BLEND_BLEND = 1, //value for SDL_BLENDMODE_BLEND
  BLEND_ADD   = 2, //value for SDL_BLENDMODE_ADD
  BLEND_MOD   = 4  //value for SDL_BLENDMODE_MODE
} BlendMode;

extern const int32_t FULL_OPACITY;
extern const int32_t ZERO_OPACITY;
typedef enum {
  IMAGE_WIDGET,
  TEXT_WIDGET,
  UNKNOWN_WIDGET_TYPE
} WidgetType;

extern const int32_t INVALID_RSRC_ID;

struct DrawParams {
  //Top left position of texture
  struct Point pos;

  //Draw dimensions of the texture
  int32_t width;
  int32_t height;
  int32_t opacity;

  //unique resourceId
  int32_t rsrcId;

  BlendMode blendMode;
  WidgetType widgetType;
};

void resetDrawParams(struct DrawParams* drawParams);

#endif 
