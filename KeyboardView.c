#include "KeyboardView.h"
#include "MeowKeyboard.h"
#include <SDL/SDL_ttf.h>
#include <stdlib.h>

const int KeyboardView_pattern[KeyboardView_notesPerOctave] =
     {0,1,0,1,0,0,1,0,1,0,1,0};

KeyboardView* KeyboardView_create(MeowSession *s) {
     KeyboardView *k = malloc(sizeof(*k));
     k->session = s;

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
     int keySize = 25;
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
		    w: keySize - padding * 2, h: keySize - padding * 2};
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
     
     keyX += keySize;
     
     for (int i=0; i<MeowKeyboard_noteCount; i++) {
	  if (keyX > screen->w - keySize) break;
	  um.x = keyX;
	  um.y = y + padding;
	  um.w = keySize - padding * 2;
	  um.h = keySize - padding * 2;
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
	  
	  keyX += keySize;
     }

     // draw the final scrollbar box
     // define the rect to draw it on
     um.x = screen->w - keySize + padding;
     um.y = y + padding;
     um.w = keySize - padding * 2;
     um.h = keySize - padding * 2;
     
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


     TTF_CloseFont(font);
}
