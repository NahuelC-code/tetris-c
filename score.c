#include "score.h"

static const int PUNTOS_LINEAS[] = {0, 100, 300, 500, 800};

void inicializar_estado(EstadoJuego* e)
{
    e->puntos = 0;
    e->piezas_caidas = 0;
    e->velocidad_ms = VELOCIDAD_INICIAL_MS;
    e->velocidad_fijacion_ms = VELOCIDAD_INICIAL_MS * 0.5;
}

void sumar_puntos_lineas(EstadoJuego* e, int lineas)
{
    if(lineas >= 1 && lineas <= 4)
        e->puntos += PUNTOS_LINEAS[lineas];
}

void sumar_puntos_bajada_manual(EstadoJuego* e)
{
    e->puntos += 1;
}

void registrar_pieza_caida(EstadoJuego* e)
{
    e->piezas_caidas++;
    if(e->piezas_caidas % PIEZAS_POR_NIVEL == 0)
    {
        e->velocidad_ms *= FACTOR_VELOCIDAD;
        e->velocidad_fijacion_ms = e->velocidad_ms * 0.5;
    }
}
