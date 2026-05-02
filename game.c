#include "game.h"
#include <stdio.h>


int valida_spawn_pieza(int board[][COL_BOARD],Tetrimino* p )
{
    int i,j;

    for (i= 0;i< TAM_TETRIMINO; i++)
    {
        for (j= 0; j< TAM_TETRIMINO; j++)
        {

            if (p->forma[i][j] == 1 && board[i+p->pos_y][p->pos_x+j] == 1)
            {
              return GAME_OVER;
            }
        }
    }
    return 1;
}

int valida_shift_down_pieza(int board[][COL_BOARD], Tetrimino* p)
{
    int i,j;

    for(i=0;i<TAM_TETRIMINO;i++)
    {
        for(j=0;j<TAM_TETRIMINO;j++)
        {
            if(p->forma[i][j] == 1)
            {
                int x = p->pos_x+j;
                int new_y = p->pos_y+i+1;


                if(new_y > FIL_BOARD - 1)
                {
                    return INSERTAR_PIEZA;
                }
                if(board[new_y][x] == 1)
                {
                    return INSERTAR_PIEZA;
                }
            }
        }
    }


    p->pos_y ++;
    return 0;
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

void mostrar_tablero(int board[][COL_BOARD],Tetrimino* p)
{
    int i,j;

    for(i=0;i<FIL_BOARD;i++)
    {
        for(j=0;j<COL_BOARD;j++)
        {
            if(i>=p->pos_y && i<=p->pos_y+3 && j >= p->pos_x && j<= p->pos_x+3 && i<FIL_BOARD && j <COL_BOARD)
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
