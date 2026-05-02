#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "tetriminos.h"
#include "board.h"

#define COLISION -1
#define INSERTAR_PIEZA 1

int valida_colision_pieza(int board[][COL_BOARD],Tetrimino* p);
int valida_shift_down_pieza(int board[][COL_BOARD], Tetrimino* p);
void valida_shift_left_pieza(int board[][COL_BOARD], Tetrimino* p);
void valida_shift_right_pieza(int board[][COL_BOARD], Tetrimino* p);
void valida_rotacion_pieza(int board[][COL_BOARD],Tetrimino* p);
void colocar_pieza(int board[][COL_BOARD],Tetrimino* p) ;
void mostrar_tablero(int board[][COL_BOARD],Tetrimino* p) ;
#endif // GAME_H_INCLUDED
