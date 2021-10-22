
#include "Engine/Engine.h"
#include <unistd.h>
#include "utils/time/Time.h"
#include "utils/thread/Thread.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "Engine/config/EngineCfg.h"
#include <SDL_timer.h>
#include <SDL_video.h>
#include "utils/containers/Vector.h"
#include "Game/config/GameCfg.h"
#include "sdl_utils/Texture.h"




static void handleEvent(struct Engine *engine) {
  //do something with the event
  handleEventGame(&engine->game, &engine->event);
}

static void drawFrame(struct Engine *engine) {
  clearScreenRenderer(&engine->renderer);
  drawGame(&engine->game, &engine->imgs);
  const size_t imagesSize = getSizeVector(&engine->imgs);
  const struct DrawParams * currDrawParams =  NULL;
  SDL_Texture* currTexture = NULL;
  for (size_t i = 0; i < imagesSize; i++)
  {
    currDrawParams = (const struct DrawParams*)getElementVector(&engine->imgs, i);

    if(IMAGE_WIDGET == currDrawParams->widgetType){
        currTexture = getImageTextureImageContainer(&engine->imgContainer, currDrawParams->rsrcId);
    }

    else if(TEXT_WIDGET == currDrawParams->widgetType){
        currTexture = getTextTextureTextContainer(&engine->textContainer, currDrawParams->rsrcId);
    }

    else{
        LOGERR("Received invalid widget %d type for rsrcid %d", currDrawParams->widgetType, currDrawParams->rsrcId);
    }
    renderTexture(&engine->renderer,currDrawParams, currTexture);
  }
  clearElementsVector(&engine->imgs);
  finishFrameRenderer(&engine->renderer);
}

static bool processFrame(struct Engine *engine) {
  while (pollInputEvent(&engine->event)) {
    if (checkForExitRequest(&engine->event)) {
      return true;
    }

    handleEvent(engine);
  }

  drawFrame(engine);
  return false;
}

static void limitFPS(int64_t elapsedNanoseconds) {
  const int64_t maxFrames = 60;
  const int64_t maxNanosecodsPerFrame = SECOND_NS / maxFrames;

  const int64_t nanosecondsFpsDelay = maxNanosecodsPerFrame
      - elapsedNanoseconds;
  if (0 < nanosecondsFpsDelay) {
    thisThreadSleepFor(nanosecondsFpsDelay);
  }
}

static void mainLoop(struct Engine *engine) {
  struct Time time;
  initTime(&time);

  while (true) {
    advanceTime(&time); //begin measure the new frame elapsed time

    if (processFrame(engine)) {
      return; //user has requested exit -> break the main loop
    }

    limitFPS(getElapsedNanoseconds(&time));
  }
}

int32_t initEngine(struct Engine* self, const struct EngineConfig* cfg) {

  if (SUCCESS != initMonitorWindow(&self->window, &cfg->windowCfg)) {
    LOGERR("initMonitorWindow() failed");
    return FAILURE;
  }

  if (SUCCESS != initRenderer(&self->renderer, self->window.sdlWindow)) {
    LOGERR("initRenderer() failed");
    return FAILURE;
  }

  if (SUCCESS != initImageContainer(&self->imgContainer,&cfg->imgContainerCfg)) {
    LOGERR("initImageContainer() failed");
    return FAILURE;
  }

  if (SUCCESS != initTextContainer(&self->textContainer ,&cfg->textContainerCfg)) {
    LOGERR("initTextContainer() failed");
    return FAILURE;
  }

  if (SUCCESS != initInputEvent(&self->event)) {
    LOGERR("initInputEvent() failed");
    return FAILURE;
  }

  const struct GameConfig gameCfg = {.imgContainer = &self->imgContainer, .textContainer = &self->textContainer};
  
  if (SUCCESS != initGame(&self->game, &gameCfg)) {
    LOGERR("initGame() failed");
    return FAILURE;
  }
  initVector(&self->imgs,10);

  return SUCCESS;
}

void deinitEngine(struct Engine *engine) {
  deinitGame(&engine->game);
  deinitInputEvent(&engine->event);
  deinitTextContainer(&engine->textContainer);
  deinitImageContainer(&engine->imgContainer);
  deinitRenderer(&engine->renderer);
  deinitMonitorWindow(&engine->window);
  freeVector(&engine->imgs);  
}

void startEngine(struct Engine *engine) {
  mainLoop(engine);
}

