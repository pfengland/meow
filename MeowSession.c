#include "MeowSession.h"
#include "MeowSynthModule.h"
#include "MeowMidiModule.h"
#include "MeowAudioModule.h"
#include <stdlib.h>

MeowSession* MeowSession_create(void) {

     MeowSession* s = malloc(sizeof(*s));
     s->quit = 0;

     s->keys = MeowKeyboard_create();

     // create startup modules
     s->modules = MeowModuleCollection_create();

     // create the audio module
     MeowModule *m = MeowAudioModule_create();
     MeowModuleCollection_add(s->modules, m);
     MeowAudioModule *audio = m->impl;
     MeowAudioModule_setGenerateCallback(audio, &MeowSession_generate, s);
     
     // create the midi input module
     m = MeowMidiModule_create(s->keys);
     MeowModuleCollection_add(s->modules, m);

     // for now - create a single synth instance on startup
     m = MeowSynthModule_create();
     MeowModuleCollection_add(s->modules, m);

     return s;
}

void MeowSession_start(MeowSession *s) {
     MeowModuleCollection_startAll(s->modules);
}

void MeowSession_free(MeowSession *s) {
     MeowModuleCollection_free(s->modules);
     MeowKeyboard_free(s->keys);
     free(s);
}

void MeowSession_generate(void *session, jack_default_audio_sample_t *out,
			  jack_nframes_t nframes, int sampleRate,
			  int *sampleCounter) {

     //     MeowSession *s = session;
     
     double amp = 0.5;
     double samplesPerMS = sampleRate / 1000;
     int i;

     /* here is where we generate the audio. We ask the mixer to generate
	the audio which follows the signal chain upwards. */
     int freq = 100;
     int samplesPerCycle = (double)sampleRate/freq;
     int speed = 100;
     int samplesPerStep = samplesPerMS * speed;
     int halfCycle = samplesPerCycle / 2;

     for (i=0; i<nframes; i++) {

	  int cycleSample = *sampleCounter % samplesPerCycle;

	  double decay = 1.0 - ((double)*sampleCounter /
				(double)samplesPerStep);

	  // square wave
	  if (cycleSample < halfCycle) {
	       out[i] = -1*amp*decay;
	  } else {
	       out[i] = amp*decay;
	  }
	  (*sampleCounter)++;
     }
}
