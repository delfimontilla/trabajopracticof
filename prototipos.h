#ifndef PROTOTIPOS__H
#define PROTOTIPOS__H 1

#include <stdio.h>

/*Contiene los prototipos de todas las funciones creadas*/

status_t imprimir_ayuda(void);
status_t imprimir_error(status_t st);
status_t validar_argumentos (int argc , char *argv[], parametros_t *argumentos, size_t *cant_palabras);
status_t inicializar_simpletron (simpletron_t **simpletron, size_t cant_palabras);
status_t liberar_memoria(simpletron_t ** simpletron);

#endif