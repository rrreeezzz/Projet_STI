#ifndef H_PARTIE1
#define H_PARTIE1

#include <stdio.h>
#include <stdlib.h>
#include "module.h"

extern void libere(Point **tab, int li);

extern Point** alloue(int li, int co);

extern int ajout_tab(Point **tab, FILE* file, int li, int co);

extern void affiche_tab(Point **tab, int li, int co);

extern int valMax_tab(Point **tab, int li, int co);

extern int propagation_bas(Point **tab, int x, int y, int h, int inonde);

extern int propagation_haut(Point **tab, int x, int y, int h, int inonde);

extern void super_propa(Point **tab, int li, int co, int dx, int dy, int fx, int fy, int h, int inonde);

extern Point** chargement();

#endif // H_PARTIE1

