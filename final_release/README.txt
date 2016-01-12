Inondation 1.0
Développeurs : Génaux Luc, Pfister Thomas, Efstathiou, Malbois Fabien

//////////A LIRE AVANT UTILISATION\\\\\\\\\\

Librairies utilisées:
SDL 1.2
SDL_gfx
SDL_ttf

Avant utilisation, veuillez changer les valeurs des variables REP_75 et REP_5 dans le fichier module.h en mettant
le chemin d'accès aux fichiers .asc des récolustions 75m et 5m. De plus, veuillez vérifier que la corse est dans
les fichiers 75m.

Le fichier .asc de la récolution 1000m doit être dans le dossier du programme.

Exemple de compilation : gcc -o prog main.c partie1.c partie2.c propagation.c bouton.c -lSDL -lSDLmain -lSDL_ttf -lSDL_gfx -lpthread

//////////\\\\\\\\\\
