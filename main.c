#include <stdio.h>
#include <stdlib.h>
#include "render.h"
#include "game.h"
#include <stdint.h>
#include <string.h>
#include "GBT/gbt.h"

/*
Apellido: CAVALLARO, NAHUEL ADRIÁN
DNI: 43587894
Usuario: NahuelC-code
Entrega: Sí

Apellido: FRANCO, LUCIO
DNI: 44838882
Usuario: -
Entrega: No

Apellido: RUBONI, CARLOS OSCAR
DNI: 42290616
Usuario: -
Entrega: No
*/


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



    Config config;
    config_cargar(&config);

    if (gbt_crear_ventana("Tetris", cfg_ejecutable.ancho, cfg_ejecutable.alto, cfg_ejecutable.escala) != 0) {
        fprintf(stderr, "Error al crear ventana: %s\n", gbt_obtener_log());
        return -1;
    }

    if(config.paleta == PALETA_CLASICA)
        aplicar_paleta_clasica();
    else
        aplicar_paleta_retro();


    int corriendo = 1;

    char nick[20] = {0};
    int nick_len = 0;

    while(corriendo)
    {
        gbt_procesar_entrada();
        dibujar_pantalla_presentacion(cfg_ejecutable);
        if(gbt_tecla_presionada(GBTK_ESCAPE))
        {
            corriendo = 0;
            break;
        }
        if(gbt_obtener_tecla_presionada() != GBTK_DESCONOCIDA)
            break;
        gbt_esperar(100);
    }

    while(corriendo)
    {
        gbt_procesar_entrada();

        if(gbt_tecla_presionada(GBTK_ESCAPE))
        {
            corriendo = 0;
            break;
        }

        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

        if(tecla == GBTK_ENTER && nick_len > 0)
            break;

        if(tecla == GBTK_RETROCESO && nick_len > 0)
        {
            nick_len--;
            nick[nick_len] = '\0';
        }

        if(nick_len < 8)
        {
            if(tecla >= GBTK_a && tecla <= GBTK_z)
            {
                nick[nick_len] = (char)tecla;
                nick_len++;
                nick[nick_len] = '\0';
            }
        }

        dibujar_pantalla_nombre(nick, cfg_ejecutable);
        gbt_esperar(100);
    }

    int jugando = corriendo;
    while(jugando)
    {
        int opcion_principal = 0;
        int en_menu_principal = 1;
        while(en_menu_principal)
        {
            gbt_procesar_entrada();
            dibujar_menu_principal(opcion_principal, cfg_ejecutable);

            if(gbt_tecla_presionada(GBTK_ARRIBA))
                if(opcion_principal > 0) opcion_principal--;

            if(gbt_tecla_presionada(GBTK_ABAJO))
                if(opcion_principal < 2) opcion_principal++;

            if(gbt_tecla_presionada(GBTK_ENTER))
            {
                if(opcion_principal == 0)
                    en_menu_principal = 0;
                else if(opcion_principal == 1)
                {
                    int opcion_config = 0;
                    int en_menu_config = 1;
                    while(en_menu_config)
                    {
                        gbt_procesar_entrada();
                        dibujar_menu_config(&config, opcion_config, cfg_ejecutable);

                        if(gbt_tecla_presionada(GBTK_ARRIBA))
                            if(opcion_config > 0) opcion_config--;

                        if(gbt_tecla_presionada(GBTK_ABAJO))
                            if(opcion_config < 3) opcion_config++;

                        if(gbt_tecla_presionada(GBTK_ENTER))
                        {
                            if(opcion_config == 0)
                            {
                                if(config.paleta == PALETA_CLASICA) config.paleta = PALETA_RETRO;
                                else config.paleta = PALETA_CLASICA;
                            }
                            else if(opcion_config == 1)
                            {
                                if(config.resolucion == RES_CGA) config.resolucion = RES_VGA;
                                else config.resolucion = RES_CGA;
                            }
                            else if(opcion_config == 2)
                            {
                                if(config.velocidad_ms == VEL_LENTA) config.velocidad_ms = VEL_NORMAL;
                                else if(config.velocidad_ms == VEL_NORMAL) config.velocidad_ms = VEL_RAPIDA;
                                else config.velocidad_ms = VEL_LENTA;
                            }
                            else if(opcion_config == 3)
                            {
                                config_guardar(&config);
                                en_menu_config = 0;
                            }
                        }

                        if(gbt_tecla_presionada(GBTK_ESCAPE))
                        {
                            config_guardar(&config);
                            en_menu_config = 0;
                        }
                        gbt_esperar(100);
                    }
                }
                else if(opcion_principal == 2)
                {
                    en_menu_principal = 0;
                    jugando = 0;
                }
            }

            if(gbt_tecla_presionada(GBTK_ESCAPE))
            {
                en_menu_principal = 0;
                jugando = 0;
            }
            gbt_esperar(100);
        }

        if(config.resolucion == RES_CGA)
            cfg_ejecutable = CFG_CGA;
        else
            cfg_ejecutable = CFG_VGA;

        gbt_destruir_ventana();
        if(gbt_crear_ventana("Tetris", cfg_ejecutable.ancho, cfg_ejecutable.alto, cfg_ejecutable.escala) != 0)
        {
            fprintf(stderr, "Error al crear ventana: %s\n", gbt_obtener_log());
            return -1;
        }
        if(config.paleta == PALETA_CLASICA)
            aplicar_paleta_clasica();
        else
            aplicar_paleta_retro();

        if(!jugando)
            break;

        EstadoJuego estado;
        inicializar_estado(&estado);
        estado.velocidad_ms = config.velocidad_ms;
        estado.velocidad_fijacion_ms = config.velocidad_ms * 0.5;

        tGBT_Temporizador *temporizador = gbt_temporizador_crear(estado.velocidad_ms/1000.0);
        if (!temporizador) {
            fprintf(stderr, "Error al crear el temporizador: %s\n", gbt_obtener_log());
            return -1;
        }
        tGBT_Temporizador *temp_fijacion = gbt_temporizador_crear(estado.velocidad_fijacion_ms/1000.0);
        if (!temp_fijacion) {
            fprintf(stderr, "Error al crear el temporizador de fijacion: %s\n", gbt_obtener_log());
            return -1;
        }

        int** board = (int**)create_init_board(FIL_TOTAL, COL_BOARD, sizeof(int));
        Vector_numeros vec_enum = crear_vector(CANT_PIEZAS);
        Tetrimino tetrimino = crear_tetrimino(TAM_TETRIMINO, &vec_enum);
        int hay_pieza_activa = 0;
        int resul_shift_down = 0;
        int lineas_completadas;
        corriendo = 1;

        while(corriendo)
        {
            gbt_procesar_entrada();

            if (gbt_tecla_presionada(GBTK_ESCAPE)) {
                corriendo = 0;
            }

            if(gbt_tecla_presionada(GBTK_p))
            {
                gbt_temporizador_pausar(temporizador);
                gbt_temporizador_pausar(temp_fijacion);
                int pausado = 1;
                while(pausado)
                {
                    gbt_procesar_entrada();
                    dibujar_pausa(cfg_ejecutable);
                    if(gbt_tecla_presionada(GBTK_p))
                        pausado = 0;
                    gbt_esperar(100);
                }
                gbt_temporizador_reanudar(temporizador);
                gbt_temporizador_reanudar(temp_fijacion);
            }

            if(resul_shift_down != INSERTAR_PIEZA)
            {
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
            }

            if(hay_pieza_activa == 0)
            {
                hay_pieza_activa = valida_colision_pieza(board,&tetrimino);
                if (hay_pieza_activa == COLISION)
                {
                    corriendo = COLISION;
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
                    estado.lineas_completadas += lineas_completadas;
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

            dibujar_tablero(board,&tetrimino,&estado,config.paleta,cfg_ejecutable, nick);
            gbt_esperar(100);
        }

        while(corriendo == COLISION)
        {
            gbt_procesar_entrada();
            dibujar_game_over(&estado, nick, cfg_ejecutable);
            if(gbt_tecla_presionada(GBTK_r))
                break;
            if(gbt_tecla_presionada(GBTK_ESCAPE))
            {
                jugando = 0;
                break;
            }
            gbt_esperar(100);
        }
        gbt_temporizador_destruir(temporizador);
        gbt_temporizador_destruir(temp_fijacion);
        destruirBoard((void**)board,FIL_TOTAL);
    }

    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}
