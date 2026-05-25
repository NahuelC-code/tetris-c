#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <GBT/gbt.h>
#include "tetriminos.h"
#include "board.h"
#include "score.h"
#include "config.h"
#include <stdio.h>

typedef struct{
    uint16_t ancho;
    uint16_t alto;
    uint8_t escala;
    uint8_t tam_bloque;
}Cfg;

extern const Cfg CFG_CGA;
extern const Cfg CFG_VGA;

void dibujar_bloque(uint16_t x, uint16_t y, int color, uint8_t tam_bloque);
void dibujar_tablero(int** board, Tetrimino* p, EstadoJuego* estado, int paleta, Cfg cfg, const char* nick);
void dibujar_texto_8x8(uint16_t x, uint16_t y, const char* texto, uint8_t color);
void dibujar_texto_8x16(uint16_t x, uint16_t y, const char* texto, uint8_t color);
void dibujar_pantalla_presentacion(Cfg cfg);
void dibujar_pantalla_nombre(char* nick, Cfg cfg);
void dibujar_pausa(Cfg cfg);
void dibujar_game_over(EstadoJuego* estado, const char* nick, Cfg cfg);
void dibujar_menu_principal(int opcion, Cfg cfg_ejecutable);
void dibujar_menu_config(Config* cfg, int opcion, Cfg cfg_ejecutable);
void aplicar_paleta_clasica(void);
void aplicar_paleta_retro(void);
void dibujar_fondo(Cfg cfg);
void dibujar_rectangulo(uint16_t x, uint16_t y, uint16_t ancho, uint16_t alto, uint8_t color_fondo, uint8_t color_borde);
void dibujar_ranking(EntradaRanking* ranking, int cantidad, Cfg cfg);
#endif // RENDER_H_INCLUDED
