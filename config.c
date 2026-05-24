#include "config.h"
#include <stdio.h>

void config_default(Config* c)
{
    c->paleta = PALETA_CLASICA;
    c->resolucion = RES_VGA;
    c->velocidad_ms = VEL_NORMAL;
}

void config_cargar(Config* c)
{
    FILE* f = fopen("config.bin", "rb");
    if(!f)
    {
        printf("No existe config.bin, usando defaults\n");
        config_default(c);
        return;
    }
    fread(c, sizeof(Config), 1, f);
    fclose(f);
}

void config_guardar(Config* c)
{
    FILE* f = fopen("config.bin", "wb");
    if(!f) return;
    fwrite(c, sizeof(Config), 1, f);
    fclose(f);
}
