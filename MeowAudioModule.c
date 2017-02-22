#include "MeowAudioModule.h"
#include <stdlib.h>
#include <stdio.h>

MeowModule* MeowAudioModule_create(void) {

     MeowAudioModule *audio = malloc(sizeof(*audio));
     audio->base = MeowModule_create();
     audio->base->impl = audio;
     audio->base->ops = &MeowAudioModule_ops;

     audio->outputPort = NULL;
     audio->jackClient = NULL;
     audio->sampleRate = 0;
     audio->sampleCounter = 0;
     
     return audio->base;
}

void MeowAudioModule_free(MeowModule *m) {
     printf("stopping audio\n");
     MeowAudioModule *audio = m->impl;
     jack_client_close(audio->jackClient);
     free(audio);
     MeowModule_free(m);
}

void MeowAudioModule_start(MeowModule *m) {

     printf("starting audio\n");
     MeowAudioModule *audio = m->impl;

     const char *clientName = "Meow";
     const char *serverName = NULL;
     jack_options_t options = JackNullOption;
     jack_status_t status;

     audio->jackClient = jack_client_open(clientName, options, &status,
					  serverName);
     if (audio->jackClient == NULL) {
	  fprintf(stderr, "jack_client_open failed, status = 0x%2.0x\n",
		  status);
	if (status & JackServerFailed) {
	     fprintf(stderr, "unable to connect to jack server\n");
	}
	exit(EXIT_FAILURE);
     }
     if (status & JackServerStarted) {
	  fprintf(stderr, "jack server started");
     }
     if (status & JackNameNotUnique) {
	  clientName = jack_get_client_name(audio->jackClient);
	  fprintf(stderr, "unique name %s assigned\n", clientName);
     }

     jack_set_process_callback(audio->jackClient, MeowAudioModule_process,
			       audio);

     jack_on_shutdown(audio->jackClient, MeowAudioModule_shutdown, audio);

     audio->sampleRate = jack_get_sample_rate(audio->jackClient);

     printf("engine sample rate: %" PRIu32 "\n", audio->sampleRate);

     audio->outputPort = jack_port_register(audio->jackClient, "output",
					    JACK_DEFAULT_AUDIO_TYPE,
					    JackPortIsOutput, 0);

     if (audio->outputPort == NULL) {
	  fprintf(stderr, "no more jack ports available\n");
	  exit(EXIT_FAILURE);
     }

     if (jack_activate(audio->jackClient)) {
	  fprintf(stderr, "can't activate client\n");
	  exit(EXIT_FAILURE);
     }

     const char **ports = jack_get_ports (audio->jackClient, NULL, NULL,
					  JackPortIsPhysical|JackPortIsInput);
     if (ports == NULL) {
	  fprintf(stderr, "no physical playback ports\n");
	  exit (1);
     }

     if (jack_connect(audio->jackClient, jack_port_name(audio->outputPort),
		      ports[0])) {
	  fprintf (stderr, "cannot connect output ports\n");
     }

     free (ports);
}

int MeowAudioModule_process(jack_nframes_t nframes, void *audio) {

     MeowAudioModule *a = audio;

     jack_default_audio_sample_t *out;

     // get the output buffer pointer
     out = jack_port_get_buffer(a->outputPort, nframes);

     a->generateCallback(a->callbackArg, out, nframes, a->sampleRate,
		      &a->sampleCounter);
     return 0;
}

void MeowAudioModule_setGenerateCallback(MeowAudioModule *a,
					 MeowAudioModule_generateCallback callback,
					 void *arg) {
     a->generateCallback = callback;
     a->callbackArg = arg;
 }


void MeowAudioModule_shutdown(void *audio) {
     printf("jack shutdown\n");
}
