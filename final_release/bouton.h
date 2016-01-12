#ifndef H_BOUTON
#define H_BOUTON

#include "module.h"

extern Bouton *CreerBouton(int positionX, int positionY, char *pathImage);

extern void init_bouton();

extern void DetruireBouton();

extern int Check(Bouton *UnBouton, int sourisX, int sourisY);

extern void choice(int c);

#endif
