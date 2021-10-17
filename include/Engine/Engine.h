#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_


#include <stdint.h>
#include "sdl_utils/MonitorWindow.h"
#include "sdl_utils/Renderer.h"
#include "sdl_utils/InputEvent.h"
#include "Game//Game.h"
#include "utils/containers/Vector.h"

struct EngineConfig;

struct Engine {
  struct MonitorWindow window;
  struct InputEvent event;
  struct Game game;
  struct Vector imgs;
  struct Renderer renderer; 
};

int32_t initEngine(struct Engine* engine, const struct EngineConfig* cfg);

void deinitEngine(struct Engine* engine);

void startEngine(struct Engine* engine);

#endif /* ENGINE_ENGINE_H_ */
