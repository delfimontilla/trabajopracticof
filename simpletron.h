#ifndef SIMPLETRON__H
#define SIMPLETRON__H 1

#include <stdio.h>
#include "tipos.h"

/*Contiene los prototipos de las funciones que crean, ejecutan y destruyen una simpletron*/

status_t inicializar_simpletron (simpletron_t **simpletron, size_t cant_palabras);
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
