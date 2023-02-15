#ifndef game_over_2048
#define game_over_2048

#include "biblio.h"
#include "const.h"
#include "struct.h"

// Win / Lose

int lose(Map * m); // si le tableau ne possède plus de coup possible
int win(Map * m); // si le tableau possède un 2048

#endif
