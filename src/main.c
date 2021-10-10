#include <stdio.h>
#include <stdint.h>

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL.h>

#include  "utils/Log.h"
#include  "utils/ErrorCodes.h"
#include  "sdl_utils/SDL_loader.h"
#include  "sdl_utils/MonitorWindow.h"
#include  "sdl_utils/Texture.h"
#include  "sdl_utils/InputEvent.h"
#include  "utils/drawing/Point.h"
#include  "utils/drawing/Rectangle.h"     
#include "Engine/Engine.h"

#include <stdbool.h>


int32_t runAppclication(){
    struct Engine engine;
    memset(&engine, 0, sizeof(struct Engine));
    if (SUCCESS != initEngine(&engine))
    {
        LOGERR("initEngine( failed) ");
        return FAILURE;
    } 
    drawEngine(&engine);
    deinitEngine(&engine);
    return SUCCESS;
}

int32_t main(int32_t argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);

    initSDL();
    if (SUCCESS != runAppclication())
    {
        LOGERR("run application failed");
    }
    
    runAppclication();
    deinitSDL();
    return SUCCESS;
}


