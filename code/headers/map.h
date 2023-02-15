#ifndef map_2048
#define map_2048

#include "biblio.h"
#include "struct.h"
#include "const.h"

// SDL Fonctions

Tileset * load_tileset(FILE * fmap); // Charge un tileset
Map * load_map(char * map_fn); // Charge une map SDL
void print_map(Map * m, SDL_Surface * screen); // Actualise la map SDL
void free_map(Map * map); // libère une map

#endif
