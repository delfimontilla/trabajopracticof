#ifndef STATUS__C
#define STATUS__C 1

#include <stdio.h>

status_t (*p_funciones[12])(simpletron_t *) = {op_leer,
	op_escribir,
	op_cargar,
	op_guardar,
	op_pcargar,
	op_pguardar,
	op_sumar,
	op_restar,
	op_dividir,
	op_multiplicar,
	op_jmp,
	op_djnz};

#endif