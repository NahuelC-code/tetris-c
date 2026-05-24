#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <GBT/gbt.h>
#include "tetriminos.h"
#include "board.h"
#include "score.h"
#include "config.h"
#include <stdio.h>

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
void dibujar_tablero(int** board, Tetrimino* p, EstadoJuego* estado, int paleta);
void dibujar_texto_8x8(uint16_t x, uint16_t y, const char* texto, uint8_t color);
void dibujar_texto_8x16(uint16_t x, uint16_t y, const char* texto, uint8_t color);
void dibujar_pantalla_presentacion(Cfg cfg);
void dibujar_pantalla_nombre(char* nick, Cfg cfg);
void dibujar_pausa(Cfg cfg);
void dibujar_game_over(EstadoJuego* estado, const char* nick, Cfg cfg);
void dibujar_menu_principal(int opcion, Cfg cfg_ejecutable);
void dibujar_menu_config(Config* cfg, int opcion, Cfg cfg_ejecutable);

#endif // RENDER_H_INCLUDED
