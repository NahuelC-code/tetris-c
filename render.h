#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <GBT/gbt.h>
#include "tetriminos.h"
#include "board.h"

#define TAM_BLOQUE 8

#define N 15 // Transparente
#define A 14 // Amarillo
#define C 3  // Celeste
#define V 2  // Verde

typedef struct{
    uint16_t ancho;
    uint16_t alto;
    uint8_t escala;
}Cfg;

extern const Cfg CFG_CGA;
extern const Cfg CFG_VGA;

void dibujar_bloque(uint16_t x, uint16_t y, int color);
void dibujar_tablero(int** board,Tetrimino* p);

#endif // RENDER_H_INCLUDED
