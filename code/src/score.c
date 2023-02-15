#include "../headers/score.h"

int score_max_save(int mdj, unsigned long int score)
{
  char name[50];

  sprintf(name, "./data/score/score_%d.txt", mdj);

  FILE * f = fopen(name, "r+");

  if (f == NULL) {
    fprintf(stdout, "Save file not found\n");
    return -1;  
  }

  rewind(f);

  unsigned long int prev_score_max;
  int nb;

  nb = fscanf(f,"%ld\n", &prev_score_max);

  if(nb != 1) {
    perror("Mauvaise lecture dans ScoreMaxPrint");
    fclose(f);
    return 1;
  }   

  fclose(f);
  
  if (score > prev_score_max) {

    FILE * f = fopen(name, "w+");
    if (f == NULL) {
      fprintf(stdout, "Save file not found\n");
      return -1;  
    }
    rewind(f);

    fprintf(f,"%ld\n", score);

    fclose(f);
  } 
  
  return 0;
}

int score_max_load(SDL_Surface * screen, SDL_Surface * bg, int mdj)
{
  TTF_Init();

  SDL_Color NOIR = {0, 0, 0};

  char name[50];

  sprintf(name, "./data/score/score_%d.txt", mdj);

  FILE * f = fopen(name, "r+");

  if (f == NULL) {
    fprintf(stdout, "Save file not found\n");
    return -1;  
  }

  rewind(f);
  
  /*recuperation score max*/
  unsigned long int score = 0;
  int nb = 0;

  nb = fscanf(f,"%ld", &score);
  
  if(nb != 1) {
    perror("Mauvaise lecture dans ScoreMaxLoad : score");
    fclose(f);
    return 1;
  }
  
  fclose(f);

  TTF_Font *police = NULL;
  police = TTF_OpenFont("./fonts/cloude.ttf", 40);
  if(police==NULL) {
    perror("Probleme chargement de la police \n");
    fclose(f);
    return 1;
  }
  
  /* init tab score*/
  char tabScore[200] = "";
  sprintf(tabScore, "RECORD (%d x %d) : %ld", mdj, mdj, score);
  
  /* Creation du texte score max*/
  SDL_Surface * texteScoreMax = NULL;

  texteScoreMax = TTF_RenderText_Blended(police, tabScore, NOIR);  
  
  SDL_Rect position;
  position.x = 15;
  position.y = 0;
  position.w = texteScoreMax->w;
  position.h = texteScoreMax->h;
  
  SDL_BlitSurface(bg, &position, screen, &position);
  SDL_BlitSurface(texteScoreMax, NULL, screen, &position);  

  SDL_Flip(screen);
  
  SDL_FreeSurface(texteScoreMax);

  TTF_CloseFont(police);
  TTF_Quit();
  
  return 0;
}

int score_load(SDL_Surface * screen, SDL_Surface * bg, unsigned long int score)
{
  TTF_Init();

  SDL_Color NOIR = {0, 0, 0};
  
  /*Chargement de la police*/
  TTF_Font *police = NULL;
  police = TTF_OpenFont("./fonts/cloude.ttf", 40);
  if(police==NULL) {
    perror("Probleme chargement de la police \n");
    return EXIT_FAILURE;
  }    

  /*score en cours*/  
  SDL_Surface * texteScoreEnCours = NULL;
  char tabScoreEnCours[300];
  sprintf(tabScoreEnCours, "SCORE : %ld", score);

  texteScoreEnCours = TTF_RenderText_Blended(police, tabScoreEnCours, NOIR);

  SDL_Rect position;
  position.x = screen->w/2 - texteScoreEnCours->w/2;
  position.y = 100;
  position.w = texteScoreEnCours->w;
  position.h = texteScoreEnCours->h;
  
  SDL_BlitSurface(bg, &position, screen, &position);  
  SDL_BlitSurface(texteScoreEnCours, NULL, screen, &position);  
  
  SDL_Flip(screen);  
  
  SDL_FreeSurface(texteScoreEnCours);
  
  TTF_CloseFont(police);
  TTF_Quit();

  return score;
}

int score_delete(SDL_Surface * screen, SDL_Surface * bg, unsigned long int score)
{
  TTF_Init();

  SDL_Color NOIR = {0, 0, 0};
  
  /*Chargement de la police*/
  TTF_Font *police = NULL;
  police = TTF_OpenFont("./fonts/cloude.ttf", 40);
  if(police==NULL) {
    perror("Probleme chargement de la police \n");
    return EXIT_FAILURE;
  }    

  /*score en cours*/  
  SDL_Surface * texteScoreEnCours = NULL;
  char tabScoreEnCours[300];
  sprintf(tabScoreEnCours, "SCORE : %ld", score);

  texteScoreEnCours = TTF_RenderText_Blended(police, tabScoreEnCours, NOIR);

  SDL_Rect position;
  position.x = screen->w/2 - texteScoreEnCours->w/2;
  position.y = 100;
  position.w = texteScoreEnCours->w;
  position.h = texteScoreEnCours->h;
  
  SDL_BlitSurface(bg, &position, screen, &position);
  //SDL_BlitSurface(texteScoreEnCours, NULL, screen, &position);  
  
  SDL_Flip(screen);  
  
  SDL_FreeSurface(texteScoreEnCours);
  
  TTF_CloseFont(police);
  TTF_Quit();

  return score;
}
