#include <stdio.h>
#include <stdlib.h>
#include "render.h"
#include "board.h"
#include "tetriminos.h"
#include "game.h"
#include <time.h>
#include <stdint.h>
#include "GBT/gbt.h"

int main()
{
    if (gbt_iniciar() != 0) {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    if (gbt_crear_ventana("Tetris", 80, 160, 3) != 0) {
        fprintf(stderr, "Error al crear ventana: %s\n", gbt_obtener_log());
        return -1;
    }

    tGBT_Temporizador *temporizador = gbt_temporizador_crear(0.5);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador: %s\n", gbt_obtener_log());
        return -1;
    }

    int** board = (int**)create_init_board(FIL_BOARD,COL_BOARD,sizeof(int));

    Vector_numeros vec_enum ;
    vec_enum = crear_vector(CANT_PIEZAS);
    Tetrimino tetrimino;
    tetrimino = crear_tetrimino(TAM_TETRIMINO,&vec_enum);
    int corriendo = 1;
    int hay_pieza_activa = 0;
    int resul_shift_down = 0;
    int lineas_completadas;

    while(corriendo)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE)) {
            corriendo = 0;
        }


        if (gbt_tecla_sostenida(GBTK_IZQUIERDA)) {
            valida_shift_left_pieza(board, &tetrimino);
        }

        if (gbt_tecla_sostenida(GBTK_DERECHA)) {
            valida_shift_right_pieza(board, &tetrimino);
        }

        if (gbt_tecla_presionada(GBTK_ARRIBA)) {
            valida_rotacion_pieza(board, &tetrimino);
        }

        if(hay_pieza_activa == 0)
        {
            hay_pieza_activa = valida_colision_pieza(board,&tetrimino);
            if (hay_pieza_activa == COLISION)
            {
                corriendo = COLISION; //fin de la ejecucion.
            }
        }

        if(gbt_tecla_sostenida(GBTK_ABAJO) || gbt_temporizador_consumir(temporizador))
        {
            resul_shift_down = valida_shift_down_pieza(board,&tetrimino);
        }

        if(resul_shift_down == 1)
        {
            colocar_pieza(board,&tetrimino);
            lineas_completadas = borrar_lineas(board);
            tetrimino = crear_tetrimino(TAM_TETRIMINO,&vec_enum);
            resul_shift_down = 0;
            hay_pieza_activa = 0;
        }

        //mostrar_tablero(board,&tetrimino);
        dibujar_tablero(board,&tetrimino);
        gbt_esperar(100);
        //system("cls");
    }

    gbt_temporizador_destruir(temporizador);
    gbt_destruir_ventana();
    gbt_cerrar();

   // print_board(board);
    destruirBoard((void**)board,FIL_BOARD);
    return 0;
}
