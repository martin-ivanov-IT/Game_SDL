#ifndef UTILS_DRAWING_COLOR_H_
#define UTILS_DRAWING_COLOR_H_

#include <stdint.h>
#include <stdbool.h>
struct RGBA {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

struct Color {
  struct RGBA rgba;
};
bool areColorsEqual(const struct Color* left, const struct Color* right);
extern const struct Color COLOR_RED;
extern const struct Color COLOR_GREEN;
extern const struct Color COLOR_BLUE;
extern const struct Color COLOR_BLACK;
extern const struct Color COLOR_WHITE ;
extern const struct Color COLOR_GRAY ;
extern const struct Color COLOR_CYAN;
extern const struct Color COLOR_MAGENTA ;
extern const struct Color COLOR_YELLOW ;
extern const struct Color COLOR_ORANGE ;
extern const struct Color COLOR_PURPLE ;
extern const struct Color COLOR_FULL_TRANSPARENT;





#endif