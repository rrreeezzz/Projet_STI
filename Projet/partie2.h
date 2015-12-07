#ifndef H_PARTIE2
#define H_PARTIE2

#include "module.h"
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>

extern void zoom(int posx, int posy, int val_zoom, SDL_Surface * tempo, SDL_Surface * ecran);

extern void pause(SDL_Surface *boutton, SDL_Surface * tempo, SDL_Surface * ecran);

extern void getPixelColor(SDL_Rect position, SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b);

extern void remplirFrance(Point **tab, SDL_Surface *pixel, SDL_Surface *sortie, int li, int co);

extern void sdl_ini(Point ** tabPt);

#endif // H_PARTIE2


