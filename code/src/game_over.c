#include "../headers/game_over.h"

int win(Map * m) // if tab have 2048
{
    int i, j;
    
    int tmp;
  
    for (i = 0; i < m->w; ++i) {
	for (j = 0; j < m->h; ++j) {
	    tmp = m->schema[i][j];
	    if (m->t->props[tmp].value == 2048) {
		return 1;
	    }
	}
    }

    return 0;
}

int lose(Map * m) // si le tableau ne possède plus de coup possible
{
    int i, j;
  
    for (i = 0; i < m->w; ++i) {
	for (j = 0; j < m->h; ++j) {

	    if (m->schema[i][j] == 0) {
		return 0;
	    }
	    if (i < (m->w)-1 && m->schema[i][j] == m->schema[i+1][j]) {
		return 0;
	    }
	    if (j < (m->h)-1 && m->schema[i][j] == m->schema[i][j+1]) {
		return 0;
	    }
	}
    }

    return 1;
}
