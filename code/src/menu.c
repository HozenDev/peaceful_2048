#include "../headers/menu.h"
#include "../headers/music.h"

int menu(SDL_Surface * screen, char * str, int transitions) // Dynamic Menu
{
    int i = 0;

    SDL_Surface * save = SDL_ConvertSurface(screen, screen->format, SDL_HWSURFACE); // save surface look
  
    SDL_Surface * black_screen = SDL_CreateRGBSurface(SDL_HWSURFACE, screen->w, screen->h, 32, 0, 0, 0, 0);

    SDL_FillRect(black_screen, NULL, 0);

    if (transitions == 1 || transitions == 2) {
	for (i = 0; i <= 200; i+=5) {
	    SDL_SetAlpha(black_screen, SDL_SRCALPHA | SDL_RLEACCEL, i);
	    SDL_BlitSurface(save, NULL, screen, NULL);
	    SDL_BlitSurface(black_screen, NULL, screen, NULL);
	    SDL_Flip(screen);
	}    
    }
    else {
	SDL_SetAlpha(black_screen, SDL_SRCALPHA | SDL_RLEACCEL, 200);
	SDL_BlitSurface(black_screen, NULL, screen, NULL);
	SDL_Flip(screen);    
    }

    //////////////////////////////////////////////

    char buf[10][CACHE_SIZE]; // Maximum of 10 options

    FILE * tmp = tmpfile();
  
    fprintf(tmp, "%s", str);
  
    i = 1;

    rewind(tmp);
  
    while (fscanf(tmp, "%[^|]|", buf[i-1]) != EOF) {
	i++;    
    }

    int taille = i-1;

    //printf("NOMBRE OPTIONS : %d\n", taille-1);
  
    fclose(tmp);

    /////////////////////////////////////////////
  
    SDL_Surface ** texts = malloc(sizeof(SDL_Surface *) * taille);

    TTF_Init();

    SDL_Color WHITE = {255, 255, 255};
    SDL_Color RED = {255, 0, 0};
  
    TTF_Font * police = NULL;

    SDL_Rect * position = malloc(sizeof(SDL_Rect) * taille);

    ///////////////////////////////////////
  
    police = TTF_OpenFont("./fonts/cloude.ttf", 120);
  
    texts[0] = TTF_RenderText_Solid(police, buf[0], WHITE);
  
    position[0].x = screen->w/2;
    position[0].y = screen->h/2 - texts[0]->h/2 + 200;
  
    SDL_BlitSurface(texts[0], NULL, screen, &position[0]);
  
    TTF_CloseFont(police);

    int space = 150/(taille-1);
  
    /////////////////////////////////////////
  
    police = TTF_OpenFont("./fonts/cloude.ttf", 70);
  
    for (i = 1; i < taille; ++i) {

	if (i==1) {
	    texts[i] = TTF_RenderText_Solid(police, buf[i], RED);
	}
	else {
	    texts[i] = TTF_RenderText_Solid(police, buf[i], WHITE);      
	}

	position[i].x = screen->w/2 + texts[0]->w + 100;
	position[i].y = screen->h/2 - texts[i]->h/2 + 200 + (i-1)*space;
      
	SDL_BlitSurface(texts[i], NULL, screen, &position[i]);
    }

    SDL_Flip(screen);

    int pause = 1;
    int ret = 1;
  
    SDL_Event key;
  
    while (pause) {
    
	SDL_WaitEvent(&key); // Wait input 

	switch (key.type) {
	case SDL_QUIT:
	    pause = 0;
	    break;
	case SDL_KEYDOWN:
	    switch (key.key.keysym.sym) {
	    case SDLK_ESCAPE:
		ret = 0;
		pause = 0;
		break;
	    case SDLK_RETURN :
		pause = 0;
		break;
	    case SDLK_UP:
		if (ret > 1) {
		    ret--;
		    SDL_FreeSurface(texts[ret]);
		    SDL_FreeSurface(texts[ret+1]);
		    texts[ret] = TTF_RenderText_Solid(police, buf[ret], RED);
		    texts[ret+1] = TTF_RenderText_Solid(police, buf[ret+1], WHITE);
		    SDL_BlitSurface(texts[ret+1], NULL, screen, &position[ret+1]);	  
		}
		break;
	    case SDLK_DOWN:
		if (ret < taille-1) {
		    ret++;
		    SDL_FreeSurface(texts[ret]);
		    SDL_FreeSurface(texts[ret-1]);
		    texts[ret] = TTF_RenderText_Solid(police, buf[ret], RED);
		    texts[ret-1] = TTF_RenderText_Solid(police, buf[ret-1], WHITE);
		    SDL_BlitSurface(texts[ret-1], NULL, screen, &position[ret-1]);	  
		}
		break;
	    default:
		break;
	    }

	    if (ret >= 1 && ret < taille) {
		SDL_BlitSurface(texts[ret], NULL, screen, &position[ret]);
		SDL_Flip(screen);
	    }
      
	}
    }

    for (i = 0; i < taille; ++i) {
	SDL_FreeSurface(texts[i]);
    }

    free(texts);
    free(position);
  
    //printf("MENU RETURN : %d\n", ret);

    TTF_CloseFont(police);
  
    TTF_Quit();
  
    if (transitions == -1 || transitions == 2) {
	for (i = 200; i >= 0; i-=5) {
	    SDL_SetAlpha(black_screen, SDL_SRCALPHA | SDL_RLEACCEL, i);
	    SDL_BlitSurface(save, NULL, screen, NULL);
	    SDL_BlitSurface(black_screen, NULL, screen, NULL);
	    SDL_Flip(screen);
	}    
    }
    else {
	SDL_BlitSurface(save, NULL, screen, NULL);
	//SDL_Flip(screen);    
    }
  
    SDL_FreeSurface(save);
    SDL_FreeSurface(black_screen);  
  
    return ret;
}

void controles(SDL_Surface * screen)
{
    SDL_Surface * save = SDL_ConvertSurface(screen, screen->format, SDL_HWSURFACE); // save surface look

    SDL_Surface * op_screen = IMG_Load("./graphics/wallpapers/key_options.png");

    SDL_Surface * white_screen = SDL_CreateRGBSurface(SDL_HWSURFACE, screen->w, screen->h, 32, 0, 0, 0, 0);

    SDL_FillRect(white_screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));  
  
    int i = 0;

    for (i = 0; i <= 255; i+=5) {
	SDL_SetAlpha(white_screen, SDL_SRCALPHA | SDL_RLEACCEL, i);
	SDL_BlitSurface(save, NULL, screen, NULL);
	SDL_BlitSurface(white_screen, NULL, screen, NULL);
	SDL_Flip(screen);
    }
  
    SDL_BlitSurface(op_screen, NULL, screen, NULL);
    SDL_Flip(screen);

    int pause = 1;
    int tempsActuel = 0;
    int tempsPrecedent = 0;
    SDL_Event key;

    SDL_Color BLACK = {0, 0, 0};

    TTF_Init();
  
    TTF_Font * police = NULL;
    police = TTF_OpenFont("./fonts/cloude.ttf", 50);
  
    SDL_Surface * text_press = TTF_RenderText_Solid(police, "Appuyez sur une touche", BLACK);

    TTF_CloseFont(police);
    TTF_Quit();  

    SDL_Rect position;
    position.x = screen->w - text_press->w - 50;
    position.y = screen->h - text_press->h - 50/2;
    position.w = text_press->w;
    position.h = text_press->h;

    char blender = 0;
    char black = 0;
  
    while (pause) {

	SDL_Flip(screen);
    
	SDL_PollEvent(&key); // Wait input 

	switch (key.type) {
	case SDL_KEYDOWN:
	    pause = 0;
	    break;
	}

	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 30) {//parallele actions
      
	    if (blender == 15 && black == 0) {
		SDL_BlitSurface(text_press, NULL, screen, &position);
		blender = 0;
		black = 1;
	    }
	    else if (blender == 15 && black == 1) {
		SDL_BlitSurface(op_screen, &position, screen, &position);
		blender = 0;
		black = 0;
	    }
	    else {
		blender++;	
	    }
      
	    tempsPrecedent = tempsActuel; 
	}
	else {      
	    SDL_Delay(30 - (tempsActuel - tempsPrecedent));  
	}    
    
    }
  
    for (i = 0; i <= 255; i+=15) {
	SDL_SetAlpha(white_screen, SDL_SRCALPHA | SDL_RLEACCEL, i);
	SDL_BlitSurface(op_screen, NULL, screen, NULL);
	SDL_BlitSurface(white_screen, NULL, screen, NULL);
	SDL_Flip(screen);
    }

    SDL_Delay(100);
  
    for (i = 255; i >= 0; i-=5) {
	SDL_SetAlpha(white_screen, SDL_SRCALPHA | SDL_RLEACCEL, i);
	SDL_BlitSurface(save, NULL, screen, NULL);
	SDL_BlitSurface(white_screen, NULL, screen, NULL);
	SDL_Flip(screen);
    }

    SDL_FreeSurface(text_press);  
    SDL_FreeSurface(white_screen);
    SDL_FreeSurface(op_screen);
    SDL_FreeSurface(save);
}

void intro_game(SDL_Surface * screen, SDL_Surface * bg)
{
    SDL_Delay(500);

    SDL_Surface * author_screen = IMG_Load("./graphics/wallpapers/authors.png");

    SDL_Surface * black_screen = SDL_CreateRGBSurface(SDL_HWSURFACE, screen->w, screen->h, 32, 0, 0, 0, 0);

    SDL_FillRect(black_screen, NULL, 0);  

    int i;
  
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
	fprintf(stderr,"Probleme du chargement de SDL mixer : %s \n", Mix_GetError());
	return;
    }

    Mix_AllocateChannels(2); // allocate 2 chanells (theme and move)
  
    Mix_Chunk * intro_chunk = chunk_load("./music/intro2.wav", 8);

    if (intro_chunk != NULL) {
	Mix_VolumeChunk(intro_chunk, MIX_MAX_VOLUME/8);    
    }
  
    play_chunk(intro_chunk); // sound of moving  
  
    for (i = 255; i >= 0; i-=5) {
	SDL_SetAlpha(black_screen, SDL_SRCALPHA | SDL_RLEACCEL, i);
	SDL_BlitSurface(author_screen, NULL, screen, NULL);
	SDL_BlitSurface(black_screen, NULL, screen, NULL);
	SDL_Flip(screen);
    }
  
    SDL_Delay(2000);

    for (i = 0; i <= 255; i+=5) {
	SDL_SetAlpha(black_screen, SDL_SRCALPHA | SDL_RLEACCEL, i);
	SDL_BlitSurface(author_screen, NULL, screen, NULL);
	SDL_BlitSurface(black_screen, NULL, screen, NULL);
	SDL_Flip(screen);
    }

    SDL_Delay(1000);
  
    for (i = 255; i >= 200; i-=1) {
	SDL_SetAlpha(black_screen, SDL_SRCALPHA | SDL_RLEACCEL, i);
	SDL_BlitSurface(bg, NULL, screen, NULL);
	SDL_BlitSurface(black_screen, NULL, screen, NULL);
	SDL_Flip(screen);
    }
  
    SDL_FreeSurface(black_screen);
    SDL_FreeSurface(author_screen);
    Mix_FreeChunk(intro_chunk); // free move chunk
    Mix_CloseAudio(); // fermeture du son
}
