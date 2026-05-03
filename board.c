#include "board.h"
#include <stdio.h>


void** create_init_board(int filas, int columnas, size_t tamElem)
{
    void** m = malloc(filas * sizeof(void*));

    if(!m)
    {
        return NULL;
    }

    void** ult = m + (filas - 1);

    for(void** i = m; i <= ult; i++)
    {
        *i = calloc(columnas, tamElem);

        if(!*i)
        {
            destruirBoard(m, i - m);
            return NULL;
        }
    }

    return m;
}

void destruirBoard(void** m, int filas)
{
    void** ult = m + (filas - 1);

    for(void** i = m; i <= ult; i++)
    {
        free(*i);
    }

    free(m);
}

void print_board(int** b)
{
    for (int i=0;i<FIL_BOARD;i++)
    {
        for (int j=0;j<COL_BOARD;j++)
        {
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
}
