#include "partie2.h"

void zoom(int posx, int posy, int val_zoom, SDL_Surface * tempo, SDL_Surface * ecran){

    SDL_Surface *nouvelleImageTemp = NULL;
    SDL_Rect positionzoom;
    SDL_Rect positionExtraction;

    positionzoom.x = 590;
    positionzoom.y = 300;

    positionExtraction.x = (posx-100/val_zoom)/0.4995; //on divise par 0.4995 car c'est le facteur entre la carte dezoom et tempo
    positionExtraction.y = (posy-50/val_zoom)/0.4995;
    positionExtraction.w = 200/(val_zoom*0.4995); // a chaque fois la zone a zoomer sur se réduit en fct de val_zoom
    positionExtraction.h = 100/(val_zoom*0.4995);

    nouvelleImageTemp = SDL_CreateRGBSurface(SDL_HWSURFACE, positionExtraction.w, positionExtraction.h, 32, 0, 0, 0, 0); // la surface a les memes dim que le rect a prendre

    SDL_BlitSurface(tempo, &positionExtraction, nouvelleImageTemp, NULL);

    nouvelleImageTemp = zoomSurface(nouvelleImageTemp, val_zoom, val_zoom, 1);


    SDL_BlitSurface(nouvelleImageTemp, NULL, ecran, &positionzoom);
    SDL_Flip(ecran); // Mise à jour de l'écran

    SDL_FreeSurface(nouvelleImageTemp);


}

void pause(SDL_Surface * boutton, SDL_Surface * tempo, SDL_Surface * ecran) {

    int continuer = 1;
    SDL_Event event;
    int val_zoom = 1;

    while (continuer) { // TANT QUE la variable ne vaut pas 0

        SDL_WaitEvent(&event); // On attend un événement qu'on récupère dans event

        switch(event.type) { // On teste le type d'événement

            case SDL_QUIT: // Si c'est un événement QUITTER
                continuer = 0; // On met le booléen à 0, donc la boucle va s'arrêter
                break;

            case SDL_MOUSEBUTTONDOWN: //si on appui sur un bouton de la sourie
                if ( event.button.button == SDL_BUTTON_LEFT && event.button.y > 200 && event.button.y <= 200 +boutton->h && event.button.x > 600 && event.button.x <= 600+boutton->w){
                    continuer = 0;
                }else if (event.button.button == SDL_BUTTON_WHEELUP){
                    val_zoom = val_zoom == 3 ? 3 : val_zoom+1; //test ternaire
                    zoom(event.motion.x, event.motion.y, val_zoom, tempo, ecran);
                }else if (event.button.button == SDL_BUTTON_WHEELDOWN){
                    val_zoom = val_zoom == 1 ? 1 : val_zoom-1; //test ternaire*
                    zoom(event.motion.x, event.motion.y, val_zoom, tempo, ecran);
                }
                break;

            case SDL_MOUSEMOTION://permet de savoir si la sourie bouge
                zoom(event.motion.x, event.motion.y, val_zoom, tempo, ecran);
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
            }else if ((tab[i][j].estInonde) == 1) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 0, 0, 255)); // remplir la surface de bleu
            }else if ((tab[i][j].estInonde) == 2) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 255, 0, 0));
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


void sdl_ini(Point ** tabPt){

    SDL_Surface *pixel = NULL; // Le pointeur qui va remplir la France
    SDL_Surface *tempo = NULL; // Va accueillir la France temporairement
    SDL_Surface *boutton = NULL; //surface pour le boutton
    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran
    SDL_Surface *dezoom = NULL; // Va dezoomer la France avant de la mettre sur ecran
    SDL_Rect positionBoutton; //rectangle acceuillant le boutton
    TTF_Font *police = NULL; //acceuille la police pour le boutton

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
    pause(boutton,tempo, ecran); // Mise en pause du programme


//LIBERATION
    SDL_FreeSurface(pixel);
    SDL_FreeSurface(tempo);
    SDL_FreeSurface(dezoom);
    TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
    TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL

}
