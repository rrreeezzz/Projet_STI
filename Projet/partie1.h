#ifndef H_PARTIE1
#define H_PARTIE1

#include "module.h"

extern void libere(Point **tab, int li);

extern void alloue(Point **tab, int li, int co);

extern int ajout_tab(Point **tab, FILE* file, int li, int co);

extern void affiche_tab(Point **tab, int li, int co);

extern int valMax_tab(Point **tab, int li, int co);

#endif // H_PARTIE1
