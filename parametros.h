#ifndef PARAMETROS__H
#define PARAMETROS__H 1

#include <stdio.h>

typedef enum {
	TRUE,
	FALSE
}bool_t;

/*Declara una estructura para guardar la información de formato ingresada por línea de comando*/

typedef struct parametros
{
	bool_t fe_txt;/*argumento que indica que la entrada se hace en formato de texto*/
	bool_t fe_bin;/*argumento que indica que la entrada se hace en formato de bin*/
	bool_t fs_txt;/*argumento que indica que el dump se hara en formato de texto*/
	bool_t fs_bin;/*argumento que indica que el dump se hara en formato binario*/
	char * inicio_arch; /*argumento que indica que apunta al archivo de entrada*/
	char * nombre_arch; /*argumento que indica que el nombre del archivo de entrada*/
}parametros_t; /*estructura con los argumentos que son pasados al momento de ejecucion*/

#endif