#include "game.h"
#include <stdio.h>


int valida_colision_pieza(int** board,Tetrimino* p )
{
    int i,j;

    for (i= 0;i< TAM_TETRIMINO; i++)
    {
        for (j= 0; j< TAM_TETRIMINO; j++)
        {

            if (p->forma[i][j] == 1 && (p->pos_x + j < 0 || p->pos_x + j >= COL_BOARD || p->pos_y + i < 0 || p->pos_y + i >= FIL_BOARD || board[i + p->pos_y][p->pos_x + j] == 1))
            {
              return COLISION;
            }
        }
    }
    return 1;
}

int valida_shift_down_pieza(int** board,Tetrimino* p)
{
    int i, j;

    for(i=0;i<TAM_TETRIMINO;i++)
    {
        for(j=0;j<TAM_TETRIMINO;j++)
        {
            if(p->forma[i][j] == 1)
            {
                if(i + p->pos_y == FIL_BOARD-1 || board[i+p->pos_y+1][j+p->pos_x] == 1)
                {
                    return INSERTAR_PIEZA;
                }
            }
        }
    }
    p->pos_y++;
    return 0;
}

void valida_shift_left_pieza(int** board,Tetrimino* p)
{
    int i,j;

    for(i=0;i<TAM_TETRIMINO;i++)
    {
        for(j=0;j<TAM_TETRIMINO;j++)
        {
            if(p->forma[i][j] == 1)
            {
                if(j+p->pos_x == 0 || board[p->pos_y + i][p->pos_x + j -1] == 1)
                    return;
            }
        }
    }
    p->pos_x --;
}

void valida_shift_right_pieza(int** board,Tetrimino* p)
{
    int i,j;

    for(i=0;i<TAM_TETRIMINO;i++)
    {
        for(j=0;j<TAM_TETRIMINO;j++)
        {
            if(p->forma[i][j] == 1)
            {
                if(j+p->pos_x == COL_BOARD-1 || board[p->pos_y + i][p->pos_x + j +1] == 1)
                    return;
            }
        }
    }
    p->pos_x ++;
}

void valida_rotacion_pieza(int** board,Tetrimino* p)
{
    Tetrimino aux = *p;

    rotar_tetrimino(p);
    if(valida_colision_pieza(board,p) == COLISION)
    {
        *p = aux;
    }
}


void colocar_pieza(int** board,Tetrimino* p)
{
    int i,j;
    for(i=0;i<TAM_TETRIMINO;i++)
    {
        for(j=0;j<TAM_TETRIMINO;j++)
        {
            if(p->forma[i][j] == 1)
            {
                board[p->pos_y+i][p->pos_x+j] = 1;
            }
        }
    }
}

