#include "Game/Game.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "sdl_utils/Texture.h"
#include "sdl_utils/InputEvent.h"
#include "utils/containers/Vector.h"

int32_t initGame(struct Game* self, const struct GameConfig* cfg){
    
  for (int32_t i = 0; i < IMAGES_COUNT; ++i) {
    if (SUCCESS != loadTextureFormFile(cfg->imgLoadPaths[i],
                & (self->images[i]))) {
        LOGERR("loadTextureFormFile() failed");
        return FAILURE;
    }
}
    
    self->currChosenImage = self->images[PRESS_KEYS];
return SUCCESS;
}

void deinitGame(struct Game* self){
    for (int32_t i = 0; i < IMAGES_COUNT; ++i) {
        freeTexture(&self->images[i]);
    }

}

void handleEventGame (struct Game* self, struct InputEvent* e){
  if (KEYBOARD_RELEASE == e->type){
    self->currChosenImage =self->images[PRESS_KEYS];
  }
  if (KEYBOARD_PRESS == e->type) {
    switch (e->key) {
    case KEY_UP:
      self->currChosenImage =self->images[UP];
      break;
    case KEY_DOWN:
      self->currChosenImage =self->images[DOWN];
      break;
    case KEY_LEFT:
      self->currChosenImage =self->images[LEFT];
      break;
    case KEY_RIGHT:
      self->currChosenImage =self->images[RIGHT];
      break;
    default:

      self->currChosenImage = self->images[PRESS_KEYS];
      break;
    }
  }

}

void drawGame(struct Game* self, struct Vector* images){
    pushElementVector(images, (void*)self->currChosenImage);
}