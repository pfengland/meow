#include "MeowWindow.h"
#include <stdlib.h>
#include <X11/Xlib.h>

MeowWindow* MeowWindow_create(MeowSession *s) {

     MeowWindow *window = malloc(sizeof(*window));

     window->update = 1;
     window->session = s;

     XInitThreads();
     SDL_Init(SDL_INIT_VIDEO);

     // get the screen
     //    int opts = SDL_SWSURFACE|SDL_NOFRAME;
     int opts = SDL_SWSURFACE;
     window->screen = SDL_SetVideoMode(640, 480, 32, opts);

     SDL_WM_SetCaption("MEOW", NULL);

     window->keyboard = KeyboardView_create(window->session);
     
     return window;
}

void MeowWindow_free(MeowWindow *w) {
     SDL_Quit();
     KeyboardView_free(w->keyboard);
     free(w);
}

void MeowWindow_mainLoop(MeowWindow *w) {

     // record start time to limit framerate when needed
     w->frameStartTime = SDL_GetTicks();

     MeowWindow_handleEvents(w);
     MeowWindow_update(w);
}

void MeowWindow_update(MeowWindow *window) {

     // drawing
     if (window->update) {

	  window->update = 0;

	  SDL_FillRect(window->screen, NULL,
		       SDL_MapRGB(window->screen->format, 0,100,100));

	  KeyboardView_draw(window->keyboard, window->screen, 0, 0);

	  SDL_Flip(window->screen);

	  // limit framerate
	  int elapsed = SDL_GetTicks() - window->frameStartTime;
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
