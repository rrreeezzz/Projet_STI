#include "partie2.h"
#include "partie1.h"
#include "propagation.h"
#include "bouton.h"



void zoom(int posx, int posy, int val_zoom, int type){

    SDL_Surface *nouvelleImageTemp = NULL;
    SDL_Surface * zoom = NULL; //obligé de créer une nouvelle surface sinon nouvelleImageTemp = zoomSurface(nouvelleImageTemp, val_zoom, val_zoom, 1); sature la mémoire
    SDL_Rect positionzoom;
    SDL_Rect positionExtraction;

    positionzoom.x = 1000; //position du carré zoom
    positionzoom.y = 350;

    if(type == 1000){

        positionExtraction.x = (posx-150/val_zoom)/DEZOOM_X_1000; //on divise par DEZOOM_X car c'est le facteur entre la surface  zoomé de data_1000 et la surface de data_1000
        positionExtraction.y = (posy-150/val_zoom)/DEZOOM_Y_1000;
        positionExtraction.w = 300/(val_zoom*DEZOOM_X_1000); // a chaque fois la zone à zoomer sur se réduit en fct de val_zoom
        positionExtraction.h = 300/(val_zoom*DEZOOM_Y_1000);

    }else if(type == 75){

        positionExtraction.x = (posx-150/val_zoom)/DEZOOM_X_75; //on divise par DEZOOM_X car c'est le facteur entre la surface  zoomé de data_1000 et la surface de data_1000
        positionExtraction.y = (posy-150/val_zoom)/DEZOOM_Y_75;
        positionExtraction.w = 300/(val_zoom*DEZOOM_X_1000); // a chaque fois la zone à zoomer sur se réduit en fct de val_zoom
        positionExtraction.h = 300/(val_zoom*DEZOOM_Y_1000);

    }else if(type == 5){

        positionExtraction.x = (posx-150/val_zoom)/DEZOOM_X_5; //on divise par DEZOOM_X car c'est le facteur entre la surface  zoomé de data_1000 et la surface de data_1000
        positionExtraction.y = (posy-150/val_zoom)/DEZOOM_Y_5;
        positionExtraction.w = 300/(val_zoom*DEZOOM_X_1000); // a chaque fois la zone à zoomer sur se réduit en fct de val_zoom
        positionExtraction.h = 300/(val_zoom*DEZOOM_Y_1000);

    }

    nouvelleImageTemp = SDL_CreateRGBSurface(SDL_HWSURFACE, positionExtraction.w, positionExtraction.h, 32, 0, 0, 0, 0); // la surface a les memes dim que le rect a prendre

    switch(type){
        case 1000:
            SDL_BlitSurface(data_1000->pt_surface, &positionExtraction, nouvelleImageTemp, NULL);
            break;
        case 75:
            SDL_BlitSurface(data_75->pt_surface, &positionExtraction, nouvelleImageTemp, NULL);
            break;
        case 5:
            SDL_BlitSurface(data_5->pt_surface, &positionExtraction, nouvelleImageTemp, NULL);
            break;

    }

    zoom = zoomSurface(nouvelleImageTemp, val_zoom, val_zoom, 1);

    SDL_BlitSurface(zoom, NULL, prog, &positionzoom);

    SDL_Surface *Noir  = SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 3, 32, 0, 0, 0, 0); // pour enlever les petits bug du zoom
    SDL_Rect pos;
    pos.x = 1000;
    pos.y = 751;
    SDL_FillRect(Noir, NULL, SDL_MapRGB(Noir->format, 0, 0, 0));
    SDL_BlitSurface(Noir, NULL, prog, &pos);
    SDL_Surface *Noir2  = SDL_CreateRGBSurface(SDL_HWSURFACE, 2, 405, 32, 0, 0, 0, 0);
    pos.x = 1404;
    pos.y = 350;
    SDL_BlitSurface(Noir2, NULL, prog, &pos);
    SDL_FreeSurface(Noir);
    SDL_FreeSurface(Noir2);



    SDL_FreeSurface(nouvelleImageTemp);
    SDL_FreeSurface(zoom);

    SDL_BlitSurface(prog, NULL, ecran, NULL);
    SDL_Flip(ecran); // Mise à jour de l'écran

}


void pause() {

    int continuer = 1;
    SDL_Event event;
    int val_zoom = 1;
    int type = 0; //1000=data_1000, 75=data_75, 5=data_5
//    choice(10);
    int h = 0;
    int affichage = 1; //1 img_accueil, 2 prog

    while (continuer) { // TANT QUE la variable ne vaut pas 0
        SDL_WaitEvent(&event); // On attend un événement qu'on récupère dans event
        switch(event.type) { // On teste le type d'événement

            case SDL_QUIT: // Si c'est un événement QUITTER
                continuer = 0; // On met le booléen à 0, donc la boucle va s'arrêter
                break;

            case SDL_MOUSEBUTTONDOWN: //si on appui sur un bouton de la souri
                if (event.button.button == SDL_BUTTON_LEFT && Check(btn[0], event.button.x, event.button.y)==1) {
                    h = 0;
                    type = 1000;
                    choice(0);
                    super_propa(0, 0, LIGNES-1 , COLONNES-1, 0, 1); // On initialise tab pour que estInonde = 1 pour la vraie mer
                        init_propa();
                    remplirFrance(data_1000->pt_tab, data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[2], event.button.x, event.button.y)==1 && data_75->done == 1) {
                    type = 75;
                    choice(1);
                    SDL_BlitSurface(data_75->pt_zoom, NULL, prog, NULL);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[4], event.button.x, event.button.y)==1 && data_5->done == 1) {
                    type = 5;
                    choice(2);
                    SDL_Surface *Noir  = SDL_CreateRGBSurface(SDL_HWSURFACE, 800, 860, 32, 0, 0, 0, 0); // pour bien mettre le fond noir
                    SDL_Rect pos;
                    pos.x = 100;
                    pos.y = 0;
                    SDL_FillRect(Noir, NULL, SDL_MapRGB(Noir->format, 0, 0, 0));
                    SDL_BlitSurface(Noir, NULL, prog, &pos);
                    SDL_FreeSurface(Noir);
                    SDL_BlitSurface(data_5->pt_zoom, NULL, prog, NULL);
                    bouton();
                }else if(event.button.button == SDL_BUTTON_LEFT && Check(btn[6], event.button.x, event.button.y)==1 && type == 1000 && chx[14] == 1) {
                    h=17;
                    choice(3);
                    init_propa();
                    super_propa(0, 0, LIGNES-1 , COLONNES-1, h, 2);
                    remplirFrance(data_1000->pt_tab, data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[8], event.button.x, event.button.y)==1 && type == 1000 && chx[14] == 1) {
                    h=19;
                    choice(4);
                    init_propa();
                    super_propa(0, 0, LIGNES-1 , COLONNES-1, h, 2);
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[10], event.button.x, event.button.y)==1 && type == 1000 && chx[14] == 1) {
                    h=18;
                    choice(5);
                    init_propa();
                    super_propa(0, 0, LIGNES-1 , COLONNES-1, h, 2);
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[12], event.button.x, event.button.y)==1 && type == 1000 && chx[14] == 1) {
                    h=22;
                    choice(6);
                    init_propa();
                    super_propa(0, 0, LIGNES-1 , COLONNES-1, h, 2);
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[14], event.button.x, event.button.y)==1 && type == 1000 && h != 0) {
                    choice(7);
                    init_propa();
                    super_propa(0, 0, LIGNES-1, COLONNES-1, h, 2);
                    scoring();
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[16], event.button.x, event.button.y)==1 && type == 1000 && h != 0) {
                    choice(8);
                    init_propa();
                    super_propa(0, 0, LIGNES-1, COLONNES-1, h, 2);
                    mega_propa_submer(1, 1, LIGNES-2, COLONNES-2, h+3, 3);
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[18], event.button.x, event.button.y)==1 && type == 1000 && h != 0) {
                    choice(9);
                    init_propa();
                    super_propa(0, 0, LIGNES-1, COLONNES-1, h, 2);
                    mega_propa_submer(1, 1, LIGNES-2, COLONNES-2, h+6, 3);
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if(event.button.button == SDL_BUTTON_LEFT && Check(btn[26], event.button.x, event.button.y)==1 && type == 1000 && chx[15] == 1) {
                    h=31;
                    choice(10);
                    init_propa();
                    super_propa(0, 0, LIGNES-1 , COLONNES-1, h, 2);
                    remplirFrance(data_1000->pt_tab, data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[28], event.button.x, event.button.y)==1 && type == 1000 && chx[15] == 1) {
                    h=33;
                    choice(11);
                    init_propa();
                    super_propa(0, 0, LIGNES-1 , COLONNES-1, h, 2);
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[30], event.button.x, event.button.y)==1 && type == 1000 && chx[15] == 1) {
                    h=32;
                    choice(12);
                    init_propa();
                    super_propa(0, 0, LIGNES-1 , COLONNES-1, h, 2);
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[32], event.button.x, event.button.y)==1 && type == 1000 && chx[15] == 1) {
                    h=37;
                    choice(13);
                    init_propa();
                    super_propa(0, 0, LIGNES-1 , COLONNES-1, h, 2);
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[22], event.button.x, event.button.y)==1 && type == 1000) {
                    h=0;
                    choice(14);
                    init_propa();
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && Check(btn[24], event.button.x, event.button.y)==1 && type == 1000) {
                    h=0;
                    choice(15);
                    init_propa();
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, type);
                    bouton();
                }else if (event.button.button == SDL_BUTTON_LEFT && event.button.y > 750 && event.button.x > 1450 && affichage == 1) {
                    accueil(1);
                }else if (event.button.button == SDL_BUTTON_LEFT && event.button.y > 630 && event.button.x > 750 && event.button.y < 758 && event.button.x < 878  && affichage == 1){
                    printf("ok\n");
                    affichage = 2;
                    SDL_BlitSurface(prog, NULL, ecran, NULL);
                    SDL_Flip(ecran);
                }else if (event.button.button == SDL_BUTTON_LEFT && event.button.y <= 800 && event.button.x <= 860 && affichage == 2) { //peut-être moins energivore ?? A débattre
                    zoom(event.motion.x, event.motion.y, val_zoom, type);
                }else if (event.button.button == SDL_BUTTON_WHEELUP && event.button.y <= 800 && event.button.x <= 860 && affichage == 2){
                    val_zoom = val_zoom == 3 ? 3 : val_zoom+1; //test ternaire
                    zoom(event.motion.x, event.motion.y, val_zoom, type);
                }else if (event.button.button == SDL_BUTTON_WHEELDOWN && event.button.y <= 800 && event.button.x <= 860 && affichage == 2){
                    val_zoom = val_zoom == 1 ? 1 : val_zoom-1; //test ternaire
                    zoom(event.motion.x, event.motion.y, val_zoom, type);
                }
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

void remplirFrance(Point **tab, SDL_Surface *sortie, SDL_Surface *blit_surface, int x, int y, int type) {

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

    SDL_Rect position_ecran;

    int max_lignes, max_colonnes;

    pixel = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0); // creation d'une surface pour un pixel

    switch(type){
        case 1000:
            max_lignes = LIGNES;
            max_colonnes = COLONNES;
            break;

        case 75:
            max_lignes = LIGNES_75;
            max_colonnes = COLONNES_75;
            position_ecran.x = x;
            position_ecran.y = 1000-y;
            break;

        case 5:
            max_lignes = LIGNES_5;
            max_colonnes = COLONNES_5;
            position_ecran.x = x*10;
            position_ecran.y = 1000-10*y;
            break;
    }

    int i,j;
    for (i=0; i<max_lignes; i++) {
        for (j=0; j<max_colonnes; j++) {
            position_sortie.x = j;
            if ((tab[i][j].cadre) == 1) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 255, 255, 255)); // créé un cadre blanc pour scoring
            }else if ((tab[i][j].estInonde) == 1) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 33, 150, 243)); // remplir la surface de bleu
            }else if ((tab[i][j].estInonde) == 2) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 250, 20, 15)); //rempli de rouge
            }else if ((tab[i][j].estInonde) == 3) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 250, 250, 15)); // remplir la surface de jaune
            }else if ((tab[i][j].metre) > 2500.00) {
                position_degrade.y = 2500;
                getPixelColor(position_degrade, degrade, &r, &g, &b);
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, r, g, b)); // remplir la surface de la couleur 2500m
            }else if ((tab[i][j].metre) < 0) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 20, 20, 20)); // remplir la surface de noir
            }else{
                position_degrade.y = (int) tab[i][j].metre;
                getPixelColor(position_degrade, degrade, &r, &g, &b);
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, r, g, b)); // remplir la surface de la couleur de l'altitude
            }
            SDL_BlitSurface(pixel, NULL, sortie, &position_sortie); // on met chaque pixel sur la surface de sortie
        }
        position_sortie.y = i;
    }

    //on obtient la France en 1161 par 1081 pour le 1000m, sinon une partie de France en 1000x1000

    if(type == 1000){
        dezoom = zoomSurface(sortie, DEZOOM_X_1000, DEZOOM_Y_1000, 1); //On transforme la surface tempo. zoomX = nouvelleLargeurX / ancienneLargeurX   zoomY = nouvelleLargeurY / ancienneLargeurY
        SDL_BlitSurface(dezoom, NULL, blit_surface, NULL); // On met la nouvelle France sur ecran
        data_1000->pt_zoom = dezoom; //on stock le zoom
    }
    else if(type == 75){
        dezoom = zoomSurface(sortie, (float) 0.075, (float) 0.075, 0); //On dezoom chaque tabeleau de 1000*1000 qu'on a placé sur une surface de 1000*1000
        SDL_BlitSurface(dezoom, NULL, blit_surface, &position_ecran); // On met les tableaux dezoomé sur une surface qui peut contenir la france en 75m, ici blit_surface c'est data_75->pt_surface
    }else if(type == 5){
        dezoom = zoomSurface(sortie, (float) 0.05, (float) 0.05, 0); //On dezoom chaque tabeleau de 1000*1000 qu'on a placé sur une surface de 1000*1000
        SDL_BlitSurface(dezoom, NULL, blit_surface, &position_ecran); // On met les tableaux dezoomé sur une surface qui peut contenir la france en 5m, ici blit_surface c'est data_5->pt_surface
    }

    SDL_FreeSurface(degrade);
    SDL_FreeSurface(pixel);
    SDL_FreeSurface(dezoom);
}


void bouton(){

  if (chx[0] == 1)
    SDL_BlitSurface(btn[1]->image, NULL, prog, &(btn[1]->position));
  else
    SDL_BlitSurface(btn[0]->image, NULL, prog, &(btn[0]->position));
  if (data_75->done == 0)
    SDL_BlitSurface(btn[20]->image, NULL, prog, &(btn[20]->position));
  else if (chx[1] == 1)
    SDL_BlitSurface(btn[3]->image, NULL, prog, &(btn[3]->position));
  else {
    SDL_Surface *Noir  = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 50, 32, 0, 0, 0, 0);
    SDL_FillRect(Noir, NULL, SDL_MapRGB(Noir->format, 0, 0, 0));
    SDL_BlitSurface(Noir, NULL, prog, &(btn[20]->position));
    SDL_FreeSurface(Noir);
    SDL_BlitSurface(btn[2]->image, NULL, prog, &(btn[2]->position));
}
  if (data_5->done == 0)
    SDL_BlitSurface(btn[21]->image, NULL, prog, &(btn[21]->position));
  else if (chx[2] == 1)
    SDL_BlitSurface(btn[5]->image, NULL, prog, &(btn[5]->position));
  else {
    SDL_Surface *Noir  = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 50, 32, 0, 0, 0, 0);
    SDL_FillRect(Noir, NULL, SDL_MapRGB(Noir->format, 0, 0, 0));
    SDL_BlitSurface(Noir, NULL, prog, &(btn[21]->position));
    SDL_FreeSurface(Noir);
    SDL_BlitSurface(btn[4]->image, NULL, prog, &(btn[4]->position));
 }
  if (chx[3] == 1)
    SDL_BlitSurface(btn[7]->image, NULL, prog, &(btn[7]->position));
  else
    SDL_BlitSurface(btn[6]->image, NULL, prog, &(btn[6]->position));
  if (chx[4] == 1)
    SDL_BlitSurface(btn[9]->image, NULL, prog, &(btn[9]->position));
  else
    SDL_BlitSurface(btn[8]->image, NULL, prog, &(btn[8]->position));
  if (chx[5] == 1)
    SDL_BlitSurface(btn[11]->image, NULL, prog, &(btn[11]->position));
  else
    SDL_BlitSurface(btn[10]->image, NULL, prog, &(btn[10]->position));
  if (chx[6] == 1)
    SDL_BlitSurface(btn[13]->image, NULL, prog, &(btn[13]->position));
  else
    SDL_BlitSurface(btn[12]->image, NULL, prog, &(btn[12]->position));
  if (chx[7] == 1)
    SDL_BlitSurface(btn[15]->image, NULL, prog, &(btn[15]->position));
  else
    SDL_BlitSurface(btn[14]->image, NULL, prog, &(btn[14]->position));
  if (chx[8] == 1)
    SDL_BlitSurface(btn[17]->image, NULL, prog, &(btn[17]->position));
  else
    SDL_BlitSurface(btn[16]->image, NULL, prog, &(btn[16]->position));
  if (chx[9] == 1)
    SDL_BlitSurface(btn[19]->image, NULL, prog, &(btn[19]->position));
  else
    SDL_BlitSurface(btn[18]->image, NULL, prog, &(btn[18]->position));
  if (chx[10] == 1)
    SDL_BlitSurface(btn[27]->image, NULL, prog, &(btn[27]->position));
  else
    SDL_BlitSurface(btn[26]->image, NULL, prog, &(btn[26]->position));
  if (chx[11] == 1)
    SDL_BlitSurface(btn[29]->image, NULL, prog, &(btn[29]->position));
  else
    SDL_BlitSurface(btn[28]->image, NULL, prog, &(btn[28]->position));
  if (chx[12] == 1)
    SDL_BlitSurface(btn[31]->image, NULL, prog, &(btn[31]->position));
  else
    SDL_BlitSurface(btn[30]->image, NULL, prog, &(btn[30]->position));
  if (chx[13] == 1)
    SDL_BlitSurface(btn[33]->image, NULL, prog, &(btn[33]->position));
  else
    SDL_BlitSurface(btn[32]->image, NULL, prog, &(btn[32]->position));
  if (chx[14] == 1)
    SDL_BlitSurface(btn[23]->image, NULL, prog, &(btn[23]->position));
  else
    SDL_BlitSurface(btn[22]->image, NULL, prog, &(btn[22]->position));
  if (chx[15] == 1)
    SDL_BlitSurface(btn[25]->image, NULL, prog, &(btn[25]->position));
  else
    SDL_BlitSurface(btn[24]->image, NULL, prog, &(btn[24]->position));


SDL_BlitSurface(prog, NULL, ecran, NULL);
    SDL_Flip(prog);
    SDL_Flip(ecran);
}

void * fichier_75(void *v){

    data_75->done = 0;

    FILE * fichier = NULL;
    DIR * rep = NULL;

    SDL_Surface *tempo_75 = NULL; //va stocker les carré de 1000*1000
    tempo_75 = SDL_CreateRGBSurface(SDL_HWSURFACE, COLONNES_75, LIGNES_75, 32, 0, 0, 0, 0); // pour les carrés de 1000*1000 en 75m

    struct dirent * info_rep = NULL;

    int x, y, i;

    char mot[9]; //impossible de supprimer mot ??
    char *coord1, *coord2;
    char repertoire[BUFSIZE];

    coord1 = (char *) malloc(4*sizeof(char));
    coord2 = (char *) malloc(4*sizeof(char));

    if((rep = opendir(REP_75)) == NULL){
        perror("Problème avec le répertoire\n");
    }


    while((info_rep = readdir(rep)) != NULL){

        strcpy(repertoire, REP_75); //on remet repertoire a 75m/

        if(info_rep->d_type & DT_REG){

            printf("%s\n", info_rep->d_name);

            if ((fichier = fopen(strcat(repertoire, info_rep->d_name), "r")) == NULL) { // ouverture du fichier en mode lecture seule
                perror("Erreur a l'ouverture du fichier");
                exit(EXIT_FAILURE);
            }

            i = 6;
            while (i--)
                fgets(repertoire, BUFSIZE, fichier); //nous place a la ligne des données

            for(i=0; i<4; i++)
                coord1[i] = info_rep->d_name[20+i];

            for(i=0; i<4; i++)
                coord2[i] = info_rep->d_name[25+i];

            x = atoi(coord1) - 75;
            y = atoi(coord2) - 6150;

            ajout_tab(fichier, 75);

            remplirFrance(data_75->pt_tab, tempo_75, data_75->pt_surface, x, y, 75); //rajouter a remplir france le fait que l'on change de fichier, et donc qu'il faut blitter les pixels en fct
            //140 000 000 points a blitter

            fclose(fichier); //on ferme le fichier ouvert
        }
    }

    printf("75m pret !\n");
    data_75->pt_zoom = zoomSurface(data_75->pt_surface, DEZOOM_X_75, DEZOOM_Y_75, 1); //on dezoom pour l'afficher en 859*800

    free(coord1);
    free(coord2);
    SDL_FreeSurface(tempo_75);
    closedir(rep);

    data_75->done = 1;

    bouton(); //fin de l'animation

    pthread_exit(NULL);
}


void * fichier_5(void *v){

    data_5->done = 0;

    FILE * fichier = NULL;
    DIR * rep = NULL;

    SDL_Surface *tempo_5 = NULL; //va stocker les carré de 1000*1000
    tempo_5 = SDL_CreateRGBSurface(SDL_HWSURFACE, COLONNES_5, LIGNES_5, 32, 0, 0, 0, 0); // pour les carrés de 1000*1000 en 75m

    struct dirent * info_rep = NULL;

    int x, y, i;

    char *coord1, *coord2;
    char repertoire[BUFSIZE];

    coord1 = (char *) malloc(4*sizeof(char));
    coord2 = (char *) malloc(4*sizeof(char));

    if((rep = opendir(REP_5)) == NULL){
        perror("Problème avec le répertoire\n");
    }

    while((info_rep = readdir(rep)) != NULL){

        strcpy(repertoire, REP_5); //on remet repertoire a 5m/

        if(info_rep->d_type & DT_REG){

            printf("%s\n", info_rep->d_name);

            if ((fichier = fopen(strcat(repertoire, info_rep->d_name), "r")) == NULL) { // ouverture du fichier en mode lecture seule
                perror("Erreur a l'ouverture du fichier");
                exit(EXIT_FAILURE);
            }

            i = 6;
            while (i--)
                fgets(repertoire, BUFSIZE, fichier); //nous place a la ligne des données

            for(i=0; i<4; i++)
                coord1[i] = info_rep->d_name[15+i];

            for(i=0; i<4; i++)
                coord2[i] = info_rep->d_name[20+i];

            x = atoi(coord1) - 203;
            y = atoi(coord2) - 6790;

            ajout_tab(fichier, 5);

            remplirFrance(data_5->pt_tab, tempo_5, data_5->pt_surface, x, y, 5); //rajouter a remplir france le fait que l'on change de fichier, et donc qu'il faut blitter les pixels en fct
            //140 000 000 points a blitter

            fclose(fichier); //on ferme le fichier ouvert
        }
    }

    printf("5m pret !\n");
    data_5->pt_zoom = zoomSurface(data_5->pt_surface, DEZOOM_X_5, DEZOOM_Y_5, 1); //on dezoom pour l'afficher en 859*800

    free(coord1);
    free(coord2);
    SDL_FreeSurface(tempo_5);
    closedir(rep);

    data_5->done = 1;

    bouton(); //fin de l'animation

    pthread_exit(NULL);
}



void accueil(int mode){

    SDL_Surface * page = NULL;
    SDL_Surface *image = SDL_LoadBMP("accueil.bmp"); //taille 500*500
    TTF_Font *police = NULL; //acceuille la police pour les boutons
    SDL_Surface *label = NULL;
    SDL_Surface *start = SDL_LoadBMP("play.bmp");;// taille 128*128
    char texte[BUFSIZE];

    SDL_Rect position_image;
    SDL_Rect labelposition;

    if(TTF_Init() == -1){ //initialise SDL_ttf
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    police = TTF_OpenFont("morningtype/Morningtype.ttf", 50);

    position_image.x = 550;
    position_image.y = 100;

    page = SDL_CreateRGBSurface(SDL_HWSURFACE, 1600, 800, 32, 0, 0, 0, 0);
    SDL_FillRect(page, NULL, SDL_MapRGB(ecran->format, 255, 250, 240)); // remplir la surface d'un "blanc floral"
    SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 255, 255)); //rendre le blanc de l'image transparent

    SDL_SetColorKey(start, SDL_SRCCOLORKEY, SDL_MapRGB(start->format, 0, 0, 0));

    labelposition.x = 750;
    labelposition.y = 630;

    SDL_BlitSurface(image, NULL, page, &position_image);
    SDL_BlitSurface(start, NULL, page, &labelposition);
    SDL_BlitSurface(page, NULL, img_accueil, NULL);

    if(mode == 0){

        labelposition.x = 1450;
        labelposition.y = 750;

        strcpy(texte, "Crédits");

        label = TTF_RenderText_Blended(police, texte, (SDL_Color) {76, 175, 80});
        SDL_BlitSurface(label, NULL, img_accueil, &labelposition);

    }else if(mode == 1){

        labelposition.x = 1300;
        labelposition.y = 550;

        strcpy(texte, "Génaux Luc");
        label = TTF_RenderText_Blended(police, texte, (SDL_Color) {76, 175, 80});
        SDL_BlitSurface(label, NULL, img_accueil, &labelposition);

        labelposition.x = 1300;
        labelposition.y = 600;

        strcpy(texte, "Malbois Fabien");
        label = TTF_RenderText_Blended(police, texte, (SDL_Color) {76, 175, 80});
        SDL_BlitSurface(label, NULL, img_accueil, &labelposition);

        labelposition.x = 1300;
        labelposition.y = 650;

        strcpy(texte, "Pfister Thomas");
        label = TTF_RenderText_Blended(police, texte, (SDL_Color) {76, 175, 80});
        SDL_BlitSurface(label, NULL, img_accueil, &labelposition);

        labelposition.x = 1300;
        labelposition.y = 700;

        strcpy(texte, "Efsthatiou Marie");
        label = TTF_RenderText_Blended(police, texte, (SDL_Color) {76, 175, 80});
        SDL_BlitSurface(label, NULL, img_accueil, &labelposition);

        labelposition.x = 1300;
        labelposition.y = 750;

        strcpy(texte, "INSA CVL 2016");
        label = TTF_RenderText_Blended(police, texte, (SDL_Color) {76, 175, 80});
        SDL_BlitSurface(label, NULL, img_accueil, &labelposition);

    }

    SDL_BlitSurface(img_accueil, NULL, ecran, NULL);

    SDL_Flip(ecran);

    SDL_FreeSurface(page);
    SDL_FreeSurface(image);
    SDL_FreeSurface(label);
    SDL_FreeSurface(start);

    TTF_CloseFont(police);
    TTF_Quit();

}

void sdl_ini(){

    pthread_t pid1; //pid du thread
    pthread_t pid2;

//AFFECTATION SURFACE POINTEURS DONNEES CARTES

    data_1000->pt_surface = NULL;

    data_75->pt_surface = NULL;
    data_75->pt_zoom = NULL;

    data_5->pt_surface = NULL;
    data_5->pt_zoom = NULL;

//CREATION ECRAN

    if (SDL_Init(SDL_INIT_VIDEO) == -1) { // Démarrage de la SDL. Si erreur :
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    SDL_WM_SetIcon(SDL_LoadBMP("play.bmp"), NULL); // Pour changer l'icone du .exe

    if ((ecran = SDL_SetVideoMode(1600, 800, 32, SDL_HWSURFACE)) == NULL) { // Si l'ouverture de la fenêtre a échoué, on le note et on arrête //1600, 800
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Inondation.exe", NULL); // changer nom de la fenêtre

    img_accueil = SDL_CreateRGBSurface(SDL_HWSURFACE, 1600, 800, 32, 0, 0, 0, 0);
    prog = SDL_CreateRGBSurface(SDL_HWSURFACE, 1600, 800, 32, 0, 0, 0, 0);

//REMPLISSAGE DE LA FRANCE

    data_1000->pt_surface = SDL_CreateRGBSurface(SDL_HWSURFACE, COLONNES, LIGNES, 32, 0, 0, 0, 0); //pour la france en 1000m
    data_75->pt_surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1300, 1300, 32, 0, 0, 0, 0); // pour la france en 75m
    data_5->pt_surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1300, 1300, 32, 0, 0, 0, 0); // pour la france en 75m


    init_bouton();

//CREATION THREAD

    if(pthread_create(&pid1, NULL, fichier_75, NULL) != 0){
        perror("Probleme avec pthread_create");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&pid2, NULL, fichier_5, NULL) != 0){
        perror("Probleme avec pthread_create");
        exit(EXIT_FAILURE);
    }

    bouton(); //on crée l'affichage sur prog
    accueil(0);// on crée l'accueil sur img_accueil et on blit sur l'écran

    SDL_Flip(ecran); // Mise à jour de l'écran
    pause(); // Mise en pause du programme

    if(data_75->done == 0)
        pthread_cancel(pid1);
    else
        pthread_join(pid1, NULL); //on check le thread pour voir si celui-la est finis, sinon on interromp pas le prog, car sinon zombi?


    if(data_5->done == 0)
        pthread_cancel(pid2);
    else
        pthread_join(pid2, NULL);

//LIBERATION
    DetruireBouton();
    SDL_FreeSurface(data_75->pt_zoom);
    SDL_FreeSurface(data_75->pt_surface);
    SDL_FreeSurface(data_5->pt_zoom);
    SDL_FreeSurface(data_5->pt_surface);
    SDL_FreeSurface(data_1000->pt_surface);
    SDL_FreeSurface(img_accueil);
    SDL_FreeSurface(prog);
    SDL_FreeSurface(ecran);

    SDL_Quit(); // Arrêt de la SDL
}
