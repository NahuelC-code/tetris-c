#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#define VELOCIDAD_INICIAL_MS 1000.0
#define FACTOR_VELOCIDAD     0.97
#define PIEZAS_POR_NIVEL     10
#define MAX_RANKING 10

typedef struct {
    int puntos;
    int piezas_caidas;
    int lineas_completadas;
    double velocidad_ms;
    double velocidad_fijacion_ms;
} EstadoJuego;

typedef struct {
    char nick[20];
    int puntos;
} EntradaRanking;

void inicializar_estado(EstadoJuego* e);
void sumar_puntos_lineas(EstadoJuego* e, int lineas);
void sumar_puntos_bajada_manual(EstadoJuego* e);
void registrar_pieza_caida(EstadoJuego* e);
void guardar_ranking(const char* nick, int puntos);
void cargar_ranking(EntradaRanking* ranking, int* cantidad);

#endif // SCORE_H_INCLUDED
