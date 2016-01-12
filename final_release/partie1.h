#ifndef H_PARTIE1
#define H_PARTIE1

#include <stdio.h>
#include <stdlib.h>
#include "module.h"

extern void libere();

extern void alloue();

extern int ajout_tab(FILE* file, int type);

extern void chargement();

extern void affiche_tab(Point ** tab);

#endif // H_PARTIE1

