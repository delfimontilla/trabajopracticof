#ifndef LANG_ENGLISH__H
#define LANG_ENGLISH__H 1

#include <stdio.h>


/* In this .h are the macros of the messages used in the program in English */

#define MSJ_ERROR "ERROR"
#define MSJ_ERROR_APERTURA_ARCHIVO "ERROR: opening file"
#define MSJ_ERROR_PTR_NULO "ERROR: null pointer"
#define MSJ_ERROR_CANT_ARG "ERROR: number of arguments"
#define MSJ_ERROR_CANT_PALABRAS "ERROR: number of words"
#define MSJ_ERROR_NO_MEM "ERROR: out of memory"
#define MSJ_ERROR_PALABRA_VACIA "ERROR: the entered word is null"
#define MSJ_ERROR_FUERA_DE_RANGO "ERROR: an attempt was made to access a memory location out of range "
#define MSJ_ERROR_LIBERAR_MEM "ERROR: error when freeing memory"
#define MSJ_ERROR_LECTURA "ERROR: reading file"
#define MSJ_ERROR_PALABRA_NEG "ERROR: negative word"
#define MSJ_ERROR_ARG_INV "ERROR: invalid argument"
#define MSJ_ERROR_NO_NUMERICO "ERROR: it's not a number"
#define MSJ_ERROR_NADA_QUE_CARGAR "ERROR: there's nothing to save"
#define MSJ_OK "OK"
#define MSJ_ERROR_EJECUCION "vector iteration"
#define MSJ_SALIR "Exit"
#define MSJ_AYUDA "Help finished"

#define MSJ_IMPRIMIR_PALABRA "Content of the position"
#define MSJ_INGRESO_PALABRA "Enter a word:"

#define MSJ_ACUM "accumulator"
#define MSJ_CONT_PROG "program counter"
#define MSJ_INST "instruction"
#define MSJ_OPCODE "opcode"
#define MSJ_OPERANDO "operand"

#define MSJ_BIENVENIDA "Welcome to Simpletron! Please enter your program one instruction (or data word) at a time. I will type the location number and a question mark (?). You then type the word for that location. Type the sentinel -99999 to stop entering your program."
#define MSJ_CARGA_COMPLETA "*** Program upload complete ***"
#define MSJ_COMIENZO_EJECUCION "*** Program execution starts ***"

#define MSJ_ACLARACION_AYUDA1 "To enter these arguments they must be placed in the order shown below. If you want to leave the field of number of words in default, you must put '-' in the first field, this only works in case the input is stdin. In case of reading from a file, you have to write the exact number of instructions."
#define MSJ_ACLARACION_AYUDA2 " If you want the entry of instructions to be stdin you must put 'stdin' and in format '-', the same will be done with stdout. In case of placing the output or the entry in a file, the name of the file must be followed by its type. \n"

#define MSJ_TITULO_ARG "Arg.\t"
#define MSJ_TITULO_OPC "Option\t"
#define MSJ_TITULO_DESC "Description\n"

#define MSJ_AYUDA_ARG "-h\t" 
#define MSJ_AYUDA_OPC "doesn't have\t" 
#define MSJ_AYUDA_DESC "Shows help.\n"

#define MSJ_MEMORIA_ARG "-m\t" 
#define MSJ_MEMORIA_OPC "N\t" 
#define MSJ_MEMORIA_DESC "Simpletron has a memory for N words. If no arguments is provided, by default it'll have 50 words.\n"

#define MSJ_SALIDA_ARG "-f\t" 
#define MSJ_SALIDA_OPC "FMT\t" 
#define MSJ_SALIDA_DESC "Indicates the format of the output. If FMT is txt, the format must be text. If FMT is bin, the format must be binary, by default the format is text.\n"

#define MSJ_ENTRADA_ARG "-\t" 
#define MSJ_ENTRADA_OPC "FMT:archivo\t" 
#define MSJ_ENTRADA_DESC "Format and name of the input file. If FMT is t, the format must be text. If FMT is b, the format must be binary, by default the format is text.\n"

#define TAB_TITULO_OP "Operation\t"
#define TAB_TITULO_CODE "OpCode\t"
#define TAB_TITULO_DESC "Description\n"

#define TAB_ENT_SAL "Input/Output Op.:\n"

#define TAB_LEER_OP "READ\t\t" 
#define TAB_LEER_CODE "10\t" 
#define TAB_LEER_DESC "Reads a word from stdin to a position of memory\n"

#define TAB_ESCRIBIR_OP "WRITE\t\t"
#define TAB_ESCRIBIR_CODE "11\t"
#define TAB_ESCRIBIR_DESC "Prints by stdout a position of memory\n"

#define TAB_MOV "Movement Op.:\n"

#define TAB_CARGAR_OP "LOAD\t\t"
#define TAB_CARGAR_CODE "20\t" 
#define TAB_CARGAR_DESC "Loads a word from the memory to the accumulator\n"

#define TAB_GUARDAR_OP "SAVE\t\t" 
#define TAB_GUARDAR_CODE "21\t" 
#define TAB_GUARDAR_DESC "Saves a word from the accumulator to the memory\n"

#define TAB_PCARGAR_OP "PLOAD\t\t" 
#define TAB_PCARGAR_CODE "22\t" 
#define TAB_PCARGAR_DESC "Same as LOAD but the operand is pointer\n"

#define TAB_PGUARDAR_OP "PSAVE\t\t"
#define TAB_PGUARDAR_CODE "23\t"
#define TAB_PGUARDAR_DESC "Same a SAVE but the operand is pointer\n"

#define TAB_MATE "Arithmetic Op.:\n"

#define TAB_SUMAR_OP "ADDITION\t" 
#define TAB_SUMAR_CODE "30\t" 
#define TAB_SUMAR_DESC "Adds a word to the accumulator\n"

#define TAB_RESTAR_OP "SUBTRACTION\t" 
#define TAB_RESTAR_CODE "31\t"
#define TAB_RESTAR_DESC "Subtract a word to the accumulator\n"
 
#define TAB_DIVIDIR_OP "DIVIION\t\t" 
#define TAB_DIVIDIR_CODE "32\t" 
#define TAB_DIVIDIR_DESC "Divides the accumulator by the operand\n"

#define TAB_MULT_OP "MULTIPLY\t" 
#define TAB_MULT_CODE "33\t" 
#define TAB_MULT_DESC "Multiplies the accumulator by the operand\n"

#define TAB_CONTROL "Control Op.:\n"

#define TAB_JUMP_OP "JMP\t\t" 
#define TAB_JUMP_CODE "40\t" 
#define TAB_JUMP_DESC "Jumps to a memory location\n"

#define TAB_JMPNEG_OP "JMPNEG\t\t" 
#define TAB_JMPNEG_CODE "41\t" 
#define TAB_JMPNEG_DESC "Idem only if the accumulator is negative\n"

#define TAB_JMPZERO_OP "JMPZERO\t\t" 
#define TAB_JMPZERO_CODE "42\t" 
#define TAB_JMPZERO_DESC "Idem only if the accumulator is zero\n"

#define TAB_JNZ_OP "JNZ\t\t"
#define TAB_JNZ_CODE "43\t"
#define TAB_JNZ_DESC "Idem only if the accumulator is NOT zero\n"

#define TAB_DJNZ_OP "DJNZ\t\t" 
#define TAB_DJNZ_CODE "44\t"
#define TAB_DJNZ_DESC "Decreases the accumulator and jump if it is NOT zero\n"

#define TAB_FIN_OP "HALT\t\t" 
#define TAB_FIN_CODE "45\t" 
#define TAB_FIN_DESC "Finishes the program\n"

#define MSJ_REGISTRO "Registers:"

#endif
