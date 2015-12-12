#ifndef H_PARTIE1
#define H_PARTIE1

#include <stdio.h>
#include <stdlib.h>
#include "module.h"

extern void libere(Point **tab, int y);

extern Point** alloue();

extern int ajout_tab(Point **tab, FILE* file);

extern Point** chargement();

#endif // H_PARTIE1

