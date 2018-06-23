#ifndef PARAMETROS__H
#define PARAMETROS__H 1

#include <stdio.h>

typedef enum {
	TRUE,
	FALSE,
}bool_t;

/*Declara una estructura para guardar la información de formato ingresada por línea de comando*/

typedef struct parametros
{
	const bool_t * f_txt;/*argumento que indica que el dump se hara en formato de texto*/
	const bool_t * f_bin;/*argumento que indica que el dump se hara en formato binario*/
	char * inicio_arch;
	const char * archivo;
}parametros_t; /*estructura con los argumentos que son pasados al momento de ejecucion*/

#endif