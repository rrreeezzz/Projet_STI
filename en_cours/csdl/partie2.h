#ifndef H_PARTIE2
#define H_PARTIE2

#include "module.h"
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>

extern void zoom(int posx, int posy, int val_zoom, SDL_Surface *tempo);

extern void pause(SDL_Rect TBoutton);

extern void getPixelColor(SDL_Rect position, SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b);

extern void remplirFrance(Point **tab, SDL_Surface *sortie, SDL_Surface *blit_surface, int x, int y, int type);

extern SDL_Rect boutton();

extern void sdl_ini();

extern void * fichier_dif(data_map * data_75);

SDL_Surface * ecran;

#endif // H_PARTIE2
