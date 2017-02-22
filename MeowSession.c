#include "MeowSession.h"
#include "MeowSynthModule.h"
#include "MeowMidiModule.h"
#include <stdlib.h>

MeowSession* MeowSession_create(void) {

     MeowSession* s = malloc(sizeof(*s));
     s->quit = 0;

     s->keys = MeowKeyboard_create();

     // create startup modules
     s->modules = MeowModuleCollection_create();

     // create the midi input module
     MeowModule *m = MeowMidiModule_create(s->keys);
     MeowModuleCollection_add(s->modules, m);

     // for now - create a single synth instance on startup
     m = MeowSynthModule_create();
     MeowModuleCollection_add(s->modules, m);

     return s;
}

void MeowSession_start(MeowSession *s) {
     MeowModuleCollection_startAll(s->modules);
}

void MeowSession_free(MeowSession *s) {
     MeowModuleCollection_free(s->modules);
     MeowKeyboard_free(s->keys);
     free(s);
}
