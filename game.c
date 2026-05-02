#include "game.h"
#include <stdio.h>


int valida_colision_pieza(int board[][COL_BOARD],Tetrimino* p )
{
    int i,j;

    for (i= 0;i< TAM_TETRIMINO; i++)
    {
        for (j= 0; j< TAM_TETRIMINO; j++)
        {

            if (p->forma[i][j] == 1 && board[i+p->pos_y][p->pos_x+j] == 1)
            {
              return COLISION;
            }
        }
    }
    return 1;
}

int valida_shift_down_pieza(int board[][COL_BOARD],Tetrimino* p)
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

void valida_shift_left_pieza(int board[][COL_BOARD],Tetrimino* p)
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

void valida_shift_right_pieza(int board[][COL_BOARD],Tetrimino* p)
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

void valida_rotacion_pieza(int board[][COL_BOARD],Tetrimino* p)
{
    Tetrimino aux = *p;

    rotar_tetrimino(p);
    if(valida_colision_pieza(board,p) == -1)
    {
        *p = aux;
    }
}


void colocar_pieza(int board[][COL_BOARD],Tetrimino* p)
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

void mostrar_tablero(int board[][COL_BOARD],Tetrimino* p) //Luego de los print se encarga el render
{
    int i,j;

    for(i=0;i<FIL_BOARD;i++)
    {
        for(j=0;j<COL_BOARD;j++)
        {
            if(i>=p->pos_y && i<=p->pos_y+3 && j >= p->pos_x && j<= p->pos_x+3)
            {
                if(p->forma[i - p->pos_y][j - p->pos_x] == 1)
                {
                    printf("%d ",p->forma[i-p->pos_y][j-p->pos_x]);
                }
                else
                {
                    printf("%d ",board[i][j]);
                }
            }
            else
            {
                printf("%d ",board[i][j]);
            }
        }
        printf("\n");
    }
}
