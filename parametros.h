#ifndef PARAMETROS__H
#define PARAMETROS__H 1

#include <stdio.h>

/*Declara una estructura para guardar la información de formato ingresada por línea de comando*/

typedef struct parametros
{
	const char * i;/*argumento que indica que el programa se leera del archivo pasado como opcion*/
	const char * ia;/*argumento que indica que el archivo de entrada se leera con el formato especificado como opcion*/
	const char * o;/*argumento que indica que el dump se hara en el archivo pasado como opcion*/
	const char * oa;/*argumento que indica que el dump se hara en el formato especificado como opcion*/
}parametros_t; /*estructura con los argumentos que son pasados al momento de ejecucion*/

#endif