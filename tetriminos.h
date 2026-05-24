#ifndef TETRIMINOS_H_INCLUDED
#define TETRIMINOS_H_INCLUDED

#include <stdlib.h>
#include <time.h>

#define TAM_TETRIMINO 4
#define CANT_PIEZAS 7

typedef struct{
    int forma[TAM_TETRIMINO][TAM_TETRIMINO];
    int pos_x;
    int pos_y;
    int id;

}Tetrimino;

typedef struct{
    int vec[CANT_PIEZAS];
    int ce;
    int ce_max;

}Vector_numeros;

Tetrimino crear_tetrimino(int columnas, Vector_numeros* v);
Vector_numeros crear_vector(int ce);
void inicializa_vector_numeros(Vector_numeros* v);
int random_num_vec(Vector_numeros* v);
void eliminar_vec_num_posicion(Vector_numeros* v, int pos);
void rotar_tetrimino(Tetrimino* p);
void rotar_tetrimino_izq(Tetrimino* p);
void normalizar_tetrimino(int m[TAM_TETRIMINO][TAM_TETRIMINO]);
#endif // TETRIMINOS_H_INCLUDED
