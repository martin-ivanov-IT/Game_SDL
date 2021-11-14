//Corresponding header
#include "manager_utils/common/DebugConsole.h"

//C system headers
#include <string.h>

//Other libraries headers

//Own components headers
#include "sdl_utils/InputEvent.h"
#include "utils/time/Time.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
#include <stdlib.h>


static const int32_t UPDATE_SKIPS = 20;

static void updateFpsText(struct Text *text, int64_t currFps) {
  const char fpsStr[] = "FPS: ";
  const size_t initialStrLen = strlen(fpsStr);
  char textContent[30];
  memset(textContent, 0, sizeof (textContent));
  size_t usedSize = 0;

  //append initial string
  strncpy(&textContent[usedSize], fpsStr, initialStrLen);
  usedSize += initialStrLen;

  //append X value:
  const size_t fpsValueStrLen = snprintf(NULL, 0, "%ld", currFps);
  snprintf(&textContent[usedSize], fpsValueStrLen + 1, "%ld", currFps);
  usedSize += fpsValueStrLen;

  setText(text, textContent);
}

static void updateTimersText(struct Text *text, int64_t activeTimersCount) {
  const char timersStr[] = "Active Timers: ";
  const size_t initialStrLen = strlen(timersStr);
  char textContent[30];
  memset(textContent, 0, sizeof (textContent));
  size_t usedSize = 0;

  //append initial string
  strncpy(&textContent[usedSize], timersStr, initialStrLen);
  usedSize += initialStrLen;

  //append X value:
  const size_t timersValueStrLen = snprintf(NULL, 0, "%ld", activeTimersCount);
  snprintf(&textContent[usedSize], timersValueStrLen + 1, "%ld",
      activeTimersCount);
  usedSize += timersValueStrLen;

  setText(text, textContent);
}

void deinitDebugConsole(struct DebugConsole *console) {
  for (int32_t i = FPS_TEXT_ID; i < DEBUG_TEXTS_COUNT; ++i) {
    destroyText(&console->debugTexts[i]);
  }
}

int32_t initDebugConsole(struct DebugConsole *console, int64_t maxFrames,
                         int32_t fontId) {
  console->maxFrames = maxFrames;
  console->updateCounter = 0;
  console->isActive = false;

  const int32_t yDissplacement = 40;
  const int32_t initialYCoord = 20;
  struct Point textPos = { .x = 20, .y = 0 };
  for (int32_t i = FPS_TEXT_ID; i < DEBUG_TEXTS_COUNT; ++i) {
    textPos.y = initialYCoord + (i * yDissplacement);
    resetText(&console->debugTexts[i]);
    createText(&console->debugTexts[i], "0", fontId, &COLOR_YELLOW, &textPos);
  }

  return SUCCESS;
}

/** @ brief used to toggle active/inactive status of the debug console
 * */
void handleEventDebugConsole(struct DebugConsole *console,
                             const struct InputEvent *e) {
  if (KEYBOARD_RELEASE == e->type) {
    if (KEY_TILDA == e->key) {
      console->isActive = !console->isActive;
    }
  }
}

void updateDebugConsole(struct DebugConsole *console,
                        struct DebugConsoleData *data) {
  -- (console->updateCounter);
  if (0 < console->updateCounter) {
    return;
  }
  console->updateCounter = UPDATE_SKIPS;

  int64_t currFrames = SECOND_NS / data->elapsedNanoseconds;
  if (currFrames > console->maxFrames) {
    currFrames = console->maxFrames;
  }

  updateFpsText(&console->debugTexts[FPS_TEXT_ID], currFrames);
  updateTimersText(
      &console->debugTexts[ACTIVE_TIMERS_TEXT_ID], data->activeTimersCount);
}

void drawDebugConsole(struct DebugConsole *console) {
  for (int32_t i = FPS_TEXT_ID; i < DEBUG_TEXTS_COUNT; ++i) {
    drawWidget(&console->debugTexts[i].widget);
  }
}

