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

    if (gbt_crear_ventana("Tetris", 128, 128, 5) != 0) {
        fprintf(stderr, "Error al crear ventana: %s\n", gbt_obtener_log());
        return -1;
    }

    tGBT_Temporizador *temporizador = gbt_temporizador_crear(0.5);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador: %s\n", gbt_obtener_log());
        return -1;
    }

    int** board = (int**)create_init_board(FIL_BOARD,COL_BOARD,sizeof(int));

    Tetrimino pieza_o = {
        .pos_y = 0,
        .pos_x = (COL_BOARD - TAM_TETRIMINO)/2,
        .forma = {
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
            }
    };
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
            valida_shift_left_pieza(board, &pieza_o);
        }

        if (gbt_tecla_sostenida(GBTK_DERECHA)) {
            valida_shift_right_pieza(board, &pieza_o);
        }

        if (gbt_tecla_sostenida(GBTK_ABAJO)) {
            valida_shift_down_pieza(board, &pieza_o);
        }

        if (gbt_tecla_presionada(GBTK_ARRIBA)) {
            valida_rotacion_pieza(board, &pieza_o);
        }

        if(hay_pieza_activa == 0)
        {
            hay_pieza_activa = valida_colision_pieza(board,&pieza_o);
            if (hay_pieza_activa == COLISION)
            {
                corriendo = COLISION; //fin de la ejecucion.
            }
        }

        if(gbt_temporizador_consumir(temporizador))
        {
            resul_shift_down = valida_shift_down_pieza(board,&pieza_o);
        }

        if(resul_shift_down == 1)
        {
            colocar_pieza(board,&pieza_o);
            lineas_completadas = borrar_lineas(board);
            pieza_o.pos_y = 0;
            pieza_o.pos_x = (COL_BOARD - TAM_TETRIMINO)/2;
            resul_shift_down = 0;
            hay_pieza_activa = 0;
        }

        mostrar_tablero(board,&pieza_o);

        gbt_esperar(100);
        system("cls");
    }

    gbt_temporizador_destruir(temporizador);
    gbt_destruir_ventana();
    gbt_cerrar();

    print_board(board);
    destruirBoard((void**)board,FIL_BOARD);
    return 0;
}
