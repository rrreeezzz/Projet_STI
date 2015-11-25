#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#define CORDX 1081 //nb de lignes
#define CORDY 1161 //nb de colonnes

typedef struct {
        int metre;
        int estInonde;
} Point;

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
            printf("\aErreur d'allocation m�moire\n");  //si il y a une erreur on rentre dans le if
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
    /* mettre le deuxi�me for en :
    while ((j<CORDY)&&(fscanf(file, "%d", &tab[i][j].metre)==1)) {
    si on ne sait pas combien il y a de caract�res par ligne */
    return 0; //tout s'est bien pass�
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




void pause() {
    int continuer = 1;
    SDL_Event event;
    while (continuer) { // TANT QUE la variable ne vaut pas 0
        SDL_WaitEvent(&event); // On attend un �v�nement qu'on r�cup�re dans event
        switch(event.type) { // On teste le type d'�v�nement
            case SDL_QUIT: // Si c'est un �v�nement QUITTER
                continuer = 0; // On met le bool�en � 0, donc la boucle va s'arr�ter
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fichier=NULL;
    Point **tabPt=NULL;

    //ALLOCATION MEMOIRE & OUVERTURE DU FICHIER
    if ((tabPt=(Point**) malloc(CORDX * sizeof(Point*)))==NULL) { // allocation m�moire de tab[x]: tableau de x pointeurs sur Point
        printf("\aErreur d'allocation m�moire\n");  // si il y a eu une erreur on est rentr� dans le if
        exit(EXIT_FAILURE);
    }
    alloue(tabPt, CORDX, CORDY); // allocation m�moire de tab[x][y]

    if ((fichier=fopen("1000m.ASC", "r"))==NULL) { // ouverture du fichier en mode lecture seule
        printf("\aErreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if(ajout_tab(tabPt, fichier, CORDX, CORDY)==1) {
        printf("\aErreur dans l'ajout des donnees du fichier a tab\n");
        exit(EXIT_FAILURE);
    }







    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'�cran
    SDL_Surface *rectangle = NULL;
    SDL_Rect position;

//CREATION ECRAN
    if (SDL_Init(SDL_INIT_VIDEO) == -1) { // D�marrage de la SDL. Si erreur :
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // �criture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    ecran = SDL_SetVideoMode(CORDX, CORDY, 16, SDL_SWSURFACE); // On tente d'ouvrir une fen�tre
    if (ecran == NULL) { // Si l'ouverture a �chou�, on le note et on arr�te
        fprintf(stderr, "Impossible de charger le mode vid�o : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Mon super .exe", NULL); // changer nom de la fen�tre

    //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); // remplir l'�cran d'une couleur
//

//CREATION SURFACE
    position.x=0;
    position.y=0;
    rectangle = SDL_CreateRGBSurface(SDL_SWSURFACE, 1, 1, 16, 0, 0, 0, 0); // creation d'une surface

    int i,j;
    for (i=0; i<CORDX; i++) {
        for (j=0; j<CORDY; j++) {
            position.x=j;
            if ((tabPt[i][j].metre)<0) {
                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
            }else if ((tabPt[i][j].metre)==0) {
                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
            }else{
                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
            }
            SDL_BlitSurface(rectangle, NULL, ecran, &position);
        }
        position.y=i;
    }

  //  SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); // remplir la surface d'une couleur
  //  SDL_BlitSurface(rectangle, NULL, ecran, &position); // mettre la surface sur l'�cran, � une position pr�cise
//


    pause(); // Mise en pause du programme

//LIBERATION SURFACE
    SDL_FreeSurface(rectangle);
    SDL_Quit(); // Arr�t de la SDL


    libere(tabPt, CORDX);
    fclose(fichier);


    return EXIT_SUCCESS;
}
