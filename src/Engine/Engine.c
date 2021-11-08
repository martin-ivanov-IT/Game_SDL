
#include "Engine/Engine.h"
#include <unistd.h>
#include "utils/time/Time.h"
#include "utils/thread/Thread.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include "Engine/config/EngineCfg.h"
#include "utils/containers/Vector.h"
#include "sdl_utils/Texture.h"
#include "manager_utils/managers/ManagerHandler.h"
#include "manager_utils/managers/DrawMgrProxy.h"
#include "Game/Game.h"
#include "manager_utils/managers/TimerMgr.h"
#include "Game/Battlefield/Battlefield.h"



static void processEngine (struct Engine* eng){
  UNUSED(eng);
  processManagerHandler();
}
static void handleEvent(struct Engine *engine) {
  //do something with the event
  handleEventGame(&engine->game, &engine->event);
  handleEventDebugConsole(&engine->debugConsole, &engine->event);


}

static void drawFrame(struct Engine *engine) {
  gDrawMgrProxy->clearScreenDrawMgr();
  drawGame(&engine->game);
  if (engine->debugConsole.isActive) {
    drawDebugConsole(&engine->debugConsole);

  }
  gDrawMgrProxy->finishFrameDrawMgr();
}


static bool processFrame(struct Engine *engine) {
  while (pollInputEvent(&engine->event)) {
    if (checkForExitRequest(&engine->event)) {
      return true;
    }

    handleEvent(engine);
  }
  processEngine(engine);
  
  drawFrame(engine);
  return false;
}

static void limitFPS(int64_t elapsedNanoseconds) {
  const int64_t maxNanosecodsPerFrame = SECOND_NS / gDrawMgrProxy->maxFrames;
  
  const int64_t nanosecondsFpsDelay = maxNanosecodsPerFrame
      - elapsedNanoseconds;
  if (0 < nanosecondsFpsDelay) {
    thisThreadSleepFor(nanosecondsFpsDelay);
  }
}

static void mainLoop(struct Engine *engine) {
  struct Time time;
  initTime(&time);
  struct DebugConsoleData debugConsoleData;

  while (true) {

    advanceTime(&time); //begin measure the new frame elapsed time

    if (processFrame(engine)) {
      return; //user has requested exit -> break the main loop
    }
    const int64_t elapsedNanoseconds = getElapsedNanoseconds(&time);
    debugConsoleData.elapsedNanoseconds = elapsedNanoseconds;
    debugConsoleData.activeTimersCount = getActiveTimersCountTimerMgr(gTimerMgr);
    updateDebugConsole(&engine->debugConsole, &debugConsoleData);
    
    limitFPS(getElapsedNanoseconds(&time));
  }
}

int32_t initEngine(struct Engine* self, const struct EngineConfig* cfg) {

  if (SUCCESS != initManagerHandler(&cfg->managerHandlerCfg) ){
    LOGERR("initManagerHadnler() failed");
    return FAILURE;
  }

  if (SUCCESS != initInputEvent(&self->event)) {
    LOGERR("initInputEvent() failed");
    return FAILURE;
  }
  
  if (SUCCESS != initGame(&self->game, &cfg->gameCfg)) {
    LOGERR("initGame() failed");
    return FAILURE;
  }

   if (SUCCESS != initDebugConsole(&self->debugConsole,
          cfg->managerHandlerCfg.drawMgrCfg.maxFrames, cfg->debugConsoleFontId)) {
    LOGERR("initDebugConsole() failed");
    return FAILURE;
  }


  onInitEndTimerMgr(gTimerMgr);
  return SUCCESS;
}

void deinitEngine(struct Engine *engine) {
  deinitGame(&engine->game);
  deinitInputEvent(&engine->event);
  
  deinitManagerHadnler();
}

void startEngine(struct Engine *engine) {
  mainLoop(engine);
}

