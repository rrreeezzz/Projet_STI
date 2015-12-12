#ifndef H_PARTIE2
#define H_PARTIE2

#include "module.h"
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>
#include <string.h>

extern void zoom(int posx, int posy, int val_zoom, SDL_Surface * tempo, SDL_Surface * ecran);

extern void pause(Point ** tabPt, SDL_Rect TBoutton, SDL_Surface * tempo, SDL_Surface * ecran);

extern void getPixelColor(SDL_Rect position, SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b);

extern void remplirFrance(Point **tab, SDL_Surface *sortie, int li, int co, SDL_Surface * ecran);

extern SDL_Rect boutton(SDL_Surface * ecran, TTF_Font * police);

extern void sdl_ini(Point ** tabPt);

#endif // H_PARTIE2


