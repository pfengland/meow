#ifndef H_MEOWCONSOLE
#define H_MEOWCONSOLE

#include "MeowSession.h"

typedef struct MeowConsole_s MeowConsole;
struct MeowConsole_s {
     MeowSession* session;
};

MeowConsole* MeowConsole_create(MeowSession *s);
void MeowConsole_free(MeowConsole *c);
void MeowConsole_prompt(MeowConsole *c);

#endif
