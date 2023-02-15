#include "../headers/move.h"

void droit(Map * m) // Déplacement Droit
{
  int i, j, k;

  //afficheTab(m->schema, 4);

  int compteur = 0;
  int val_case = 0;
  
  for (i = 0; i < m->w; ++i) {

    //////// COUVRE LES 0 /////////////////
    
    for (j = m->h-2; j >= 0; --j) {

      if (m->schema[j][i] != 0) {      
      
	for (k = j+1; k < m->h; ++k) {
	  if (m->schema[k][i] != 0) {
	    break;
	  }
	  compteur++;
	}
	if (compteur != 0) {
	  m->schema[j+compteur][i] = m->schema[j][i];
	  m->schema[j][i] = 0;
	}
	compteur = 0;
      }
    }

    /////////// ADDITION //////////////////
    
    for (j = m->h-2; j >= 0; --j) {

      if (m->schema[j][i] != 0 && m->schema[j][i] == m->schema[j+1][i]) {
	val_case = m->schema[j][i];
	m->score += m->t->props[val_case].value*2;
	m->schema[j+1][i] += 1;
	m->schema[j][i] = 0;
      }
    }

    //////// COUVRE LES 0 /////////////////
    
    for (j = m->h-2; j >= 0; --j) {

      if (m->schema[j][i] != 0) {      
      
	for (k = j+1; k < m->h; ++k) {
	  if (m->schema[k][i] != 0) {
	    break;
	  }
	  compteur++;
	}
	if (compteur != 0) {
	  m->schema[j+compteur][i] = m->schema[j][i];
	  m->schema[j][i] = 0;
	}
	compteur = 0;
      }
    } 
  }
}

void gauche(Map * m) // Déplacement Gauche
{
  int i;
  for (i = 0; i < 2; ++i) {
    rota_droite(m->schema, m->w);
  }

  droit(m);

  for (i = 0; i < 2; ++i) {
    rota_droite(m->schema, m->w);
  }
}

void haut(Map * m) // Déplacement Haut
{
  int i;
  for (i = 0; i < 3; ++i) {
    rota_droite(m->schema, m->w);
  }

  droit(m);

  for (i = 0; i < 1; ++i) {
    rota_droite(m->schema, m->w);
  }
}

void bas(Map * m) // Déplacement Bas
{
  int i;
  for (i = 0; i < 1; ++i) {
    rota_droite(m->schema, m->w);
  }

  droit(m);
  
  for (i = 0; i < 3; ++i) {
    rota_droite(m->schema, m->w);
  }
}

////////////////////////////////////////////

void rota_droite(char ** schema, int n) // Rota 90° à droite du tableau 2D
{
  int i, j;

  char sauv;
  
  for (i = 0; i < n; ++i) {
    for (j = i; j < n; ++j) {
      sauv = schema[i][j];
      schema[i][j] = schema[j][i];
      schema[j][i] = sauv;
    }
  }
  
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n/2; ++j) {
      sauv = schema[i][j];
      schema[i][j] = schema[i][n-1-j];
      schema[i][n-1-j] = sauv;
    }
  }
}

////////////////////////////////////////////

int random_pop_up(Map * m) // ajoute un 2 ou 4 apres un coup
{
  int i, j;

  int compteur = 0;
  
  int * X = malloc(sizeof(int) * m->w * m->h);
  int * Y = malloc(sizeof(int) * m->h * m->h);
  
  for (i = 0; i < m->w; ++i) {
    for (j = 0; j < m->h; ++j) {

      if (m->schema[i][j] == 0) {

	X[compteur] = i;
	Y[compteur] = j;
	compteur++;
	
      }
      
    }
  }

  if (compteur == 0) {
    fprintf(stdout, "Error in RandomPopUp : No 0 in tab\n");
    return 1;
  }
  
  int r = rand()%compteur;

  int value = rand()%2+1;

  //printf("%d %d\n", compteur, r);

  m->schema[X[r]][Y[r]] = value;
  
  free(X);
  free(Y);

  return 0;
}
