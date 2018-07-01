#ifndef MEMORIA__C
#define MEMORIA__C 1

#include <stdio.h>

status_t inicializar_simpletron (simpletron_t **simpletron, size_t cant_palabras)
/*Esta funcion recibe un doble puntero a la estructura simpletron para poder modificar su contenido, 
y un size_t de cant_palabras para darle la memoria dinamica necesaria al vector de palabras*/	
{
	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}	
	if(!cant_palabras)
	{
		return ST_ERROR_NADA_QUE_CARGAR;
	}	
	if((*simpletron = (simpletron_t *) calloc(1, sizeof(simpletron_t)))==NULL)
	{
		return ST_ERROR_NO_MEM;
	}	
	if(((*simpletron)->memoria=vector_crear(cant_palabras))==NULL)
	{
		liberar_memoria(simpletron);
		return ST_ERROR_NO_MEM;
	}
	(*simpletron)->acumulador=0;
	(*simpletron)->contador_programa=0;
	(*simpletron)->opcode=0;
	(*simpletron)->operando=0;

	return ST_OK;
}

status_t liberar_memoria(simpletron_t ** simpletron)
/*Recibe puntero al simpletron para liberar la memoria pedida*/
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

#endif