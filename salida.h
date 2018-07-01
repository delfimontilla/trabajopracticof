#ifndef ENTRADA__H
#define ENTRADA__H 1

#include <stdio.h>

status_t abrir_archivo_salida(parametros_t *argumentos, FILE ** fsalida);
status_t imprimir_archivo_txt(simpletron_t *simpletron, FILE *fsalida);
status_t imprimir_archivo_bin (simpletron_t *simpletron, FILE *fsalida);

#endif