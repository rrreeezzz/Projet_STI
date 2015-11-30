#ifndef H_PARTIE2
#define H_PARTIE2

#include "module.h"

extern void pause(SDL_Surface *boutton);

extern void getPixelColor(SDL_Rect position, SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b);

extern void remplirFrance(Point **tab, SDL_Surface *pixel, SDL_Surface *sortie, int li, int co);

#endif // H_PARTIE2


