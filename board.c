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

int borrar_lineas(int** b)
{
    int i, j, k, cant_lineas=0;
    int* aux;
    int** m = b;

    for(i=FIL_BOARD-1;i>= 0; i--)
    {
        if(m[i][0] == 1)
        {
            j=1;
            while(j < COL_BOARD && m[i][j] == 1)
            {
                j++;
            }
            if(j == COL_BOARD)
            {
                cant_lineas++;
                aux = *(m+i);
                for(k = i; k > 0 ; k--)
                {
                    *(m+k) = *(m+k-1);
                }
                vaciar_fila(aux);
                *(m) = aux;
                i++;
            }

        }
    }


    return cant_lineas;
}

void vaciar_fila(int* v)
{
    int i;

    for(i = 0; i < COL_BOARD; i++)
    {
        *(v+i) = 0;
    }
}
