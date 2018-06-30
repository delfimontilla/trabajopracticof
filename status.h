#ifndef STATUS__H
#define STATUS__H 1

#include <stdio.h>

/*Se define un nuevo tipo enumerativo que se usará para conocer
el estado de las funciones y se declara un arreglo de char 
con los mensajes de los estados posibles*/

typedef enum
{
	ST_OK,/*RV_SUCCESS*/
	ST_ERROR_PTR_NULO,/*RV_ILLEGAL*/
	ST_ERROR_CANT_ARG,
	ST_ERROR_FUERA_DE_RANGO,
	ST_ERROR_LECTURA,
	ST_ERROR_PALABRA_NEG,
	ST_ERROR_PALABRA_VACIA,
	ST_ERROR_APERTURA_ARCHIVO,
	ST_ERROR_ARG_INV,
	ST_ERROR_CANT_PALABRAS,
	ST_ERROR_NO_NUMERICO,
	ST_ERROR_NO_MEM,
	ST_ERROR_LIBERAR_MEM,
	ST_ERROR_NADA_QUE_CARGAR,
	ST_AYUDA,
	ST_SALIR
} status_t;

#endif