#include "../headers/map.h"

Tileset * load_tileset(FILE * fmap) // Charge un tileset
{
    //tilest name input

    char buf[CACHE_SIZE];
  
    fscanf(fmap, "%[^\n]\n", buf);

    //Verify if tileset file exist

    char ts_name[CACHE_SIZE] = "./graphics/tilesets/";

    strcat(ts_name, buf);
  
    struct stat buffer;
  
    if (stat(ts_name, &buffer) == -1) {
	fprintf(stdout, "Error : %s not found", buf);
	return NULL;
    }

    //tilesett exist -> Load img
  
    SDL_Surface * tmp_img = NULL;

    //  fprintf(stdout, "tileset name : %s\n", buf);
  
    tmp_img = SDL_LoadBMP(ts_name);
  
    if (tmp_img == NULL) {
	fprintf(stdout, "Error in IMG_Load : line %d", __LINE__);
	return NULL;
    }

    //Si image bien chargée -> alloue le tileset

    Tileset * t = NULL;
    t = malloc(sizeof(Tileset));

    if (t == NULL) {
	fprintf(stdout, "Error in tileset allocation : line %d", __LINE__);
	SDL_FreeSurface(tmp_img);
	return NULL;
    }

    SDL_SetColorKey(tmp_img, SDL_SRCCOLORKEY, SDL_MapRGB(tmp_img->format, 0, 255, 0));
  
    // met l'imamge deans le tileset
  
    t->im = SDL_DisplayFormat(tmp_img);

    SDL_FreeSurface(tmp_img);

    // Taille du tileset :

    fscanf(fmap, "%d %d", &t->w, &t->h);

    // résoltution des tiles en px

    t->res = t->im->w / t->w;

    //Représentation des tiles en SDL

    t->props = malloc(sizeof(TileProp)*t->w*t->h);

    if (t->props == NULL) {
	fprintf(stdout, "Error in t->props memory allocation");
	free(t->im);
	free(t);
	return NULL;
    
    }

    int i, j;
    for (i = 0; i < t->w; ++i) {
	for (j = 0; j < t->h; ++j) {
	    t->props[i].R.w = t->res;
	    t->props[i].R.h = t->res;
	    t->props[i].R.x = i*t->res;
	    t->props[i].R.y = j*t->res;

	}
    }  
  
    // propriétés de tiles

    char id_tile[10]; //tmp buffer
    char colision[10]; // tmp buffer
    int tile_value;
  
    for (i = 0; i < t->w*t->h; ++i) {

	fscanf(fmap, "%[^ ] : %[^;];%d", id_tile, colision, &tile_value);
	//fprintf(stdout, "%s, %s, %d\n", id_tile, colision, tile_value);
    
	if (strcmp(colision, "plein") == 0) {
	    t->props[i].plein = 1;
	}
	else {
	    t->props[i].plein = 0;
	}

	t->props[i].value = tile_value;
	//printf("%d, %d %d %d\n", t->props[i].plein, t->props[i].value, t->props[i].R.x, t->props[i].R.y);

	//printf("%d, %d\n", t->props[i].R.w, t->props[i].R.h);
    
    }

    //printf("%d, %d, %d\n", t->w, t->h, t->res);
    
    return t;
}

Map * load_map(char * map_fn) // Charge une map SDL
{
    FILE * fmap = NULL;

    char map_name[CACHE_SIZE] = "./data/maps/";

    strcat(map_name, map_fn);
  
    fmap = fopen(map_name, "r");

    if (fmap == NULL) {
	fprintf(stdout, "Error : %s not found\n", map_name);
	return NULL;    
    }
  
    rewind(fmap);

    char buf[CACHE_SIZE]; // buffer which read the current line from a file.

    fscanf(fmap, "%[^\n]\n", buf);

    if (!strstr(buf, "#tileset")) {
	fprintf(stdout, "Error in %s : please define a tileset or append '#tileset' before\n", map_fn);
	fclose(fmap);
	return NULL;
    }  

    Map * m = NULL;

    m = malloc(sizeof(Map));

    if (m == NULL) {
	fprintf(stdout, "Error in map memory allocation");
	fclose(fmap);
	return NULL;
    
    }
  
    m->t = load_tileset(fmap);

    if (m->t == NULL) {
	fprintf(stdout, "Error in m->t (tileset) memory allocation");
	free(m);
	fclose(fmap);
	return NULL;
    }
  
    int iter=0;
  
    while (!strstr(buf, "#level")) {
	if (fgets(buf, CACHE_SIZE, fmap) == NULL) {
	    fprintf(stdout, "Error in %s : define a level or append '#level' before\n", map_fn);
	    return m;
	}
	iter++;
    }

    fscanf(fmap, "%d %d", &m->w, &m->h);

    int i, j;

    m->schema = malloc(sizeof(char *)*m->w);

    if (m->schema == NULL) {
	fprintf(stdout, "Error in map->schema memory allocation");
	free(m->t);
	free(m);
	fclose(fmap);
	return NULL;
    
    }

    for (i = 0; i < m->w; ++i) {
	m->schema[i] = malloc(sizeof(char)*m->h);
	if (m->schema[i] == NULL) {
	    for (j = i; j >= 0; --j) {
		free(m->schema[i]);
	    }
	}
    }
  
    for (i = 0; i < m->h; ++i) {
	for (j = 0; j < m->w; ++j) {
	    m->schema[j][i] = 0;
	    //fprintf(stdout, "%d", m->schema[j][i]);
	}
	//printf("\n");
    }

    fscanf(fmap, "%s", buf);

    m->score = 0; // score initialisation
  
    fclose(fmap);
  
    return m;
}

void print_map(Map * m, SDL_Surface * screen) // Actualise la map SDL
{
    SDL_Rect R_sc; // rect for screen
    int i, j;
    int num_tile; //numéro tile du schéma
    
    for (i = 0; i < m->w; ++i) {
	for (j = 0; j < m->h; ++j) {

	    R_sc.x = i*m->t->res;
	    R_sc.y = j*m->t->res;
      
	    num_tile = m->schema[i][j];

	    if (num_tile < m->t->w) {
		SDL_BlitSurface(m->t->im, &(m->t->props[num_tile].R), screen, &R_sc);	
	    }
	}    
    }
    //SDL_Flip(screen);
}

void free_map(Map * map) // libère une map
{
    map->score = 0;

    int i;
    for (i = 0; i < map->w; ++i) {
	free(map->schema[i]);
    }
    free(map->schema);
  
    free(map->t->props);
    SDL_FreeSurface(map->t->im);
    free(map->t);  
    free(map);  
}
