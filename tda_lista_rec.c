#ifndef TDA_LISTA__C
#define TDA_LISTA__C
/**
 * @file tda_lista_rec.c
 * @brief Contiene la implementación, 100% recursiva, de las primitivas de una
 * lista polimórfica simplemente enlazada.
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

/*Se modificó del original creado por PATRICIO MORENO; se cambio dato
por simpletron, con su correspondiente tipo, y los status_t de las funciones aux
a las que se llama con su correspondiente formato.
Esto tiene como objetivo mas claridad al leer el programa completo.*/

#include <stdlib.h>
#include "tda_lista.h"
#include "tipos.h"

bool_t LISTA_esta_vacia(lista_t lista)
/*Devuelve true si es está vacía, y false si contiene algo. Usamos NULL cuando la lista está creada pero esta vacía*/
{
    return lista == NULL;
}

status_t LISTA_crear(lista_t * plista)
/*Crea una lista. Devuelve ST_ERROR_PTR_NULO en caso de no pasarle un argumento valido, sino la crea y devuelvo ST_OK*/
{
    if(plista == NULL)
    {
        return ST_ERROR_PTR_NULO;
    }
    *plista = NULL;
    return ST_OK;
}

status_t LISTA_crear_nodo(nodo_t ** pnodo, simpletron_t * simpletron)
/*Crea un nodo dandole memoria dinamica y le coloca la simpletron pasada*/
{
    if(pnodo == NULL)
    {
        return ST_ERROR_PTR_NULO;
    }
    if((*pnodo = (nodo_t *)calloc(1, sizeof(nodo_t))) == NULL)/*Se crea la memoria para el nodo, y se valida.*/
    {
        return ST_ERROR_NO_MEM;
    }
    (*pnodo)->siguiente = NULL;/*Se pone el siguiente nodo en NULL*/
    (*pnodo)->simpletron = simpletron; /*Se le guarda el valor de la simpletron*/

    return ST_OK;
}

status_t LISTA_destruir_nodo(nodo_t ** pnodo, status_t (*destructor_simpletron)(simpletron_t **))
/*Destruye el nodo pasado como primer parametro,
liberando la memoria con la funcion del segundo argumento*/
{
    simpletron_t * simpletron=NULL;

    if(pnodo == NULL)
    {
        return ST_ERROR_PTR_NULO;
    }
    if(LISTA_esta_vacia(*pnodo))/*Verifica si el nodo ya está vacio, si lo está, ya sale de la función*/
    {
        return ST_OK;
    }
    simpletron = (*pnodo)->simpletron;/*Se hace una copia local del puntero a la estructura*/
    (*pnodo)->siguiente = NULL;/*Se ponen en NULL los punteros*/
    (*pnodo)->simpletron = NULL;
    free(*pnodo);
    *pnodo = NULL;
    return (destructor_simpletron != NULL) ? (*destructor_simpletron)(&simpletron) : ST_OK;
}

status_t LISTA_destruir_primero(lista_t * plista, status_t (*destructor_simpletron)(simpletron_t **))
/*Destruye el primer nodo de la lista*/
{
    nodo_t * primero=NULL;

    if(plista == NULL)
    {
        return ST_ERROR_PTR_NULO;
    }
    if(*plista == NULL)/* es equivalente a LISTA_esta_vacia(*plista) */
    {
        return ST_OK;
    }
    primero = *plista;/*Copia a una variable local la direccion de lo que quiero destruir.*/
    *plista = (*plista)->siguiente; /*Copia en el primer nodo el siguiente nodo.*/

    return LISTA_destruir_nodo(&primero, destructor_simpletron);
    /*Llama a la funcion LISTA_destruir_nodo para que destruya el nodo deseado.
    Se manda la dirección por medio de la variable local.*/
}

status_t LISTA_destruir(lista_t * plista, status_t (*destructor_simpletron)(simpletron_t **))
/*Destruye toda la lista. Se le pasa por argumento el puntero a la lista
y el puntero a funcion para liberar memoria.*/
{
    nodo_t * siguiente=NULL;

    if(plista == NULL)
    {
        return ST_ERROR_PTR_NULO;
    }
    if(LISTA_esta_vacia(*plista))
    {
        return ST_OK;
    }
    siguiente = (*plista)->siguiente;/*Copia en una variable local el puntero al siguiente elemento de la lista.*/
    LISTA_destruir_nodo(plista, destructor_simpletron);/*Destruye el nodo actual*/
    return LISTA_destruir(&siguiente, destructor_simpletron);
    /*Vuelve a llamarse a si misma, pasandole la direccion del siguiente nodo.*/
}

status_t LISTA_insertar_al_ppio(lista_t * plista, simpletron_t * simpletron)
/*Inserta al principio de la lista un nuevo nodo con su estructura.*/
{
    nodo_t * nuevo=NULL;
    status_t st;

    if(plista == NULL)
    {
        return ST_ERROR_PTR_NULO;
    }
    if((st = LISTA_crear_nodo(&nuevo, simpletron)) != ST_OK)
    /*Crea el nodo y si llega a tener un error devuelve ese error. */
    {
        return st;
    }
    nuevo->siguiente = *plista; /*se apunta a la lista original con miembro siguiente del nuevo nodo creado*/
    *plista = nuevo; /*el nuevo nodo es el comienzo de la lista*/

    return ST_OK;
}

status_t LISTA_insertar_al_final(lista_t * plista, simpletron_t * simpletron) /*Inserta un nodo al final de la lista*/
{
    if(plista == NULL)
    {
        return ST_ERROR_PTR_NULO;
    }
    if(LISTA_esta_vacia(*plista)) /*Si la siguiente posicion de la lista está vacia lo inserta ahi*/
    {
        return LISTA_insertar_al_ppio(plista, simpletron);
    }

    return LISTA_insertar_al_final(&((*plista)->siguiente), simpletron);/*Avanza al siguiente nodo llamandose a si misma.*/
}

status_t LISTA_insertar_decreciente(lista_t * plista, simpletron_t * simpletron, int (*cmp)/*Compare*/(void *, void *))
/*Inserta un simpletron en orden decreciente.*/
{
    status_t st;
    nodo_t * nuevo=NULL;

    if(plista == NULL)
    {
        return ST_ERROR_PTR_NULO;
    }
    if(LISTA_esta_vacia(*plista) || (*cmp)( (*plista)->simpletron, simpletron) < 0 )
    /*Si el puntero es al último de la lista o si lo que ingreso es mas grande que lo que está en esa posicion
    se crea el nodo y se introduce la estructura. */
    {
        if((st = LISTA_crear_nodo(&nuevo, simpletron)) != ST_OK)
        {
            return st;
        }
        nuevo->siguiente = *plista;
        *plista = nuevo;

        return ST_OK;
    }

    return LISTA_insertar_decreciente(&((*plista)->siguiente), simpletron, cmp);
}

void * LISTA_buscar(lista_t pnodo, void * t, int (*es_igual)(void *, void *))
/*Busca una simpletron. Recibe como argumento un nodo de mi lista,
el dato a encontrar y un puntero a una función que compara y dice si son iguales.
Retorna un puntero al dato (la simpletron)*/
{
    if(pnodo == NULL)
    {
        return NULL;
    }
    if((*es_igual)(t, pnodo->simpletron))
    {
        return pnodo->simpletron;
    }
    return LISTA_buscar(pnodo->siguiente, t, es_igual);/*Busca en el nodo siguiente*/
}

status_t LISTA_imprimir(lista_t pnodo, FILE * ofile, status_t (*impresor)(simpletron_t *, FILE *))
/*Imprime la lista el nodo en el archivo pasado por argumento con la funcion (*impresor)*/
{
    status_t st;
    if(pnodo == NULL) /*Validacion de fin de la lista*/
    {
        return ST_OK;
    }
    if ((st=(*impresor)(pnodo->simpletron, ofile))!=ST_OK)
    {
        return st;
    }
    /*Imprime la simpletron contenida en el nodo*/
    LISTA_imprimir(pnodo->siguiente, ofile, impresor);/*Imprime el siguiente nodo*/
    return ST_OK;
}

status_t LISTA_recorrer(lista_t pnodo, status_t (*funcion)(simpletron_t *))
/*Recorre la lista desde el nodo pasado como argumento aplicandole la funcion deseada.*/
{
    status_t st;
    if(pnodo == NULL)
    {
        return ST_OK;
    }
    if ((st=(*funcion)(pnodo->simpletron))!=ST_OK)
    {
        return st;
    }
    return LISTA_recorrer(pnodo->siguiente, funcion);
}

#endif
