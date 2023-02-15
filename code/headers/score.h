#ifndef score_2048
#define score_2048

#include "biblio.h"
#include "const.h"
#include "struct.h"

int score_load(SDL_Surface * screen, SDL_Surface * bg, unsigned long int score); // now score load
int score_max_load(SDL_Surface * screen, SDL_Surface * bg, int mdj); // score max of a
int score_max_save(int mdj, unsigned long int score); //print in score file
int score_delete(SDL_Surface * screen, SDL_Surface * bg, unsigned long int score); //delete score

#endif
