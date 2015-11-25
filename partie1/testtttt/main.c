#include <stdio.h>
#include <stdlib.h>

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
            printf("\aErreur d'allocation mémoire\n");  //si il y a une erreur on rentre dans le if
            libere(tab, i);
            exit(EXIT_FAILURE);
        }
    }
}

int ajout_tab(Point **tab, FILE* file, int x, int y) {
    int i,j;
    for (i=0;i<CORDX;i++) {
        for (j=0;j<CORDY;j++) {
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

int main() {
    FILE *fichier=NULL;
    Point **tabPt=NULL;
    long a=0;

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



   /* int c=0;    Code pas utilisé mais à laisser en attendant
    while((c=fgetc(file))!=EOF) {
        if(c==' ') {
           printf(" ");
        }else {
        printf("%c", c);
        }
    } */

    if(ajout_tab(tabPt, fichier, CORDX, CORDY)==1) {
        printf("\aErreur dans l'ajout des donnees du fichier a tab\n");
        exit(EXIT_FAILURE);
    }

    a=ftell(fichier);
    printf("%ld\n",a);


    //affiche_tab(tabPt, CORDX, CORDY);
    printf("la hauteur maximale est : %d\n", valMax_tab(tabPt, CORDX, CORDY));

    //LIBERATION MEMOIRE & FERMETURE DU FICHIER
    libere(tabPt, CORDX);
    fclose(fichier);
    exit(EXIT_SUCCESS);
}

