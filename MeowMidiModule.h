#ifndef H_MEOWMIDIMODULE
#define H_MEOWMIDIMODULE

#include "MeowModule.h"
#include "MeowKeyboard.h"
#include <alsa/asoundlib.h>
#include <pthread.h>

typedef struct MeowMidiModule_s MeowMidiModule;
struct MeowMidiModule_s {

     MeowModule *base;

     MeowKeyboard *keys;

     pthread_t midiInputThread;
     snd_rawmidi_t *midiInput;
     int stopInputThread;
};

MeowModule* MeowMidiModule_create(MeowKeyboard *keys);
void MeowMidiModule_free(MeowModule *midi);
void MeowMidiModule_start(MeowModule *midi);
void* MeowMidiModule_inputThread(void *m);

static const MeowModule_ops MeowMidiModule_ops = {
     MeowMidiModule_free,
     MeowMidiModule_start
};
     
#endif
