#include "../headers/biblio.h"
#include "../headers/const.h"
#include "../headers/struct.h"

#include "../headers/game_over.h"
#include "../headers/map.h"
#include "../headers/menu.h"
#include "../headers/move.h"
#include "../headers/music.h"
#include "../headers/save.h"
#include "../headers/score.h"
#include "../headers/tab.h"
#include "../headers/time.h"
#include "../headers/console.h"

int main(void)
{
    fprintf(stdout, "\nBienvenue,\n\nVoulez-vous jouer en console (c) ou en sdl (default) ? : ");

    char game_type;
  
    scanf("%c", &game_type);

    if (game_type == 'c') {//if game in console
	main_console();
	fprintf(stdout, "\nA bientôt !\n\n");    
	return EXIT_SUCCESS;
    }
  
    srand(time(NULL)); // time initialisation

    SDL_Init(SDL_INIT_VIDEO); // SDL Init

    //////////////////////////////////// Options window

    SDL_WM_SetCaption("2048", NULL); //texte fenetre
  
    //////////////////////////////////// Principal Screen
  
    SDL_Surface * screen = SDL_SetVideoMode(W_SC, H_SC, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  
    if (screen == NULL) {
	fprintf(stdout, "Error : %s", SDL_GetError());
	SDL_Quit();
	return EXIT_FAILURE;
    }
  
    ///////////////////////////////// Variables

    int game_loop = 1; // game loop
  
    int keyup = 1; // if player realease a key -> stop key repeats
  
    int played = 0; // if the player played

    int wined = 0; // If the player have wined
    int reset = 0; // If reset (new party)

    int mode_de_jeu = 4; // game mode by the width of the game

    unsigned long int score_prec = 0; // score before a movement

    int temps_actuel = 0;
    int temps_precedent = 0; // for Poll Event and control fps
    unsigned long int time_begin_party = 0; // time when begin a party    

    char ** prec_schema; // Schema du jeu à coup-1
  
    ///////////////////////////////////// Screen background
  
    SDL_Surface * img = IMG_Load("./graphics/background/projet2048_bgHD.png"); // background load

    SDL_Surface * bg = SDL_DisplayFormat(img); // for fast blitting

    SDL_FreeSurface(img); // don't need anymore

    intro_game(screen, bg);
  
    /////////////////////////////////// Audio

    Mix_Init(MIX_INIT_MP3);

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
	fprintf(stderr,"Probleme du chargement de SDL mixer : %s \n", Mix_GetError());
	return EXIT_FAILURE;
    }

    Mix_AllocateChannels(2); // allocate 2 chanells (theme and move)

    Mix_Music * theme_principal = music_load("./music/theme.mp3");  

    Mix_Chunk * move = chunk_load("./music/move.wav", 4);
  
    //////////////////////////////////// MENU BEGIN

    SDL_BlitSurface(bg, NULL, screen, NULL); // background blit  

    switch(menu(screen, "2048|Nouvelle partie|Quitter", 0)) {
    case 1:
	switch (menu(screen, "Mode de jeu|3 x 3|4 x 4 (default)|5 x 5", -1)) {
	case 1:
	    mode_de_jeu = 3;
	    break;
	case 3:
	    mode_de_jeu = 5;
	default:
	    break;
	}    
	break;
    default :
	SDL_FreeSurface(bg);
	Mix_FreeMusic(theme_principal); // free musique
	Mix_FreeChunk(move);
	Mix_CloseAudio(); // fermeture du son    
	SDL_Quit();
	return EXIT_SUCCESS;
    }
  
    //////////////////////////////////// Map Loading

    char map_name[50];
    sprintf(map_name, "map%d.txt", mode_de_jeu); // load map name by game mode
  
    Map * m = load_map(map_name); // Load the map

    if (m == NULL) {
	fprintf(stdout, "Error in Map Loading\n");
	return EXIT_FAILURE;
    }

    //////////////////////////////// SDL GAME SURFACE
  
    SDL_Surface * game_screen // screen of the game 2048
	= SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, m->w*m->t->res, m->h*m->t->res, 32, 0, 0, 0, 0);

    if (game_screen == NULL) {
	fprintf(stdout, "Error : %s", SDL_GetError());
	return EXIT_FAILURE;
    }

    SDL_Rect game_position; // position of the game screen

    game_position.x = W_SC / 2 - m->w*m->t->res / 2;
    game_position.y = H_SC / 2 - m->h*m->t->res / 2 - 50;

    game_position.w = game_screen->w;
    game_position.h = game_screen->h;
  
    random_pop_up(m); // two case initialisation
    random_pop_up(m);

    /////////////////////////////////// Game screen Blit

    if (game_loop) {
	SDL_BlitSurface(screen, &game_position, game_screen, NULL);
    }

    /////////////////////////////////// Score Init

    score_max_load(screen, bg, mode_de_jeu);

    score_load(screen, bg, m->score); // print in frame the score  

    /////////////////////////////////// Variables Init

    prec_schema = copie_tab(m->schema, m->w); // Copy of the schema before player modify it

    time_begin_party = SDL_GetTicks();
  
    /////////////////////////////////// Process

    SDL_Event key; // keybord input
  
    while (game_loop) {//game_loop
    
	print_map(m, game_screen); // maj map blit
	SDL_BlitSurface(game_screen, NULL, screen, &game_position); //blit game_screen to screen
	SDL_Flip(screen); // actualise screen
    
	SDL_PollEvent(&key); // Wait input
    
	switch (key.type) {//keyboard input
	case SDL_QUIT: // if player quit with mouse
	    game_loop = 0;
	    break;
	case SDL_KEYUP: // if player realease a key
	    keyup = 1;
	    break;
	case SDL_KEYDOWN: // if the player put down a key
	    if (keyup == 1) {
		switch (key.key.keysym.sym) {
		case SDLK_ESCAPE: // if press escape key
		    switch (menu(screen, "PAUSE|Nouvelle partie|Sauvegarder|Charger|Controles|Quitter", 2)) {//menu pause
		    case 1:
			reset = 1;
			break;
		    case 2:
			sauv(m, "save.txt", mode_de_jeu);
			score_max_save(mode_de_jeu, m->score);
			score_max_load(screen, bg, mode_de_jeu);
			break;
		    case 3:
			charge_sauv(m, "save.txt", mode_de_jeu);
			score_max_save(mode_de_jeu, m->score);
			score_max_load(screen, bg, mode_de_jeu);	    
			score_load(screen, bg, m->score);
			time_begin_party = SDL_GetTicks();
			break;
		    case 4:
			controles(screen);
			break;
		    case 5:
			game_loop = 0;
			break;
		    }
		    break;
		case SDLK_UP: // if press up key
		    free_tab_2D(prec_schema, m->w); // free the last prec_schema
		    prec_schema = copie_tab(m->schema, m->w); // Copy of the old schema
		    score_prec = m->score; // copy of the old score
		    haut(m); // direction play
		    played = 1;
		    break;
		case SDLK_DOWN:
		    free_tab_2D(prec_schema, m->w); // if press down key
		    prec_schema = copie_tab(m->schema, m->w); // Copy of the old schema
		    score_prec = m->score; // copy of the old score
		    bas(m); // direction play
		    played = 1;
		    break;
		case SDLK_RIGHT:
		    free_tab_2D(prec_schema, m->w); // if press right key
		    prec_schema = copie_tab(m->schema, m->w); // Copy of the old schema
		    score_prec = m->score; // Copy of the old score	  
		    droit(m); // direction play
		    played = 1;
		    break;
		case SDLK_LEFT:
		    free_tab_2D(prec_schema, m->w); // if press left key
		    prec_schema = copie_tab(m->schema, m->w); // Copy of the schema
		    score_prec = m->score; // Copy of the old score
		    gauche(m); // direction play
		    played = 1;
		    break;
		case SDLK_a: // r for return key
		    score_delete(screen, bg, m->score); // delete score print in the current frame
		    m->schema = copie_tab(prec_schema, m->w); // recopied the old schema 
		    m->score = score_prec; // recopied the old score
		    played = 1;
		default:
		    break;
		}
		keyup = 0;
	    }
	}

	temps_actuel = SDL_GetTicks();
	if (temps_actuel - temps_precedent > 30) {//parallele actions
	    chrono(screen, bg, time_begin_party); // timer
	    temps_precedent = temps_actuel; 
	}
	else {
	    SDL_Delay(30 - (temps_actuel - temps_precedent));
	}

	if (played) {// after the player have done an action
      
	    print_map(m, game_screen); // blit map
	    SDL_BlitSurface(game_screen, NULL, screen, &game_position); // Actualise avant le popUp pour faciliter la lecture.
	    score_load(screen, bg, m->score); // load score
	    SDL_Flip(screen); // flip screen
      
	    if (tab_cmp(prec_schema, m->schema, m->w)) { // random new case after a play

		play_chunk(move); // sound of moving
		SDL_Delay(50); // delay for visual confort
		random_pop_up(m); // random new case
		print_map(m, game_screen); // blit game map
		SDL_BlitSurface(game_screen, NULL, screen, &game_position); // blit game screen
		SDL_Flip(screen); // flip screen
	    }
      
	    if (win(m) == 1 && wined == 0) {// Win test and play only once
		printf("Vous avez gagné\n");
		switch (menu(screen, "BRAVO !|Continuer|Nouvelle Partie|Quitter", 2)) {
		case 2:
		    reset = 1;
		    break;
		case 3:
		    game_loop = 0;
		    break;
		default:
		    wined = 1;
		    break;	  
		}
	    }
	    else if (lose(m)) {// Lose test
		printf("Vous avez perdu.\n");
		switch (menu(screen, "GAME OVER|Nouvelle Partie|Quitter", 2)) {
		case 1:
		    reset = 1;
		    break;
		case 2:
		    score_max_save(mode_de_jeu, m->score);
		    game_loop = 0;
		    break;
		}
	    }
	    played = 0; // player can play      
	}

	if (reset) {// if player create a new party

	    score_max_save(mode_de_jeu, m->score); // print max score in file
	    score_max_load(screen, bg, mode_de_jeu); // reload max score in frame
	    score_delete(screen, bg, m->score); // delete score print in the current frame
      
	    free_map(m); // free the current map
	    m = load_map(map_name); // load a new one

	    random_pop_up(m); // two case initialisation
	    random_pop_up(m);

	    score_load(screen, bg, m->score); // print in frame the score
      
	    wined = 0; // reset win
	    reset = 0; // end of reset

	    time_begin_party = SDL_GetTicks(); // new time for a new party
	}

	//if (!game_loop) {// if the game stop for a safe save
	//  if (menu(screen, "Sauvegarder ?|Oui|Non", 2) == 1) { // menu safe save
	//	sauv(m, "save.txt", mode_de_jeu);
	//  }
	//}
    }
  
    SDL_FreeSurface(game_screen); // free game 2048 frame
    SDL_FreeSurface(bg); // free background image
    free_tab_2D(prec_schema, m->w); //free prec_schema
    free_map(m); // free map
  
    Mix_FreeMusic(theme_principal); // free music theme_principal
    Mix_FreeChunk(move); // free move chunk
    Mix_CloseAudio(); // fermeture du son

    Mix_Quit();
  
    SDL_Quit();

    fprintf(stdout, "\nA bientôt !\n\n");
  
    return EXIT_SUCCESS;
}
