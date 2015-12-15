#include "propagation.h"

void init_propa(Point **tab) {
    int i,j;
    for (i=0; i<LIGNES; i++) {
        for (j=0; j<COLONNES; j++) {
            if (tab[i][j].estInonde == 2)
                tab[i][j].estInonde = 0;
        }
    }
}

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
                }else if ((i == 0) && ((tab[i+1][j].estInonde > 0) || (tab[i][j-1].estInonde > 0) || (tab[i][j+1].estInonde > 0))) {
                    tab[i][j].estInonde = inonde;
                    res=res+1;
                // si on est à la première colonnes (on enlève les cas avec j+1)
                }else if ((j == 0) && ((tab[i-1][j].estInonde > 0) || (tab[i][j+1].estInonde > 0) || (tab[i+1][j].estInonde > 0))) {
                    tab[i][j].estInonde = inonde;
                    res=res+1;
                // sinon
                }else if ((tab[i-1][j].estInonde >0 ) || (tab[i][j-1].estInonde > 0) || (tab[i+1][j].estInonde > 0) || (tab[i][j+1].estInonde > 0)) {
                    tab[i][j].estInonde = inonde;
                    res=res+1;
                }
            }
        }
    }
    return res;
}

void super_propa(Point **tab, int dx, int dy, int fx, int fy, int h, int inonde) { // mettre inonde à 1 si c'est pour la mer, 2 si c'est pour la propagation
    int a = 1;
    int b = 1;
    do {
        if (a > 0) a = propagation_haut(tab, dx, dy, h, inonde);
        if (b > 0) b = propagation_bas(tab, fx, fy, h, inonde);
    } while ((a > 0) || (b > 0));
}


/*
int submersion_haut(Point **tab,int x, int y, int h, int inonde) {
    int res = 0;
    int i,j;
    for (i=x;i<860;i++) {
        for(j=y;j<600;j++) {
            if ((tab[i][j].estInonde == 0) && (tab[i][j].metre > 0) && (tab[i][j].metre <= h+3)) {
                if (((tab[i+1][j].estInonde > 0) && (tab[i+1][j].estInonde < inonde)) || ((tab[i][j+1].estInonde > 0) && (tab[i][j+1].estInonde < inonde)) || ((tab[i-1][j].estInonde > 0) && (tab[i-1][j].estInonde < inonde)) || ((tab[i][j-1].estInonde > 0) && (tab[i][j-1].estInonde < inonde))) {
                    if ((tab[i+1][j].estInonde == 0) && (tab[i+1][j].metre < h+3)) {
                        tab[i+1][j].estInonde = inonde;
                        super_propa_submer(tab, i+1, j, h, inonde);
                    }else if ((tab[i][j+1].estInonde == 0) && (tab[i][j+1].metre < h+3)) {
                        tab[i][j+1].estInonde = inonde;
                        super_propa_submer(tab, i, j+1, h, inonde);
                    }else if ((tab[i-1][j].estInonde == 0) && (tab[i-1][j].metre < h+3)) {
                        tab[i-1][j].estInonde = inonde;
                        super_propa_submer(tab, i-1, j, h, inonde);
                    }else if ((tab[i][j-1].estInonde == 0) && (tab[i][j-1].metre < h+3)) {
                        tab[i][j-1].estInonde = inonde;
                        super_propa_submer(tab, i, j-1, h, inonde);
                    }
                }
            }
        }
    }
    return res;
}

int propa_submer(Point **tab, int x, int y, int h, int inonde) {
    int res = 0;
    int i,j;
    for (i=x-10;i<x+10;i++) {
        for(j=y-10;j<y+10;j++) {
            if ((tab[i][j].metre >= 0) && (tab[i][j].metre < h+3) && (tab[i][j].estInonde == 0)) {
                if ((tab[i-1][j].estInonde == inonde) || (tab[i][j-1].estInonde == inonde) || (tab[i+1][j].estInonde == inonde) || (tab[i][j+1].estInonde == inonde)) {
                    tab[i][j].estInonde = inonde;
                    res=res+1;
                }
            }
        }
    }
    return res;
}

void super_propa_submer(Point **tab, int x, int y, int h, int inonde) {
    int a = 1;
    do {
        a = propa_submer(tab, x, y, h, inonde);
    } while (a != 0);
}
*/
