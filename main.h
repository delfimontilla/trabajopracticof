#ifndef MAIN__H
#define MAIN__H 1

#include <stdio.h>

/*Contiene los prototipos de las funciones que interactuan con la terminal directamente*/

status_t validar_argumentos (int argc , char *argv[], parametros_t *argumentos, size_t *cant_palabras, size_t *posicion_arch);
status_t imprimir_ayuda();
status_t imprimir_error(status_t st);

#endif