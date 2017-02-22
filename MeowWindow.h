#ifndef H_MEOWWINDOW
#define H_MEOWWINDOW

#include <SDL/SDL.h>
#include "MeowSession.h"

static const int MeowWindow_frameRate = 30;

typedef struct MeowWindow_s MeowWindow;
struct MeowWindow_s {
     SDL_Surface *screen;
     int update;
     MeowSession *session;
     int frameStartTime;
};

MeowWindow* MeowWindow_create(MeowSession *s);
void MeowWindow_free(MeowWindow *w);
void MeowWindow_mainLoop(MeowWindow *w);
void MeowWindow_handleEvents(MeowWindow *w);
void MeowWindow_update(MeowWindow *w);

#endif
