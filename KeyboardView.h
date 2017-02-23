#ifndef H_KEYBOARDVIEW
#define H_KEYBOARDVIEW

#include "MeowSession.h"
#include <SDL/SDL.h>

#define KeyboardView_notesPerOctave 12

typedef struct KeyboardView_s KeyboardView;
struct KeyboardView_s {
     MeowSession *session;
     int x, y, h, w;
     int firstKey;
     int maxFirstKey;
     int keySize;
     int scrollDownPressed;
     int scrollUpPressed;
     int mouseDownTime;
     int mouseRepeatTime;
     int mouseDownX, mouseDownY;
     SDL_TimerID repeatTimer;
     SDL_MouseButtonEvent lastButton;
     int update;
};

KeyboardView* KeyboardView_create(MeowSession *s);
void KeyboardView_free(KeyboardView *k);
void KeyboardView_draw(KeyboardView *k, SDL_Surface *screen, int x, int y);
// returns 1 if a draw update is needed
int KeyboardView_mouseButtonEvent(KeyboardView *k, SDL_MouseButtonEvent *event);

#endif
