//Corresponding header
#include "sdl_utils/SDL_loader.h"

//C system headers

//C++ system headers

//Other libraries headers
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

//Own components headers
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

int32_t initSDL() {
  if (-1 == TTF_Init()) {
    LOGERR("SDL_ttf could not initialize! SDL_ttf Error: %s", TTF_GetError());
    return FAILURE;
  }

  if (0 > SDL_Init(SDL_INIT_VIDEO)) {
    LOGERR("SDL could not be initialised! SDL Error: %s", TTF_GetError());
    return FAILURE;
  }

  //Initialise PNG loading
  const int32_t imgFlags = IMG_INIT_PNG;
  if (! (IMG_Init(imgFlags) & imgFlags)) {
    LOGERR("SDL_image could not be initialised! SDL_image Error: %s",
    IMG_GetError());
    return FAILURE;
  }

  if (0 > SDL_Init(SDL_INIT_TIMER)) {
    LOGERR("SDL TIMER could not be initialised! SDL Error: %s", SDL_GetError());
    return FAILURE;
  }

  if (0 > SDL_Init(SDL_INIT_AUDIO)) {
    LOGERR("SDL Audio could not be initialised! SDL Error: %s", SDL_GetError());
    return FAILURE;
  }

  if (0 > Mix_OpenAudio(44100, //sound frequency
          MIX_DEFAULT_FORMAT,  //sample format
          2,                   //stereo hardware channels
          2048)) {             //chunk size
    LOGERR("SDL_mixer could not be initialised! SDL Error: %s", Mix_GetError());
    return FAILURE;
  }

  return SUCCESS;
}

void deinitSDL() {
  //Quit SDL subsystems
  IMG_Quit();
  TTF_Quit();
  Mix_Quit();
  SDL_Quit();
}
