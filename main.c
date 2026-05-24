#include <stdio.h>
#include <stdlib.h>
#include "render.h"
#include "board.h"
#include "tetriminos.h"
#include "game.h"
#include "score.h"
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "GBT/gbt.h"

int main(int argc, char* argv[])
{
    if (gbt_iniciar() != 0) {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    Cfg cfg_ejecutable = CFG_VGA;

    if(argc == 3)
    {
        if(strcmp(argv[1], "CGA") == 0)
            cfg_ejecutable = CFG_CGA;
        else
            cfg_ejecutable = CFG_VGA;

        cfg_ejecutable.escala = (uint8_t)atoi(argv[2]);

        if(cfg_ejecutable.escala == 0)
        {
            fprintf(stderr, "Escala invalida\n");
            return -1;
        }
    }



    if (gbt_crear_ventana("Tetris", cfg_ejecutable.ancho, cfg_ejecutable.alto, cfg_ejecutable.escala) != 0) {
        fprintf(stderr, "Error al crear ventana: %s\n", gbt_obtener_log());
        return -1;
    }


    EstadoJuego estado;
    inicializar_estado(&estado);

    tGBT_Temporizador *temporizador = gbt_temporizador_crear(estado.velocidad_ms/1000.0);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador: %s\n", gbt_obtener_log());
        return -1;
    }
    tGBT_Temporizador *temp_fijacion = gbt_temporizador_crear(estado.velocidad_fijacion_ms/1000.0);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador de fijacion: %s\n", gbt_obtener_log());
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

        if (gbt_tecla_presionada(GBTK_q)) {
            valida_rotacion_pieza_izq(board, &tetrimino);
        }

        if(hay_pieza_activa == 0)
        {
            hay_pieza_activa = valida_colision_pieza(board,&tetrimino);
            if (hay_pieza_activa == COLISION)
            {
                corriendo = COLISION; //fin de la ejecucion.
            }
        }

        if(gbt_tecla_sostenida(GBTK_ABAJO))
        {
            resul_shift_down = valida_shift_down_pieza(board,&tetrimino);
            if(resul_shift_down != INSERTAR_PIEZA)
            {
                sumar_puntos_bajada_manual(&estado);
            }

        }

        if(gbt_temporizador_consumir(temporizador))
        {
            resul_shift_down = valida_shift_down_pieza(board,&tetrimino);
        }

        if(resul_shift_down == INSERTAR_PIEZA)
        {
            if(gbt_temporizador_consumir(temp_fijacion))
            {
                colocar_pieza(board,&tetrimino);
                lineas_completadas = borrar_lineas(board);
                sumar_puntos_lineas(&estado, lineas_completadas);
                registrar_pieza_caida(&estado);

                gbt_temporizador_destruir(temporizador);
                temporizador = gbt_temporizador_crear(estado.velocidad_ms / 1000.0);
                gbt_temporizador_destruir(temp_fijacion);
                temp_fijacion = gbt_temporizador_crear(estado.velocidad_fijacion_ms / 1000.0);

                tetrimino = crear_tetrimino(TAM_TETRIMINO,&vec_enum);
                resul_shift_down = 0;
                hay_pieza_activa = 0;
            }


        }

        dibujar_tablero(board,&tetrimino,&estado);
        gbt_esperar(100);
    }

    gbt_temporizador_destruir(temporizador);
    gbt_temporizador_destruir(temp_fijacion);
    gbt_destruir_ventana();
    gbt_cerrar();
    destruirBoard((void**)board,FIL_BOARD);
    return 0;
}
