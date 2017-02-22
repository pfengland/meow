#ifndef H_MEOWSESSION
#define H_MEOWSESSION

#include "MeowModuleCollection.h"
#include "MeowKeyboard.h"
#include <jack/jack.h>

typedef struct MeowSession_s MeowSession;
struct MeowSession_s {
     int quit;
     MeowModuleCollection *modules;
     MeowKeyboard *keys;
};

MeowSession* MeowSession_create(void);
void MeowSession_start(MeowSession *s);
void MeowSession_free(MeowSession *s);
void MeowSession_generate(void *session, jack_default_audio_sample_t *out,
			  jack_nframes_t nframes, int sampleRate,
			  int *sampleCounter);

#endif
