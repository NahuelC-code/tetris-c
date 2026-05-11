#include "render.h"

void dibujar_bloque(uint16_t x, uint16_t y, int color)
{
    uint16_t pixel_x = x * TAM_BLOQUE;
    uint16_t pixel_y = y * TAM_BLOQUE;

     for(int i = 0; i < TAM_BLOQUE; i++)
     {
        for(int j = 0; j < TAM_BLOQUE; j++)
        {
            gbt_dibujar_pixel(pixel_x + j, pixel_y + i, color);
        }
     }
}
void dibujar_tablero(int** board,Tetrimino* p)
{
    int i, j;

    gbt_borrar_backbuffer(0);

    for(i = 0; i < FIL_BOARD; i++)
    {
        for(j = 0; j < COL_BOARD; j++)
        {
            if(board[i][j] == 1)
            {
                dibujar_bloque(j, i, C);
            }
        }
    }

    for(i = 0; i < TAM_TETRIMINO; i++)
    {
        for(j = 0; j < TAM_TETRIMINO; j++)
        {
            if(p->forma[i][j] == 1)
            {
                dibujar_bloque(
                    p->pos_x + j,
                    p->pos_y + i,
                    A
                );
            }
        }
    }

    gbt_volcar_backbuffer();
}
