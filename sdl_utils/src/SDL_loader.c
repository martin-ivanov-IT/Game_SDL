#include "sdl_utils/SDL_loader.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

int32_t initSDL(){
	if (SUCCESS != TTF_Init())
    {
        LOGERR("TTF_Init() Reason: %s",SDL_GetError());
        return FAILURE;
    }

	if (SUCCESS != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO))
    {
        LOGERR("SDL_Init() Reason: %s",SDL_GetError());
        return FAILURE;
    }

	const int32_t imgFlags = IMG_INIT_PNG;
	if (! (IMG_Init(imgFlags) & imgFlags)) {
		LOGERR("SDL_image could not be initialised! SDL_image Error: %s",
		IMG_GetError());
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
void deinitSDL(){
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();

}
