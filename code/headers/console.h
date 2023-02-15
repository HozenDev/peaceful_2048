#ifndef console_2048
#define console_2048

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define N 4 // taille de la grille 4*4 par default


int ** initTab2D();
void afficheGrille(int **);
void copieGrille(int ** , int ** );
void freeTab2D(int ** );
int compareGrille(int **, int **);  // retorun 1 si different


void remplieAleatoirement(int ** );
int contient2048(int ** ); // retourn 1 si fini sinon 0
int bloquer(int **); // renvoie 1 si plus de coup possible



void deplacementDroitCaseVide(int **);
void rotaD(int **); // rota de 90° vers la droite


int deplacementDroite(int ** );
int deplacementGauche(int **);
int deplacementHaut(int **);
int deplacementBas(int **);


void start();
char saisieLettre();
unsigned long int recupScoreMax();
void ecritScore(unsigned long int );
int jeu(int **, int ** );

int main_console(void);

#endif
