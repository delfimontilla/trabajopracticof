#ifndef SIMPLETRON__H
#define SIMPLETRON__H 1

#include <stdio.h>

/*define un tipo de dato int, 
un tipo enumerativo para las operaciones, 
y una estructura para la Simpletron*/

typedef int palabra_t;

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

typedef enum opcode
{
	OP_LEER = 10,
	OP_ESCRIBIR = 11,
	OP_CARGAR = 20,
	OP_GUARDAR = 21,
	OP_PCARGAR = 22,
	OP_PGUARDAR = 23,
	OP_SUMAR = 30,
	OP_RESTAR = 31,
	OP_DIVIDIR = 32,
	OP_MULTIPLICAR = 33,
	OP_JMP = 40,
	OP_JMPNEG = 41,
	OP_JMPZERO = 42,
	OP_JNZ = 43,
	OP_DJNZ = 44,
	OP_HALT = 45
}opcode_t;

typedef enum 
{
	F_OP_LEER = 0,
	F_OP_ESCRIBIR = 1,
	F_OP_CARGAR = 2,
	F_OP_GUARDAR = 3,
	F_OP_PCARGAR = 4,
	F_OP_PGUARDAR = 5,
	F_OP_SUMAR = 6,
	F_OP_RESTAR = 7,
	F_OP_DIVIDIR = 8,
	F_OP_MULTIPLICAR = 9,
	F_OP_JMP = 10
}vector_punteros_t;

typedef enum bool 
{
  false = 0,
  true = 1
} bool_t;

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

typedef struct memoria{
	size_t pedido; 
	palabra_t * palabras;
} memoria_t;

typedef struct estado
{
 	memoria_t * memoria;/*vector donde estan guardadas las palabras*/
	palabra_t acumulador;/*cantidad guardada en el acumulador*/
	size_t contador_programa;/*cuenta el numero de paso y de memoria que se encuentra el programa*/
    size_t opcode; /*el codigo de operacion, que especifica la operación a realizar*/
    size_t operando; /*represeta la dirección de memoria que contiene la palabra a la que se le aplica la operación*/
}simpletron_t; /*una estructura para almacenar el estado del Simpletron*/

#endif