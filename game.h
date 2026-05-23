#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "tetriminos.h"
#include "board.h"

#define COLISION 0
#define INSERTAR_PIEZA 1

int valida_colision_pieza(int** board,Tetrimino* p);
int valida_shift_down_pieza(int** board, Tetrimino* p);
void valida_shift_left_pieza(int** board, Tetrimino* p);
void valida_shift_right_pieza(int** board, Tetrimino* p);
void valida_rotacion_pieza(int** board,Tetrimino* p);
void valida_rotacion_pieza_izq(int** board,Tetrimino* p);
void colocar_pieza(int** board,Tetrimino* p) ;
#endif // GAME_H_INCLUDED
