#ifndef OPERACIONES__H
#define OPERACIONES__H 1

#include <stdio.h>

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