#ifndef TETRIMINOS_H_INCLUDED
#define TETRIMINOS_H_INCLUDED

#include <stdlib.h> // utilizar rand()

#define TAM_TETRIMINO 4

typedef struct{
    int forma[TAM_TETRIMINO][TAM_TETRIMINO];
    int pos_x;
    int pos_y;

}Tetrimino;

void rotar_tetrimino(Tetrimino* p);

#endif // TETRIMINOS_H_INCLUDED
