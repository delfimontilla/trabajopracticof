#ifndef PARAMETROS__H
#define PARAMETROS__H 1

#include <stdio.h>

typedef enum bool 
{
  false = 0,
  true = 1
} bool_t;

typedef enum retval 
{
  RV_SUCCESS = 0,
  RV_ILLEGAL = 1,
  RV_NOSPACE = 2,
  RV_ERROR = 3,
  RV_NOTIMPLEMENTED = 4,
  RV_MISSING_ARGS = 5
} retval_t;

/*Declara una estructura para guardar la información de formato ingresada por línea de comando*/

typedef struct parametros
{
	bool_t fmt_ent_txt;/*argumento que indica que la entrada se hace en formato de texto*/
	bool_t fmt_ent_bin;/*argumento que indica que la entrada se hace en formato de bin*/
	bool_t fmt_ent_stdin; /*argumento que indica que la entrada se hace por stdin*/
	bool_t fmt_sal_txt;/*argumento que indica que el dump se hara en formato de texto*/
	bool_t fmt_sal_bin;/*argumento que indica que el dump se hara en formato binario*/
	char * inicio_arch; /*argumento que indica que apunta al archivo de entrada*/
	char * nombre_arch; /*argumento que indica que el nombre del archivo de entrada*/
}parametros_t; /*estructura con los argumentos que son pasados al momento de ejecucion*/

#endif