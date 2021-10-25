#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_TEXT_IMAGE_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_TEXT_IMAGE_H_
#include <stdint.h>
#include "manager_utils/drawing/Widget.h"
#include "utils/drawing/Color.h"

struct Text {
  struct Widget widget;
  char *textContent;
  struct Color color;
  int32_t fontId;
};

void createText(struct Text *self, const char *textContent, int32_t fontId,
                const struct Color *color, const struct Point *pos);

void destroyText(struct Text *self);

void resetText(struct Text *self);

void setText(struct Text *self, const char *textContent);

void setColorText(struct Text *self, const struct Color *color);

void drawText(struct Text* self);


#endif