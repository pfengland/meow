#include "KeyboardView.h"
#include "MeowKeyboard.h"
#include <stdlib.h>

const int KeyboardView_pattern[KeyboardView_notesPerOctave] =
     {0,1,0,1,0,0,1,0,1,0,1,0};

KeyboardView* KeyboardView_create(MeowSession *s) {
     KeyboardView *k = malloc(sizeof(*k));
     k->session = s;
     return k;
}

void KeyboardView_free(KeyboardView *k) {
     free(k);
}

void KeyboardView_draw(KeyboardView *k, SDL_Surface *screen, int x, int y) {
     // draw the keyboard
     int keySize = 15;
     int i;
     int keyX = x;
     for (i=0; i<MeowKeyboard_noteCount; i++) {
	  if (keyX > screen->w) break;
	  SDL_Rect um = {x: keySize * i + x + 1, y: y + 1, w: keySize - 2,
			 h: keySize - 2};
	  if (KeyboardView_pattern[i%KeyboardView_notesPerOctave]) {
	       SDL_FillRect(screen, &um, SDL_MapRGB(screen->format, 100,0,100));
	  } else {
	       SDL_FillRect(screen, &um, SDL_MapRGB(screen->format, 0, 200, 0));
	  }
	  keyX += keySize;
     }
}
