#ifndef H_PROPAGATION
#define H_PROPAGATION

#include "module.h"

extern void init_propa(Point **tab);

extern int propagation_bas(Point **tab, int x, int y, int h, int inonde);

extern int propagation_haut(Point **tab,int x, int y, int h, int inonde);

extern void super_propa(Point **tab, int dx, int dy, int fx, int fy, int h, int inonde);

#endif // H_PROPAGATION


