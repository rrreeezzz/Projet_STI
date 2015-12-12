#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "partie1.h"
#include "partie2.h"
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>


int main(int argc, char *argv[]) {

    Point **tabPt = NULL;
<<<<<<< HEAD

//ALLOCATION MEMOIRE & OUVERTURE DU FICHIER

    tabPt = chargement(); // allocation mémoire de tab[x][y]
=======
    tabPt = chargement();
>>>>>>> efc96029c20b9bd39c71691afe16a487432ea941

    sdl_ini(tabPt);

    libere(tabPt, LIGNES);
<<<<<<< HEAD

=======
>>>>>>> efc96029c20b9bd39c71691afe16a487432ea941
    return EXIT_SUCCESS;
}
