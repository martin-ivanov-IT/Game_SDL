#include "Game/Entities/Island_Boy.h"
#include "Game/Entities/Hero.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

void handleEventIslandBoy (struct Hero* self, struct InputEvent* e);

int32_t initIslandBoy(struct Hero* self,const struct HeroCfg* cfg);

void deinitIslandBoy(struct Hero* self);

void drawIslandBoy(struct Hero* self);

void startAnim(struct Hero* self);