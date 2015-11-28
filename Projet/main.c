#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "partie1.h"
#include "partie2.h"

int main(int argc, char *argv[]) {
    FILE *fichier = NULL;
    Point **tabPt = NULL;
    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran
    SDL_Surface *pixel = NULL; // Le pointeur qui va remplir la France


//ALLOCATION MEMOIRE & OUVERTURE DU FICHIER
    if ((tabPt = (Point**) malloc(LIGNES * sizeof(Point*))) == NULL) { // allocation mémoire de tab[x]: tableau de x pointeurs sur Point
        printf("\aErreur d'allocation mémoire\n");  // si il y a eu une erreur on est rentré dans le if
        exit(EXIT_FAILURE);
    }
    alloue(tabPt, LIGNES, COLONNES); // allocation mémoire de tab[x][y]

    if ((fichier = fopen("1000m.ASC", "r")) == NULL) { // ouverture du fichier en mode lecture seule
        printf("\aErreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if(ajout_tab(tabPt, fichier, LIGNES, COLONNES) == 0) {
        printf("\aErreur dans l'ajout des donnees du fichier a tab\n");
        exit(EXIT_FAILURE);
    }

//CREATION ECRAN
    if (SDL_Init(SDL_INIT_VIDEO) == -1) { // Démarrage de la SDL. Si erreur :
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    ecran = SDL_SetVideoMode(COLONNES, LIGNES, 16, SDL_HWSURFACE); // On tente d'ouvrir une fenêtre
    if (ecran == NULL) { // Si l'ouverture a échoué, on le note et on arrête
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Mon super .exe", NULL); // changer nom de la fenêtre

    //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); // remplir l'écran d'une couleur

//REMPLISSAGE DE LA FRANCE
    pixel = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 16, 0, 0, 0, 0); // creation d'une surface
    remplirFrance(tabPt, pixel, ecran, LIGNES, COLONNES);

    SDL_Flip(ecran); // Mise à jour de l'écran
    pause(); // Mise en pause du programme


//LIBERATION
    SDL_FreeSurface(pixel);
    SDL_Quit(); // Arrêt de la SDL


    libere(tabPt, LIGNES);
    fclose(fichier);

    return EXIT_SUCCESS;
}
