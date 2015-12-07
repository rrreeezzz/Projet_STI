#include "partie1.h"
#include "partie2.h"


int main(int argc, char *argv[]) {

    FILE * fichier;
    Point ** tabPt = NULL;

//ALLOCATION MEMOIRE & OUVERTURE DU FICHIER
    if ((tabPt = (Point**) malloc(LIGNES * sizeof(Point*))) == NULL) { // allocation mémoire de tab[x]: tableau de x pointeurs sur Point
        printf("\aErreur d'allocation mémoire\n");  // si il y a eu une erreur on est rentré dans le if
        exit(EXIT_FAILURE);
    }

    alloue(tabPt, LIGNES, COLONNES); // allocation mémoire de tab[x][y]

    if ((fichier = fopen("1000m.ASC", "r")) == NULL) { // ouverture du fichier en mode lecture seule
        printf("\aErreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if(ajout_tab(tabPt, fichier, LIGNES, COLONNES) == 0) {
        printf("\aErreur dans l'ajout des donnees du fichier a tab\n");
        exit(EXIT_FAILURE);
    }

    sdl_ini(tabPt);

    fclose(fichier);

    return EXIT_SUCCESS;
}
