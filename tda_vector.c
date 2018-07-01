#ifndef TDA_VECTOR__H
#define TDA_VECTOR__H

#include <stdio.h>

memoria_t * vector_crear (size_t sz)
{
	memoria_t *v;
	v=(memoria_t*)calloc (1,sizeof(memoria_t));
	if(v==NULL)
	{
		return NULL;
	}
		
	v->palabras=(palabra_t *)calloc(1,sz*sizeof(palabra_t));
	if(v->palabras==NULL)
	{
		free(v);
		return NULL;
	}
	v->pedido=sz;
	return v;
}	

status_t vector_destruir(memoria_t ** v){
	if(v&&*v)
	{
		free((*v)->palabras);
	}	
		free(*v);
		*v=NULL;
		return ST_OK;
}
status_t vector_iterar (memoria_t *v, void (*func) (void*, palabra_t), void *arg){
	size_t i;
	if(v&&func){
		for (i=0; i< v->pedido;i++)
		{
			if(v->palabras[i])
				(*func)(arg,v->palabras[i]);
		}
		return ST_OK;
	}
	return ST_ERROR_EJECUCION;
}

#endif
