#ifndef H_MEOWSYNTHMODULE
#define H_MEOWSYNTHMODULE

#include "MeowModule.h"

typedef struct MeowSynthModule_s MeowSynthModule;
struct MeowSynthModule_s {
     MeowModule *base;
};

MeowModule* MeowSynthModule_create();
void MeowSynthModule_free(MeowModule *synth);
void MeowSynthModule_start(MeowModule *synth);

static const MeowModule_ops MeowSynthModule_ops = {
     MeowSynthModule_free,
     MeowSynthModule_start
};
     
#endif
