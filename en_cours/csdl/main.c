#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "partie1.h"
#include "partie2.h"
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>


int main(int argc, char *argv[]) {
    FILE *fichier = NULL;
    Point **tabPt = NULL;

    SDL_Surface *pixel = NULL; // Le pointeur qui va remplir la France
    SDL_Surface *tempo = NULL; // Va accueillir la France temporairement
    SDL_Surface *boutton = NULL; //surface pour le boutton
    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran
    SDL_Surface *dezoom = NULL; // Va dezoomer la France avant de la mettre sur ecran
    SDL_Rect positionBoutton; //rectangle acceuillant le boutton
    TTF_Font *police = NULL; //acceuille la police pour le boutton


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

    if(TTF_Init() == -1){ //initialise SDL_ttf
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    //SDL_WM_SetIcon(SDL_LoadBMP("SUPER8ICONE.bmp"), NULL); // Pour changer l'icone du .exe

    ecran = SDL_SetVideoMode(1000, 540, 32, SDL_HWSURFACE); // On tente d'ouvrir une fenêtre
    if (ecran == NULL) { // Si l'ouverture a échoué, on le note et on arrête
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Mon super .exe", NULL); // changer nom de la fenêtre

    //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); // remplir l'écran d'une couleur


//REMPLISSAGE DE LA FRANCE
    pixel = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0); // creation d'une surface
    tempo = SDL_CreateRGBSurface(SDL_HWSURFACE, COLONNES, LIGNES, 32, 0, 0, 0, 0);
    remplirFrance(tabPt, pixel, tempo, LIGNES, COLONNES); // on obtient la France en 1161 par 1081

    dezoom = SDL_CreateRGBSurface(SDL_HWSURFACE, 580, 540, 32, 0, 0, 0, 0);
    dezoom = zoomSurface(tempo, 0.4995, 0.4995, 1); //On transforme la surface tempo. zoomX = nouvelleLargeurX / ancienneLargeurX   zoomY = nouvelleLargeurY / ancienneLargeurY
    SDL_BlitSurface(dezoom, NULL, ecran, NULL); // On met la nouvelle France sur ecran

    police = TTF_OpenFont("morningtype/Morningtype.ttf", 20);
    boutton = TTF_RenderText_Blended(police, "Ok !", (SDL_Color) {255, 255, 255});
    positionBoutton.x = 600;
    positionBoutton.y = 200;
    SDL_BlitSurface (boutton,NULL,ecran, &positionBoutton);

    SDL_Flip(ecran); // Mise à jour de l'écran
    pause(boutton,tempo, ecran, tabPt); // Mise en pause du programme


//LIBERATION
    SDL_FreeSurface(pixel);
    SDL_FreeSurface(tempo);
    SDL_FreeSurface(dezoom);
    TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
    TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL


    libere(tabPt, LIGNES);
    fclose(fichier);

    return EXIT_SUCCESS;
}
