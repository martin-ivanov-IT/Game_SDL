#include "Engine/Engine.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "sdl_utils/Texture.h"
#include <SDL_image.h>
#include <SDL_timer.h>

static int32_t loadResources(const char* filePath, SDL_Surface** outImage){
    return loadSurfaceFormFile(filePath, outImage);

}

int32_t initEngine(struct Engine* self){
        const char* windowName = "Hello";
        const struct Point windowPos = POINT_UNDEFINED;
        const int32_t windowWidth = 640;
        const int32_t windowHeight = 480;  
        const uint32_t windowMode = WINDOW_SHOWN; 

        struct MonitorWindowCfg windowCfg = {.name = windowName, .pos = windowPos, .width = windowWidth, .hight = windowHeight, .mode = windowMode};

        if (SUCCESS != initMonitorWindow(&self->window, &windowCfg))
        {
            LOGERR("initMonitorWindow() failed");
            return FAILURE;
        }
        const char* filePath = "../resources/hello.png";
        if (SUCCESS != loadResources(filePath,&self->image))
        {
            LOGERR("loadResources() failed");
            return FAILURE;
        
        }

        if (SUCCESS != initInputEvent(&self->event)){
        LOGERR("initInputEvent( failed) ");
        return FAILURE;
    }
    return SUCCESS;
}
int32_t deinitEngine(struct Engine* self){
        deinitMonitorWindow(&self->window);
        freeSurface(&self->image);
        deinitInputEvent(&self->event);
        
        SDL_Quit(); 
        return SUCCESS;
}
void drawEngine(struct Engine* self){
    SDL_BlitSurface(self->image, NULL, self->window.windowSurface, NULL);
    updateMonitorWindowSurface(&self->window);
    SDL_Delay(3000);
}

