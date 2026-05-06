#include "tetriminos.h"

int piezas[CANT_PIEZAS][TAM_TETRIMINO][TAM_TETRIMINO] =
{
    {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    {
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }
};


Tetrimino crear_tetrimino(int columnas)
{
    Tetrimino t;

    t.pos_y = 0;
    t.pos_x = columnas / 2;
   // t.forma =

    return t;

}

void rotar_tetrimino(Tetrimino* p)
{
    int i,j,aux;

    for(i=0;i<TAM_TETRIMINO;i++)
    {
        for(j=i+1;j<TAM_TETRIMINO;j++)
        {
            aux = p->forma[i][j];
            p->forma[i][j] = p->forma[j][i];
            p->forma[j][i] = aux;
        }
    }

    for(i=0;i<TAM_TETRIMINO;i++)
    {
        for(j=0;j<TAM_TETRIMINO/2;j++)
        {
            aux = p->forma[i][j];
            p->forma[i][j] = p->forma[i][TAM_TETRIMINO - 1 - j];
            p->forma[i][TAM_TETRIMINO - 1 - j] = aux;
        }
    }

    normalizar_tetrimino(p->forma);
}

void normalizar_tetrimino(int m[TAM_TETRIMINO][TAM_TETRIMINO])
{
    int min_fila = TAM_TETRIMINO, min_col = TAM_TETRIMINO;

    for (int i = 0; i < TAM_TETRIMINO; i++)
    {
        for (int j = 0; j < TAM_TETRIMINO; j++)
        {
            if (m[i][j])
            {
                if (i < min_fila) min_fila = i;
                if (j < min_col)  min_col = j;
            }
        }
    }

    int aux[TAM_TETRIMINO][TAM_TETRIMINO] = {0};

    for (int i = min_fila; i < TAM_TETRIMINO; i++)
    {
        for (int j = min_col; j < TAM_TETRIMINO; j++)
        {
            if (m[i][j])
            {
                aux[i - min_fila][j - min_col] = 1;
            }
        }
    }

    for (int i = 0; i < TAM_TETRIMINO; i++)
        for (int j = 0; j < TAM_TETRIMINO; j++)
            m[i][j] = aux[i][j];
}
