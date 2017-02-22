#ifndef H_MEOWAUDIOMODULE
#define H_MEOWAUDIOMODULE

#include "MeowModule.h"
#include <jack/jack.h>

typedef void (*MeowAudioModule_generateCallback)(void *arg,
						 jack_default_audio_sample_t *out,
						 jack_nframes_t nframes,
						 int sampleRate,
						 int *sampleCounter);

typedef struct MeowAudioModule_s MeowAudioModule;
struct MeowAudioModule_s {
     MeowModule *base;

     jack_port_t *outputPort;
     jack_client_t *jackClient;
     int sampleRate;
     int sampleCounter;

     MeowAudioModule_generateCallback generateCallback;
     void *callbackArg;
};

MeowModule* MeowAudioModule_create(void);
void MeowAudioModule_free(MeowModule *m);
void MeowAudioModule_start(MeowModule *m);
int MeowAudioModule_process(jack_nframes_t nframes, void *audio);
void MeowAudioModule_shutdown(void *audio);
void MeowAudioModule_setGenerateCallback(MeowAudioModule *audio,
					 MeowAudioModule_generateCallback callback,
					 void *arg);

static const MeowModule_ops MeowAudioModule_ops = {
     MeowAudioModule_free,
     MeowAudioModule_start
};

#endif
