#ifndef H_MODULE
#define H_MODULE

#define LIGNES 1081 // nb de lignes
#define COLONNES 1161 // nb de colonnes
#define LIGNES_75 1000 // nb de lignes
#define COLONNES_75 1000 // nb de colonnes
#define LIGNES_5 1000 // nb de lignes
#define COLONNES_5 1000 // nb de colonnes

#define DEZOOM_X_1000 0.740055504 //800/1081
#define DEZOOM_Y_1000 0.740750741   // 860/1161

#define DEZOOM_X_75 0.715384615 //800/1081
#define DEZOOM_Y_75 0.661538462  // 860/1161

#define DEZOOM_X_5 0.614285714
#define DEZOOM_Y_5 0.614285714 //860/1400

#define REP_75 "/media/fabien/Data/75m/"
#define REP_5 "/media/fabien/Data/5m/"
#define BUFSIZE 50

#include <SDL/SDL.h>

SDL_Surface * ecran;

SDL_Surface * img_accueil; //reçoit l'accueil

SDL_Surface * prog;

typedef struct {
        double metre;
        int estInonde;
	int cadre;
} Point;

typedef struct { //structure qui contient les cartes
    Point ** pt_tab; //pour pointer sur le tableau de donnée, pas sur que ce soit super...
    SDL_Surface * pt_surface;
    SDL_Surface * pt_zoom;
    int done;
} data_map; //struct pour les map

data_map * data_75;
data_map * data_1000;
data_map * data_5;

typedef struct {
  SDL_Rect position;
  SDL_Surface *image;
} Bouton;

Bouton *btn[34];

int chx[15];

#endif // H_MODULE

