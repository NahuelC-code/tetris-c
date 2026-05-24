#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define PALETA_CLASICA    0
#define PALETA_RETRO      1

#define VEL_LENTA   2000.0
#define VEL_NORMAL  1000.0
#define VEL_RAPIDA   500.0

#define RES_CGA 0
#define RES_VGA 1

typedef struct {
    int paleta;
    int resolucion;
    double velocidad_ms;
} Config;

void config_cargar(Config* c);
void config_guardar(Config* c);
void config_default(Config* c);

#endif // CONFIG_H_INCLUDED
