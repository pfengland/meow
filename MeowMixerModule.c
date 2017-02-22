#include "MeowMixerModule.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

MeowModule* MeowMixerModule_create(void) {

     MeowMixerModule *mixer = malloc(sizeof(*mixer));
     mixer->base = MeowModule_create();
     mixer->base->impl = mixer;
     mixer->base->ops = &MeowMixerModule_ops;

     return mixer->base;
}

void MeowMixerModule_free(MeowModule *m) {
     printf("stopping mixer\n");

     MeowMixerModule *mixer = m->impl;

     free(mixer);
     MeowModule_free(m);
}

void MeowMixerModule_start(MeowModule *m) {

     printf("starting mixer\n");

     //     MeowMixerModule *mixer = m->impl;
     
}



void MeowMixerModule_generate(MeowMixerModule *mixer, jack_default_audio_sample_t *out,
			      jack_nframes_t nframes, int sampleRate,
			      int *sampleCounter) {

     // test tone
     
     double amp = 0.1;
     int i;

     /* here is where we generate the audio. We ask the mixer to generate
	the audio which follows the signal chain upwards. */
     int freq = 100;
     int samplesPerCycle = (double)sampleRate/freq;
     int halfCycle = samplesPerCycle / 2;

     for (i=0; i<nframes; i++) {

	  int cycleSample = *sampleCounter % samplesPerCycle;

	  // square wave
	  if (cycleSample < halfCycle) {
	       out[i] = -1*amp;
	  } else {
	       out[i] = amp;
	  }
	  (*sampleCounter)++;
     }
}
