#include "MeowWindow.h"
#include <stdlib.h>
#include <X11/Xlib.h>

MeowWindow* MeowWindow_create(void) {

     MeowWindow *window = malloc(sizeof(*window));

     XInitThreads();
     SDL_Init(SDL_INIT_VIDEO);

     // get the screen
     //    int opts = SDL_SWSURFACE|SDL_NOFRAME;
     int opts = SDL_SWSURFACE;
     window->screen = SDL_SetVideoMode(640, 480, 32, opts);

     SDL_WM_SetCaption("MEOW", NULL);
     SDL_FillRect(window->screen, NULL,
		  SDL_MapRGB(window->screen->format, 0,100,100));
     SDL_Flip(window->screen);

     return window;
}

void MeowWindow_free(MeowWindow *app) {
     SDL_Quit();
     free(app);
}
