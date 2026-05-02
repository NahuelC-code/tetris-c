#include "tetriminos.h"

int forma_o[TAM_TETRIMINO][TAM_TETRIMINO] = {{0,1,1,0},
                                             {0,1,1,0},
                                             {0,0,0,0},
                                             {0,0,0,0}};

int forma_i[TAM_TETRIMINO][TAM_TETRIMINO] = {{1,1,1,1},
                                             {0,0,0,0},
                                             {0,0,0,0},
                                             {0,0,0,0}};

int forma_j[TAM_TETRIMINO][TAM_TETRIMINO] = {{1,0,0,0},
                                             {1,1,1,0},
                                             {0,0,0,0},
                                             {0,0,0,0}};

int forma_l[TAM_TETRIMINO][TAM_TETRIMINO] = {{0,0,0,1},
                                             {0,1,1,1},
                                             {0,0,0,0},
                                             {0,0,0,0}};

int forma_s[TAM_TETRIMINO][TAM_TETRIMINO] = {{0,0,1,1},
                                             {0,1,1,0},
                                             {0,0,0,0},
                                             {0,0,0,0}};

int forma_t[TAM_TETRIMINO][TAM_TETRIMINO] = {{0,1,0,0},
                                             {1,1,1,0},
                                             {0,0,0,0},
                                             {0,0,0,0}};

int forma_z[TAM_TETRIMINO][TAM_TETRIMINO] = {{1,1,0,0},
                                             {0,1,1,0},
                                             {0,0,0,0},
                                             {0,0,0,0}};



void rotar_tetrimino(Tetrimino* p)
{
    int i,j,aux;

    for(i=0;i<TAM_TETRIMINO;i++)
    {
        for(j=i+1;j<TAM_TETRIMINO;j++)
        {
            aux = p->forma[i][j];
            p->forma[i][j] = p->forma[j][i];
            p->forma[j][i] = aux;
        }
    }

    for(i=0;i<TAM_TETRIMINO;i++)
    {
        for(j=0;j<TAM_TETRIMINO/2;j++)
        {
            aux = p->forma[i][j];
            p->forma[i][j] = p->forma[i][TAM_TETRIMINO - 1 - j];
            p->forma[i][TAM_TETRIMINO - 1 - j] = aux;
        }
    }
}
