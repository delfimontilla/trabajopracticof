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

/**Se modificó del orginal creado por PATRICIO MORENO cada vez que dice dato por simpletron para que sea más acorde a lo que se hace en el resto del programa.**/
#include <stdlib.h>
#include "../lib/types.h"
#include "tda_lista.h"

bool_t LISTA_esta_vacia(lista_t lista)/*Devuelve TRUE si es está vacía, y false si contiene algo. Usamos NULL cuando  la lista está creada pero esta vacía*/ 
{
    return lista == NULL;
}

status_t LISTA_crear(lista_t * plista) /*Crea una lista. Devuelve RV_ILLEGAL(1) cuando la lista está ya creada, si no la crea y devuelvo RV_SUCCESS(0)*/
{
    if(plista == NULL)
        return RV_ILLEGAL;

    *plista = NULL;

    return RV_SUCCESS;
}

status_t LISTA_crear_nodo(nodo_t ** pnodo, void * simpletron) /*Crea un nodo y le coloca el valor del simpletron que se quiere.*/
{
    if(pnodo == NULL) /*Se ingresa un puntero nulo???????????????????*/
        return RV_ILLEGAL;

    if((*pnodo = (nodo_t *)calloc(1, sizeof(nodo_t))) == NULL)/*Se crea la memoria para el nodo, y se valida.*/
        return RV_NOSPACE;

    (*pnodo)->siguiente = NULL;/*Se pone el siguiente nodo en NULL*/
    (*pnodo)->simpletron = simpletron; /*Se le guarda el valor de la simpletron*/

    return RV_SUCCESS;
}

status_t LISTA_destruir_nodo(nodo_t ** pnodo, status_t (*destructor_simpletron)(void *))/*Destruye el nodo pasado como parametro y se destruye la simpletron contendia en ese nodo.*/
{
    void * simpletron;

    if(pnodo == NULL)/*Validacion*/
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*pnodo))/*Verifica si el nodo ya está vacio, si lo está, ya sale de la función*/
        return RV_SUCCESS;

    simpletron = (*pnodo)->simpletron;/*Se hace una copia local del puntero a la estructura*/

    (*pnodo)->siguiente = NULL;/*Se llevan a NULL los nodos y se libera la memoria pedida para este nodo.*/
    (*pnodo)->simpletron = NULL;
    free(*pnodo);
    *pnodo = NULL;

    return (destructor_simpletron != NULL) ? (*destructor_simpletron)(simpletron) : RV_SUCCESS;/*Verifica si ya se pudo destruir simpletron y si no se pudo se destruye.*/
}

status_t LISTA_destruir_primero(lista_t * plista, status_t (*destructor_simpletron)(void *))/*Destruye el primer nodo de la lista*/
{
    nodo_t * primero;

    if(plista == NULL)/*Valida*/
        return RV_ILLEGAL;

    if(*plista == NULL)/* es equivalente a LISTA_esta_vacia(*plista) */
        return RV_SUCCESS;

    primero = *plista;/*Copia a una variable local la direccion de lo que quiero destruir.*/
    *plista = (*plista)->siguiente; /*Copia en el primer nodo el siguiente nodo.*/

    return LISTA_destruir_nodo(&primero, destructor_simpletron);/*Llama a la funcion destruir_nodo para que destruya el nodo deseada. Se manda la dirección por medio de la variable local.*/
}

status_t LISTA_destruir(lista_t * plista, status_t (*destructor_simpletron)(void *))/*Destruye toda la lista. Se le pasa por argumento el primer nodo de la lista y el puntero a funcion.*/
{
    nodo_t * siguiente;

    if(plista == NULL)/*Validaciones*/
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*plista))
        return RV_SUCCESS;

    siguiente = (*plista)->siguiente;/*Copia en una variable local el puntero al siguiente elemento de la lista.*/

    LISTA_destruir_nodo(plista, destructor_simpletron );/*Destruye el nodo actual*/
    return LISTA_destruir(&siguiente, destructor_simpletron);/*Vuelve a llamarse a si misma, pasandole la direccion del siguiente nodo.*/
}

status_t LISTA_insertar_al_ppio(lista_t * plista, void * simpletron) /*Inserta al principio de la lista un nuevo nodo con su estructura.*/
{
    nodo_t * nuevo;
    status_t rv;

    if(plista == NULL) /*Validaciones*/
        return RV_ILLEGAL;

    if((rv = LISTA_crear_nodo(&nuevo, simpletron)) != RV_SUCCESS)/*Crea el nodo y si llega a tener un error  devuelve ese error. */
        return rv;

    nuevo->siguiente = *plista;/*copio en una variable local en el siguiente nodo para luego copiar en el primer nodo lo conseguido en crear_nodo*/
    *plista = nuevo;

    return RV_SUCCESS;
}

status_t LISTA_insertar_al_final(lista_t * plista, void * simpletron) /*Inserta un nodo al final de la lista*/ 
{
    if(plista == NULL)
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*plista)) /*Si el nodo está vacio lo inserta delante de este*/
        return LISTA_insertar_al_ppio(plista, simpletron);

    return LISTA_insertar_al_final(&((*plista)->siguiente), simpletron);/*Avanza al siguiente nodo llamandose a si misma.*/
}

status_t LISTA_insertar_decreciente(lista_t * plista, void * simpletron, int (*cmp)/*Compare*/(void *, void *)) /*Inserta un simpletron en orden decreciente.*/
{
    status_t rv;
    nodo_t * nuevo;

    if(plista == NULL)
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*plista) || (*cmp)( (*plista)->simpletron, simpletron) < 0 ) /*Si el puntero es al último de la lista o si lo que ingreso es mas grande????????????????? que lo que está en esa posicion se crea el nodo y se introduce la estructura. */
    {
        if((rv = LISTA_crear_nodo(&nuevo, simpletron)) != RV_SUCCESS)
            return rv;

        nuevo->siguiente = *plista;
        *plista = nuevo;

        return RV_SUCCESS;
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

status_t LISTA_imprimir(lista_t pnodo, FILE * ofile, status_t (*impresor)(void *, FILE *)) /*imprime la lista desde el nodo pasado por argumento en el archivo pasado por argumento con la funcion pasada como argumento*/
{
    if(pnodo == NULL) /*Validaciones*/
        return RV_SUCCESS;

    (*impresor)(pnodo->simpletron, ofile);/*Imprime el simpletron contenido en el nodo*/
    LISTA_imprimir(pnodo->siguiente, ofile, impresor);/*Imprime el siguiente nodo*/

    return RV_SUCCESS;
}

status_t LISTA_recorrer(lista_t pnodo, status_t (*funcion)(void *, void *), void * argumento) /*Recorre la lista desde el nodo pasado como argumento aplicandole la funcion deseada.*/
{
    if(pnodo == NULL)
        return RV_SUCCESS;

    (*funcion)(pnodo->simpletron, argumento);
    return LISTA_recorrer(pnodo->siguiente, funcion, argumento);
}


/*****************hacer funcion destruir simpletor, cmp, es_igual, impresor, funcion**************/

/**
defino mi funcion como normalmente
typedef tipo de la funcion * nombregenerico (argumentos);
int main*(){
    nombregenerico=nombredefunccion;
    nombredefunccion=PONER LA FUNCION;
     y ya la uso como puntero a funcion
}





**/
typedef status_t * punteroafuncion(lista_t pnodo, FILE * ofile, status_t (*impresor)(void *, FILE*));
int main(int argc, char const *argv[])
{
    




    if (argumentos.fs_bin==TRUE){
        punteroafuncion = imprimir_archivo_bin/*(simpletron, fsalida)*/;
        if((st=punteroafuncion(simpletron, fsalida))!=ST_OK){
            free(simpletron);
            simpletron=NULL;
            if(fentrada!=NULL)
                fclose(fentrada);
            if(fsalida!=NULL)
                fclose(fsalida);
            imprimir_error(st);
            return EXIT_FAILURE;
        }       
    }

    else 
        punteroafuncion = imprimir_archivo_txt/*(simpletron, fsalida)*/;
        if((st=punteroafuncion(simpletron, fsalida))!=ST_OK){
        free(simpletron);
        simpletron=NULL;
        if(fentrada!=NULL)
            fclose(fentrada);
        if(fsalida!=NULL)
            fclose(fsalida);
        imprimir_error(st);
        return EXIT_FAILURE;
    }
    return 0;
}

    



status_t imprimir_archivo_txt(const void *simpletron, FILE *fsalida)
 /*Recibe el puntero del archivo de salida y a la de simpletron para imprimir los datos guardados en el acumulador, 
 en el contador del programa, la ultima instruccion ejecutada, el ultimo opcode y operando, además de la lista de todas las palabras, en forma de matriz. 
 Esto se hara en un archivo txt o por stdout teniendo en cuenta lo guardado en la estructura de los argumentos*/
{
    int i,l;

    if (!simpletron){
        fprintf(fsalida,"%s\n", MSJ_REGISTRO);
        fprintf(fsalida, "%25s: %6x\n",MSJ_ACUM, simpletron->acumulador );
        fprintf(fsalida, "%25s: %6lu\n",MSJ_CONT_PROG, simpletron->contador_programa );
        fprintf(fsalida, "%25s: %6d\n",MSJ_INST, simpletron->palabras[simpletron->contador_programa] );
        simpletron->opcode=simpletron->palabras[simpletron->contador_programa]/10000;/*divido por 100 entonces como es un int borra los numeros despues de la coma y me queda el entero que quiero (ejemplo, si llega 2598 me queda 25.98 pero se guarda 25)*/
        simpletron->operando = simpletron->palabras[simpletron->contador_programa] - (simpletron->opcode*10000);/*necesito los ultimos dos entonces al multiplicar opcode por 100 tengo 2500 del ejemplo entonces 2598-2500 da 98 que son los ultimos dos digitos que necesito*/
        fprintf(fsalida, "%25s: %6lu\n",MSJ_OPCODE, simpletron->opcode );
        fprintf(fsalida, "%25s: %6lu\n",MSJ_OPERANDO, simpletron->operando );
        fprintf(fsalida,"    ");
        for (l = 0; l < 10; l++)
            fprintf(fsalida,"  %i   ",l) ;
        for ( i = 0; i < lsimpletron->memoria->pedido ; i++){ 
            if ((i%10)==0){
                fprintf(fsalida,"\n%02i  ",i);
            }         
            fprintf(fsalida,"%+05i ",simpletron->palabras[i] );
        }
        fprintf(fsalida,"\n");
    }

    else 
        return ST_ERROR;

    return ST_OK;
}

status_t imprimir_archivo_bin (const void *simpletron, FILE *fsalida)
 /*Recibe el puntero del archivo de salida y el de la estructura de la simpletron para imprimir los datos guardados en ella*/

{
    fwrite(simpletron, sizeof(simpletron_t),1, fsalida);
    return ST_OK;
}
