#ifndef H_MODULE
#define H_MODULE

#define LIGNES 1081 // nb de lignes
#define COLONNES 1161 // nb de colonnes
#define LIGNES_75 1000 // nb de lignes
#define COLONNES_75 1000 // nb de colonnes

#define DEZOOM_X 859
#define DEZOOM_Y 800    // 859x800 environ
#define REP "/media/fabien/Data/75m/"
#define BUFSIZE 50

#include <SDL/SDL.h>

typedef struct {
        double metre;
        int estInonde;
} Point;

typedef struct { //structure qui contient les cartes
    Point ** pt_tab; //pour pointer sur le tableau de donnée, pas sur que ce soit super...
    SDL_Surface * pt_surface;
    SDL_Surface * pt_zoom;
    int done;
} data_map; //struct pour les map

data_map * data_75;
data_map * data_1000;

#endif // H_MODULE
