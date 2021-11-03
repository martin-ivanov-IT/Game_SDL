#ifndef MANAGER_UTILS_COMMON_DEBUGCONSOLE_H_
#define MANAGER_UTILS_COMMON_DEBUGCONSOLE_H_

//C system headers
#include <stdint.h>
#include <stdbool.h>

//Other libraries headers

//Own components headers
#include "manager_utils/drawing/Text.h"

//Forward declarations
struct InputEvent;

enum DebugTexts {
  FPS_TEXT_ID,
  ACTIVE_TIMERS_TEXT_ID,

  DEBUG_TEXTS_COUNT
};

struct DebugConsoleData {
  int64_t elapsedNanoseconds;
  int32_t activeTimersCount;
};

struct DebugConsole {
  struct Text debugTexts[DEBUG_TEXTS_COUNT];
  int64_t maxFrames;
  int32_t updateCounter;
  bool isActive;
};

int32_t initDebugConsole(struct DebugConsole *console, int64_t maxFrames,
                         int32_t fontId);

void deinitDebugConsole(struct DebugConsole *console);

/** @ brief used to toggle active/inactive status of the debug console
 * */
void handleEventDebugConsole(struct DebugConsole *console,
                             const struct InputEvent *e);

void updateDebugConsole(struct DebugConsole *console,
                        struct DebugConsoleData* data);

void drawDebugConsole(struct DebugConsole *console);

#endif /* MANAGER_UTILS_COMMON_DEBUGCONSOLE_H_ */

