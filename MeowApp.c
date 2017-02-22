#include "MeowApp.h"
#include <stdlib.h>

MeowApp* MeowApp_create(void) {
     MeowApp *app = malloc(sizeof(*app));
     app->session = MeowSession_create();
     app->console = MeowConsole_create(app->session);
     app->window = MeowWindow_create(app->session);
     return app;
}

void MeowApp_start(MeowApp *app) {

     // start the session
     MeowSession_start(app->session);

     /*    while (!app->session->quit) {
	 MeowConsole_prompt(app->console);
	 } */
    
     while (!app->session->quit) {
	  MeowWindow_mainLoop(app->window);
     }
}

void MeowApp_free(MeowApp *app) {
     MeowWindow_free(app->window);
     MeowConsole_free(app->console);
     MeowSession_free(app->session);
     free(app);
}
