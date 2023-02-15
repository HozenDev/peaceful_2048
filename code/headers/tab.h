#ifndef tab_2D_char_2048
#define tab_2D_char_2048

#include "biblio.h"
#include "const.h"
#include "struct.h"

void affiche_tab(char ** tab, int n); // affiche un tableau 2D
int tab_cmp(char ** t1, char ** t2, int n); // renvoie vrai si tableau différent
char ** copie_tab(char ** src, int n); // copie source et renvoie la tableau copié
void free_tab_2D(char ** t, int n); // free 2D char * tab

#endif
