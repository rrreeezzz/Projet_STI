#include "partie1.h"

void libere(Point **tab, int y) {

    int i;
    for (i=0; i<y; i++) {
        free(tab[i]);
    }
    free(tab);
    printf("libération réussie");
}

Point** alloue() {

    Point **tab = NULL;
    if ((tab = (Point**) malloc(LIGNES * sizeof(Point*))) == NULL) { // allocation mémoire de tab[x]: tableau de x pointeurs sur Point
        printf("\aErreur d'allocation mémoire dans alloue\n");  // si il y a eu une erreur on est rentré dans le if
        exit(EXIT_FAILURE);
    }
    int i;
    for (i=0; i<LIGNES; i++) {
        if ((tab[i] = (Point*) malloc(COLONNES * sizeof(Point))) == NULL) { // chaque pointeur pointe sur un tableau de y Point
            printf("\aErreur d'allocation mémoire dans le for de alloue\n");  // si il y a une erreur on rentre dans le if
            libere(tab, i);
            exit(EXIT_FAILURE);
        }
    }
    return tab;
}

int ajout_tab(Point **tab, FILE* file) {

    int i,j;
    for (i=0; i<LIGNES; i++) {
        for (j=0; j<COLONNES; j++) {
            if(fscanf(file, "%d", &tab[i][j].metre) != 1)
                return 0; // il y a eu une erreur
            tab[i][j].estInonde = 0; // initialisation
        }
    }
    /* mettre le deuxième for en :
    while ((j<co)&&(fscanf(file, "%d", &tab[i][j].metre)==1)) {
    si on ne sait pas combien il y a de caractères par ligne */
    return 1; //tout s'est bien passé
}

/*void affiche_tab(Point **tab) {
    int i,j;
    for (i=0; i<LIGNES; i++) {
        for (j=0; j<COLONNES; j++) {
            printf("%d ", tab[i][j].metre);
        }
        printf("\n");
    }
}*/

/*int valMax_tab(Point **tab, int li, int co) {  // Permet d'avoir le plus haut sommet de France
    int i,j;
    int max = tab[0][0].metre;
    for (i=0; i<li; i++) {
        for (j=0; j<co; j++) {
            if (tab[i][j].metre > max)
                max = tab[i][j].metre;
        }
    }
    return max;
}*/

Point** chargement() {

//ALLOCATION MEMOIRE & OUVERTURE DU FICHIER
    FILE *fichier = NULL;
    Point **tab;

    if ((tab = alloue()) == NULL ) { // allocation mémoire de tab[x][y]
        printf("\aErreur d'allocation mémoire dans chargement\n");  // si il y a eu une erreur on est rentré dans le if
        exit(EXIT_FAILURE);
    }

    if ((fichier = fopen("1000m.ASC", "r")) == NULL) { // ouverture du fichier en mode lecture seule
        printf("\aErreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if(ajout_tab(tab, fichier) == 0) {
        printf("\aErreur dans l'ajout des donnees du fichier a tab\n");
        exit(EXIT_FAILURE);
    }

    fclose(fichier);
    return tab;
}
