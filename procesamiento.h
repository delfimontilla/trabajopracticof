#ifndef PROCESAMIENTO__H
#define PROCESAMIENTO__H 1

#include <stdio.h>
#include "tipos.h"
/* En este .h se encuentran los prototipos de las funciones utilizadas en el procesamiento.c*/
status_t abrir_archivo_entrada(parametros_t *argumentos, FILE **fentrada);
status_t leer_archivo_txt(simpletron_t ** simpletron, FILE *fentrada);
status_t leer_archivo_stdin(simpletron_t ** simpletron);
status_t leer_archivo_bin(simpletron_t ** simpletron, FILE *fentrada);

status_t abrir_archivo_salida(parametros_t *argumentos, FILE ** fsalida);
status_t imprimir_archivo_txt(simpletron_t *simpletron, FILE *fsalida);
status_t imprimir_archivo_bin (simpletron_t *simpletron, FILE *fsalida);

#endif
