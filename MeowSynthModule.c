#include "MeowSynthModule.h"
#include <stdlib.h>
#include <stdio.h>

MeowModule* MeowSynthModule_create() {
     MeowSynthModule *synth = malloc(sizeof(*synth));
     synth->base = MeowModule_create();
     synth->base->impl = synth;
     synth->base->ops = &MeowSynthModule_ops;
     return synth->base;
}

void MeowSynthModule_start(MeowModule *synth) {
     printf("starting synth\n");
}

void MeowSynthModule_free(MeowModule *m) {
     printf("stopping synth\n");
     MeowSynthModule *synth = m->impl;
     MeowModule_free(m);
     free(synth);
}
