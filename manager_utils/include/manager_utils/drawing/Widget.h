#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_WIDGETIMAGE_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_WIDGETIMAGE_H_
#include <stdint.h>
#include <stdbool.h>
#include "utils/drawing/DrawParams.h"
struct Widget {
  struct DrawParams drawParams;

  bool isCreated;
  bool isDestroyed;
  bool isVisible;
  bool isAlphaModulationEnabled;
};

void drawWidget(struct Widget *widget);

void resetWidget(struct Widget *widget);

bool containsPointWidget(const struct Widget *widget,const struct Point *point);

void setOpacityWidget(struct Widget *widget, int32_t opacity);

void activateAlphaModulationWidget(struct Widget *widget);

void deactivateAlphaModulationWidget(struct Widget *widget);

void hideWidget(struct Widget* widget);

void showWidget(struct Widget* widget);

//move methods could be added for convenience
//show & hide methods could also be implemented for convenience

#endif