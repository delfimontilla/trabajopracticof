#ifndef SIMPLETRON__H
#define SIMPLETRON__H 1

#include <stdio.h>

/*define un tipo de dato int, 
un tipo enumerativo para las operaciones, 
y una estructura para la Simpletron*/


typedef int palabra_t;

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

typedef struct estado
{
	palabra_t acumulador;/*posicion de memoria del acumulador*/
	size_t contador_programa;/*cuenta el numero de paso y de memoria que se encuentra el programa*/
    palabra_t *palabras;/*vector donde estan guardadas las palabras*/
    size_t opcode; /*el codigo de operacion, que especifica la operación a realizar*/
    size_t operando; /*represeta la dirección de memoria que contiene la palabra a la que se le aplica la operación*/
}simpletron_t; /*una estructura para almacenar el estado del Simpletron*/

#endif