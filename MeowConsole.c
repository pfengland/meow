#include "MeowConsole.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>

/* text interface for meow music studio

   commands:

   modules:
   create instrument synth "bass"
   show instruments
   delete instrument synth "bass" 
   delete all instruments */

MeowConsole* MeowConsole_create(MeowSession *s) {
     MeowConsole* c = malloc(sizeof(*c));
     c->session = s;
     return c;
}

void MeowConsole_free(MeowConsole *c) {
     free(c);
}

void MeowConsole_prompt(MeowConsole *c) {
     char *line = readline("meow->$ ");
     if (strcmp(line, "quit") == 0) {
	  c->session->quit = 1;
     }
     free(line);
}
