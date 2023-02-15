#ifndef move_2048
#define move_2048

#include "biblio.h"
#include "const.h"
#include "struct.h"

void droit(Map * m); // Déplacement Droite
void gauche(Map * m); // Déplacement Gauche
void haut(Map * m); // Déplacement Haut
void bas(Map * m); // Déplacement Bas

void rota_droite(char ** schema, int n); // Rota 90° à droite du tableau 2D

int random_pop_up(Map * m); // ajoute un 2 ou 4 apres un coup

#endif
