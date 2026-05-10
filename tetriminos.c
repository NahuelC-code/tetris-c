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


Tetrimino crear_tetrimino(int columnas,Vector_numeros* v)
{
    Tetrimino t;

    t.pos_y = 0;
    t.pos_x = columnas / 2;
    int pos = random_num_vec(v);
    int id = v->vec[pos];

    for(int i=0;i<TAM_TETRIMINO;i++)
    {
        for(int j=0;j<TAM_TETRIMINO;j++)
        {
            t.forma[i][j] = piezas[id][i][j];
        }
    }

    eliminar_vec_num_posicion(v,pos);

    return t;

}

Vector_numeros crear_vector(int ce)
{
    Vector_numeros v;
    v.ce = ce;
    v.ce_max = ce;
    inicializa_vector_numeros(&v);

    return v;
}
void inicializa_vector_numeros(Vector_numeros* v)
{
    int i;

    for(i=0;i<v->ce_max;i++)
    {
        v->vec[i] = i ;
    }

    if(v->ce == 0 )
        v->ce = v->ce_max;

}

int random_num_vec(Vector_numeros* v)
{
    int id;
    if(v->ce == 0)
    {
        inicializa_vector_numeros(v);
    }
    id = rand() % v->ce;

    return id;
}

void eliminar_vec_num_posicion(Vector_numeros* v, int pos)
{
    int i;

    if(pos < 0 || pos >= v->ce)
        return;

    for(i = pos; i < v->ce - 1; i++)
    {
        v->vec[i] = v->vec[i + 1];
    }
    v->ce--;
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
