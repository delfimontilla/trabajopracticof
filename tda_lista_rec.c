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

/**Se modificó del original creado por PATRICIO MORENO cada vez que dice dato por simpletron para que sea más acorde a lo que se hace en el resto del programa.**/
#include <stdlib.h>

bool_t LISTA_esta_vacia(lista_t lista)/*Devuelve TRUE si es está vacía, y false si contiene algo. Usamos NULL cuando  la lista está creada pero esta vacía*/ 
{
    return lista == NULL;
}

status_t LISTA_crear(lista_t * plista) /*Crea una lista. Devuelve ST_ERROR_PTR_NULO(1) cuando la lista está ya creada, si no la crea y devuelvo ST_OK(0)*/
{
    if(plista == NULL)
        return ST_ERROR_PTR_NULO;

    *plista = NULL;

    return ST_OK;
}

status_t LISTA_crear_nodo(nodo_t ** pnodo, simpletron_t * simpletron) /*Crea un nodo y le coloca el valor del simpletron que se quiere.*/
{
    if(pnodo == NULL) 
        return ST_ERROR_PTR_NULO;

    if((*pnodo = (nodo_t *)calloc(1, sizeof(nodo_t))) == NULL)/*Se crea la memoria para el nodo, y se valida.*/
        return RV_NOSPACE;

    (*pnodo)->siguiente = NULL;/*Se pone el siguiente nodo en NULL*/
    (*pnodo)->simpletron = simpletron; /*Se le guarda el valor de la simpletron*/

    return ST_OK;
}

status_t LISTA_destruir_nodo(nodo_t ** pnodo, status_t (*destructor_simpletron)(simpletron_t **))/*Destruye el nodo pasado como parametro y se destruye la simpletron contendia en ese nodo.*/
{
    void * simpletron;

    if(pnodo == NULL)/*Validacion*/
        return ST_ERROR_PTR_NULO;

    if(LISTA_esta_vacia(*pnodo))/*Verifica si el nodo ya está vacio, si lo está, ya sale de la función*/
        return ST_OK;

    simpletron = (*pnodo)->simpletron;/*Se hace una copia local del puntero a la estructura*/

    (*pnodo)->siguiente = NULL;/*Se llevan a NULL los nodos y se libera la memoria pedida para este nodo.*/
    (*pnodo)->simpletron = NULL;
    free(*pnodo);
    *pnodo = NULL;

    return (destructor_simpletron != NULL) ? (*destructor_simpletron)(simpletron) : ST_OK;/*Verifica si ya se pudo destruir simpletron y si no se pudo se destruye.*/
}

status_t LISTA_destruir_primero(lista_t * plista, status_t (*destructor_simpletron)(simpletron_t **))/*Destruye el primer nodo de la lista*/
{
    nodo_t * primero;

    if(plista == NULL)/*Valida*/
        return ST_ERROR_PTR_NULO;

    if(*plista == NULL)/* es equivalente a LISTA_esta_vacia(*plista) */
        return ST_OK;

    primero = *plista;/*Copia a una variable local la direccion de lo que quiero destruir.*/
    *plista = (*plista)->siguiente; /*Copia en el primer nodo el siguiente nodo.*/

    return LISTA_destruir_nodo(&primero, destructor_simpletron);/*Llama a la funcion destruir_nodo para que destruya el nodo deseada. Se manda la dirección por medio de la variable local.*/
}

status_t LISTA_destruir(lista_t * plista, status_t (*destructor_simpletron)(simpletron_t **))/*Destruye toda la lista. Se le pasa por argumento el primer nodo de la lista y el puntero a funcion.*/
{
    nodo_t * siguiente;

    if(plista == NULL)/*Validaciones*/
        return ST_ERROR_PTR_NULO;

    if(LISTA_esta_vacia(*plista))
        return ST_OK;

    siguiente = (*plista)->siguiente;/*Copia en una variable local el puntero al siguiente elemento de la lista.*/

    LISTA_destruir_nodo(plista, destructor_simpletron );/*Destruye el nodo actual*/
    return LISTA_destruir(&siguiente, destructor_simpletron);/*Vuelve a llamarse a si misma, pasandole la direccion del siguiente nodo.*/
}

status_t LISTA_insertar_al_ppio(lista_t * plista, simpletron_t * simpletron) /*Inserta al principio de la lista un nuevo nodo con su estructura.*/
{
    nodo_t * nuevo;
    status_t rv;

    if(plista == NULL) /*Validaciones*/
        return ST_ERROR_PTR_NULO;

    if((rv = LISTA_crear_nodo(&nuevo, simpletron)) != ST_OK)/*Crea el nodo y si llega a tener un error  devuelve ese error. */
        return rv;

    nuevo->siguiente = *plista;/*copio en una variable local en el siguiente nodo para luego copiar en el primer nodo lo conseguido en crear_nodo*/
    *plista = nuevo;

    return ST_OK;
}

status_t LISTA_insertar_al_final(lista_t * plista, simpletron_t * simpletron) /*Inserta un nodo al final de la lista*/ 
{
    if(plista == NULL)
        return ST_ERROR_PTR_NULO;

    if(LISTA_esta_vacia(*plista)) /*Si el nodo está vacio lo inserta delante de este*/
        return LISTA_insertar_al_ppio(plista, simpletron);

    return LISTA_insertar_al_final(&((*plista)->siguiente), simpletron);/*Avanza al siguiente nodo llamandose a si misma.*/
}

status_t LISTA_insertar_decreciente(lista_t * plista, simpletron_t * simpletron, int (*cmp)/*Compare*/(void *, void *)) /*Inserta un simpletron en orden decreciente.*/
{
    status_t rv;
    nodo_t * nuevo;

    if(plista == NULL)
        return ST_ERROR_PTR_NULO;

    if(LISTA_esta_vacia(*plista) || (*cmp)( (*plista)->simpletron, simpletron) < 0 ) /*Si el puntero es al último de la lista o si lo que ingreso es mas grande????????????????? que lo que está en esa posicion se crea el nodo y se introduce la estructura. */
    {
        if((rv = LISTA_crear_nodo(&nuevo, simpletron)) != ST_OK)
            return rv;

        nuevo->siguiente = *plista;
        *plista = nuevo;

        return ST_OK;
    }

    return LISTA_insertar_decreciente(&((*plista)->siguiente), simpletron, cmp);
}

void * LISTA_buscar(lista_t pnodo, void * t, int (*es_igual)(void *, void *)) /*Busca el nodo que pido. Recibe como argumento el nodo donde me paro, el nodo que quiero y un puntero a una función que compara dos nodos y dice si son iguales.*/
{
    if(pnodo == NULL)/*validaciones*/
        return NULL;

    if((*es_igual)(t, pnodo->simpletron))/*Se fija si el nodo donde estoy es igual a lo que quiero, si es así, devuelvo ese nodo.*/
        return pnodo->simpletron;

    return LISTA_buscar(pnodo->siguiente, t, es_igual);/*Si no lo encuentra se vuelve a llamar*/
}

status_t LISTA_imprimir(lista_t pnodo, FILE * ofile, status_t (*impresor)(simpletron_t *, FILE *)) /*imprime la lista desde el nodo pasado por argumento en el archivo pasado por argumento con la funcion pasada como argumento*/
{
    if(pnodo == NULL) /*Validaciones*/
        return ST_OK;

    (*impresor)(pnodo->simpletron, ofile);/*Imprime el simpletron contenido en el nodo*/
    LISTA_imprimir(pnodo->siguiente, ofile, impresor);/*Imprime el siguiente nodo*/

    return ST_OK;
}

status_t LISTA_recorrer(lista_t pnodo, status_t (*funcion)(simpletron_t *)) /*Recorre la lista desde el nodo pasado como argumento aplicandole la funcion deseada.*/
{
    if(pnodo == NULL)
        return ST_OK;

    (*funcion)(pnodo->simpletron);
    return LISTA_recorrer(pnodo->siguiente, funcion);
}


/*****************hacer funcion destruir simpletor, cmp, es_igual, impresor, funcion**************/
/*
defino mi funcion como normalmente
typedef tipo de la funcion * nombregenerico (argumentos);
int main*(){
    nombregenerico=nombredefunccion;
    nombredefunccion=PONER LA FUNCION;
     y ya la uso como puntero a funcion
}
*/