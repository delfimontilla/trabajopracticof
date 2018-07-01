#ifndef ENTRADA__H
#define ENTRADA__H 1

#include <stdio.h>

status_t abrir_archivo_entrada(parametros_t *argumentos, FILE **fentrada);
status_t leer_archivo_txt(simpletron_t ** simpletron, FILE *fentrada);
status_t leer_archivo_stdin(simpletron_t ** simpletron);
status_t leer_archivo_bin(simpletron_t ** simpletron, FILE *fentrada);

#endif