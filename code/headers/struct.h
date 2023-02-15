#ifndef structures_2048
#define structures_2048

#include "biblio.h"
#include "const.h"

typedef struct {

  SDL_Rect R;
  int plein;
  int value;
  
}TileProp; // Structure de propriété de tile

typedef struct {
  
  int w; //number of column 
  int h; //number of line

  int res; //résolution d'une tile

  SDL_Surface * im; // image du tileset
  
  TileProp * props; //tableau de tiles -> propriétés de cahque tile
  
}Tileset; // Tileset

typedef struct {

  Tileset * t; //tileset

  int w; // weight
  int h; //height

  char ** schema; // schema of map

  unsigned long int score; //score of currently map
  
}Map; // Map

#endif
