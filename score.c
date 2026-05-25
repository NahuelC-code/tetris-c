#include "score.h"
#include <string.h>
#include <stdio.h>

static const int PUNTOS_LINEAS[] = {0, 100, 300, 500, 800};

void inicializar_estado(EstadoJuego* e)
{
    e->puntos = 0;
    e->piezas_caidas = 0;
    e->lineas_completadas = 0;
    e->velocidad_ms = VELOCIDAD_INICIAL_MS;
    e->velocidad_fijacion_ms = VELOCIDAD_INICIAL_MS * 0.5;
}

void sumar_puntos_lineas(EstadoJuego* e, int lineas)
{
   int nivel;
    if(lineas >= 1 && lineas <= 4)
    {
        nivel = e->piezas_caidas / PIEZAS_POR_NIVEL + 1;
        e->puntos += PUNTOS_LINEAS[lineas] * nivel;
    }
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

void guardar_ranking(const char* nick, int puntos)
{
    EntradaRanking ranking[MAX_RANKING];
    int cantidad = 0;
    int i, j;
    EntradaRanking aux;

    cargar_ranking(ranking, &cantidad);

    if(cantidad == MAX_RANKING && puntos <= ranking[MAX_RANKING - 1].puntos)
        return;

    if(cantidad < MAX_RANKING)
    {
        strncpy(ranking[cantidad].nick, nick, 19);
        ranking[cantidad].nick[19] = '\0';
        ranking[cantidad].puntos = puntos;
        cantidad++;
    }
    else
    {
        strncpy(ranking[MAX_RANKING - 1].nick, nick, 19);
        ranking[MAX_RANKING - 1].nick[19] = '\0';
        ranking[MAX_RANKING - 1].puntos = puntos;
    }

    for(i = 0; i < cantidad - 1; i++)
    {
        for(j = 0; j < cantidad - 1 - i; j++)
        {
            if(ranking[j].puntos < ranking[j+1].puntos)
            {
                aux = ranking[j];
                ranking[j] = ranking[j+1];
                ranking[j+1] = aux;
            }
        }
    }

    FILE* f = fopen("ranking.bin", "wb");
    if(!f) return;
    fwrite(&cantidad, sizeof(int), 1, f);
    fwrite(ranking, sizeof(EntradaRanking), cantidad, f);
    fclose(f);
}

void cargar_ranking(EntradaRanking* ranking, int* cantidad)
{
    *cantidad = 0;
    FILE* f = fopen("ranking.bin", "rb");
    if(!f) return;
    fread(cantidad, sizeof(int), 1, f);
    if(*cantidad > MAX_RANKING)
    {
        *cantidad = MAX_RANKING;
    }

    fread(ranking, sizeof(EntradaRanking), *cantidad, f);
    fclose(f);
}
