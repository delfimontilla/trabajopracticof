#ifndef ERRORES__C
#define ERRORES__C 1

#include <stdio.h>
#include "tipos.h"

#ifdef LENG_ESPANOL
#include "leng_espanol.h"

#elif defined (LENG_INGLES)
#include "leng_ingles.h"

#else
#include "leng_espanol.h"
#endif

/*Este .c contiene el vector de errores del programa, cuyas macros se encuentran en los .h de idiomas*/

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
	MSJ_ERROR_EJECUCION,
	MSJ_SALIR
};

status_t imprimir_error(status_t st)
/*Imprime el error correspondiente al status pasado*/
{
  fprintf(stderr, "%s\n", errmsg[st]);
	return ST_OK;
}

#endif
