#include <stdio.h>
#include <stdlib.h>

#include "leng_espanol.h"


typedef int palabra_t;

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

int main()
{
    FILE *fp;
    simpletron_t simpletron;
    fp = fopen("dump", "rb");


    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    while( fread(&simpletron, sizeof(simpletron_t), 1, fp) == 1 )
    {
        printf("%s\n", MSJ_REGISTRO);
        printf("%25s: %6i\n",MSJ_ACUM, simpletron.acumulador );
        printf("%25s: %6lu\n",MSJ_CONT_PROG, simpletron.contador_programa );
        printf("%25s: %6i\n",MSJ_INST, simpletron.memoria->palabras[simpletron.contador_programa] );   
        printf("%25s: %6lu\n",MSJ_OPCODE, simpletron.opcode );
        printf("%25s: %6lu\n",MSJ_OPERANDO, simpletron.operando );

}
    fclose(fp);
    return 0;
}
