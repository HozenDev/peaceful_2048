#include "../headers/music.h"

Mix_Music * music_load(char * name)
{
  Mix_Music * musique = NULL;

  musique = Mix_LoadMUS(name);

  if(musique == NULL)
  {
    fprintf(stdout, "Music Error %s\n", Mix_GetError());
    return NULL;
  }

  Mix_VolumeMusic(MIX_MAX_VOLUME/4);
  Mix_PlayMusic(musique, -1);

  return musique;
}

Mix_Chunk * chunk_load(char * name, int level)
{
  Mix_Chunk * son;

  son = Mix_LoadWAV(name);

  if (son == NULL) {
    fprintf(stdout, "Music Error %s\n", Mix_GetError());
    return NULL;
  }

  if (level > 0) {
    Mix_VolumeChunk(son, MIX_MAX_VOLUME/level);    
  }
  
  return son;
}

void play_chunk(Mix_Chunk * son)
{
  Mix_PlayChannel(-1, son, 0);  
}
