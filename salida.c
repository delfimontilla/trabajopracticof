#ifndef SALIDA__C
#define SALIDA__C 1

#include <stdio.h>
#include "salida.h"

status_t abrir_archivo_salida (parametros_t * argumentos, FILE ** fsalida){
	
	if(argumentos->fmt_sal_txt==true)
	{
		if((*fsalida=fopen(argumentos->nombre_arch_sal,"wt"))==NULL)
		{	
			return ST_ERROR_APERTURA_ARCHIVO;
		}	
	}
	else if(argumentos->fmt_sal_bin==true)
	{
		if((*fsalida=fopen(argumentos->nombre_arch_sal,"wb"))==NULL)
		{	
			return ST_ERROR_APERTURA_ARCHIVO;
		}	
	}
	return ST_OK;
}

status_t imprimir_error(status_t st)
/*Imprime el error correspondiente*/
{
    fprintf(stderr, "%s\n", errmsg[st]);
	return ST_OK;
}


status_t imprimir_ayuda()
 /*Imprime la información de ayuda: tabla del orden de los argumentos y
 tabla de las operaciones validas*/
{
	printf("%s%s%s%s%s\n%s%s%s",MSJ_ACLARACION_AYUDA1, MSJ_ACLARACION_AYUDA2,TXT_AYUDA1,TXT_AYUDA2,TXT_AYUDA3,TXT_AYUDA4,TXT_AYUDA5,TXT_AYUDA6 );
	return ST_OK;
}


status_t imprimir_archivo_txt(simpletron_t *simpletron, FILE *fsalida)
 /*Recibe el puntero del archivo de salida y a la de simpletron para imprimir los datos guardados en el acumulador, 
 en el contador del programa, la ultima instruccion ejecutada, el ultimo opcode y operando, además de la lista de todas las palabras, en forma de matriz. 
 Esto se hara en un archivo txt o por stdout teniendo en cuenta lo guardado en la estructura de los argumentos*/
{
	int i,l;

	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
    
    fprintf(fsalida,"%s\n", MSJ_REGISTRO);
	fprintf(fsalida, "%25s: %6d\n",MSJ_ACUM, simpletron->acumulador );
	fprintf(fsalida, "%25s: %6lu\n",MSJ_CONT_PROG, simpletron->contador_programa );
	fprintf(fsalida, "%25s: %6d\n",MSJ_INST, simpletron->memoria->palabras[simpletron->contador_programa]);
	simpletron->opcode=(simpletron->memoria->palabras[simpletron->contador_programa]/10000);
	simpletron->operando=(simpletron->memoria->palabras[simpletron->contador_programa]-(simpletron->opcode)*10000);
	fprintf(fsalida, "%25s: %6lu\n",MSJ_OPCODE, simpletron->opcode );
	fprintf(fsalida, "%25s: %6lu\n",MSJ_OPERANDO, simpletron->operando);
	fprintf(fsalida,"    ");
	for (l = 0; l < 10; l++)
		fprintf(fsalida,"  %i   ",l) ;
	for ( i = 0; i < simpletron->memoria->pedido ; i++)
	{ 
    	if ((i%10)==0)
    	{
	 		fprintf(fsalida,"\n%02i  ",i);
		}		  
		fprintf(fsalida,"%+05i ",simpletron->memoria->palabras[i] );
	}
    fprintf(fsalida,"\n");
    
    return ST_OK;
}

status_t imprimir_archivo_bin (simpletron_t *simpletron, FILE *fsalida)
 /*Recibe el puntero del archivo de salida y el de la estructura de la simpletron para imprimir los datos guardados en ella*/

{
	fwrite(simpletron, sizeof(simpletron_t),1, fsalida);
	return ST_OK;
}


#endif