#include "MeowMidiModule.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

MeowModule* MeowMidiModule_create(MeowKeyboard *keys) {

     MeowMidiModule *midi = malloc(sizeof(*midi));
     midi->base = MeowModule_create();
     midi->base->impl = midi;
     midi->base->ops = &MeowMidiModule_ops;

     midi->keys = keys;

     midi->midiInput = NULL;
     midi->stopInputThread = 0;

     return midi->base;
}

void MeowMidiModule_free(MeowModule *m) {
     printf("stopping midi\n");

     MeowMidiModule *midi = m->impl;

     midi->stopInputThread = 1;

     snd_rawmidi_close(midi->midiInput);
     midi->midiInput = NULL;
     
     free(midi);
     MeowModule_free(m);
}

void* MeowMidiModule_inputThread(void *m) {

     MeowMidiModule *midi = (MeowMidiModule*)m;
     printf("midi thread started\n");

     int status;
     char buffer[1];
     int note, velo;

     while (1) {
	  if (midi->stopInputThread) break;
	  if ((status = snd_rawmidi_read(midi->midiInput, buffer, 1)) < 0) {
	       printf("Problem reading MIDI input: %s\n", snd_strerror(status));
	  }
	  if ((unsigned char)buffer[0] == 0x90) {
	       if ((status = snd_rawmidi_read(midi->midiInput,
					      buffer, 1)) < 0) {
		    printf("Problem reading MIDI input: %s\n",
			   snd_strerror(status));
	       }
	       note = (unsigned char)buffer[0];
	       if ((status = snd_rawmidi_read(midi->midiInput,
					      buffer, 1)) < 0) {
		    printf("Problem reading MIDI input: %s\n",
			   snd_strerror(status));
	       }
	       velo = (unsigned char)buffer[0];
	       printf("note on: %d %d\n", note, velo);
	       if (velo == 0) {
		    midi->keys->channels[0].notes[note].on = 0;
		    midi->keys->channels[0].notes[note].velo = 0;
	       } else {
		    midi->keys->channels[0].notes[note].on = 1;
		    midi->keys->channels[0].notes[note].velo = velo;
	       }
	       fflush(stdout);
	  }
     }
     
     return NULL;
}

void MeowMidiModule_start(MeowModule *m) {

     printf("starting midi\n");

     MeowMidiModule *midi = m->impl;
     
     const char* portname = "hw:1,0,0";
     int mode = 0;
     int status;
     if ((status = snd_rawmidi_open(&midi->midiInput, NULL,
				    portname, mode)) < 0) {
	  printf("Problem opening MIDI input: %s\n", snd_strerror(status));
	  exit(1);
     }

     status = pthread_create(&midi->midiInputThread, NULL,
			     MeowMidiModule_inputThread, midi);
     if (status == -1) {
	  printf("Unable to create MIDI input thread\n");
	  exit(1);
     }
}

