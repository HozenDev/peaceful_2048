#include "../headers/tab.h"

void affiche_tab(char ** tab, int n) // affiche un tableau 2D
{
  int i, j;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      printf("%3d", tab[j][i]);
    }
    printf("\n");
  }
}

char ** copie_tab(char ** src, int n) // copie source et renvoie la tableau copié
{
  char ** t = NULL;
  t = malloc(sizeof(char *) * n);

  int i;
  
  for (i = 0; i < n; ++i) {
    t[i] = malloc(sizeof(char) * n);
  }

  int j;

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {

      t[i][j] = src[i][j];
      
    }
  }

  return t;
}

int tab_cmp(char ** t1, char ** t2, int n) // renvoie vrai si tableau différent
{
  int i, j;

  //  int same = 0;
  
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {

      if (t1[i][j] != t2[i][j]) {
	return 1;
      } 
    }
  }

  return 0;
}

void free_tab_2D(char ** t, int n)
{
  if (t == NULL) {
    fprintf(stdout, "Free : Tab at NULL\n");
    return;
  }

  int i;

  for (i = 0; i < n; ++i) {
    if (t[i] == NULL) {
      continue;
    }    
    free(t[i]);
    t[i]=NULL;
  }

  free(t);
  t=NULL;
}
