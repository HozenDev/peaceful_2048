#ifndef music_2048
#define music_2048

#include "biblio.h"
#include "const.h"
#include "struct.h"

// Music

Mix_Music * music_load(char * name); // music load
Mix_Chunk * chunk_load(char * name, int level); //sound load
void play_chunk(Mix_Chunk * son); // sound load

#endif
