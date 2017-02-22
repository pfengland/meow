#ifndef H_MEOWAPP
#define H_MEOWAPP

#include "MeowWindow.h"
#include "MeowConsole.h"
#include "MeowSession.h"

typedef struct MeowApp_s MeowApp;
struct MeowApp_s {
     MeowWindow *window;
     MeowConsole *console;
     MeowSession *session;
     int update;
};

MeowApp* MeowApp_create(void);
void MeowApp_start(MeowApp *app);
void MeowApp_free(MeowApp *app);

#endif
