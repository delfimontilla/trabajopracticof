#ifndef STATUS__C
#define STATUS__C 1

#include <stdio.h>

const char * errmsg[] = {
	MSJ_OK,
	MSJ_ERROR_PTR_NULO,
	MSJ_ERROR_CANT_ARG,
	MSJ_ERROR_FUERA_DE_RANGO,
	MSJ_ERROR_LECTURA,
	MSJ_ERROR_PALABRA_NEG,
	MSJ_ERROR_PALABRA_VACIA,
	MSJ_ERROR_APERTURA_ARCHIVO,
	MSJ_ERROR_ARG_INV,
	MSJ_ERROR_CANT_PALABRAS,
	MSJ_ERROR_NO_NUMERICO,
	MSJ_ERROR_NO_MEM,
	MSJ_ERROR_LIBERAR_MEM,
	MSJ_ERROR_NADA_QUE_CARGAR,
	MSJ_AYUDA,
	MSJ_SALIR
};

status_t (*x[])(simpletron_t *) = [op_leer(),
	op_escribir(),
	op_cargar(),
	op_guardar(),
	op_pcargar(),
	op_pguardar(),
	op_sumar(),
	op_restar(),
	op_dividir(),
	op_multiplicar(),
	op_jmp(),
	op_djnz()];

#endif