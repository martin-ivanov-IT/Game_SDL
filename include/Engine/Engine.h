#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_


#include <stdint.h>

#include "sdl_utils/InputEvent.h"
#include "manager_utils/common/DebugConsole.h"
#include "Game//Game.h"

struct EngineConfig;

struct Engine {
  struct InputEvent event;
  struct Game game;
  struct DebugConsole debugConsole;

};

int32_t initEngine(struct Engine* engine, const struct EngineConfig* cfg);

void deinitEngine(struct Engine* engine);

void startEngine(struct Engine* engine);

#endif /* ENGINE_ENGINE_H_ */
