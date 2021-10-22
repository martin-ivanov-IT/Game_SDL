#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_CONTAINERS_TEXTCONATINER_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_CONTAINERS_TEXTCONATINER_H_
#include "sdl_utils/config/TextContainerCfg.h"
#include "utils/drawing/Color.h"


#include <stdint.h>

#include <stdint.h>
#include <stdbool.h>

typedef struct SDL_Texture SDL_Texture;
typedef struct _TTF_Font TTF_Font;
#define MAX_FONT_SIZE 10
struct TextContainer {
  //the textures we'll be drawing
  SDL_Texture *textures[MAX_TEXT_SIZE];

  TTF_Font* fonts [MAX_FONT_NAME_LEN];
};
void createTextTextContainer(struct TextContainer *self,
                             const char *text, const struct Color *color,
                             int32_t rsrcId, int32_t *outTextId,
                             int32_t *outTextWidth, int32_t *outTextHeight);
                             
void reloadTextTextContainer(struct TextContainer *self,
                             const char *text, const struct Color *color,
                             int32_t rsrcId, int32_t TextId,
                             int32_t *outTextWidth, int32_t *outTextHeight);                             

void unloadTextTextContainer(struct TextContainer *self,  int32_t textId);


int32_t initTextContainer(struct TextContainer *self, const struct TextContainerCfg* cfg);
void deinitTextContainer(struct TextContainer *self);
SDL_Texture* getTextTextureTextContainer(const struct TextContainer *self, int32_t rsrcId);





#endif
