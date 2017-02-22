#ifndef H_MEOWSESSION
#define H_MEOWSESSION

#include "MeowModuleCollection.h"
#include "MeowKeyboard.h"

typedef struct MeowSession_s MeowSession;
struct MeowSession_s {
     int quit;
     MeowModuleCollection *modules;
     MeowKeyboard *keys;
};

MeowSession* MeowSession_create(void);
void MeowSession_start(MeowSession *s);
void MeowSession_free(MeowSession *s);

#endif
