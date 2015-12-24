#include "partie1.h"

void chargement() {

//CREATION STRUCTURE DE DONNEES POUR LES CARTES

    data_75 = (data_map *) malloc(sizeof(data_map));
    data_1000 = (data_map *) malloc(sizeof(data_map));

//ALLOCATION MEMOIRE & OUVERTURE DU FICHIER

    FILE *fichier_1000 = NULL;

    alloue(); //gestion des erreurs déjà fait dans alloue

//REMPLISSAGE TABLEAU 1000 "DE BASE"

    if ((fichier_1000 = fopen("1000m.ASC", "r")) == NULL) { // ouverture du fichier en mode lecture seule
        printf("\aErreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if(ajout_tab(fichier_1000, 1000) == 0) {
        printf("\aErreur dans l'ajout des donnees du fichier a tab\n");
        exit(EXIT_FAILURE);
    }

    fclose(fichier_1000);
}


void libere() {

    int i;

    for (i=0; i<LIGNES; i++) {
        free(data_1000->pt_tab[i]);
    }

    for (i=0; i<LIGNES_75; i++) {
        free(data_75->pt_tab[i]);
    }

    free(data_1000->pt_tab); //Libere bien les tableaux ??
    free(data_75->pt_tab);

    printf("Liberation reussie ! \n");
}

void alloue() {

    int i;

    if ((data_1000->pt_tab = (Point**) malloc(LIGNES * sizeof(Point*))) == NULL) { // allocation mémoire de tab[x]: tableau de x pointeurs sur Point
        printf("\aErreur d'allocation mémoire dans alloue.\n");  // si il y a eu une erreur on est rentré dans le if
        exit(EXIT_FAILURE);
    }

    for (i=0; i<LIGNES; i++) {
        if ((data_1000->pt_tab[i] = (Point*) malloc(COLONNES * sizeof(Point))) == NULL) { // chaque pointeur pointe sur un tableau de y Point
            printf("\aErreur d'allocation mémoire dans le for de alloue.\n");  // si il y a une erreur on rentre dans le if
            libere();
            exit(EXIT_FAILURE);
        }
    }

    if ((data_75->pt_tab = (Point**) malloc(LIGNES_75 * sizeof(Point*))) == NULL) { // allocation mémoire de tab[x]: tableau de x pointeurs sur Point
        printf("\aErreur d'allocation mémoire dans alloue.\n");  // si il y a eu une erreur on est rentré dans le if
        exit(EXIT_FAILURE);
    }

    for (i=0; i<LIGNES_75; i++) {
        if ((data_75->pt_tab[i] = (Point*) malloc(COLONNES_75 * sizeof(Point))) == NULL) { // chaque pointeur pointe sur un tableau de y Point
            printf("\aErreur d'allocation mémoire dans le for de alloue.\n");  // si il y a une erreur on rentre dans le if
            libere();
            exit(EXIT_FAILURE);
        }
    }
}

int ajout_tab(FILE * file, int type) {

    int i = 0, j = 0;

    switch(type){
        case 1000:

            for (i=0; i<LIGNES; i++) {
                for (j=0; j<COLONNES; j++) {

                    if(fscanf(file, "%lf", &data_1000->pt_tab[i][j].metre) != 1)
                        return 0; // il y a eu une erreur

                    data_1000->pt_tab[i][j].estInonde = 0; // initialisation

                }
            }

            break;

        case 75:

            for (i=0; i<LIGNES_75; i++) {
                for (j=0; j<COLONNES_75; j++) {

                    if(fscanf(file, "%lf", &data_75->pt_tab[i][j].metre) != 1)
                        return 0; // il y a eu une erreur

                    data_75->pt_tab[i][j].estInonde = 0; // initialisation

                }
            }

            break;


    }

    /* mettre le deuxième for en :
    while ((j<co)&&(fscanf(file, "%d", &tab[i][j].metre)==1)) {
    si on ne sait pas combien il y a de caractères par ligne */
    return 1; //tout s'est bien passé
}

void affiche_tab(Point **tab) {
    int i,j;
    for (i=0; i<5; i++) {
        for (j=0; j<5; j++) {
            printf("%lf ", tab[i][j].metre);
        }
        printf("\n");
    }
}

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

