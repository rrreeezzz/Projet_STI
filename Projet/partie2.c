#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "partie2.h"
#include "module.h"

void pause() {
    int continuer = 1;
    SDL_Event event;
    while (continuer) { // TANT QUE la variable ne vaut pas 0
        SDL_WaitEvent(&event); // On attend un événement qu'on récupère dans event
        switch(event.type) { // On teste le type d'événement
            case SDL_QUIT: // Si c'est un événement QUITTER
                continuer = 0; // On met le booléen à 0, donc la boucle va s'arrêter
                break;
        }
    }
}

void remplirFrance(Point **tab, SDL_Surface *surface, SDL_Surface *screen, int li, int co) {
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    int i,j;
    for (i=0; i<li; i++) {
        for (j=0; j<co; j++) {
            position.x = j;
            if ((tab[i][j].metre) < 0) {
                SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
            }else if ((tab[i][j].metre) == 0) {
                SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 0, 0, 255));
            }else{
                SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 0, 255, 0));
            }
            SDL_BlitSurface(surface, NULL, screen, &position);
        }
        position.y = i;
    }
}
// SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 255, 255, 255)); // remplir la surface d'une couleur
// SDL_BlitSurface(surface, NULL, screen, &position); // mettre la surface sur l'écran, à une position précise
