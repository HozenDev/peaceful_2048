#include "../headers/save.h"

int charge_sauv(Map * m, char * name, int mdj)
{
  FILE * f = fopen(name, "r");

  if (f == NULL) {
    fprintf(stdout, "Save file not found\n");
    return -1;  
  }

  rewind(f);
  
  int i, j;

  int num;

  int mdj_save;

  fscanf(f, "#save %d\n", &mdj_save);

  if (mdj != -1 && mdj_save != mdj) {
    fprintf(stdout, "Chargement impossible : %d x %d et jeu en %d x %d \n", mdj_save, mdj_save, m->w, m->w);
    fclose(f);
    return -1;
  }
  
  for (i = 0; i < m->w; ++i) {
    for (j = 0; j < m->h; ++j) {
      fscanf(f, "%d", &num);
      m->schema[i][j] = num;
    }
    fscanf(f, "\n");
  }

  fscanf(f, "score : %ld\n", &m->score);
  
  fprintf(stdout, "Sauvegarde Chargée\n");

  fclose(f);
  
  return mdj_save;
}

int sauv(Map * m, char * name, int mdj)
{
  FILE * f = fopen(name, "w+");

  if (f == NULL) {
    fprintf(stdout, "Error : impossble d'ouvrir le fichier de sauvegarde");
    return 1;
  }

  rewind(f);
  
  fprintf(f, "#save %d\n", mdj);

  int i, j;
  
  for (i = 0; i < m->w; ++i) {
    for (j = 0; j < m->h; ++j) {
      fprintf(f, "%d ", m->schema[i][j]);
    }
    fprintf(f, "\n");
  }
  
  fprintf(f, "score : %ld\n", m->score);

  fclose(f);

  fprintf(stdout, "Partie Sauvegardée\n");
  
  return 0;
}
