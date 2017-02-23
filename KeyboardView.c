#include "KeyboardView.h"
#include "MeowKeyboard.h"
#include <SDL/SDL_ttf.h>
#include <stdlib.h>

const int KeyboardView_pattern[KeyboardView_notesPerOctave] =
     {0,1,0,1,0,0,1,0,1,0,1,0};

KeyboardView* KeyboardView_create(MeowSession *s) {
     KeyboardView *k = malloc(sizeof(*k));
     k->session = s;
     k->x = 0;
     k->y = 0;
     k->w = 0;
     k->h = 0;
     k->firstKey = 0;
     k->keySize = 25;
     return k;
}

void KeyboardView_free(KeyboardView *k) {
     free(k);
}

void KeyboardView_draw(KeyboardView *k, SDL_Surface *screen, int x, int y) {

     // load the font
     TTF_Font *font=TTF_OpenFont("bitwise.ttf", 10);
     if(!font) {
	  printf("TTF_OpenFont: %s\n", TTF_GetError());
	  exit(1);
     }

     // draw the keyboard

     // define pixel size of key squares

     // keep track of the x coordinate as we draw squares
     int keyX = x;
     // pixel padding for squares and numbers
     int padding = 1;

     SDL_Color color={0,0,0};
     SDL_Surface *text_surface;
     char numberText[100];

     // draw the initial scrollbar box
     // define the rect to draw it on
     SDL_Rect um = {x: x + padding, y: y + padding,
		    w: k->keySize - padding * 2, h: k->keySize - padding * 2};
     SDL_FillRect(screen, &um, SDL_MapRGB(screen->format, 100, 100, 100));

     if(!(text_surface=TTF_RenderText_Solid(font,"<",color))) {
	  //handle error here, perhaps print TTF_GetError at least
     } else {
	  um.x += padding;
	  um.y += padding;
	  SDL_BlitSurface(text_surface,NULL,screen,&um);
	  //perhaps we can reuse it, but I assume not for simplicity.
	  SDL_FreeSurface(text_surface);
     }
     
     keyX += k->keySize;
     
     for (int i=k->firstKey; i<MeowKeyboard_noteCount; i++) {
	  if (keyX > screen->w - k->keySize) break;
	  um.x = keyX;
	  um.y = y + padding;
	  um.w = k->keySize - padding * 2;
	  um.h = k->keySize - padding * 2;
	  if (KeyboardView_pattern[i%KeyboardView_notesPerOctave]) {
	       SDL_FillRect(screen, &um, SDL_MapRGB(screen->format, 100,0,100));
	  } else {
	       SDL_FillRect(screen, &um, SDL_MapRGB(screen->format, 0, 200, 0));
	  }

	  sprintf(numberText, "%d", i);
	  if(!(text_surface=TTF_RenderText_Solid(font,numberText,color))) {
	       //handle error here, perhaps print TTF_GetError at least
	  } else {
	       um.x += padding;
	       um.y += padding;
	       SDL_BlitSurface(text_surface,NULL,screen,&um);
	       //perhaps we can reuse it, but I assume not for simplicity.
	       SDL_FreeSurface(text_surface);
	  }
	  
	  keyX += k->keySize;
     }

     // draw the final scrollbar box
     // define the rect to draw it on
     um.x = screen->w - k->keySize + padding;
     um.y = y + padding;
     um.w = k->keySize - padding * 2;
     um.h = k->keySize - padding * 2;
     
     SDL_FillRect(screen, &um, SDL_MapRGB(screen->format, 100, 100, 100));

     if(!(text_surface=TTF_RenderText_Solid(font,">",color))) {
	  //handle error here, perhaps print TTF_GetError at least
     } else {
	  um.x += padding;
	  um.y += padding;
	  SDL_BlitSurface(text_surface,NULL,screen,&um);
	  //perhaps we can reuse it, but I assume not for simplicity.
	  SDL_FreeSurface(text_surface);
     }

     k->x = x;
     k->y = y;
     k->w = screen->w - x;
     k->h = k->keySize;

     TTF_CloseFont(font);
}

int KeyboardView_mouseButtonEvent(KeyboardView *k, SDL_MouseButtonEvent *event) {
     if (event->x <= k->x + k->keySize) {
	  // down scroll button pressed
	  k->firstKey--;
	  if (k->firstKey < 0 ) k->firstKey = 0;
	  return 1;
     } else if (event->x >= k->x + k->w - k->keySize) {
	  // up scroll button pressed
	  k->firstKey++;
	  if (k->firstKey >= MeowKeyboard_noteCount)
	       k->firstKey = MeowKeyboard_noteCount - 1;
	  return 1;
     }
     return 0;
}
