#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_IMAGE_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_IMAGE_H_
#include <stdint.h>
#include "manager_utils/drawing/Widget.h"

struct Image {
     struct Widget widget;
};

void createImage(struct Image *self, int32_t rsrcId, const struct Point *pos);
void destroyImage(struct Image *self);
void resetImage(struct Image *self);
void drawImage(struct Image *self);


#endif