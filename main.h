#ifndef MAIN__H
#define MAIN__H 1

#include <stdio.h>

/*Contiene los prototipos de todas las funciones creadas*/

status_t validar_argumentos (int argc , char *argv[], parametros_t *argumentos, size_t *cant_palabras, size_t *j);
status_t imprimir_ayuda();
status_t imprimir_error(status_t st);

#endif