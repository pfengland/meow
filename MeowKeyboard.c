#include "MeowKeyboard.h"
#include <stdlib.h>

MeowKeyboard* MeowKeyboard_create(void) {
     int i;
     int j;
     MeowKeyboard *keys = malloc(sizeof(*keys));
     for (i=0; i<MeowKeyboard_channelCount; i++) {
	  for (j=0; j<MeowKeyboard_noteCount; j++) {
	       keys->channels[i].notes[j].on = 0;
	       keys->channels[i].notes[j].velo = 0;
	  }
     }
     return keys;
}

void MeowKeyboard_free(MeowKeyboard *keys) {
     free(keys);
}
