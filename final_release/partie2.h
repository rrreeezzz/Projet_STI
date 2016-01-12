#ifndef H_PARTIE2
#define H_PARTIE2

#include "module.h"
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>

extern void zoom(int posx, int posy, int val_zoom, int type);

extern void accueil(int mode);

extern void pause();

extern void getPixelColor(SDL_Rect position, SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b);

extern void remplirFrance(Point **tab, SDL_Surface *sortie, SDL_Surface *blit_surface, int x, int y, int type);

extern void bouton();

extern void sdl_ini();

extern void * fichier_75(void *v);

extern void * fichier_5(void *v);

#endif // H_PARTIE2

