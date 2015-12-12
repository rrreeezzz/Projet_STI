#include "partie2.h"
#include "propagation.h"

void zoom(int posx, int posy, int val_zoom, SDL_Surface * tempo, SDL_Surface * ecran){

    SDL_Surface *nouvelleImageTemp = NULL;
    SDL_Surface * zoom = NULL; //obligé de créer une nouvelle surface sinon nouvelleImageTemp = zoomSurface(nouvelleImageTemp, val_zoom, val_zoom, 1); sature la mémoire
    SDL_Rect positionzoom;
    SDL_Rect positionExtraction;

    positionzoom.x = 1000;
    positionzoom.y = 350;

    positionExtraction.x = (posx-150/val_zoom)/DEZOOM_X; //on divise par DEZOOM_X car c'est le facteur entre la carte dezoom et tempo
    positionExtraction.y = (posy-150/val_zoom)/DEZOOM_Y;
    positionExtraction.w = 300/(val_zoom*DEZOOM_X); // a chaque fois la zone à zoomer sur se réduit en fct de val_zoom
    positionExtraction.h = 300/(val_zoom*DEZOOM_Y);

    nouvelleImageTemp = SDL_CreateRGBSurface(SDL_HWSURFACE, positionExtraction.w, positionExtraction.h, 32, 0, 0, 0, 0); // la surface a les memes dim que le rect a prendre

    SDL_BlitSurface(tempo, &positionExtraction, nouvelleImageTemp, NULL);

    zoom = zoomSurface(nouvelleImageTemp, val_zoom, val_zoom, 1);

    SDL_BlitSurface(zoom, NULL, ecran, &positionzoom);

    SDL_FreeSurface(nouvelleImageTemp);
    SDL_FreeSurface(zoom);

    SDL_Flip(ecran); // Mise à jour de l'écran

}

void pause(Point **tab, SDL_Rect TBoutton, SDL_Surface *tempo, SDL_Surface *ecran) {

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
                if ( event.button.button == SDL_BUTTON_LEFT && event.button.y > 200 && event.button.y <= 200+TBoutton.h && event.button.x > 1000 && event.button.x <= 1000+TBoutton.w) {
                    init_propa(tab);
                    remplirFrance(tab, tempo, ecran);
                    SDL_Flip(ecran);
                }else if( event.button.button == SDL_BUTTON_LEFT && event.button.y > 200 && event.button.y <= 200+TBoutton.h && event.button.x > 1050 && event.button.x <= 1050+TBoutton.w) {
                    init_propa(tab);
                    super_propa(tab, 0, 0, LIGNES-1 , COLONNES-1, 10, 2);
                    remplirFrance(tab, tempo, ecran);
                    SDL_Flip(ecran);
                }else if( event.button.button == SDL_BUTTON_LEFT && event.button.y > 200 && event.button.y <= 200+TBoutton.h && event.button.x > 1100 && event.button.x <= 1100+TBoutton.w) {
                    init_propa(tab);
                    super_propa(tab, 0, 0, LIGNES-1 , COLONNES-1, 20, 2);
                    remplirFrance(tab, tempo, ecran);
                    SDL_Flip(ecran);
                }else if( event.button.button == SDL_BUTTON_LEFT && event.button.y > 200 && event.button.y <= 200+TBoutton.h && event.button.x > 1150 && event.button.x <= 1150+TBoutton.w) {
                    init_propa(tab);
                    super_propa(tab, 0, 0, LIGNES-1 , COLONNES-1, 30, 2);
                    remplirFrance(tab, tempo, ecran);
                    SDL_Flip(ecran);
                /*}else if( event.button.button == SDL_BUTTON_LEFT && event.button.y <= tempo->h && event.button.x <= tempo->w) { //peut-être moins energivore ?? A débattre
                    zoom(event.motion.x, event.motion.y, val_zoom, tempo, ecran);*/

                }else if (event.button.button == SDL_BUTTON_WHEELUP){
                    val_zoom = val_zoom == 3 ? 3 : val_zoom+1; //test ternaire
                    zoom(event.motion.x, event.motion.y, val_zoom, tempo, ecran);
                }else if (event.button.button == SDL_BUTTON_WHEELDOWN){
                    val_zoom = val_zoom == 1 ? 1 : val_zoom-1; //test ternaire
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

void remplirFrance(Point **tab, SDL_Surface *sortie, SDL_Surface *ecran) {

    SDL_Surface *pixel = NULL; // Le pointeur qui va remplir la France
    SDL_Surface *dezoom = NULL; // Va dezoomer la France avant de la mettre sur ecran
    SDL_Surface *degrade = SDL_LoadBMP("degrade.bmp");
    SDL_LockSurface(degrade);
    Uint8 r, g, b;

    SDL_Rect position_sortie;
    position_sortie.x = 0;
    position_sortie.y = 0;
    SDL_Rect position_degrade;
    position_degrade.x = 1;
    position_degrade.y = 0;

    pixel = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0); // creation d'une surface

    int i,j;
    for (i=0; i<LIGNES; i++) {
        for (j=0; j<COLONNES; j++) {
            position_sortie.x = j;
            if ((tab[i][j].metre) < 0) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 20, 20, 20)); // remplir la surface de noir
            }else if ((tab[i][j].estInonde) == 1) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 33, 150, 243)); // remplir la surface de bleu
            }else if ((tab[i][j].estInonde) == 2) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 250, 20, 15)); //rempli de rouge
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
    //on obtient la France en 1161 par 1081

    dezoom = zoomSurface(sortie, DEZOOM_X, DEZOOM_Y, 1); //On transforme la surface tempo. zoomX = nouvelleLargeurX / ancienneLargeurX   zoomY = nouvelleLargeurY / ancienneLargeurY
    SDL_BlitSurface(dezoom, NULL, ecran, NULL); // On met la nouvelle France sur ecran

    SDL_FreeSurface(degrade);
    SDL_FreeSurface(pixel);
    SDL_FreeSurface(dezoom);
}

SDL_Rect boutton(SDL_Surface *ecran, TTF_Font *police){

    int i = 0;
    char texte[10];
    SDL_Surface *Boutton; //pour les 3 boutons
    SDL_Rect positionBoutton; //rectangle acceuillant le boutton

    Boutton = NULL;
    police = TTF_OpenFont("morningtype/Morningtype.ttf", 20);

    for(i=0; i<4; i++){ //on initialise et affiche les 3 bouttons
        switch(i) {
            case 0 : strcpy(texte, "0m");
                break;
            case 1 : strcpy(texte, "10m");
                break;
            case 2 : strcpy(texte, "20m");
                break;
            case 3 : strcpy(texte, "30m");
                break;
        }
        Boutton = TTF_RenderText_Blended(police, texte, (SDL_Color) {255, 255, 255});
        positionBoutton.x = 1000 + i*50;
        positionBoutton.y = 200;
        SDL_BlitSurface (Boutton, NULL, ecran, &positionBoutton);
    }

    positionBoutton.h = Boutton->h;
    positionBoutton.w = Boutton->w;

    SDL_FreeSurface(Boutton);
    TTF_CloseFont(police);

    return positionBoutton;
}


void sdl_ini(Point ** tab){

    SDL_Surface *tempo = NULL; // Va accueillir la France temporairement
    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran
    TTF_Font *police = NULL; //acceuille la police pour les bouttons
    SDL_Rect TBoutton; //on stock la taille des boutons

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

    if ((ecran = SDL_SetVideoMode(1600, 800, 32, SDL_HWSURFACE)) == NULL) { // Si l'ouverture de la fenêtre a échoué, on le note et on arrête
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Mon super .exe", NULL); // changer nom de la fenêtre

//REMPLISSAGE DE LA FRANCE
    super_propa(tab, 0, 0, LIGNES-1 , COLONNES-1, 0, 1); // On initialise tab pour que estInonde = 1 pour la vraie mer

    tempo = SDL_CreateRGBSurface(SDL_HWSURFACE, COLONNES, LIGNES, 32, 0, 0, 0, 0);
    remplirFrance(tab, tempo, ecran);
    TBoutton = boutton(ecran, police);

    SDL_Flip(ecran); // Mise à jour de l'écran
    pause(tab, TBoutton, tempo, ecran); // Mise en pause du programme

//LIBERATION
    SDL_FreeSurface(tempo);
    TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL
}
