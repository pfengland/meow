#include "MeowApp.h"
#include <stdlib.h>

MeowApp* MeowApp_create(void) {
     MeowApp *app = malloc(sizeof(*app));
     app->update = 0;
     //     app->window = MeowWindow_create();
     app->session = MeowSession_create();
     app->console = MeowConsole_create(app->session);
     return app;
}

void MeowApp_start(MeowApp *app) {

     // limit framerate
     //    int fps = 30;
    //    int starttime;

     // start the session
     MeowSession_start(app->session);

    while (!app->session->quit) {
	 MeowConsole_prompt(app->console);
    }
    
    /*    SDL_Event event;
    while (!app->quit) {

        // record start time to limit framerate when needed
        starttime = SDL_GetTicks();

	if (SDL_PollEvent(&event)) {

	    if (event.type == SDL_KEYDOWN) {

		 if (event.key.keysym.sym == SDLK_q) {
		      app->quit = 1;
		 }

            } else if (event.type == SDL_QUIT) {
		 app->quit = 1;
	    }
	}

        // drawing
	if (app->update) {

	    app->update = 0;

            // limit framerate
            int elapsed = SDL_GetTicks() - starttime;
            int frametime = 1000 / fps;
            if (elapsed < frametime) {
                int pause = frametime - elapsed;
                SDL_Delay(pause);
            }
        } 
	} */
}

void MeowApp_free(MeowApp *app) {
     MeowWindow_free(app->window);
     MeowConsole_free(app->console);
     MeowSession_free(app->session);
     free(app);
}
