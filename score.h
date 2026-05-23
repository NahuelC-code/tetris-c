#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#define VELOCIDAD_INICIAL_MS 1000.0
#define FACTOR_VELOCIDAD     0.97
#define PIEZAS_POR_NIVEL     10

typedef struct {
    int puntos;
    int piezas_caidas;
    double velocidad_ms;      // velocidad de caida actual
    double velocidad_fijacion_ms; // 50% de velocidad_ms
} EstadoJuego;

void inicializar_estado(EstadoJuego* e);
void sumar_puntos_lineas(EstadoJuego* e, int lineas);
void sumar_puntos_bajada_manual(EstadoJuego* e);
void registrar_pieza_caida(EstadoJuego* e);

#endif // SCORE_H_INCLUDED
