#include "partie2.h"
#include "partie1.h"
#include "propagation.h"

void zoom(int posx, int posy, int val_zoom, int type){

    SDL_Surface *nouvelleImageTemp = NULL;
    SDL_Surface * zoom = NULL; //oblig� de cr�er une nouvelle surface sinon nouvelleImageTemp = zoomSurface(nouvelleImageTemp, val_zoom, val_zoom, 1); sature la m�moire
    SDL_Rect positionzoom;
    SDL_Rect positionExtraction;

    positionzoom.x = 1000; //position du carr� zoom
    positionzoom.y = 350;

    if(type == 1000){

        positionExtraction.x = (posx-150/val_zoom)/DEZOOM_X_1000; //on divise par DEZOOM_X car c'est le facteur entre la surface  zoom� de data_1000 et la surface de data_1000
        positionExtraction.y = (posy-150/val_zoom)/DEZOOM_Y_1000;
        positionExtraction.w = 300/(val_zoom*DEZOOM_X_1000); // a chaque fois la zone � zoomer sur se r�duit en fct de val_zoom
        positionExtraction.h = 300/(val_zoom*DEZOOM_Y_1000);

    }else if(type == 75){

        positionExtraction.x = (posx-150/val_zoom)/DEZOOM_X_75; //on divise par DEZOOM_X car c'est le facteur entre la surface  zoom� de data_1000 et la surface de data_1000
        positionExtraction.y = (posy-150/val_zoom)/DEZOOM_Y_75;
        positionExtraction.w = 300/(val_zoom*DEZOOM_X_1000); // a chaque fois la zone � zoomer sur se r�duit en fct de val_zoom
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
    }

    zoom = zoomSurface(nouvelleImageTemp, val_zoom, val_zoom, 1);

    SDL_BlitSurface(zoom, NULL, ecran, &positionzoom);

    SDL_FreeSurface(nouvelleImageTemp);
    SDL_FreeSurface(zoom);

    SDL_Flip(ecran); // Mise � jour de l'�cran

}

void pause(SDL_Rect TBoutton) {

    int continuer = 1;
    SDL_Event event;
    int val_zoom = 1;
    int type = 1000; //1000=data_1000, 75=data_75

    while (continuer) { // TANT QUE la variable ne vaut pas 0
        SDL_WaitEvent(&event); // On attend un �v�nement qu'on r�cup�re dans event
        switch(event.type) { // On teste le type d'�v�nement

            case SDL_QUIT: // Si c'est un �v�nement QUITTER
                continuer = 0; // On met le bool�en � 0, donc la boucle va s'arr�ter
                break;

            case SDL_MOUSEBUTTONDOWN: //si on appui sur un bouton de la souri
                if ( event.button.button == SDL_BUTTON_LEFT && event.button.y > 200 && event.button.y <= 200+TBoutton.h && event.button.x > 1000 && event.button.x <= 1000+TBoutton.w) {
                    init_propa(data_1000->pt_tab);
                    remplirFrance(data_1000->pt_tab, data_1000->pt_surface, ecran, 0, 0, 1000);
                    SDL_Flip(ecran);
                    type = 1000;
                }else if( event.button.button == SDL_BUTTON_LEFT && event.button.y > 200 && event.button.y <= 200+TBoutton.h && event.button.x > 1050 && event.button.x <= 1050+TBoutton.w) {
                    init_propa(data_1000->pt_tab);
                    super_propa(data_1000->pt_tab, 0, 0, LIGNES-1 , COLONNES-1, 10, 2);
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, ecran, 0, 0, 1000);
                    SDL_Flip(ecran);
                    type = 1000;
                }else if( event.button.button == SDL_BUTTON_LEFT && event.button.y > 200 && event.button.y <= 200+TBoutton.h && event.button.x > 1100 && event.button.x <= 1100+TBoutton.w) {
                    init_propa(data_1000->pt_tab);
                    super_propa(data_1000->pt_tab, 0, 0, LIGNES-1 , COLONNES-1, 20, 2);
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, ecran, 0, 0, 1000);
                    SDL_Flip(ecran);
                    type = 1000;
                }else if( event.button.button == SDL_BUTTON_LEFT && event.button.y > 200 && event.button.y <= 200+TBoutton.h && event.button.x > 1150 && event.button.x <= 1150+TBoutton.w) {
                    init_propa(data_1000->pt_tab);
                    super_propa(data_1000->pt_tab, 0, 0, LIGNES-1 , COLONNES-1, 30, 2);
                    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, ecran, 0, 0, 1000);
                    SDL_Flip(ecran);
                    type = 1000;
                }else if( event.button.button == SDL_BUTTON_LEFT && event.button.y > 100 && event.button.y <= 100+TBoutton.h && event.button.x > 1000 && event.button.x <= 1000+TBoutton.w && data_5->done == 1) {
                    SDL_BlitSurface(data_5->pt_zoom, NULL, ecran, NULL);
                    SDL_Flip(ecran);
                    type = 1000;
                }else if( event.button.button == SDL_BUTTON_LEFT && event.button.y <= data_1000->pt_surface->h && event.button.x <= data_1000->pt_surface->w) { //peut-�tre moins energivore ?? A d�battre
                    zoom(event.motion.x, event.motion.y, val_zoom, type);
                }else if (event.button.button == SDL_BUTTON_WHEELUP){
                    val_zoom = val_zoom == 3 ? 3 : val_zoom+1; //test ternaire
                    zoom(event.motion.x, event.motion.y, val_zoom, type);
                }else if (event.button.button == SDL_BUTTON_WHEELDOWN){
                    val_zoom = val_zoom == 1 ? 1 : val_zoom-1; //test ternaire
                    zoom(event.motion.x, event.motion.y, val_zoom, type);
                }
                break;

            /*case SDL_MOUSEMOTION://permet de savoir si la sourie bouge
                zoom(event.motion.x, event.motion.y, val_zoom, tempo, ecran);
                break;*/


        }
    }
}



void getPixelColor(SDL_Rect position, SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b) {

    if(position.x>0 && position.y>0 && position.x<surface->w && position.y<surface->h) {
        int bpp = surface->format->BytesPerPixel;
        Uint8 *p = (Uint8 *)surface->pixels + position.y * surface->pitch + position.x * bpp;
        SDL_GetRGB(*(Uint32 *)p,surface->format, r, g, b);
    }else{ // sinon on renvoie noir, pour �viter de planter dans certains cas
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
            position_ecran.x = x*10+100;
            position_ecran.y = 500-10*y;
            break;
    }

    int i,j;
    for (i=0; i<max_lignes; i++) {
        for (j=0; j<max_colonnes; j++) {
            position_sortie.x = j;
            if ((tab[i][j].metre) < 0) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 20, 20, 20)); // remplir la surface de noir
            }else if ((tab[i][j].estInonde) == 1) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 33, 150, 243)); // remplir la surface de bleu
            }else if ((tab[i][j].estInonde) == 2) {
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, 250, 20, 15)); //rempli de rouge
            }else if ((tab[i][j].metre) > 2500.00) {
                position_degrade.y = 2500;
                getPixelColor(position_degrade, degrade, &r, &g, &b);
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, r, g, b)); // remplir la surface de la couleur 2500m
            }else{
                position_degrade.y = (int) tab[i][j].metre;
                getPixelColor(position_degrade, degrade, &r, &g, &b);
                SDL_FillRect(pixel, NULL, SDL_MapRGB(sortie->format, r, g, b)); // remplir la surface de la couleur de l'altitude
            }
            SDL_BlitSurface(pixel, NULL, sortie, &position_sortie); // on met chaque pixel sur la surface de sortie
        }
        position_sortie.y = i;
    }

    //on obtient la France en 1161 par 1081

    if(type == 1000){
        dezoom = zoomSurface(sortie, DEZOOM_X_1000, DEZOOM_Y_1000, 1); //On transforme la surface tempo. zoomX = nouvelleLargeurX / ancienneLargeurX   zoomY = nouvelleLargeurY / ancienneLargeurY
        SDL_BlitSurface(dezoom, NULL, blit_surface, NULL); // On met la nouvelle France sur ecran
        data_1000->pt_zoom = dezoom; //on stock le zoom
    }
    else if(type == 75){
        dezoom = zoomSurface(sortie, (float) 0.075, (float) 0.075, 0); //On dezoom chaque tabeleau de 1000*1000 qu'on a plac� sur une surface de 1000*1000
        SDL_BlitSurface(dezoom, NULL, blit_surface, &position_ecran); // On met les tableaux dezoom� sur une surface qui peut contenir la france en 75m, ici blit_surface c'est data_75->pt_surface
    }else if(type == 5){
        dezoom = zoomSurface(sortie, (float) 0.05, (float) 0.05, 0); //On dezoom chaque tabeleau de 1000*1000 qu'on a plac� sur une surface de 1000*1000
        SDL_BlitSurface(dezoom, NULL, blit_surface, &position_ecran); // On met les tableaux dezoom� sur une surface qui peut contenir la france en 5m, ici blit_surface c'est data_5->pt_surface
    }

    SDL_FreeSurface(degrade);
    SDL_FreeSurface(pixel);
    SDL_FreeSurface(dezoom);
}

SDL_Rect boutton(){

    TTF_Font *police = NULL; //acceuille la police pour les bouttons

    if(TTF_Init() == -1){ //initialise SDL_ttf
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    int i = 0;
    char texte[BUFSIZE];
    SDL_Surface *Boutton = NULL; //pour les 3 boutons
    SDL_Surface *Noir = NULL;
    SDL_Rect positionBoutton; //rectangle acceuillant le boutton
    SDL_Rect positionNoir;
    police = TTF_OpenFont("morningtype/Morningtype.ttf", 20);

    if(data_75->done == 0){ //Petite animation au top
        strcpy(texte, "Chargement carte 75m..."); //bouton pour choisir le fichier
        Boutton = TTF_RenderText_Blended(police, texte, (SDL_Color) {255, 255, 255});
        positionBoutton.x = 1000;
        positionBoutton.y = 80;
        SDL_BlitSurface (Boutton, NULL, ecran, &positionBoutton);

    }else{

        Noir = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 20, 32, 0, 0, 0, 0);
        SDL_FillRect(Noir, NULL, SDL_MapRGB(Noir->format, 0, 0, 0));
        positionNoir.x = 1000;
        positionNoir.y = 80;
        SDL_BlitSurface(Noir, NULL, ecran, &positionNoir);

        strcpy(texte, "Fichier :"); //bouton pour choisir le fichier
        Boutton = TTF_RenderText_Blended(police, texte, (SDL_Color) {255, 255, 255});
        positionBoutton.x = 1000;
        positionBoutton.y = 80;
        SDL_BlitSurface (Boutton, NULL, ecran, &positionBoutton);

        strcpy(texte, "75m"); //bouton pour choisir le fichier
        Boutton = TTF_RenderText_Blended(police, texte, (SDL_Color) {255, 255, 255});
        positionBoutton.x = 1000;
        positionBoutton.y = 100;
        SDL_BlitSurface (Boutton, NULL, ecran, &positionBoutton);
    }

    for(i=0; i<4; i++){ //on initialise et affiche les 3 bouttons pour le niveau de l'eau a 1000m
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
    SDL_FreeSurface(Noir);
    TTF_CloseFont(police);
    TTF_Quit();

    SDL_Flip(ecran);

    return positionBoutton;
}

void * fichier_75(void){

    data_75->done = 0;

    FILE * fichier = NULL;
    DIR * rep = NULL;

    SDL_Surface *tempo_75 = NULL; //va stocker les carr� de 1000*1000
    tempo_75 = SDL_CreateRGBSurface(SDL_HWSURFACE, COLONNES_75, LIGNES_75, 32, 0, 0, 0, 0); // pour les carr�s de 1000*1000 en 75m

    struct dirent * info_rep = NULL;

    int x, y, i;

    char mot[9]; //impossible de supprimer mot ??
    char *coord1, *coord2;
    char repertoire[BUFSIZE];

    coord1 = (char *) malloc(4*sizeof(char));
    coord2 = (char *) malloc(4*sizeof(char));

    if((rep = opendir(REP_75)) == NULL){
        perror("Probl�me avec le r�pertoire\n");
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
                fgets(repertoire, BUFSIZE, fichier); //nous place a la ligne des donn�es

            for(i=0; i<4; i++){
                coord1[i] = info_rep->d_name[20+i];
            }

            for(i=0; i<4; i++){
                coord2[i] = info_rep->d_name[25+i];
            }

            x = atoi(coord1) - 75;
            y = atoi(coord2) - 6150;

            ajout_tab(fichier, 75);

            remplirFrance(data_75->pt_tab, tempo_75, data_75->pt_surface, x, y, 75); //rajouter a remplir france le fait que l'on change de fichier, et donc qu'il faut blitter les pixels en fct
            //140 000 000 points a blitter

            fclose(fichier); //on ferme le fichier ouvert

        }
    }

    printf("75 pret !\n");
    data_75->pt_zoom = zoomSurface(data_75->pt_surface, DEZOOM_X_75, DEZOOM_Y_75, 1); //on dezoom pour l'afficher en 859*800

    free(coord1);
    free(coord2);
    SDL_FreeSurface(tempo_75);
    closedir(rep);

    data_75->done = 1;

    boutton(); //fin de l'animation

    pthread_exit(NULL);


}

void * fichier_5(void){

    data_5->done = 0;

    FILE * fichier = NULL;
    DIR * rep = NULL;

    SDL_Surface *tempo_5 = NULL; //va stocker les carr� de 1000*1000
    tempo_5 = SDL_CreateRGBSurface(SDL_HWSURFACE, COLONNES_5, LIGNES_5, 32, 0, 0, 0, 0); // pour les carr�s de 1000*1000 en 75m

    struct dirent * info_rep = NULL;

    int x, y, i;

    char mot[9]; //impossible de supprimer mot ??
    char *coord1, *coord2;
    char repertoire[BUFSIZE];

    coord1 = (char *) malloc(4*sizeof(char));
    coord2 = (char *) malloc(4*sizeof(char));

    if((rep = opendir(REP_5)) == NULL){
        perror("Probl�me avec le r�pertoire\n");
    }


    while((info_rep = readdir(rep)) != NULL){

        strcpy(repertoire, REP_5); //on remet repertoire a 75m/

        if(info_rep->d_type & DT_REG){

            printf("%s\n", info_rep->d_name);

            if ((fichier = fopen(strcat(repertoire, info_rep->d_name), "r")) == NULL) { // ouverture du fichier en mode lecture seule
                perror("Erreur a l'ouverture du fichier");
                exit(EXIT_FAILURE);
            }

            i = 6;
            while (i--)
                fgets(repertoire, BUFSIZE, fichier); //nous place a la ligne des donn�es

            for(i=0; i<4; i++){
                coord1[i] = info_rep->d_name[15+i];
            }

            for(i=0; i<4; i++){
                coord2[i] = info_rep->d_name[20+i];
            }

            x = atoi(coord1) - 200;
            y = atoi(coord2) - 6790;

            ajout_tab(fichier, 5);

            remplirFrance(data_5->pt_tab, tempo_5, data_5->pt_surface, x, y, 5); //rajouter a remplir france le fait que l'on change de fichier, et donc qu'il faut blitter les pixels en fct
            //140 000 000 points a blitter

            fclose(fichier); //on ferme le fichier ouvert

            SDL_BlitSurface(data_5->pt_surface, NULL, ecran, NULL);
            SDL_Flip(ecran);


        }
    }

    printf("5 pret !\n");
    data_5->pt_zoom = zoomSurface(data_5->pt_surface, DEZOOM_X_75, DEZOOM_Y_75, 1); //on dezoom pour l'afficher en 859*800

    free(coord1);
    free(coord2);
    SDL_FreeSurface(tempo_5);
    closedir(rep);

    data_5->done = 1;

    boutton(); //fin de l'animation

    pthread_exit(NULL);


}

void sdl_ini(){

    SDL_Rect TBoutton; //on stock la taille des boutons
    pthread_t pid1; //pid du thread
    pthread_t pid2;


//AFFECTATION SURFACE POINTEURS DONNEES CARTES

    data_1000->pt_surface = NULL;

    data_75->pt_surface = NULL;
    data_75->pt_zoom = NULL;

    data_5->pt_surface = NULL;
    data_5->pt_zoom = NULL;

//CREATION ECRAN

    if (SDL_Init(SDL_INIT_VIDEO) == -1) { // D�marrage de la SDL. Si erreur :
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // �criture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    //SDL_WM_SetIcon(SDL_LoadBMP("SUPER8ICONE.bmp"), NULL); // Pour changer l'icone du .exe

    if ((ecran = SDL_SetVideoMode(1600, 800, 32, SDL_HWSURFACE)) == NULL) { // Si l'ouverture de la fen�tre a �chou�, on le note et on arr�te //1600, 800
        fprintf(stderr, "Impossible de charger le mode vid�o : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Mon super .exe", NULL); // changer nom de la fen�tre

//REMPLISSAGE DE LA FRANCE

    super_propa(data_1000->pt_tab, 0, 0, LIGNES-1 , COLONNES-1, 0, 1); // On initialise tab pour que estInonde = 1 pour la vraie mer

    data_1000->pt_surface = SDL_CreateRGBSurface(SDL_HWSURFACE, COLONNES, LIGNES, 32, 0, 0, 0, 0); //pour la france en 1000m
    data_75->pt_surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1300, 1300, 32, 0, 0, 0, 0); // pour la france en 75m
    data_5->pt_surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1300, 1300, 32, 0, 0, 0, 0); // pour la france en 75m

    //remplirFrance(data_1000->pt_tab, data_1000->pt_surface, ecran, 0, 0, 1000); //on cr�e la surface pour 1000m pour afficher la france en 1000m en premier

//CREATION THREAD

    /*if(pthread_create(&pid1, NULL, &fichier_75, NULL) != 0){
        perror("Probleme avec pthread_create");
        exit(EXIT_FAILURE);
    }*/

    if(pthread_create(&pid2, NULL, &fichier_5, NULL) != 0){
        perror("Probleme avec pthread_create");
        exit(EXIT_FAILURE);
    }

    //fichier_dif(tab, surface_75, ecran); //on cr�e la surface pour 75m

    TBoutton = boutton(); //on cr�e l'affichage

    SDL_Flip(ecran); // Mise � jour de l'�cran
    pause(TBoutton); // Mise en pause du programme

   /* if(data_75->done == 0)
        pthread_cancel(pid1);
    else
        pthread_join(pid1, NULL); //on check le thread pour voir si celui-la est finis, sinon on interromp pas le prog, car sinon zombi?
    */

    if(data_5->done == 0)
        pthread_cancel(pid2);
    else
        pthread_join(pid2, NULL);

//LIBERATION
    SDL_FreeSurface(data_75->pt_zoom);
    SDL_FreeSurface(data_75->pt_surface);
    SDL_FreeSurface(data_5->pt_zoom);
    SDL_FreeSurface(data_5->pt_surface);
    SDL_FreeSurface(data_1000->pt_surface);
    SDL_FreeSurface(ecran);

    SDL_Quit(); // Arr�t de la SDL
}
