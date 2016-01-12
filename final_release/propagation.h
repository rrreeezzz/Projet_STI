#ifndef H_PROPAGATION
#define H_PROPAGATION

#include "module.h"

extern void init_propa();

extern int propagation_bas(int x, int y, int h, int inonde);

extern int propagation_haut(int x, int y, int h, int inonde);

extern void super_propa(int dx, int dy, int fx, int fy, int h, int inonde);

extern void score_haut(int *tab);

extern void score_bas(int *tab);

extern int scoring();

extern void cadre(int *tab);

extern void submersion_haut(int x, int y, int h, int inonde);

extern int propa_submer(int x, int y, int h, int inonde);

extern void super_propa_submer(int x, int y, int h, int inonde);

extern void submersion_bas(int x, int y, int h, int inonde);

extern void mega_propa_submer(int dx, int dy, int fx, int fy, int h, int inonde);

#endif // H_PROPAGATION

