#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "partie1.h"
#include "partie2.h"
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>


int main(int argc, char *argv[]) {

    Point **tabPt = NULL;

//ALLOCATION MEMOIRE & OUVERTURE DU FICHIER

    tabPt = chargement(); // allocation mémoire de tab[x][y]

    sdl_ini(tabPt);

    libere(tabPt, LIGNES);

    return EXIT_SUCCESS;
}
