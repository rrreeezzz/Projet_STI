#include "partie1.h"


void libere(Point **tab, int li) {

    int i;

    for (i=0; i<li; i++) {
        free(tab[i]);
    }

    free(tab);
}

void alloue(Point **tab, int li, int co) {

    int i;

    for (i=0; i<li; i++) {

        if ((tab[i] = (Point*) malloc(co * sizeof(Point))) == NULL) { // chaque pointeur pointe sur un tableau de y Point
            printf("\aErreur d'allocation mémoire\n");  // si il y a une erreur on rentre dans le if
            libere(tab, i);
            exit(EXIT_FAILURE);
        }
    }
}

int ajout_tab(Point **tab, FILE* file, int li, int co) {

    int i,j;

    for (i=0; i<li; i++) {
        for (j=0; j<co; j++) {
            if(fscanf(file, "%d", &tab[i][j].metre) != 1)
                return 0; // il y a eu une erreur
        }
    }
    /* mettre le deuxième for en :
    while ((j<co)&&(fscanf(file, "%d", &tab[i][j].metre)==1)) {
    si on ne sait pas combien il y a de caractères par ligne */
    return 1; //tout s'est bien passé
}

void affiche_tab(Point **tab, int li, int co) {

    int i,j;

    for (i=0; i<li; i++) {
        for (j=0; j<co; j++) {
            printf("%d ", tab[i][j].metre);
        }
        printf("\n");
    }
}

int valMax_tab(Point **tab, int li, int co) {  // Permet d'avoir le plus haut sommet de France

    int i,j;

    int max = tab[0][0].metre;
    for (i=0; i<li; i++) {
        for (j=0; j<co; j++) {
            if (tab[i][j].metre > max)
                max = tab[i][j].metre;
        }
    }
    return max;
}


   /* int c=0;    Code pas utilisé mais à laisser en attendant, sert à lire le fichier caractère par caractère
    while((c=fgetc(file))!=EOF) {
        if(c==' ') {
           printf(" ");
        }else {
        printf("%c", c);
        }
    } */

    /*
    long a=0;
    a=ftell(fichier);
    printf("%ld\n",a);
    */


