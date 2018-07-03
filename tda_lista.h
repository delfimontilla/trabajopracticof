/**
 * @file tda_lista.h
 * @brief Encabezado y definición de primitivas para una lista polimórfica
 * simplemente enlazada. Las primitivas implementadas pueden ser recursivas o
 * iterativas, según el archivo .c contra el que se compile.
 *
 * En esta implementación de lista polimórfica simplemente enlazada, la lista
 * no es dueña del dato que almacena. Si lo fuese, debería recibir, en cada
 * función que crea nuevos nodos, un puntero a función que sepa cómo clonar el
 * dato apuntado, de forma de almacenar una copia del dato.
 *
 * IMPORTANTE: La función LISTA_filtrar() retorna una lista con los datos sin
 * replicar, por lo mencionado anteriormente.
 *
 * Para salvar eso, LISTA_crear_nodo(), LISTA_insertar_XXX() y LISTA_filtrar()
 * deberían recibir el clonador de datos.
 *
 * @author PATRICIO MORENO
 * @date 2017-05-30
 * @license beerware
 * ---------------------------------------------------------------------------
 * "LA LICENCIA BEER-WARE" (Versión 42):
 * Yo escribí este archivo. Siempre y cuando usted mantenga este aviso, puede
 * hacer lo que quiera con él. Si nos encontramos algún día, y piensa que esto
 * vale la pena, me puede comprar una cerveza a cambio.        PATRICIO MORENO
 * ---------------------------------------------------------------------------
 */
#ifndef TDA_LISTA__H
#define TDA_LISTA__H

#include <stdio.h>

/*En este archivo, se encuentran los prototipos de las funciones otorgadas para la utilizacion en este trabajo*/

typedef struct nodo {
  struct nodo * siguiente;
  simpletron_t * simpletron;
} nodo_t, * lista_t;

bool_t LISTA_esta_vacia(lista_t);
status_t LISTA_crear(lista_t *);
status_t LISTA_crear_nodo(nodo_t ** pnodo, simpletron_t * simpletron);
status_t LISTA_destruir_nodo(nodo_t ** pnodo, status_t (*destructor_simpletron)(simpletron_t **));
status_t LISTA_destruir_primero(lista_t * plista, status_t (*destructor_simpletron)(simpletron_t **));
status_t LISTA_destruir(lista_t * plista, status_t (*destructor_simpletron)(simpletron_t **));
status_t LISTA_insertar_al_ppio(lista_t * plista, simpletron_t * simpletron);
status_t LISTA_insertar_al_final(lista_t * plista, simpletron_t * simpletron);
status_t LISTA_insertar_decreciente(lista_t * plista, simpletron_t * simpletron, int (*cmp)(void *, void *));

void * LISTA_buscar(nodo_t *, void *, int (*cmp)(void *, void *));
status_t LISTA_imprimir(lista_t pnodo, FILE * ofile, status_t (*impresor)(simpletron_t*, FILE *));
status_t LISTA_recorrer(lista_t pnodo, status_t (*funcion)(simpletron_t *));

#endif
