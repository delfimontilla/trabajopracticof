#ifndef TDA_VECTOR__H
#define TDA_VECTOR__H 1

#include <stdio.h>

/*Este .h contiene los prototipos de las funciones implementadas en tda_vector.c*/

memoria_t * vector_crear (size_t sz);
status_t vector_destruir1(memoria_t ** v);
status_t vector_destruir2(memoria_t **v, void (*f)(void *));
bool_t vector_guardar(memoria_t *v, int i, palabra_t dato, palabra_t (*copiar)(palabra_t), void (*destruir)(palabra_t*));
const void * vector_buscar(const memoria_t * v, palabra_t * t, int (*cmp)(palabra_t, palabra_t));
bool_t vector_redimensionar(memoria_t *v, size_t sz, void (*liberar)(void *));
status_t vector_iterar (memoria_t *v, void (*func) (void*, palabra_t), void *arg);

#endif