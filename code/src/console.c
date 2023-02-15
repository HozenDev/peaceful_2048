#include "../headers/console.h"

int ** initTab2D()
{
  int ** tab = NULL;
  tab = malloc(N*sizeof(int *));
  if(tab == NULL)
    {
      return NULL;
    }

  int i = 0; int j =0;
  for(i=0; i<N; i++)
    {
      tab[i] = (int *) calloc(N,sizeof(int));
      if(tab[i] == NULL)
	{
	  for(j=0; j<i; j++)
	    {
	      free(tab[j]);
	    }
	  return NULL;
	}
    }
  return tab;
}

void afficheGrille(int ** tab)
{
  int i = 0 ; int j = 0;

  for(i=0; i<N; i++)
    {
      for(j=0; j<N; j++)
	{
	  printf("|%8d  ", tab[i][j]);
	}
      printf("|\n");
    }
  printf("\n");
}

void remplieAleatoirement(int ** tab)
{
  int i = 0; int j = 0; int reussi = 0; int val = 0;

  while( !(reussi) )
    {
      i = rand()%N;
      j = rand()%N;
      if (tab[i][j] == 0)
	{
	  val = rand()%2;
	  if(val == 0)
	    {
	      val = 2; 
	    }
	  else
	    {
	      val = 4;
	    }
	  tab[i][j] = val;
	  reussi = 1;
	}
    }
}

void copieGrille(int ** tabDep , int ** tabArr)
{
  int i=0; int j =0;
  for(i=0; i<N; i++)
    {
      for(j=0; j<N; j++)
	{
	  tabArr[i][j] = tabDep[i][j];
	}
    }
}

void deplacementDroitCaseVide(int ** tab) //intermediare
{
  int i =0; int j =0; int deplacement = 0;
  while(!(deplacement))
    {
      deplacement = 1;
      for(i=0; i<N; i++)
	{
	  for(j=0; j<N-1; j++) // -1 car dernière colonne pas de deplacement à droite
	    {
	      if(tab[i][j] != 0 && tab[i][j+1] == 0)
		{
		  tab[i][j+1] = tab[i][j];
		  tab[i][j] = 0;
		  deplacement = 0;
		}
	    }
	}
    }
}

int deplacementDroite(int ** tab) // fonction finale de deplacement
{
  // gere les cases vides
  deplacementDroitCaseVide(tab);

  int i =0; int j =0; int score = 0;
  // même case cote à cote
  for(i=0; i<N; i++)
    {
      for(j=N-1; j>0 ; j--)
	{
	  if(tab[i][j] == tab[i][j-1])
	    {
	      tab[i][j] *= 2;
	      score += tab[i][j];
	      tab[i][j-1] = 0;
	    }
	}
    }
  //re-decalle les nouvelles cases vides
  deplacementDroitCaseVide(tab);
  return score;
}

int contient2048(int ** tab) // retourn 1 si fini sinon 0
{
  int i = 0 ; int j = 0 ;

  for(i=0; i<N; i++)
    {
      for(j=0; j<N; j++)
	{
	  if(tab[i][j]==2048)
	    {
	      return 1;
	    }
	}
    }
  return 0;
}

void freeTab2D(int ** tab)
{
  if (tab != NULL)
    {
      int i = 0;
      for(i=0; i<N; i++)
	{
	  if(tab[i] != NULL)
	    {
	      free(tab[i]);
	      tab[i] = NULL;
	    }
	}
      free(tab); tab = NULL;
    }
}

void rotaD(int ** tab) // rota de 90° vers la droite
{
  int ** sauv = NULL;
  sauv = initTab2D();

  if(sauv == NULL)
    {
      perror("Probleme rotation, le jeu peu planter suite à un probleme d'allocation mémoire (plus de place certainement) ... Veuillez relancez le jeu s'il vous plaît \n");
    }

  copieGrille(tab, sauv);

  int i = 0; int j = 0;
  for (i = 0; i < N; i++) 
    {
      for (j = 0; j < N; j++) 
    	{
	  tab[i][j] = sauv[j][i];
    	}
    }

  int sauvInt = 0;

  for (i = 0; i < N; ++i) 
    {
      for (j = 0; j < N/2; ++j) 
    	{
	  sauvInt = tab[i][j];
	  tab[i][j] = tab[i][N-1-j];
	  tab[i][N-1-j] = sauvInt;
	}
    }
  freeTab2D(sauv);
}

int deplacementGauche(int ** tab)
{
  int i=0; int score =0;
  for (i = 0; i < 2; i++) 
    {
      rotaD(tab);
    }

  score += deplacementDroite(tab);

  for (i = 0; i < 2; i++)
    {
      rotaD(tab);
    }
  return score;
}

int deplacementBas(int ** tab)
{
  int i=0; int score = 0; 
  for (i = 0; i < 3; i++)
    {
      rotaD(tab);
    }

  score += deplacementDroite(tab);

  for (i = 0; i < 1; i++) 
    {
      rotaD(tab);
    }

  return score;
}

int deplacementHaut(int ** tab)
{
  int i=0 ; int score=0;
  for (i = 0; i < 1; i++) 
    {
      rotaD(tab);
    }

  score += deplacementDroite(tab);
  
  for (i = 0; i < 3; i++) 
    {
      rotaD(tab);
    }

  return score;
}

void start()
{
  printf("Vous venez de lancer un 2048 de taille %d*%d. \n\n\n", N,N);
  sleep(3);
  printf("Vous pouvez vous deplacer avec les touches : \n\t-'d' : pour se deplacer à droite, \n\t-'g' : pour se deplacer à gauche, \n\t-'h' : pour se deplacer en haut, \n\t-'b' : pour se deplacer en bas, \n\t-'r' : pour revenir une seule fois en arrière (non-cumulable).\n\n\n");
  sleep(5);

  printf("Le score maximum est de %ld.\n\n\n",recupScoreMax());
  sleep(2);
  printf("La partie commence dans : \n");
  printf("\t 3 sec. \n");
  sleep(1.5);
  printf("\t 2 sec. \n");
  sleep(1.5);
  printf("\t 1 sec. \n\n\n");
  sleep(1.5);
}

void vider_buf()	 			// vider le buffer pour éviter le bug des scanf
{
  int c; 
  do {
    c = getchar();
  } while(c != '\n' && c != EOF);
}

unsigned long int recupScoreMax()
{
  unsigned long int scoreMax = 0;

  FILE * fscore = NULL; int nbTrouve = 0;
  fscore = fopen("./data/score/score_4.txt", "r");
  if(fscore == NULL)
    {
      perror("Probleme recuperation score maximum");
      return 0;
    }
  nbTrouve = fscanf(fscore, "%ld", &scoreMax);
  if(nbTrouve != 1)
    {
      perror("Probleme lecture fichier scoreMax");
      fclose(fscore);
      return 0;
    }

  fclose(fscore);
  return scoreMax;
}

void ecritScore(unsigned long int score)
{
  FILE * fscore = NULL;
  fscore = fopen("./data/score/score_4.txt", "w+");
  if(fscore == NULL)
    {
      perror("Probleme sauvegarde score du à un probleme d'ouverture du fichier\n");
    }
  else
    {
      fprintf(fscore,"%ld", score);
    }
  fclose(fscore);
}

int contientZeros(int ** tab)
{
  int i=0; int j=0;

  for(i=0; i<N; i++)
    {
      for(j=0; j<N; j++)
	{
	  if(tab[i][j] == 0)
	    {
	      return 1;
	    }
	}
    }
  return 0;
}

char saisieLettre()
{
  char lettre;
  scanf(" %c",&lettre);
  vider_buf();

  while(lettre != 'd' && lettre != 'g' && lettre != 'h' && lettre !='b' && lettre != 'r')
    {
      printf("Saisie invalide, seulement les lettres ['d','g','h','b','r'] sont autorisées.\n\nVeuillez re-saisir votre choix : ");
      scanf(" %c", &lettre);
    }
  return lettre;
}

int compareGrille(int ** tab, int ** tabPrec) // retorun 1 si different
{
  int i = 0 ; int j = 0;
  for(i=0; i<N; i++)
    {
      for(j=0; j<N; j++)
	{
	  if (tab[i][j] != tabPrec[i][j] )
	    {
	      return 1;
	    }
	}
    }
  return 0;
}

int bloquer(int ** tab) // renvoie 1 si plus de coup possible
{
  if (contientZeros(tab) == 1)
    {
      return 0;
    }

  int ** sauv = NULL;
  sauv = initTab2D();
  if(sauv==NULL)
    {
      perror("Probleme allocation mémoire pour tester si grille complete");
    }

  copieGrille(tab, sauv);

  deplacementBas(sauv);
  if(compareGrille(sauv, tab) == 1)
    {
      freeTab2D(sauv);
      return 0;
    }

  deplacementGauche(sauv);
  if(compareGrille(sauv, tab) == 1)
    {

      freeTab2D(sauv);
      return 0;
    }

  deplacementHaut(sauv);
  if(compareGrille(sauv, tab) == 1)
    {
      freeTab2D(sauv);
      return 0;
    }

  deplacementDroite(sauv);
  if(compareGrille(sauv, tab) == 1)
    {
      freeTab2D(sauv);
      return 0;
    }

  freeTab2D(sauv);
  return 1;
}

int jeu(int ** grilleJeu, int ** grilleJeuPrec) //renvoi le score à la fin de la partie
{
  int continuer = 1; int coupTotal = 0; char lettre = ' '; unsigned long int score = 0; int coupJouer = 0;  
  
  int ** sauv = NULL;
  sauv = initTab2D();
  if(sauv == NULL)
    {
      perror("Probleme allocation mémoire, veuillez relancer le jeu, je ne garantie pas sons bon fonctionnement\n");
      exit(EXIT_FAILURE);
    }

  remplieAleatoirement(grilleJeu);
  
  while(continuer)
    {

      remplieAleatoirement(grilleJeu);
      copieGrille(grilleJeu, sauv);
      coupJouer = 0;
      while(!coupJouer)
	{
	  if(contient2048(grilleJeu) == 1)
	    {
	      printf("\n\nFélicitations vous avez gagné ᕦ( ⊡ 益 ⊡ )ᕤ\n\n");
	      goto stop;
	    }
	  if(coupTotal >= N*N)
	    {
	      if(bloquer(grilleJeu) == 1)
		{
		  printf("\n\nVous avez perdu, peut-être une prochaine fois (｡ŏ﹏ŏ) \n\n");
		  goto stop;
		}
	    }

	  afficheGrille(grilleJeu);
	  printf("Voici le coup numéro %d et le score actuel est %ld. \n\nVeuillez saisir votre déplacement ['d','g','h','b','r'] : ", coupTotal, score);
	  lettre = saisieLettre();

	  switch (lettre)
	    {
	    case 'd' : 
	      copieGrille(grilleJeu, grilleJeuPrec);
	      score += deplacementDroite(grilleJeu);
	      coupJouer = compareGrille(sauv, grilleJeu);
	      break;
	    case 'g' :
	      copieGrille(grilleJeu, grilleJeuPrec);
	      score += deplacementGauche(grilleJeu);
	      coupJouer = compareGrille(sauv, grilleJeu);
	      break;
	    case 'h' : 
	      copieGrille(grilleJeu, grilleJeuPrec);
	      score += deplacementHaut(grilleJeu);
	      coupJouer = compareGrille(sauv, grilleJeu);
	      break;
	    case 'b' :
	      copieGrille(grilleJeu, grilleJeuPrec);
	      score += deplacementBas(grilleJeu);
	      coupJouer = compareGrille(sauv, grilleJeu);
	      break;
	    case 'r' :
	      copieGrille(grilleJeuPrec, grilleJeu);
	      break;
	    default :
	      printf("Erreur de saisie (dans le switch)\n\n");
	      break;
	    }
			
	}
      coupTotal++;
    }
 stop :
  freeTab2D(sauv);
  return score;
}

int main_console(void)
{
  srand(time(NULL));

  int ** grilleJeu = NULL; int ** grilleJeuPrec = NULL;
  grilleJeu = initTab2D(); grilleJeuPrec = initTab2D();
  if (grilleJeu == NULL || grilleJeuPrec == NULL)
    {
      perror("Erreur de l'initialisation du tableau, pointeur == NULL");
      exit(EXIT_FAILURE);
    }

  start();
  unsigned long int scoreMax = 0;
  scoreMax = recupScoreMax();
  unsigned long int scoreEnCours = 0;

  scoreEnCours = jeu(grilleJeu, grilleJeuPrec);


  if (scoreEnCours > scoreMax)
    {
      printf("Votre score est de %ld, vous avez battu le meilleur score max (%ld)\n", scoreEnCours, scoreMax);
      scoreMax = scoreEnCours;
    }
  else
    {
      printf("Votre score est de %ld, vous n'avez pas battu le meilleur score max (%ld)\n", scoreEnCours, scoreMax);
    }

  ecritScore(scoreMax);


  freeTab2D(grilleJeu); freeTab2D(grilleJeuPrec);

  return EXIT_SUCCESS; 
}
