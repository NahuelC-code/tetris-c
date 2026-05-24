#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#define FIL_OCULTAS 1
#define FIL_BOARD 20
#define FIL_TOTAL (FIL_BOARD + FIL_OCULTAS)
#define COL_BOARD 10

#include <stdlib.h>

void** create_init_board(int filas, int columnas, size_t tam);
void destruirBoard(void** m, int filas);
int borrar_lineas(int** b) ;
void vaciar_fila(int* v);


#endif // BOARD_H_INCLUDED
