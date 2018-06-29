#include <stdio.h>
#include <stdlib.h>


typedef struct memoria{
	size_t pedido; 
	palabra_t * palabras;
} memoria_t;

memoria_t * vector_crear (size_t sz){
	memoria_t *v;
	v= (memoria_t*)calloc (1,sizeof(memoria_t));
	if(v==NULL)
		return NULL;
	v->palabras=(palabra_t *)calloc(1,sz*sizeof(palabra_t));
	if(v->palabras==NULL){
		free(v);
		return NULL;
	}
	v->pedido=sz;
	return v;
}	

void vector_destruir(vector_t ** v){
	if(v&&*v){
		if ((*v)->palabras)
			free((*v)->palabras);
		free(*v);
		*v=NULL;
	}
}

void vector_iterar (vector_t *v, void (*func) (void*, void*), void *arg){
	size_t i;
	if(v&&func){
		for (i=0; i< v->pedido;){
			if(v->palabras[i])
				(*func)(arg,v->palabras[i]);
		}
	}
}

void print(void *vstream, void *vint){
	FILE *f=(FILE*) vstream;
	int * i= (int *) vint;
	fprintf(f, "%i\n",*i);
}	
