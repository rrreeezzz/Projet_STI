#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#define CORDX 1081 //nb de lignes
#define CORDY 1161 //nb de colonnes

typedef struct {
        int metre;
        int estInonde;
} Point;

typedef struct { //pour différentes catégories de couleur, pour représenter les points de + de 200m
        int r;
        int g;
        int b;
} couleur;

typedef struct {
        int hauteur;
        int largeur;
} ecran; //contient la taille de la fênetre a afficher

void libere(Point **tab, int x) {
    int i;
    for (i=0;i<x;i++) {
        free(tab[i]);
    }
    free(tab);
}

void alloue(Point **tab, int x, int y) {
    int i;
    for (i=0;i<x;i++) {
        if ((tab[i]=(Point*) malloc(y * sizeof(Point)))==NULL) { //chaque pointeur pointe sur un tableau de y Point
            printf("\aErreur d'allocation mémoire\n");  //si il y a une erreur on rentre dans le if
            libere(tab, i);
            exit(EXIT_FAILURE);
        }
    }
}

int ajout_tab(Point **tab, FILE* file, int x, int y) {
    int i,j;
    for (i=0;i<x;i++) {
        for (j=0;j<y;j++) {
            if(fscanf(file, "%d", &tab[i][j].metre)!=1)
                return 1; //il y a eu une erreur
        }
    }
    /* mettre le deuxième for en :
    while ((j<CORDY)&&(fscanf(file, "%d", &tab[i][j].metre)==1)) {
    si on ne sait pas combien il y a de caractères par ligne */
    return 0; //tout s'est bien passé
}

void affiche_tab(Point **tab, int x, int y) {
    int i,j;
    for (i=0;i<x;i++) {
        for (j=0;j<y;j++) {
            printf("%d ", tab[i][j].metre);
        }
        printf("\n");
    }
}

int valMax_tab(Point **tab, int x, int y) {
    int i,j;
    int max=tab[0][0].metre;
    for (i=0;i<x;i++) {
        for (j=0;j<y;j++) {
            if (tab[i][j].metre > max)
                max=tab[i][j].metre;
        }
    }
    return max;
}

/* void scrolling(ecran* m,SDL_Surface* screen)
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
                scroll(posx, posy);
            }
    }
}*/


void pause() {
    int continuer = 1;
    SDL_Event event;
    while (continuer) { // TANT QUE la variable ne vaut pas 0
        SDL_WaitEvent(&event); // On attend un événement qu'on récupère dans event
        switch(event.type) { // On teste le type d'événement
            case SDL_QUIT: // Si c'est un événement QUITTER
                continuer = 0; // On met le booléen à 0, donc la boucle va s'arrêter
                break;
            /*case SDL_MOUSEBUTTONDOWN:
                mousemov();
                break;*/
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fichier=NULL;
    Point **tabPt=NULL;

    //ALLOCATION MEMOIRE & OUVERTURE DU FICHIER
    if ((tabPt=(Point**) malloc(CORDX * sizeof(Point*)))==NULL) { // allocation mémoire de tab[x]: tableau de x pointeurs sur Point
        printf("\aErreur d'allocation mémoire\n");  // si il y a eu une erreur on est rentré dans le if
        exit(EXIT_FAILURE);
    }
    alloue(tabPt, CORDX, CORDY); // allocation mémoire de tab[x][y]

    if ((fichier=fopen("1000m.ASC", "r"))==NULL) { // ouverture du fichier en mode lecture seule
        printf("\aErreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if(ajout_tab(tabPt, fichier, CORDX, CORDY)==1) {
        printf("\aErreur dans l'ajout des donnees du fichier a tab\n");
        exit(EXIT_FAILURE);
    }


    /*ecran *fenetre;
    fenetre->hauteur = 1000;
    fenetre->largeur=1000;*/


    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran
    SDL_Surface *rectangle = NULL; //surface pour les points
    couleur * degrade1 = NULL; //tableau pour la structure couleur
    SDL_Rect position;

//CREATION ECRAN
    if (SDL_Init(SDL_INIT_VIDEO) == -1) { // Démarrage de la SDL. Si erreur :
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    ecran = SDL_SetVideoMode(1000, 1000, 16, SDL_SWSURFACE); // On tente d'ouvrir une fenêtre
    if (ecran == NULL) { // Si l'ouverture a échoué, on le note et on arrête
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Mon super .exe", NULL); // changer nom de la fenêtre

    //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); // remplir l'écran d'une couleur
//

//CREATION SURFACE
    position.x=0;
    position.y=0;
    rectangle = SDL_CreateRGBSurface(SDL_SWSURFACE, 1, 1, 16, 0, 0, 0, 0); // creation d'une surface
    degrade1 = calloc(50, sizeof(couleur)); // surface degradé, tableau de couleur et pas de pointeur sur couleur...

    int i,j;

    for(i=0; i<50; i++){
        degrade1[i].r = 200-2*i; //200-2*50 = 100
        degrade1[i].g = 200-3*i; //200-3*50 = 50
        degrade1[i].b = 0;
    }

    for (i=0; i<CORDX; i++) {
        for (j=0; j<CORDY; j++) {
            position.x=j;
            if ((tabPt[i][j].metre)<0) {
                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
            }else if ((tabPt[i][j].metre)==0) {
                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
            }else if ((tabPt[i][j].metre)<=200) {
                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, tabPt[i][j].metre, 200, 0));
            }else if ((tabPt[i][j].metre)>200) {
                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, degrade1[(tabPt[i][j].metre-200)/100].r, degrade1[(tabPt[i][j].metre-200)/100].g, 0));
            }
            SDL_BlitSurface(rectangle, NULL, ecran, &position);
        }
        position.y=i;
    }

  //  SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); // remplir la surface d'une couleur
  //  SDL_BlitSurface(rectangle, NULL, ecran, &position); // mettre la surface sur l'écran, à une position précise
//

    SDL_Flip(ecran);
    pause(); // Mise en pause du programme

//Sauver surface en BPM
    //SDL_SaveBMP(ecran, "France");

//LIBERATION SURFACE
    SDL_FreeSurface(rectangle);
    SDL_Quit(); // Arrêt de la SDL


    free(degrade1);
    libere(tabPt, CORDX);
    fclose(fichier);


    return EXIT_SUCCESS;
}
