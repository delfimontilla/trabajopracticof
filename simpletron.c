#ifndef SIMPLETRON__C
#define SIMPLETRON__C 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpletron.h"
#include "tipos.h"
#include "constantes.h"
#include "tda_vector.h"

#ifdef LENG_ESPANOL
#include "leng_espanol.h"

#elif defined (LENG_INGLES)
#include "leng_ingles.h"

#else
#include "leng_espanol.h"
#endif

/*vector de punteros a las funciones de las operaciones del simpletron*/
status_t (*p_funciones[12])(simpletron_t *) = {op_leer,
	op_escribir,
	op_cargar,
	op_guardar,
	op_pcargar,
	op_pguardar,
	op_sumar,
	op_restar,
	op_dividir,
	op_multiplicar,
	op_jmp,
	op_djnz};

status_t inicializar_simpletron (simpletron_t ** simpletron, size_t cant_palabras)
/*Esta funcion recibe un doble puntero a la estructura simpletron para poder modificar su contenido,
y un size_t de cant_palabras para darle la memoria dinamica necesaria al vector de palabras*/
{
	if (!simpletron)/*Validaciones*/
	{
		return ST_ERROR_PTR_NULO;
	}
	if(!cant_palabras)
	{
		return ST_ERROR_NADA_QUE_CARGAR;
	}
	if((*simpletron = (simpletron_t *) calloc(1, sizeof(simpletron_t)))==NULL)/*Pide memoria para una estructura*/
	{
		return ST_ERROR_NO_MEM;
	}
	if(((*simpletron)->memoria=vector_crear(cant_palabras))==NULL)/*Crea el vector memoria*/
	{
		liberar_memoria(simpletron);
		return ST_ERROR_NO_MEM;
	}
	(*simpletron)->acumulador=0;/*Inicializa los valores de la estructura*/
	(*simpletron)->contador_programa=0;
	(*simpletron)->opcode=0;
	(*simpletron)->operando=0;

	return ST_OK;
}

status_t liberar_memoria(simpletron_t ** simpletron)
/*Recibe puntero doble a la estructura simpletron para liberar la memoria pedida*/
{

	if (simpletron!=NULL && *simpletron!=NULL){
		if((*simpletron)->memoria!=NULL)
		{
			vector_destruir1(&((*simpletron)->memoria));
		}

		(*simpletron)->acumulador=0;
		(*simpletron)->contador_programa=0;
		(*simpletron)->opcode=0;
		(*simpletron)->operando=0;
	}
	free(*simpletron);
	*simpletron=NULL;
	return ST_OK;
}

status_t ejecutar_simpletron (simpletron_t * simpletron)
 /*Recibe el puntero a la estructura de simpletron para hacer un análisis de las instrucciones que se encuentran
 en el vector palabras, y después se llama a una función que realiza la operación necesaria por medio del vector de funciones.
 Ademas, se valida que el operando sea una posicion de memoria existente*/
{
	status_t st;
	vector_punteros_t pt;
	st=ST_OK;

	if (!simpletron)/*Valida*/
	{
		return ST_ERROR_PTR_NULO;
	}

	while(st==ST_OK)
	{
		if((simpletron->opcode=(simpletron->memoria->palabras[simpletron->contador_programa]/10000))<0 && simpletron->opcode>MAX_CANT_OPCODE)
		/*Divide la memoria en opcode y operando. Verifica que estén dentro del rango utilizable.*/
		{
			return ST_ERROR_FUERA_DE_RANGO;
		}
		if((simpletron->operando=(simpletron->memoria->palabras[simpletron->contador_programa]-(simpletron->opcode)*10000))<0 && simpletron->operando>MAX_CANT_OPERANDO)
		{
			return ST_ERROR_FUERA_DE_RANGO;
		}
		switch (simpletron->opcode)
		/*Decide en que opcode */
		{
			case (OP_LEER):
				pt=F_OP_LEER;
				st=p_funciones[pt](simpletron);
				simpletron->contador_programa++;
				break;
			case (OP_ESCRIBIR):
				pt=F_OP_ESCRIBIR;
				st=p_funciones[pt](simpletron);
				simpletron->contador_programa++;
				break;
			case (OP_CARGAR):
				pt=F_OP_CARGAR;
				st=p_funciones[pt](simpletron);
				simpletron->contador_programa++;
				break;
			case (OP_GUARDAR):
				pt=F_OP_GUARDAR;
				st=p_funciones[pt](simpletron);
				simpletron->contador_programa++;
				break;
			case (OP_PCARGAR):
				pt=F_OP_PCARGAR;
				st=p_funciones[pt](simpletron);
				simpletron->contador_programa++;
				break;
			case(OP_PGUARDAR):
				pt=F_OP_PGUARDAR;
				st=p_funciones[pt](simpletron);
				simpletron->contador_programa++;
				break;
			case(OP_SUMAR):
				pt=F_OP_SUMAR;
				st=p_funciones[pt](simpletron);
				simpletron->contador_programa++;
				break;
			case(OP_RESTAR):
				pt=F_OP_RESTAR;
				st=p_funciones[pt](simpletron);
				simpletron->contador_programa++;
				break;
			case(OP_DIVIDIR):
				pt=F_OP_DIVIDIR;
				st=p_funciones[pt](simpletron);
				simpletron->contador_programa++;
				break;
			case(OP_MULTIPLICAR):
				pt=F_OP_MULTIPLICAR;
				st=p_funciones[pt](simpletron);
				simpletron->contador_programa++;
				break;
			case(OP_JMP):
				pt=F_OP_JMP;
				st=p_funciones[pt](simpletron);
				break;
			case(OP_JMPNEG):
				pt=F_OP_JMP;
				if(simpletron->acumulador<0)
				{
					st=p_funciones[pt](simpletron);
				}
				else
				{
					simpletron->contador_programa++;
				}
				break;
			case(OP_JMPZERO):
				pt=F_OP_JMP;
				if(simpletron->acumulador==0)
				{
					st=p_funciones[pt](simpletron);
				}
				else
				{
					simpletron->contador_programa++;
				}
				break;
			case(OP_JNZ):
				pt=F_OP_JMP;
				if(simpletron->acumulador!=0)
				{
					st=p_funciones[pt](simpletron);
				}
				else
				{
				 	simpletron->contador_programa++;
				}
				break;
			case(OP_DJNZ):
				pt=F_OP_JMP;
				st=p_funciones[pt](simpletron);
				break;
			case (OP_HALT):
				st=ST_SALIR;
				break;
			default:
				simpletron->contador_programa++;
				break;
		}
	}
	if(st==ST_SALIR)
		st=ST_OK;
	return st;
}

status_t op_leer (simpletron_t * simpletron)
 /*Lee una palabra por stdin a una posicion de memoria que está indicada por el operando (miembro de la estructura simpletron)
 recibe un puntero a la estructura*/
{
	long numero=0;
	char * pc=NULL;
	char lectura[MAX_CADENA];

	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	printf("%s\n", MSJ_INGRESO_PALABRA);
	if ((fgets(lectura,MAX_CADENA,stdin))==NULL)
	{
		return ST_ERROR_PALABRA_VACIA;
	}
	if((pc=strchr(lectura,'\n'))!=NULL)
	{
		*pc='\0';
	}
	numero = strtol(lectura,&pc,10);
	if(*pc!='\0')
	{
	    return ST_ERROR_NO_NUMERICO;
	}
	if(numero<MIN_PALABRA||numero>MAX_PALABRA)
	{
	 	return ST_ERROR_FUERA_DE_RANGO;
	}
	simpletron->memoria->palabras[simpletron->operando] = numero;
	return ST_OK;
}

status_t op_escribir(simpletron_t * simpletron)
 /*imprime por stdout el contenido de la posicion del operando (miembro de la estructura simpletron).
 Recibe un puntero a la estructura simpletron*/
{
	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	fprintf(stdout, "%s %i : %i\n", MSJ_IMPRIMIR_PALABRA, (int) simpletron->operando, simpletron->memoria->palabras[simpletron->operando]);
	return ST_OK;
}

status_t op_cargar (simpletron_t * simpletron)
/*Carga en el acumulador (miembro de la estructura simpletron) la posicion de memoria indicada
por el operando(miembro de la estructura simpletron). Recibe como argumento un puntero a la estructura simpletron*/
{
	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	simpletron->acumulador = simpletron->memoria->palabras[simpletron->operando];
	return ST_OK;
}


status_t op_pcargar (simpletron_t * simpletron)
 /*Carga en el acumulador (miembro de la estructura simpletron) la posicion de memoria indicada
 por la palabra a la que apunta el operando(miembro de la estructura simpletron).
 Recibe como argumento un puntero a la estructura simpletron*/
{
	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	if(!simpletron->memoria->pedido)
	{
		return ST_ERROR_CANT_PALABRAS;
	}
	if(simpletron->memoria->palabras[simpletron->operando] > simpletron->memoria->pedido)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}

	simpletron->acumulador = simpletron->memoria->palabras[simpletron->memoria->palabras[simpletron->operando]];
	return ST_OK;
}

status_t op_guardar (simpletron_t * simpletron)
 /*Guarda en la posicion de memoria indicada por el operando(miembro de la estructura simpletron)
  lo que está en el acumulador(miembro de la estructura simpletron)
  Recibe como argumento un puntero a la estructura simpletron*/
{
	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	simpletron->memoria->palabras[simpletron->operando] = simpletron->acumulador ;
	return ST_OK;
}

status_t op_pguardar (simpletron_t * simpletron)
 /*guarda en la posicion de memoria indicada por la palabra a la que apunta el operando (miembro de la estructura simpletron)
 lo que esta en el acumulador(miembro de la estructura simpletron).
 Recibe como argumento un puntero a la estructura simpletron*/
{
	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	if(!simpletron->memoria->pedido)
	{
		return ST_ERROR_CANT_PALABRAS;
	}
	if(simpletron->memoria->palabras[simpletron->operando] > simpletron->memoria->pedido)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	simpletron->memoria->palabras[simpletron->memoria->palabras[simpletron->operando]] = simpletron->acumulador ;
	return ST_OK;
}

status_t op_sumar(simpletron_t * simpletron)
 /*suma al acumulador (miembro de la estructura simpletron) lo guardado en la posicion de memoria indcada
 por el operando(miembro de la estructura simpletron).
 Recibe como argumento un puntero a la estructura simpletron*/
{
	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	simpletron->acumulador += simpletron->memoria->palabras[simpletron->operando];
	if(simpletron->acumulador>MAX_PALABRA)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	return ST_OK;
}

status_t op_restar (simpletron_t * simpletron)
 /*resta al acumulador (miembro de la estructura simpletron) lo guardado en la posicion de memoria indcada
 por el operando(miembro de la estructura simpletron)
 Recibe como argumento un puntero a la estructura simpletron*/
{
	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	if(simpletron->acumulador>MAX_PALABRA)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	simpletron->acumulador -= simpletron->memoria->palabras[simpletron->operando];
	return ST_OK;
}

status_t op_dividir (simpletron_t * simpletron)
 /*divide al acumulador (miembro de la estructura simpletron) por lo guardado en la posicion de memoria indicada
  por el operando(miembro de la estructura simpletron).
  Recibe como argumento un puntero a la estructura simpletron*/
{
	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	if(simpletron->acumulador>MAX_PALABRA)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	simpletron->acumulador /= simpletron->memoria->palabras[simpletron->operando];
	return ST_OK;
}

status_t op_multiplicar (simpletron_t * simpletron)
 /*multiplica al acumulador (miembro de la estructura simpletron)lo guardado en la posicion de memoria indicada
 por el operando(miembro de la estructura simpletron).Recibe como argumento un puntero a la estructura simpletron*/
{
	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	simpletron->acumulador *= simpletron->memoria->palabras[simpletron->operando];
	if(simpletron->acumulador>MAX_PALABRA)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	return ST_OK;
}

status_t op_jmp (simpletron_t * simpletron)
/*salta a la posicion de memoria indicada por el operando(miembro de la estructura simpletron)
Recibe como argumento un puntero a la estructura simpletron*/
{
	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	simpletron->contador_programa = simpletron->operando;
	return ST_OK;
}

status_t op_djnz (simpletron_t * simpletron)
 /*decrementa en 1 el acumulador (miembro de la estructura simpletron) y salta a la posicion indicada
 por el operando (miembro de la estructura simpletron) en el caso que el acumulador sea distinto de 0.
 Recibe como argumento un puntero a la estructura simpletron*/
{
	if(!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	if(simpletron->acumulador>MAX_PALABRA)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	simpletron->acumulador--;
	if (simpletron->acumulador!=0)
	{
		simpletron->contador_programa = simpletron->operando;
	}
	else
	{
		simpletron->contador_programa++;
	}
	return ST_OK;
}

#endif
