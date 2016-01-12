#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "partie1.h"
#include "partie2.h"
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>

int main(int argc, char *argv[]) {

    chargement();

    sdl_ini();

    libere();

    return EXIT_SUCCESS;
}

