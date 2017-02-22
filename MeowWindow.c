#include "MeowWindow.h"
#include <stdlib.h>
#include <X11/Xlib.h>

MeowWindow* MeowWindow_create(MeowSession *s) {

     MeowWindow *window = malloc(sizeof(*window));

     window->update = 0;
     window->session = s;

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

void MeowWindow_mainLoop(MeowWindow *w) {

     // record start time to limit framerate when needed
     w->frameStartTime = SDL_GetTicks();

     MeowWindow_handleEvents(w);
     MeowWindow_update(w);
}

void MeowWindow_update(MeowWindow *w) {

     // drawing
     if (w->update) {

	  w->update = 0;

	  // limit framerate
	  int elapsed = SDL_GetTicks() - w->frameStartTime;
	  int frametime = 1000 / MeowWindow_frameRate;
	  if (elapsed < frametime) {
	       int pause = frametime - elapsed;
	       SDL_Delay(pause);
	  }
     } 
}

void MeowWindow_handleEvents(MeowWindow *w) {

     SDL_Event event;

     if (SDL_PollEvent(&event)) {

	  if (event.type == SDL_KEYDOWN) {

	       /*	       if (event.key.keysym.sym == SDLK_q) {
		    w->session->quit = 1;
		    } */

	  } else if (event.type == SDL_QUIT) {
	       w->session->quit = 1;
	  }
     }

}
