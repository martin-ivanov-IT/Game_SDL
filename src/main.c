//C system headers
#include <stdint.h>
#include <string.h>

//Other libraries headers

//Own components headers
#include "Engine/Engine.h"
#include "Engine/EngineConfigLoader.h"
#include "sdl_utils/SDL_loader.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

static int32_t runApplication() {
  struct Engine engine;
  memset(&engine, 0, sizeof(engine));

  const struct EngineConfig engineCfg = loadEngineConfig();
  if (SUCCESS != initEngine(&engine, &engineCfg)) {
    LOGERR("Error in initEngine()");
    return FAILURE;
  }

  startEngine(&engine);

  deinitEngine(&engine);
  return SUCCESS;
}

int32_t main(int argc, char *args[]) {
  UNUSED(argc);
  UNUSED(args);

  if (SUCCESS != initSDL()) {
    LOGERR("Error in initSDL()");
    return FAILURE;
  }

  if (SUCCESS != runApplication()) {
    LOGERR("Error in runApplication()");
    return FAILURE;
  }

  //close SDL libraries
  deinitSDL();

  return SUCCESS;
}
