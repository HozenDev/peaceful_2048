#ifndef menu_2048
#define menu_2048

#include "biblio.h"
#include "const.h"
#include "struct.h"

int menu(SDL_Surface * screen, char * str, int transitions); // Dynamic Menu
void controles(SDL_Surface * screen); // Controles
void intro_game(SDL_Surface * screen, SDL_Surface * bg); // Intro

#endif
