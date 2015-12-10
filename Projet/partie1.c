#include "partie1.h"

void libere(Point **tab, int li) {
    int i;
    for (i=0; i<li; i++) {
        free(tab[i]);
    }
    free(tab);
    printf("libération réussie");
}

Point** alloue(int li, int co) {
    Point **tab = NULL;
    if ((tab = (Point**) malloc(LIGNES * sizeof(Point*))) == NULL) { // allocation mémoire de tab[x]: tableau de x pointeurs sur Point
        printf("\aErreur d'allocation mémoire dans alloue\n");  // si il y a eu une erreur on est rentré dans le if
        exit(EXIT_FAILURE);
    }
    int i;
    for (i=0; i<li; i++) {
        if ((tab[i] = (Point*) malloc(co * sizeof(Point))) == NULL) { // chaque pointeur pointe sur un tableau de y Point
            printf("\aErreur d'allocation mémoire dans le for de alloue\n");  // si il y a une erreur on rentre dans le if
            libere(tab, i);
            exit(EXIT_FAILURE);
        }
    }
    return tab;
}

int ajout_tab(Point **tab, FILE* file, int li, int co) {
    int i,j;
    for (i=0; i<li; i++) {
        for (j=0; j<co; j++) {
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

void affiche_tab(Point **tab, int li, int co) {
    int i,j;
    for (i=0; i<li; i++) {
        for (j=0; j<co; j++) {
            printf("%d ", tab[i][j].metre);
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

int propagation_bas(Point **tab, int x, int y, int h, int inonde) {
    int res = 0;
    int mx = 0, my = 0;
    if (h<20) {
        mx = 800;
        my = 600;
    }else if (h<100){
        mx = 500;
        my = 500;
    }else if (h<180) {
        mx = 450;
        my = 450;
    }else{
        mx = 0;
        my = 0;
    }
    int i,j;
    for (i=x;i>mx;i--) {
        for(j=y;j>my;j--) {
            if ((tab[i][j].metre >= 0) && (tab[i][j].metre <= h) && (tab[i][j].estInonde == 0)) {
                // si on est au point de départ, pour éviter de tester tab i-1 et tab j-1
                if ((i == x) && (j == y)) {
                    tab[x][y].estInonde = inonde;
                    res=res+1;
                // si on est à la dernière ligne (on enlève les cas avec i+1)
                }else if ((i == LIGNES-1) && ((tab[i-1][j].estInonde > 0) || (tab[i][j-1].estInonde > 0) || (tab[i][j+1].estInonde > 0) || (tab[i-1][j-1].estInonde > 0) || (tab[i-1][j+1].estInonde > 0))) {
                    tab[i][j].estInonde = inonde;
                    res=res+1;
                // si on est à la dernière colonnes (on enlève les cas avec j+1)
                }else if ((j == COLONNES-1) && ((tab[i-1][j].estInonde > 0) || (tab[i][j-1].estInonde > 0) || (tab[i+1][j].estInonde > 0) || (tab[i+1][j-1].estInonde > 0) || (tab[i-1][j-1].estInonde > 0))) {
                    tab[i][j].estInonde = inonde;
                    res=res+1;
                // sinon
                }else if ((tab[i-1][j].estInonde > 0) || (tab[i][j-1].estInonde > 0) || (tab[i+1][j].estInonde > 0) || (tab[i][j+1].estInonde > 0) || (tab[i+1][j-1].estInonde > 0) || (tab[i+1][j+1].estInonde > 0) || (tab[i-1][j+1].estInonde > 0) || (tab[i-1][j-1].estInonde > 0)) {
                    tab[i][j].estInonde = inonde;
                    res=res+1;
                }
            }
        }
    }
    return res;
}

int propagation_haut(Point **tab,int x, int y, int h, int inonde) {
    int res = 0;
    int mx = 0, my = 0;
    if (h<20) {
        mx = 880;
        my = 600;
    }else if (h<100){
        mx = 880;
        my = 740;
    }else if (h<180) {
        mx = 880;
        my = 800;
    }else{
        mx = LIGNES-1;
        my = COLONNES-1;
    }
    int i,j;
    for (i=x;i<mx;i++) {
        for(j=y;j<my;j++) {
            if ((tab[i][j].metre >= 0) && (tab[i][j].metre <= h) && (tab[i][j].estInonde == 0)) {
                // si on est au point de départ, pour éviter de tester tab i+1 et tab j+1
                if ((i == x) && (j == y)) {
                    tab[x][y].estInonde = inonde;
                    res=res+1;
                // si on est à la première ligne (on enlève les cas avec i+1)
                }else if ((i == 0) && ((tab[i+1][j].estInonde > 0) || (tab[i][j-1].estInonde > 0) || (tab[i][j+1].estInonde > 0) || (tab[i+1][j-1].estInonde > 0) || (tab[i+1][j+1].estInonde > 0))) {
                    tab[i][j].estInonde = inonde;
                    res=res+1;
                // si on est à la première colonnes (on enlève les cas avec j+1)
                }else if ((j == 0) && ((tab[i-1][j].estInonde > 0) || (tab[i][j+1].estInonde > 0) || (tab[i+1][j].estInonde > 0) || (tab[i+1][j+1].estInonde > 0) || (tab[i-1][j+1].estInonde > 0))) {
                    tab[i][j].estInonde = inonde;
                    res=res+1;
                // sinon
                }else if ((tab[i-1][j].estInonde >0 ) || (tab[i][j-1].estInonde > 0) || (tab[i+1][j].estInonde > 0) || (tab[i][j+1].estInonde > 0) || (tab[i+1][j-1].estInonde > 0) || (tab[i+1][j+1].estInonde > 0) || (tab[i-1][j+1].estInonde > 0) || (tab[i-1][j-1].estInonde > 0)) {
                    tab[i][j].estInonde = inonde;
                    res=res+1;
                }
            }
        }
    }
    return res;
}

void super_propa(Point **tab, int li, int co, int dx, int dy, int fx, int fy, int h, int inonde) { // mettre inonde à 1 si c'est pour la mer, 2 si c'est pour la propagation
    int a = 1;
    int b = 1;
    do {
        if (a > 0) a = propagation_haut(tab, dx, dy, h, inonde);
        if (b > 0) b = propagation_bas(tab, fx, fy, h, inonde);
    } while ((a > 0) || (b > 0));
}


/*void propagation_r(Point **tab, int li, int co, int x, int y) {
    if((x>=0)&&(x<li)&&(y>=0)&&(y<co)&&(tab[x][y].metre == 0)&&(tab[x][y].estInonde == 0)) {
        tab[x][y].estInonde = 1;
        propagation_r(tab,li,co,x+1,y);
        propagation_r(tab,li,co,x,y+1);
        propagation_r(tab,li,co,x-1,y);
        propagation_r(tab,li,co,x,y-1);
    }
}*/

Point** chargement() {
    FILE *fichier = NULL;
    Point **tab;

    if ((tab = alloue(LIGNES, COLONNES)) == NULL ) { // allocation mémoire de tab[x][y]
        printf("\aErreur d'allocation mémoire dans chargement\n");  // si il y a eu une erreur on est rentré dans le if
        exit(EXIT_FAILURE);
    }

    if ((fichier = fopen("1000m.ASC", "r")) == NULL) { // ouverture du fichier en mode lecture seule
        printf("\aErreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if(ajout_tab(tab, fichier, LIGNES, COLONNES) == 0) {
        printf("\aErreur dans l'ajout des donnees du fichier a tab\n");
        exit(EXIT_FAILURE);
    }

    super_propa(tab, LIGNES, COLONNES, 0, 0, LIGNES-1 , COLONNES-1, 0, 1);
    super_propa(tab, LIGNES, COLONNES, 0, 0, LIGNES-1 , COLONNES-1, 80, 2); //celui là on l'enleverra et on le mettra dans un fichier qui prend en compte l'altitude d'inondation qu'on choisit

    fclose(fichier);
    return tab;
}
