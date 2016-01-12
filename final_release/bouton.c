#include "bouton.h"


Bouton *CreerBouton (int positionX, int positionY, char *pathImage) {
    SDL_Surface *Temporaire = SDL_LoadBMP(pathImage);
    if (Temporaire == NULL)
    {
        fprintf(stderr, "Erreur lors de la creation d'un bouton : %s.\n", SDL_GetError());
        return NULL;
    }

    if (positionX<0 || 1600<positionX || positionY<0 || 800<positionY)
    {
        if (positionX<0 || 1600<positionX)
            fprintf(stderr, "Erreur lors de la creation d'un bouton : Dimension positionX non valide\n");

        if (positionY<0 || 800<positionY)
            fprintf(stderr, "Erreur lors de la creation d'un bouton : Dimension positionY non valide\n");

        return NULL;
    }
    /* Ici, tout est bon, on peut creer le bouton */
    Bouton *UnBouton = (Bouton*) malloc (sizeof(Bouton));

    UnBouton->image = SDL_DisplayFormat(Temporaire);
    SDL_FreeSurface(Temporaire);

    SDL_Rect pos;
    pos.x = positionX;
    pos.y = positionY;
    UnBouton->position = pos;

    return UnBouton;
}

void init_bouton() {
   btn[0] = CreerBouton(900, 40, "data/images/1fichier1000.bmp");
   btn[1] = CreerBouton(900, 40, "data/images/fichier1000.bmp");
   btn[2] = CreerBouton(1100, 40, "data/images/1fichier75.bmp");
   btn[3] = CreerBouton(1100, 40, "data/images/fichier75.bmp");
   btn[4] = CreerBouton(1300, 40, "data/images/1fichier5.bmp");
   btn[5] = CreerBouton(1300, 40, "data/images/fichier5.bmp");
   btn[6] = CreerBouton(1100, 160, "data/images/12.bmp");
   btn[7] = CreerBouton(1100, 160, "data/images/2.bmp");
   btn[8] = CreerBouton(1200, 160, "data/images/14.bmp");
   btn[9] = CreerBouton(1200, 160, "data/images/4.bmp");
   btn[10] = CreerBouton(1300, 160, "data/images/16.bmp");
   btn[11] = CreerBouton(1300, 160, "data/images/6.bmp");
   btn[12] = CreerBouton(1400, 160, "data/images/18.bmp");
   btn[13] = CreerBouton(1400, 160, "data/images/8.bmp");
   btn[14] = CreerBouton(900, 280, "data/images/1scoring.bmp");
   btn[15] = CreerBouton(900, 280, "data/images/scoring.bmp");
   btn[16] = CreerBouton(1050, 280, "data/images/1faible.bmp");
   btn[17] = CreerBouton(1050, 280, "data/images/faible.bmp");
   btn[18] = CreerBouton(1250, 280, "data/images/1forte.bmp");
   btn[19] = CreerBouton(1250, 280, "data/images/forte.bmp");
   btn[20] = CreerBouton(1100, 40, "data/images/charg75.bmp");
   btn[21] = CreerBouton(1300, 40, "data/images/charg5.bmp");
   btn[22] = CreerBouton(900, 150, "data/images/1s46.bmp");
   btn[23] = CreerBouton(900, 150, "data/images/s46.bmp");
   btn[24] = CreerBouton(900, 200, "data/images/1s65.bmp");
   btn[25] = CreerBouton(900, 200, "data/images/s65.bmp");
   btn[26] = CreerBouton(1100, 210, "data/images/12.bmp");
   btn[27] = CreerBouton(1100, 210, "data/images/2.bmp");
   btn[28] = CreerBouton(1200, 210, "data/images/14.bmp");
   btn[29] = CreerBouton(1200, 210, "data/images/4.bmp");
   btn[30] = CreerBouton(1300, 210, "data/images/16.bmp");
   btn[31] = CreerBouton(1300, 210, "data/images/6.bmp");
   btn[32] = CreerBouton(1400, 210, "data/images/18.bmp");
   btn[33] = CreerBouton(1400, 210, "data/images/8.bmp");




 int i;
 SDL_BlitSurface(btn[0]->image, NULL, prog, &(btn[0]->position));
 for (i=6; i<20; i+=2)
   SDL_BlitSurface(btn[i]->image, NULL, prog, &(btn[i]->position));
 for (i=22; i<33; i+=2)
   SDL_BlitSurface(btn[i]->image, NULL, prog, &(btn[i]->position));
 SDL_BlitSurface(btn[20]->image, NULL, prog, &(btn[20]->position));
 SDL_BlitSurface(btn[21]->image, NULL, prog, &(btn[21]->position));



}

void DetruireBouton () {
    int i;
    for (i=0; i<33; i++) {
      SDL_FreeSurface(btn[i]->image);
    }
}


/* Fonction permettant de savoir si on a cliquer sur le Bouton
    renvoi le resultat sous forme de booleen */
int Check (Bouton *UnBouton, int sourisX, int sourisY) {
   if (sourisX >= UnBouton->position.x && sourisX <= (UnBouton->position.x+UnBouton->image->w) && sourisY >= UnBouton->position.y && sourisY <= (UnBouton->position.y+UnBouton->image->h))
      return 1;
   return 0;
}

void choice(int c) {
   int i;
   if (c < 3) {
     for (i=0; i<16; i++)
       chx[i] = 0;
     chx[c] = 1;
   }else if (c < 7) {
     for (i=3; i<10; i++)
       chx[i] = 0;
     chx[c] = 1;
   }else if (c == 7) {
     chx[8] = 0; chx[9] = 0;
     chx[c] = 1;
   }else if (c <10) {
     chx[7] = 0; chx[8] = 0; chx[9] = 0;
     chx[c] = 1;
  }else if (c < 14) {
    for (i=10; i<14; i++)
      chx[i] = 0;
    chx[c] = 1;
    chx[7] = 0; chx[8] = 0; chx[9] = 0;
  }else{
    for (i=3; i<16; i++)
      chx[i] = 0;
    chx[c] = 1;
  }
}
