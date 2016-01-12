#include "propagation.h"
#include "partie2.h"

void init_propa() {
    int i,j;
    for (i=0; i<LIGNES; i++) {
        for (j=0; j<COLONNES; j++) {
            if (data_1000->pt_tab[i][j].estInonde > 1)
                data_1000->pt_tab[i][j].estInonde = 0;
	    if (data_1000->pt_tab[i][j].cadre == 1)
		data_1000->pt_tab[i][j].cadre = 0;
        }
    }
}

int propagation_bas(int x, int y, int h, int inonde) {
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
            if ((data_1000->pt_tab[i][j].metre >= 0) && (data_1000->pt_tab[i][j].metre <= h) && (data_1000->pt_tab[i][j].estInonde == 0)) {
                // si on est au point de départ, pour éviter de tester data_1000->pt_tab i-1 et data_1000->pt_tab j-1
                if ((i == x) && (j == y)) {
                    data_1000->pt_tab[x][y].estInonde = inonde;
                    res=res+1;
                // si on est à la dernière ligne (on enlève les cas avec i+1)
                }else if ((i == LIGNES-1) && ((data_1000->pt_tab[i-1][j].estInonde > 0) || (data_1000->pt_tab[i][j-1].estInonde > 0) || (data_1000->pt_tab[i][j+1].estInonde > 0) || (data_1000->pt_tab[i-1][j-1].estInonde > 0) || (data_1000->pt_tab[i-1][j+1].estInonde > 0))) {
                    data_1000->pt_tab[i][j].estInonde = inonde;
                    res=res+1;
                // si on est à la dernière colonnes (on enlève les cas avec j+1)
                }else if ((j == COLONNES-1) && ((data_1000->pt_tab[i-1][j].estInonde > 0) || (data_1000->pt_tab[i][j-1].estInonde > 0) || (data_1000->pt_tab[i+1][j].estInonde > 0) || (data_1000->pt_tab[i+1][j-1].estInonde > 0) || (data_1000->pt_tab[i-1][j-1].estInonde > 0))) {
                    data_1000->pt_tab[i][j].estInonde = inonde;
                    res=res+1;
                // sinon
                }else if ((data_1000->pt_tab[i-1][j].estInonde > 0) || (data_1000->pt_tab[i][j-1].estInonde > 0) || (data_1000->pt_tab[i+1][j].estInonde > 0) || (data_1000->pt_tab[i][j+1].estInonde > 0) || (data_1000->pt_tab[i+1][j-1].estInonde > 0) || (data_1000->pt_tab[i+1][j+1].estInonde > 0) || (data_1000->pt_tab[i-1][j+1].estInonde > 0) || (data_1000->pt_tab[i-1][j-1].estInonde > 0)) {
                    data_1000->pt_tab[i][j].estInonde = inonde;
                    res=res+1;
                }
            }
        }
    }
    return res;
}

int propagation_haut(int x, int y, int h, int inonde) {
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
            if ((data_1000->pt_tab[i][j].metre >= 0) && (data_1000->pt_tab[i][j].metre <= h) && (data_1000->pt_tab[i][j].estInonde == 0)) {
                // si on est au point de départ, pour éviter de tester data_1000->pt_tab i+1 et data_1000->pt_tab j+1
                if ((i == x) && (j == y)) {
                    data_1000->pt_tab[x][y].estInonde = inonde;
                    res=res+1;
                // si on est à la première ligne (on enlève les cas avec i+1)
                }else if ((i == 0) && ((data_1000->pt_tab[i+1][j].estInonde > 0) || (data_1000->pt_tab[i][j-1].estInonde > 0) || (data_1000->pt_tab[i][j+1].estInonde > 0))) {
                    data_1000->pt_tab[i][j].estInonde = inonde;
                    res=res+1;
                // si on est à la première colonnes (on enlève les cas avec j+1)
                }else if ((j == 0) && ((data_1000->pt_tab[i-1][j].estInonde > 0) || (data_1000->pt_tab[i][j+1].estInonde > 0) || (data_1000->pt_tab[i+1][j].estInonde > 0))) {
                    data_1000->pt_tab[i][j].estInonde = inonde;
                    res=res+1;
                // sinon
                }else if ((data_1000->pt_tab[i-1][j].estInonde >0 ) || (data_1000->pt_tab[i][j-1].estInonde > 0) || (data_1000->pt_tab[i+1][j].estInonde > 0) || (data_1000->pt_tab[i][j+1].estInonde > 0)) {
                    data_1000->pt_tab[i][j].estInonde = inonde;
                    res=res+1;
                }
            }
        }
    }
    return res;
}

void super_propa(int dx, int dy, int fx, int fy, int h, int inonde) { // mettre inonde à 1 si c'est pour la mer, 2 si c'est pour la propagation
    int a = 1;
    int b = 1;
    do {
        if (a > 0) a = propagation_haut(dx, dy, h, inonde);
        if (b > 0) b = propagation_bas(fx, fy, h, inonde);
    } while ((a > 0) || (b > 0));
}


void score_haut(int *tab) {
  int score = 0;
  int max = 0;
  int i, j, k, l;

  for (i=1; i<800-1; i++) {
    for (j=20; j<600-1; j++) {
      for (k=i; k<i+25; k++) {
        for (l=j; l<j+25; l++) {
          if (data_1000->pt_tab[k][l].estInonde == 2) {
            score++;
          }
        }
      }
      if (score > max) {
        max = score;
        tab[0] = k; tab[1] = l; tab[2] = max;
      }
      score = 0;
    }
  }
printf("%d %d %d \n\n\n", tab[0], tab[1], tab[2]);
}

void score_bas(int *tab) {
  int score = 0;
  int max = 0;
  int i, j, k, l;

  for (i=LIGNES-28; i>800-1; i--) {
    for (j=COLONNES-28; j>600-1; j--) {
      for (k=i; k<i+25; k++) {
        for (l=j; l<j+25; l++) {
          if (data_1000->pt_tab[k][l].estInonde == 2) {
            score++;
          }
        }
      }
      if (score > max) {
        max = score;
        tab[3] = k; tab[4] = l; tab[5] = max;
      }
      score = 0;
    }
  }
printf("%d %d %d \n\n\n", tab[3], tab[4], tab[5]);
}

int scoring() {
  int tab[6];
  score_haut(tab);
  score_bas(tab);
  if(tab[2] > tab[5]) {
    cadre(tab);
  remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, 1000);
    zoom(tab[1]*DEZOOM_X_1000, tab[0]*DEZOOM_Y_1000, 1, 1000);
   return *tab;
  }else{
    cadre(tab+3);
    remplirFrance(data_1000->pt_tab,  data_1000->pt_surface, prog, 0, 0, 1000);
    zoom(tab[4]*DEZOOM_X_1000, tab[3]*DEZOOM_Y_1000, 1, 1000);
    return *(tab+3);
  }
}


void cadre(int *tab) {
  int i;
  for (i=tab[0]+1; i>tab[0]-26; i--)
    data_1000->pt_tab[i][tab[1]+1].cadre = 1;
  for (i=tab[1]+1; i>tab[1]-26; i--)
    data_1000->pt_tab[tab[0]+1][i].cadre = 1;
  for (i=tab[0]+1; i>tab[0]-26; i--)
    data_1000->pt_tab[i][tab[1]-26].cadre = 1;
  for (i=tab[1]+1; i>tab[1]-26; i--)
    data_1000->pt_tab[tab[0]-26][i].cadre = 1;
}


void submersion_haut(int x, int y, int h, int inonde) {
    int i,j;
    for (i=x;i<1000;i++) {
        for(j=y;j<600;j++) {
            if ((data_1000->pt_tab[i][j].estInonde == 0) && (data_1000->pt_tab[i][j].metre > 0) && (data_1000->pt_tab[i][j].metre < h)) {
                if (((data_1000->pt_tab[i+1][j].estInonde > 0) && (data_1000->pt_tab[i+1][j].estInonde < inonde)) || ((data_1000->pt_tab[i][j+1].estInonde > 0) && (data_1000->pt_tab[i][j+1].estInonde < inonde)) || ((data_1000->pt_tab[i-1][j].estInonde > 0) && (data_1000->pt_tab[i-1][j].estInonde < inonde)) || ((data_1000->pt_tab[i][j-1].estInonde > 0) && (data_1000->pt_tab[i][j-1].estInonde < inonde))) {
                    data_1000->pt_tab[i][j].estInonde = inonde;
                    super_propa_submer(i, j, h, inonde);
                }
            }
        }
    }
}

int propa_submer(int x, int y, int h, int inonde) {
    int i,j;
    int v = h;
    for (i=x-10;i<x+10;i++) {
        for(j=y-10;j<y+10;j++) {
            if ((v>0) && (data_1000->pt_tab[i][j].metre >= 0) && (data_1000->pt_tab[i][j].metre <= v) && (data_1000->pt_tab[i][j].estInonde == 0)) {
                if ((data_1000->pt_tab[i-1][j].estInonde == inonde) || (data_1000->pt_tab[i][j-1].estInonde == inonde) || (data_1000->pt_tab[i+1][j].estInonde == inonde) || (data_1000->pt_tab[i][j+1].estInonde == inonde)) {
                    data_1000->pt_tab[i][j].estInonde = inonde;
                    v-=2;
                }
            }
        }
    }
    v--;
    return v;
}

void super_propa_submer(int x, int y, int h, int inonde) {
    int a = h;
    while (a > 0) {
        a = propa_submer(x, y, a, inonde);
    }
}


void submersion_bas(int x, int y, int h, int inonde) {
    int i,j;
    for (i=x;i>800;i--) {
        for(j=y;j>600;j--) {
            if ((data_1000->pt_tab[i][j].estInonde == 0) && (data_1000->pt_tab[i][j].metre > 0) && (data_1000->pt_tab[i][j].metre < h)) {
                if (((data_1000->pt_tab[i+1][j].estInonde > 0) && (data_1000->pt_tab[i+1][j].estInonde < inonde)) || ((data_1000->pt_tab[i][j+1].estInonde > 0) && (data_1000->pt_tab[i][j+1].estInonde < inonde)) || ((data_1000->pt_tab[i-1][j].estInonde > 0) && (data_1000->pt_tab[i-1][j].estInonde < inonde)) || ((data_1000->pt_tab[i][j-1].estInonde > 0) && (data_1000->pt_tab[i][j-1].estInonde < inonde))) {
                    data_1000->pt_tab[i][j].estInonde = inonde;
                    super_propa_submer(i, j, h, inonde);
                }
            }
        }
    }
}


void mega_propa_submer(int dx, int dy, int fx, int fy, int h, int inonde) {
    submersion_haut(dx, dy, h, inonde);
    submersion_bas(fx, fy, h, inonde);
}
