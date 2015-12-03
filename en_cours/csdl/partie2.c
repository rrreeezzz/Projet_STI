#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include "partie2.h"
#include "module.h"


void zoom(int posx, int posy, int val_zoom, SDL_Surface * tempo, SDL_Surface * ecran, Point ** tab){

    SDL_Surface *nouvelleImageTemp = NULL;
    SDL_Surface *degrade = SDL_LoadBMP("degrade.bmp");
    SDL_Rect positionzoom;
    SDL_Rect positionExtraction;
    SDL_Surface *pixel = NULL;
    int i, j;

    SDL_Rect position_sortie;
    position_sortie.x = 0;
    position_sortie.y = 0;
    SDL_Rect position_degrade;
    position_degrade.x = 1;
    position_degrade.y = 0;
    Uint8 r, g, b;

    positionzoom.x = 590;
    positionzoom.y = 300;


    if(val_zoom == 0){

        positionExtraction.x = (posx-100)/0.4995; //on divise par 0.4995 car c'est le facteur entre la carte dezoom et tempo
        positionExtraction.y = (posy-50)/0.4995;
        positionExtraction.w = 200/0.4995;
        positionExtraction.h = 100/0.4995;

        nouvelleImageTemp = SDL_CreateRGBSurface(SDL_HWSURFACE, 200/0.4995, 100/0.4995, 32, 0, 0, 0, 0);

        SDL_BlitSurface(tempo, &positionExtraction, nouvelleImageTemp, NULL); //on prend la surface a zoommé sur, qu'on met dans nouvelleImageTemp

    }else if(val_zoom > 0){

        positionExtraction.x = (posx-100/val_zoom)/0.4995; //on divise par 0.4995 ar c'est le facteur entre la carte dezoom et tempo
        positionExtraction.y = (posy-50/val_zoom)/0.4995;
        positionExtraction.w = 200/(val_zoom*0.4995); //a chaque fois la zone a zoomé sur se réduit en fct de val_zoom
        positionExtraction.h = 100/(val_zoom*0.4995);

        nouvelleImageTemp = SDL_CreateRGBSurface(SDL_HWSURFACE, positionExtraction.w, positionExtraction.h, 32, 0, 0, 0, 0); //la surface a les memes dim que le rect a prendre

        for (i=0; i<positionExtraction.w; i++) {
            for (j=0; j<positionExtraction.h; j++) {
                position_sortie.x = j;
                if ((tab[i + positionExtraction.x][j + positionExtraction.y].metre) < 0) {
                    SDL_FillRect(pixel, NULL, SDL_MapRGB(nouvelleImageTemp->format, 0, 0, 0)); // remplir la surface de noir
                }else if ((tab[i + positionExtraction.x][j + positionExtraction.y].metre) == 0) {
                    SDL_FillRect(pixel, NULL, SDL_MapRGB(nouvelleImageTemp->format, 0, 0, 255)); // remplir la surface de bleu
                }else if ((tab[i + positionExtraction.x][j + positionExtraction.y].metre) > 2500) {
                    position_degrade.y = 2500;
                    getPixelColor(position_degrade, degrade, &r, &g, &b);
                    SDL_FillRect(pixel, NULL, SDL_MapRGB(nouvelleImageTemp->format, r, g, b)); // remplir la surface de la couleur 2500m
                }else{
                    position_degrade.y = tab[i + positionExtraction.x][j + positionExtraction.y].metre;
                    getPixelColor(position_degrade, degrade, &r, &g, &b);
                    SDL_FillRect(pixel, NULL, SDL_MapRGB(nouvelleImageTemp->format, r, g, b)); // remplir la surface de la couleur de l'altitude
                }
                SDL_BlitSurface(pixel, NULL, nouvelleImageTemp, &position_sortie); // on met chaque pixel sur la surface de sortie

            }
            position_sortie.y = i;

        }
    }

    SDL_BlitSurface(nouvelleImageTemp, NULL, ecran, &positionzoom);
    SDL_Flip(ecran); // Mise à jour de l'écran

    SDL_FreeSurface(nouvelleImageTemp);
    SDL_FreeSurface(degrade);
    SDL_FreeSurface(pixel);
}


void pause(SDL_Surface * boutton, SDL_Surface * tempo, SDL_Surface * ecran, Point ** tab) {

    int continuer = 1;
    SDL_Event event;

    int val_zoom = 0;

    while (continuer) { // TANT QUE la variable ne vaut pas 0
        SDL_WaitEvent(&event); // On attend un événement qu'on récupère dans event
        switch(event.type) { // On teste le type d'événement
            case SDL_QUIT: // Si c'est un événement QUITTER
                continuer = 0; // On met le booléen à 0, donc la boucle va s'arrêter
                break;
            case SDL_MOUSEBUTTONDOWN:
                if ( event.button.button == SDL_BUTTON_LEFT
                    && event.button.y > 200
                    && event.button.y <= 200 +boutton->h  // si clic sur boutton
                    && event.button.x > 600
                    && event.button.x <= 600+boutton->w){
                    continuer = 0;
                }else if (event.button.button == SDL_BUTTON_WHEELDOWN){
                    val_zoom += 1;
                }else if (event.button.button == SDL_BUTTON_WHEELUP){
                    val_zoom = val_zoom == 0 ? 0 : val_zoom-1; //test ternaire
                }
                break;
            case SDL_MOUSEMOTION://permet de savoir si la sourie bouge
                zoom(event.motion.x, event.motion.y, val_zoom, tempo, ecran, tab);
                break;
            }
        }
}

void getPixelColor(SDL_Rect position, SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b) {

    if(position.x>0 && position.y>0 && position.x<surface->w && position.y<surface->h) {
        int bpp = surface->format->BytesPerPixel;
        Uint8 *p = (Uint8 *)surface->pixels + position.y * surface->pitch + position.x * bpp;
        SDL_GetRGB(*(Uint32 *)p,surface->format, r, g, b);
    }else{ // sinon on renvoie noir, pour éviter de planter dans certains cas
        r = 0;
        g = 0;
        b = 0;
    }
}

void remplirFrance(Point **tab, SDL_Surface *pixel, SDL_Surface *sortie, int li, int co) {

    SDL_Surface *degrade = SDL_LoadBMP("degrade.bmp");
    SDL_LockSurface(degrade);
    Uint8 r, g, b;
    SDL_Rect position_sortie;
    position_sortie.x = 0;
    position_sortie.y = 0;
    SDL_Rect position_degrade;
    position_degrade.x = 1;
    position_degrade.y = 0;

    int i,j;
    for (i=0; i<li; i++) {
        for (j=0; j<co; j++) {
            position_sortie.x = j;
            if ((tab[i][j].metre) < 0) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 0, 0, 0)); // remplir la surface de noir
            }else if ((tab[i][j].metre) == 0) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 0, 0, 255)); // remplir la surface de bleu
            }else if ((tab[i][j].metre) > 2500) {
                position_degrade.y = 2500;
                getPixelColor(position_degrade, degrade, &r, &g, &b);
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, r, g, b)); // remplir la surface de la couleur 2500m
            }else{
                position_degrade.y = tab[i][j].metre;
                getPixelColor(position_degrade, degrade, &r, &g, &b);
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, r, g, b)); // remplir la surface de la couleur de l'altitude
            }
            SDL_BlitSurface(pixel, NULL, sortie, &position_sortie); // on met chaque pixel sur la surface de sortie
        }
        position_sortie.y = i;
    }
    SDL_FreeSurface(degrade);
}
