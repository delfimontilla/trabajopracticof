#ifndef PROTOTIPOS__H
#define PROTOTIPOS__H 1

#include <stdio.h>

/*Contiene los prototipos de todas las funciones creadas*/

status_t imprimir_ayuda();
status_t imprimir_error(status_t st);
status_t validar_argumentos (int argc , char *argv[], parametros_t *argumentos, size_t *cant_palabras);
status_t inicializar_simpletron (simpletron_t **simpletron, size_t cant_palabras);

status_t abrir_archivo_entrada(parametros_t *argumentos, FILE **fentrada);
status_t abrir_archivo_salida(parametros_t *argumentos, FILE ** fsalida);

status_t leer_archivo_txt(simpletron_t ** simpletron, FILE *fentrada);
status_t leer_archivo_stdin(simpletron_t ** simpletron);
status_t leer_archivo_bin(simpletron_t ** simpletron, FILE *fentrada);

status_t imprimir_archivo_txt(simpletron_t *simpletron, FILE *fsalida);
status_t imprimir_archivo_bin (simpletron_t *simpletron, FILE *fsalida);
status_t liberar_memoria(simpletron_t ** simpletron);

status_t ejecutar_simpletron (simpletron_t * simpletron);
status_t op_leer (simpletron_t * simpletron);
status_t op_escribir(simpletron_t * simpletron);
status_t op_cargar (simpletron_t * simpletron);
status_t op_pcargar (simpletron_t * simpletron);
status_t op_guardar (simpletron_t * simpletron);
status_t op_pguardar (simpletron_t * simpletron);
status_t op_sumar(simpletron_t * simpletron);
status_t op_restar (simpletron_t * simpletron);
status_t op_dividir (simpletron_t * simpletron);
status_t op_multiplicar (simpletron_t * simpletron);
status_t op_jmp (simpletron_t * simpletron);
status_t op_djnz (simpletron_t * simpletron);

#endif