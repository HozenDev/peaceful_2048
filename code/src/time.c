#include "../headers/time.h"

int chrono(SDL_Surface * screen, SDL_Surface * bg, unsigned long int time_begin)
{
  TTF_Init();

  SDL_Color NOIR = {0, 0, 0};

  /*Chargement de la police*/
  TTF_Font * police = NULL;
  police = TTF_OpenFont("./fonts/cloude.ttf", 40);
  if(police==NULL) {
    perror("Probleme chargement de la police \n");
    return EXIT_FAILURE;
  }
  
  /* chrono */
  unsigned long int tempsGlobalMin = 0;
  unsigned long int tempsGlobalSec = 0;
  char tabTempsGlobal[500] = "";
  SDL_Surface * texteTemps = NULL;
  
  tempsGlobalMin = ((SDL_GetTicks()-time_begin) / 60000);
  tempsGlobalSec = (((SDL_GetTicks()-time_begin) % 60000 )/ 1000);
            
  sprintf(tabTempsGlobal, "TEMPS : %ld min %.2ld sec", tempsGlobalMin, tempsGlobalSec );
  texteTemps = TTF_RenderText_Blended(police, tabTempsGlobal, NOIR);

  SDL_Rect position;
  position.x = screen->w/2 - texteTemps->w/2;
  position.y = 0;
  position.w = texteTemps->w;
  position.h = texteTemps->h;

  SDL_BlitSurface(bg, &position, screen, &position);
  SDL_BlitSurface(texteTemps, NULL, screen, &position); /* Blit du chrono*/  

  /////////////////////////////////////

  SDL_Flip(screen);
  
  SDL_FreeSurface(texteTemps);

  TTF_CloseFont(police);
  TTF_Quit();
  
  return 0;
}
