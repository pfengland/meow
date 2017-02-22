#ifndef H_KEYBOARDVIEW
#define H_KEYBOARDVIEW

#include "MeowSession.h"
#include <SDL/SDL.h>

#define KeyboardView_notesPerOctave 12

typedef struct KeyboardView_s KeyboardView;
struct KeyboardView_s {
     MeowSession *session;
};

KeyboardView* KeyboardView_create(MeowSession *s);
void KeyboardView_free(KeyboardView *k);
void KeyboardView_draw(KeyboardView *k, SDL_Surface *screen, int x, int y);

#endif
