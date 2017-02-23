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
     k->scrollDownPressed = 0;
     k->scrollUpPressed = 0;
     k->mouseDownTime = 0;
     k->mouseRepeatTime = 0;
     k->mouseDownX = 0;
     k->mouseDownY = 0;
     k->update = 0;
     k->maxFirstKey = 127;
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
     SDL_Color scrollColor = {100,100,100};
     SDL_Color scrollClickColor = {200,200,200};
     SDL_Surface *text_surface;
     char numberText[100];

     // draw the initial scrollbar box
     // define the rect to draw it on
     SDL_Rect um = {x: x + padding, y: y + padding,
		    w: k->keySize - padding * 2, h: k->keySize - padding * 2};
     if (k->scrollDownPressed) {
	  SDL_FillRect(screen, &um, SDL_MapRGB(screen->format,
					       scrollClickColor.r,
					       scrollClickColor.g,
					       scrollClickColor.b));
     } else {
	  SDL_FillRect(screen, &um, SDL_MapRGB(screen->format,
					       scrollColor.r,
					       scrollColor.g,
					       scrollColor.b));

     }

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

     // find out if we're scrolled off the end and change the firstKey
     // find out how many keys will fit
     int screenKeys = k->w / k->keySize - 2;
     // calculate offset for first key
     int keyOffset = 0;
     if (k->firstKey > MeowKeyboard_noteCount - 1 - screenKeys) {
	  k->firstKey = MeowKeyboard_noteCount - 1 - screenKeys;
	  k->maxFirstKey = k->firstKey;
	  keyOffset = k->w % k->keySize - k->keySize;
     }
     
     for (int i=k->firstKey; i<MeowKeyboard_noteCount; i++) {
	  if (keyX > screen->w - k->keySize) break;
	  um.x = keyX + keyOffset;
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

     if (k->scrollUpPressed) {
	  SDL_FillRect(screen, &um, SDL_MapRGB(screen->format,
					       scrollClickColor.r,
					       scrollClickColor.g,
					       scrollClickColor.b));
     } else {
	  SDL_FillRect(screen, &um, SDL_MapRGB(screen->format,
					       scrollColor.r,
					       scrollColor.g,
					       scrollColor.b));

     }

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

Uint32 KeyboardView_timeout(Uint32 interval, void *keyboard) {
     printf("timeout called\n");
     KeyboardView *k = keyboard;
     //     SDL_Event event = {type: SDL_MOUSEBUTTONDOWN, button: k->lastButton};
     //          SDL_PushEvent(&event);
	       // down scroll button pressed
     if (k->scrollDownPressed) {
	  k->firstKey--;
	  if (k->firstKey < 0 ) k->firstKey = 0;
	  k->update = 1;
     } else if (k->scrollUpPressed) {
	  if (k->firstKey < k->maxFirstKey) {
	       k->firstKey++;
	       if (k->firstKey >= MeowKeyboard_noteCount)
		    k->firstKey = MeowKeyboard_noteCount - 1;
	  }
	  k->update = 1;
     }
     
     return 100;
}

int KeyboardView_mouseButtonEvent(KeyboardView *k, SDL_MouseButtonEvent *event) {
     if (event->state == SDL_PRESSED) {
	  if (event->x <= k->x + k->keySize) {
	       // down scroll button pressed
	       k->firstKey--;
	       if (k->firstKey < 0 ) k->firstKey = 0;
	       k->scrollDownPressed = 1;

	       k->lastButton.type = event->type;
	       k->lastButton.button = event->button;
	       k->lastButton.state = event->state;
	       k->lastButton.x = event->x;
	       k->lastButton.y = event->y;
	       printf("adding timer\n");
	       k->repeatTimer = SDL_AddTimer(300,
					     KeyboardView_timeout,
					     k);
	       
	       return 1;
	  } else if (event->x >= k->x + k->w - k->keySize) {
	       // up scroll button pressed
	       if (k->firstKey < k->maxFirstKey) {
		    k->firstKey++;
		    if (k->firstKey >= MeowKeyboard_noteCount)
			 k->firstKey = MeowKeyboard_noteCount - 1;
	       }
	       k->scrollUpPressed = 1;
	       k->lastButton.type = event->type;
	       k->lastButton.button = event->button;
	       k->lastButton.state = event->state;
	       k->lastButton.x = event->x;
	       k->lastButton.y = event->y;
	       printf("adding timer\n");	       
	       k->repeatTimer = SDL_AddTimer(300,
					     KeyboardView_timeout,
					     k);
	       return 1;
	  }
     } else {
	  if (k->scrollDownPressed) {
	       k->scrollDownPressed = 0;
	       printf("removing timer\n");
	       SDL_RemoveTimer(k->repeatTimer);
	       return 1;
	  } else if (k->scrollUpPressed) {
	       k->scrollUpPressed = 0;
	       printf("removing timer\n");
	       SDL_RemoveTimer(k->repeatTimer);
	       return 1;
	  }
     }
     return 0;
}
