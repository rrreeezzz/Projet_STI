#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "partie2.h"
#include "module.h"

/*void scrolling(ecran* m,SDL_Surface* screen)
{
    int i,j;
    SDL_Rect Rect_dest;
    int numero_tile;
    for(i=0;i< fenetre->largeur;i++){
        for(j=0;j< fenetre->hauteur;j++){
            SDL_BlitSurface()
        }
    }
}
void mousemov(void){ //va permettre "d'ecouter" la sourie
    int posx, posy;
    int stop = 1;
    SDL_Event event;
    while(stop){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_MOUSEBUTTONUP:
                stop=0;
                break;
            default:
                posx=event.button.x;
                posy=event.button.y;
                scrolling(posx, posy);
            }
    }
}*/


void pause(SDL_Surface *boutton /*,int * pzoom*/) {
    int continuer = 1;
    SDL_Event event;
    while (continuer) { // TANT QUE la variable ne vaut pas 0
        SDL_WaitEvent(&event); // On attend un événement qu'on récupère dans event
        switch(event.type) { // On teste le type d'événement
            case SDL_QUIT: // Si c'est un événement QUITTER
                continuer = 0; // On met le booléen à 0, donc la boucle va s'arrêter
                break;
            case SDL_MOUSEBUTTONUP:
              if (   event.button.y > 200
                  && event.button.y <= 200 +boutton->h  // si clic sur boutton
                  && event.button.x > 600
                  && event.button.x <= 600+boutton->w){
                    continuer = 0;
              }/*else if(*pzoom =! 0){
                    mousemov();
                }
              break;
            case  SDL_BUTTON_WHEELDOWN:
                */
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
