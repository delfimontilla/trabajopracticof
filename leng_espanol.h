#ifndef LANG_SPANISH__H
#define LANG_SPANISH__H 1

#include <stdio.h>

/*En este .h se encuentran las macros de los mensajes utilizados en el programa en el idioma Español*/

#define MSJ_ERROR "ERROR"
#define MSJ_ERROR_APERTURA_ARCHIVO "ERROR: apertura de archivo"
#define MSJ_ERROR_PTR_NULO "ERROR: puntero nulo"
#define MSJ_ERROR_CANT_ARG "ERROR: cantidad de argumentos"
#define MSJ_ERROR_CANT_PALABRAS "ERROR: cantidad de palabras"
#define MSJ_ERROR_NO_MEM "ERROR: no hay memoria"
#define MSJ_ERROR_PALABRA_VACIA "ERROR: la palabra ingresada es nula"
#define MSJ_ERROR_FUERA_DE_RANGO "ERROR: se ha intentado acceder a una posición de memoria fuera de rango"
#define MSJ_ERROR_LIBERAR_MEM "ERROR: error al liberar memoria"
#define MSJ_ERROR_LECTURA "ERROR: lectura de archivo"
#define MSJ_ERROR_PALABRA_NEG "ERROR: palabra negativa"
#define MSJ_ERROR_ARG_INV "ERROR: argumento invalido"
#define MSJ_ERROR_NO_NUMERICO "ERROR: no es un numero"
#define MSJ_ERROR_NADA_QUE_CARGAR "ERROR: no hay nada que cargar"
#define MSJ_OK "OK"
#define MSJ_ERROR_EJECUCION "ERROR: iteracion del vector"
#define MSJ_SALIR "Salir"
#define MSJ_AYUDA "Finaliza la ayuda"

#define MSJ_IMPRIMIR_PALABRA "Contenido de la posicion"
#define MSJ_INGRESO_PALABRA "Ingrese una palabra:"

#define MSJ_ACUM "acumulador"
#define MSJ_CONT_PROG "contador del programa"
#define MSJ_INST "instruccion"
#define MSJ_OPCODE "opcode"
#define MSJ_OPERANDO "operando"

#define MSJ_BIENVENIDA "Bienvenide a la Simpletron! Por favor, ingrese su programa una instrucción (o dato) a la vez. Yo escribiré la ubicación y un signo de pregunta (?).Luego usted ingrese la palabra para esa ubicación. Ingrese -99999999 para finalizar."

#define MSJ_CARGA_COMPLETA "*** Carga del programa completa ***"
#define MSJ_COMIENZO_EJECUCION "*** Comienza la ejecución del programa ***"

#define MSJ_ACLARACION_AYUDA1 "Los argumentos que acompañaran a la ejecucion son posicionales, pero estos pueden estar o no presentes, por lo tanto, se deberán colocar en el orden mostrado a continuación. En caso de querer dejar el campo de cantidad de palabras en default se deberá colocar '-' en el primer campo"
#define MSJ_ACLARACION_AYUDA2 "En el siguiente argumento se debe colocar el formato de salida, indicando '-f' y como siguiente argumento, se indica si será un archivo txt o un bin. Si se quiere que la entrada de instrucciones sea por stdin se deberá colocar '-', en caso contrario se deben ingresar los diferentes archivos indicando antes el formato como por ejemplo t:suma.lms para un archivo de texto o b:suma.bin para un archivo binario.\n "

#define MSJ_TITULO_ARG "Arg.\t"
#define MSJ_TITULO_OPC "Opción\t"
#define MSJ_TITULO_DESC "Descripción\n"

#define MSJ_AYUDA_ARG "-h\t" 
#define MSJ_AYUDA_OPC "no posee\t" 
#define MSJ_AYUDA_DESC "Muestra una ayuda.\n"

#define MSJ_MEMORIA_ARG "-m\t" 
#define MSJ_MEMORIA_OPC "N\t" 
#define MSJ_MEMORIA_DESC "Simpletron tiene una memoria de N palabras. Si no se da el argumento, por omisión tendrá 50 palabras.\n"

#define MSJ_SALIDA_ARG "-f\t" 
#define MSJ_SALIDA_OPC "FMT\t" 
#define MSJ_SALIDA_DESC "Indica el formato de la salida. Si FMT es txt, el formato debe ser texto. Si FMT es bin, el formato debe ser binario, por omisión el formato es texto.\n"

#define MSJ_ENTRADA_ARG "-\t" 
#define MSJ_ENTRADA_OPC "FMT:archivo\t" 
#define MSJ_ENTRADA_DESC "Formato y nombre de archivo. Si FMT es t, el formato debe ser texto. Si FMT es b, el formato debe ser binario, por omisión el formato es texto.\n"

#define TAB_TITULO_OP "Operación\t"
#define TAB_TITULO_CODE "OpCode\t"
#define TAB_TITULO_DESC "Descripción\n"

#define TAB_ENT_SAL "Op. de Entrada/Salida:\n"

#define TAB_LEER_OP "LEER\t\t" 
#define TAB_LEER_CODE "10\t" 
#define TAB_LEER_DESC "Lee una palabra de stdin a una posición de memoria\n"

#define TAB_ESCRIBIR_OP "ESCRIBIR\t"
#define TAB_ESCRIBIR_CODE "11\t"
#define TAB_ESCRIBIR_DESC "Imprime por stdout una posición de memoria\n"

#define TAB_MOV "Op. de movimiento:\n"

#define TAB_CARGAR_OP "CARGAR\t\t"
#define TAB_CARGAR_CODE "20\t" 
#define TAB_CARGAR_DESC "Carga una palabra de la memoria en el acumulador\n"

#define TAB_GUARDAR_OP "GUARDAR\t\t" 
#define TAB_GUARDAR_CODE "21\t" 
#define TAB_GUARDAR_DESC "Guarda una palabra del acumulador a la memoria\n"

#define TAB_PCARGAR_OP "PCARGAR\t\t" 
#define TAB_PCARGAR_CODE "22\t" 
#define TAB_PCARGAR_DESC "Idem CARGAR pero el operando es puntero\n"

#define TAB_PGUARDAR_OP "PGUARDAR\t\t"
#define TAB_PGUARDAR_CODE "23\t"
#define TAB_PGUARDAR_DESC "Idem GUARDAR pero el operando es puntero\n"

#define TAB_MATE "Op. aritméticas:\n"
#define TAB_SUMAR_OP "SUMAR\t\t" 
#define TAB_SUMAR_CODE "30\t" 
#define TAB_SUMAR_DESC "Suma una palabra al acumulador\n"

#define TAB_RESTAR_OP "RESTAR\t\t" 
#define TAB_RESTAR_CODE "31\t"
#define TAB_RESTAR_DESC "Resta una palabra al acumulador\n"
 
#define TAB_DIVIDIR_OP "DIVIDIR\t\t" 
#define TAB_DIVIDIR_CODE "32\t" 
#define TAB_DIVIDIR_DESC "Divide el acumulador por el operando\n"

#define TAB_MULT_OP "MULTIPLICAR\t" 
#define TAB_MULT_CODE "33\t" 
#define TAB_MULT_DESC "Multiplica el acumulador por el operando\n"

#define TAB_CONTROL "Op. control:\n"
#define TAB_JUMP_OP "JMP\t\t" 
#define TAB_JUMP_CODE "40\t" 
#define TAB_JUMP_DESC "Salta a una ubicación de memoria\n"

#define TAB_JMPNEG_OP "JMPNEG\t\t" 
#define TAB_JMPNEG_CODE "41\t" 
#define TAB_JMPNEG_DESC "Idem sólo si el acumulador es negativo\n"

#define TAB_JMPZERO_OP "JMPZERO\t\t" 
#define TAB_JMPZERO_CODE "42\t" 
#define TAB_JMPZERO_DESC "Idem sólo si el acumulador es cero\n"

#define TAB_JNZ_OP "JNZ\t\t"
#define TAB_JNZ_CODE "43\t"
#define TAB_JNZ_DESC "Idem sólo si el acumulador NO es cero\n"

#define TAB_DJNZ_OP "DJNZ\t\t" 
#define TAB_DJNZ_CODE "44\t"
#define TAB_DJNZ_DESC "Decrementa el acumulador y salta si NO es cero\n"

#define TAB_FIN_OP "HALT\t\t" 
#define TAB_FIN_CODE "45\t" 
#define TAB_FIN_DESC "Finaliza el programa\n"

#define MSJ_REGISTRO "Registros:"

#endif
