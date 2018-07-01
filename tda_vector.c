#ifndef TDA_VECTOR__C
#define TDA_VECTOR__C

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

status_t vector_destruir1(memoria_t ** v)
{
	if(v&&*v)
	{
		free((*v)->palabras);
	}	
	free(*v);
	*v=NULL;
	return ST_OK;
}

status_t vector_destruir2(memoria_t **v, void (*f)(void *))
{
	if(v&&*v)
	{
		if((*v)->palabras)
		{
			if(f!=NULL)
			{
				(*f)((*v)->palabras);
			}
			free((*v)->palabras);
		}
		free(*v);
		*v=NULL;
	}
	return ST_OK;
}

bool_t vector_guardar(memoria_t *v, int i, palabra_t dato, palabra_t (*copiar)(palabra_t), void (*destruir)(palabra_t*))
{
	palabra_t aux;
	if(!v)
	{
		return false;
	}
	if(i>=v->pedido||i<0)
	{
		return false;
	}
	if((aux=(*copiar)(dato)))
	{
		if(v->palabras[i])
		{
			(*destruir)(v->palabras);
		}
		v->palabras[i]=aux;
		return true;
	}
	return false;
}

const void * vector_buscar(const memoria_t * v, palabra_t * t, int (*cmp)(palabra_t, palabra_t))
{
	size_t i;
	if(!v||!t||!cmp)
	{
		return NULL;
	}
	for(i=0;i<v->pedido; i++)
	{
		if(v->palabras[i])
		{
			if(((*cmp)(*t,v->palabras[i]))==0)
			{
				return &(v->palabras[i]);
			}
		}
	}
	return NULL;
}

bool_t vector_redimensionar(memoria_t *v, size_t sz, void (*liberar)(void *))
{
	palabra_t * aux;

	if(v==NULL||liberar==NULL)
	{
		return false;
	}
	if(sz<v->pedido)
	{
		if(liberar!=NULL)
		{
			(*liberar)(v->palabras);
		}
	}
	if ((aux=(palabra_t *) realloc(v->palabras, sz*sizeof(palabra_t)))==NULL)
	{
		return false;
	}
	v->palabras=aux;
	v->pedido=sz;
	return true;
}

status_t vector_iterar (memoria_t *v, void (*func) (void*, palabra_t), void *arg){
	size_t i;
	if(v&&func)
	{
		for (i=0; i< v->pedido;i++)
		{
			if(v->palabras[i])
			{
				(*func)(arg,v->palabras[i]);		
			}
		}
		return ST_OK;
	}
	return ST_ERROR_EJECUCION;
}

#endif