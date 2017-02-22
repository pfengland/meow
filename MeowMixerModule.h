#ifndef H_MEOWMIXERMODULE
#define H_MEOWMIXERMODULE

#include "MeowModule.h"
#include "DynamicArray.h"
#include <jack/jack.h>

typedef struct MeowMixerModule_s MeowMixerModule;
struct MeowMixerModule_s {

     MeowModule *base;

     DynamicArray *channels;
};

MeowModule* MeowMixerModule_create(void);
void MeowMixerModule_free(MeowModule *mixer);
void MeowMixerModule_start(MeowModule *mixer);
void MeowMixerModule_generate(MeowMixerModule *mixer, jack_default_audio_sample_t *out,
			      jack_nframes_t nframes, int sampleRate,
			      int *sampleCounter);

static const MeowModule_ops MeowMixerModule_ops = {
     MeowMixerModule_free,
     MeowMixerModule_start
};
     
#endif
