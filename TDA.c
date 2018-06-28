#include <stdio.h>
#include <stdlib.h>


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

typedef struct memoria{
	size_t usado, pedido; 
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

typedef struct nodo {
  struct nodo * siguiente;
  void * simpletron;
} nodo_t, * lista_t;




/*hacer un array de punteros a funcion, struct{opcode_t op; void(*p) ();}   
iterar con un arreglo de opcodes y un arreglo de estructuras*/