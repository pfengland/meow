#ifndef H_MEOWWINDOW
#define H_MEOWWINDOW

#include <SDL/SDL.h>

typedef struct MeowWindow_s MeowWindow;
struct MeowWindow_s {
     SDL_Surface *screen;
};

MeowWindow* MeowWindow_create(void);
void MeowWindow_free(MeowWindow *app);

#endif
