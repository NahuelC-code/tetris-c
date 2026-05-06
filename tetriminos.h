#ifndef TETRIMINOS_H_INCLUDED
#define TETRIMINOS_H_INCLUDED

#include <stdlib.h> // utilizar rand()

#define TAM_TETRIMINO 4
#define CANT_PIEZAS 7

typedef struct{
    int forma[TAM_TETRIMINO][TAM_TETRIMINO];
    int pos_x;
    int pos_y;

}Tetrimino;

typedef enum{
    o,
    z,
    s,
    l,
    i,
    t,
    j
}Indice_pieza;

Tetrimino crear_tetrimino(int columnas);
void rotar_tetrimino(Tetrimino* p);
void normalizar_tetrimino(int m[TAM_TETRIMINO][TAM_TETRIMINO]);

#endif // TETRIMINOS_H_INCLUDED
