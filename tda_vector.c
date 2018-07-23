#ifndef TDA_VECTOR__C
#define TDA_VECTOR__C

#include <stdio.h>
#include <stdlib.h>
#include "tda_vector.h"
#include "tipos.h"
/*Contiene la implementacion de las primitivas del TDA Vector*/

memoria_t * vector_crear (size_t sz)
/*Devuelve un puntero a una estructura que tiene memoria dinamica asignada
para si y para un vector de tamaño especificado por el argumento pasado*/
{
	memoria_t *v=NULL;
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
/*Libera la memoria pedida para la estrcutura pasada*/
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
/*Libera la memoria pedida para la estructura pasada utilizando la funcion
del segundo argumento*/
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
/*Guarda el dato en la posicion i del vector palabras, para lo cual utiliza la funcion de copiar pasada
y en el caso de ya tener algo en esa posicion, borra el dato viejo con la funcion destruir pasada*/
{
	palabra_t aux=0;
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
/*Devuelvo un puntero al dato t si se encuentra en el vector palabras,
se utiliza la funcion cmp para comparar cada dato hasta encontrarlo o hasta que se terminen
los datos almacenados*/
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
/*modifica el tamaño del vector palabras segun sz, el segundo argumento;
antes de ello, libera la memoria de ese vecto con la funcion liberar pasada*/
{
	palabra_t * aux=NULL;

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

status_t vector_iterar (memoria_t *v, void (*func) (void*, palabra_t), void *arg)
/*ejecuta la funcion pasada en cada miembro del vector palabras*/
{
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
