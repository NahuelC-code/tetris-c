#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#define FIL_BOARD 20
#define COL_BOARD 10

#include <stdlib.h>

void** create_init_board(int filas, int columnas, size_t tam);
void destruirBoard(void** m, int filas);
void print_board(int** b);
int borrar_lineas(int** b) ;
void vaciar_fila(int* v);


#endif // BOARD_H_INCLUDED
