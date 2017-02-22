#include "MeowModule.h"
#include <stdlib.h>

MeowModule* MeowModule_create(void) {
     MeowModule* m = malloc(sizeof(*m));
     m->ops = NULL;
     m->impl = NULL;
     return m;
}

void MeowModule_free(MeowModule *m) {
     free(m);
}

