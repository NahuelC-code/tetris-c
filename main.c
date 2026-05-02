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



    tGBT_Temporizador *temporizador = gbt_temporizador_crear(0.2);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador para los dibujos: %s\n", gbt_obtener_log());
        return -1;
    }



    int board[FIL_BOARD][COL_BOARD];
    init_board(board);

    Tetrimino pieza_o = { .pos_y = 0, //reemplazar por sistema de generación de piezas
                        .pos_x = (COL_BOARD - TAM_TETRIMINO)/2,
                        .forma =   {{0,1,1,0},
                                    {0,1,1,0},
                                    {0,0,0,0},
                                    {0,0,0,0}}};


    int corriendo = 1;
    int hay_pieza_activa = 0;
    int resul_shift_down = 0;

    while(corriendo)
    {
        gbt_procesar_entrada();
        if(hay_pieza_activa == 0)
        {
            hay_pieza_activa = valida_spawn_pieza(board,&pieza_o) ;
            if (hay_pieza_activa == GAME_OVER)
            {
                corriendo = 0;
            }
        }

        if(gbt_temporizador_consumir(temporizador))
        {
            resul_shift_down = valida_shift_down_pieza(board,&pieza_o);
        }

        if(resul_shift_down == 1)
        {
            colocar_pieza(board,&pieza_o);
            pieza_o.pos_y = 0; //reemplazar por sistema de generación de piezas
            pieza_o.pos_x = (COL_BOARD - TAM_TETRIMINO)/2; //reemplazar por sistema de generación de piezas
            resul_shift_down = 0;
            hay_pieza_activa = 0;
        }
        mostrar_tablero(board,&pieza_o);//Reemplazar por render GBT
        gbt_esperar(100); //Reemplazar por render GBT
        system("cls"); // Reemplazar por render GBT
    }



    gbt_temporizador_destruir(temporizador);
    gbt_cerrar();
    print_board(board);
    system("pause");
    return 0;
}
