#include "MeowWindow.h"
#include <stdlib.h>
#include <X11/Xlib.h>
#include <SDL/SDL_ttf.h>

MeowWindow* MeowWindow_create(MeowSession *s) {

     MeowWindow *window = malloc(sizeof(*window));

     window->update = 1;
     window->session = s;

     XInitThreads();
     SDL_Init(SDL_INIT_VIDEO);
     if (TTF_Init() == -1) {
	  printf("TTF_Init: %s\n", TTF_GetError());
	  exit(1);
     }

     // get the screen
     //    int opts = SDL_SWSURFACE|SDL_NOFRAME;
     int opts = SDL_SWSURFACE|SDL_RESIZABLE;
     window->screen = SDL_SetVideoMode(640, 480, 32, opts);

     SDL_WM_SetCaption("MEOW", NULL);

     window->keyboard = KeyboardView_create(window->session);
     
     return window;
}

void MeowWindow_free(MeowWindow *w) {
     TTF_Quit();
     SDL_Quit();
     KeyboardView_free(w->keyboard);
     free(w);
}

void MeowWindow_mainLoop(MeowWindow *w) {

     // record start time to limit framerate when needed
     w->frameStartTime = SDL_GetTicks();

     MeowWindow_handleEvents(w);
     MeowWindow_repeatEvents(w);
     MeowWindow_update(w);
}

void MeowWindow_repeatEvents(MeowWindow *w) {
     int repeatDelay = 300;
     int repeatInterval = 100;
     int time = SDL_GetTicks();
     // mouse has been held past the repeat delay
     // and no repeat events have been sent
     if (time - w->keyboard->mouseDownTime >= repeatDelay &&
	 !w->keyboard->mouseRepeatTime) {
	  if (KeyboardView_mouseButtonRepeat(w->keyboard)) {
	       w->update = 1;
	  }
     } else if (time - w->keyboard->mouseRepeatTime >= repeatInterval &&
		w->keyboard->mouseRepeatTime) {
	  if (KeyboardView_mouseButtonRepeat(w->keyboard)) {
	       w->update = 1;
	  }
     }
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

     while (SDL_PollEvent(&event)) {

	  if (event.type == SDL_KEYDOWN) {

	       /*	       if (event.key.keysym.sym == SDLK_q) {
		    w->session->quit = 1;
		    } */

	  } else if (event.type == SDL_QUIT) {
	       w->session->quit = 1;
	  } else if (event.type == SDL_VIDEORESIZE) {
	       int opts = SDL_SWSURFACE|SDL_RESIZABLE;
	       w->screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 32, opts);
	       w->update = 1;
	  } else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
	       // need to pass the event to the child view
	       // child views can have a base class defining their rectangle
	       // to easily check who needs to get the mouse event etc
	       if (event.button.x >= w->keyboard->x &&
		   event.button.x <= w->keyboard->x + w->keyboard->w &&
		   event.button.y >= w->keyboard->y &&
		   event.button.y <= w->keyboard->y + w->keyboard->h) {
		    printf("keyboard clicked\n");

		    if (KeyboardView_mouseButtonEvent(w->keyboard, &event.button)) {
			 w->update = 1;
		    }

		    // reset repeat timer
		    w->keyboard->mouseRepeatTime = 0;

		    // record the time when the mouse button was pressed so we can send repeat events
		    // after a certain delay
		    if (event.type == SDL_MOUSEBUTTONDOWN) {
			 w->keyboard->mouseDownTime = SDL_GetTicks();
			 w->keyboard->mouseDownX = event.button.x;
			 w->keyboard->mouseDownY = event.button.y;
		    }
	       }
	  }
     }
}
