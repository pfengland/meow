/* music entertainment operating workstation */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "MeowApp.h"

MeowApp *app = NULL;

void handle_signal(int signum) {
    printf("meow: caught signal, quitting\n");
    MeowApp_free(app);
    exit(0);
}

int main(int argc, char *argv[]) {

    signal(SIGINT, handle_signal);

    app = MeowApp_create();

    printf("meow: ready\n");
    MeowApp_start(app);

    MeowApp_free(app);

    printf("meow: done\n");
    exit(0);
}
