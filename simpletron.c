#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define LENG_ESPANOL /*elección del idioma del programa*/

#ifdef LENG_ESPANOL
#include "leng_espanol.h"

#elif defined (LENG_INGLES)
#include "leng_ingles.h"

#else 
#include "leng_espanol.h"
#endif

#include "constantes.h"
#include "simpletron.h"
#include "status.h"
#include "status.c"
#include "parametros.h"
#include "prototipos.h"
#include "tda_lista.h"
#include "tda_lista_rec.c"
#include "tda_vector.c"

int main(int argc, char *argv[])
{
	lista_t lsimpletron;
	simpletron_t * simpletron;
	size_t cant_palabras; /*la cantidad de palabras que han sido asignadas en memoria para las instrucciones*/
	parametros_t argumentos;
    status_t st;
    FILE *fentrada, *fsalida;
    
   	cant_palabras=0;
    simpletron=NULL;
    fentrada=NULL;
    fsalida=NULL;

    if((st=validar_argumentos(argc, argv, &argumentos, &cant_palabras))!=ST_OK)
    {
    	if (st==ST_AYUDA)
    	{
    		imprimir_ayuda(st);
    		return ST_OK;
    	}
    	else
    	{
    		imprimir_error(st);
    		return EXIT_FAILURE;
    	}	
    }
    if((st=LISTA_crear(&lsimpletron))!=ST_OK)
    {
    	imprimir_error(st);
    	return EXIT_FAILURE;
    }
    while(argumentos.inicio_arch!= NULL)
    {
		if((st=inicializar_simpletron(&simpletron, cant_palabras))!=ST_OK)
		{
     		imprimir_error(st);
     		if((st=LISTA_destruir(&lsimpletron, liberar_memoria(&simpletron)))!=ST_OK)
     		{
 		    	if(fentrada!=NULL)
 		    	{
	   			    fclose(fentrada);
	   			}
				imprimir_error(st);
				return EXIT_FAILURE;
     		}
			if(fentrada!=NULL)
			{
	        	fclose(fentrada);
	    	}
	   		return EXIT_FAILURE;
	   	}
	   	if (argumentos.fmt_ent_stdin==true)
	    {
	   		if((st=leer_archivo_stdin(&simpletron))!=ST_OK)
			{
		       	imprimir_error(st);
		       	free(simpletron);
		       	simpletron=NULL;
		       	if((st=LISTA_destruir(&lsimpletron,liberar_memoria(&simpletron)))!=ST_OK)
     			{
  			   		if(fentrada!=NULL)
  			   		{
  			   			fclose(fentrada);
  			   		}	   					
					imprimir_error(st);
					return EXIT_FAILURE;
				}	
  		   		if(fentrada!=NULL)
  		   		{
  		   			fclose(fentrada);
  		   		}	  				    	   					
				return EXIT_FAILURE;
		   	}
		   	if((st=LISTA_crear_nodo(&lsimpletron,simpletron))!=ST_OK)
		   	{
		   		imprimir_error(st);
		   		free(simpletron);
			   	simpletron=NULL;
		   		if((st=LISTA_destruir(&lsimpletron, liberar_memoria(&simpletron)))!=ST_OK)
	  			{
	 		   		if(fentrada!=NULL)
	 		   		{
	  		   			fclose(fentrada);
	  		   		}  				    	   					
					imprimir_error(st);
					return EXIT_FAILURE;
	     		}
		   	}
		   	break;
		}	
	   	if (argumentos.fmt_ent_stdin==false)
	    {
	   		if((st=abrir_archivo_entrada(&argumentos, &fentrada))!=ST_OK)
	   		{
   	   			imprimir_error(st);
   	   			free(simpletron);
		       	simpletron=NULL;
     			if((st=LISTA_destruir(&lsimpletron,liberar_memoria(&simpletron)))!=ST_OK)
     			{
 		    		if(fentrada!=NULL)
 		    		{	
	   				    fclose(fentrada);
			   		}	
					imprimir_error(st);
					return EXIT_FAILURE;
     			}
	   			return EXIT_FAILURE;
	   		}
		   	if (argumentos.fmt_ent_bin==true)
		   	{
				if((st=leer_archivo_bin(&simpletron, fentrada))!=ST_OK)
				{
		       		imprimir_error(st);
		       		free(simpletron);
		       		simpletron=NULL;
			     	if((st=LISTA_destruir(&lsimpletron, liberar_memoria(&simpletron)))!=ST_OK)
	     			{
	  			   		if(fentrada!=NULL)
	  			   		{
	  			   			fclose(fentrada);
	  			   		}		   				       					
						imprimir_error(st);
						return EXIT_FAILURE;
	     			}
		       		if(fentrada!=NULL)
		       		{
		       			fclose(fentrada);
		       		}
		   			return EXIT_FAILURE;
		   		}
		   	}
		   	else if (argumentos.fmt_ent_txt==true)
		   	{
				if((st=leer_archivo_txt(&simpletron, fentrada))!=ST_OK)
				{
			       	imprimir_error(st);
			       	free(simpletron);
			       	simpletron=NULL;
			       	if((st=LISTA_destruir(&lsimpletron,liberar_memoria(&simpletron)))!=ST_OK)
	     			{
	  			   		if(fentrada!=NULL)
	  			   		{
	  			   			fclose(fentrada);
	  			   		}	   					
						imprimir_error(st);
						return EXIT_FAILURE;
					}	
	  		   		if(fentrada!=NULL)
	  		   		{
	  		   			fclose(fentrada);
	  		   		}	  				    	   					
					return EXIT_FAILURE;
			   	}
			} 
		   	if((st=LISTA_crear_nodo(&lsimpletron,simpletron))!=ST_OK)
		   	{
		   		imprimir_error(st);
		   		free(simpletron);
			   	simpletron=NULL;
		   		if((st=LISTA_destruir(&lsimpletron, liberar_memoria(&simpletron)))!=ST_OK)
	  			{
	 		   		if(fentrada!=NULL)
	 		   		{
	  		   			fclose(fentrada);
	  		   		}  				    	   					
					imprimir_error(st);
					return EXIT_FAILURE;
	     		}
		   	}
		}   	
	   	argumentos.inicio_arch++;
	}
 	if((st=LISTA_recorrer(lsimpletron, ejecutar_simpletron(simpletron)))!=ST_OK)
 	{
   		imprimir_error(st);
     	if((st=LISTA_destruir(&lsimpletron,liberar_memoria(&simpletron)))!=ST_OK)
     	{
  			if(fentrada!=NULL)
  	   		{
  	   			fclose(fentrada);
  	   		}	   				    	   					
			imprimir_error(st);
			return EXIT_FAILURE;
     	}
   		if(fentrada!=NULL)
   		{
   			fclose(fentrada);
   		}	   				       					
		return EXIT_FAILURE;
	}	
   	if((st=abrir_archivo_salida(&argumentos, &fsalida))!=ST_OK)
   	{
   	   	imprimir_error(st);	
   		if((st=LISTA_destruir(&lsimpletron,liberar_memoria(&simpletron)))!=ST_OK)
     	{
  			if(fentrada!=NULL)
  	   		{
  	   			fclose(fentrada);
  	   		}	   				    	   					
			imprimir_error(st);
			return EXIT_FAILURE;
     	}
   		if(fentrada!=NULL)
   		{
   			fclose(fentrada);
   		}
   		return EXIT_FAILURE;
   	}
   	if (argumentos.fmt_sal_txt==true)
   	{	
		if((st=LISTA_imprimir(lsimpletron, fsalida, imprimir_archivo_txt(simpletron,fsalida)))!=ST_OK)
	   	{
	   	   	imprimir_error(st);	
	   		if((st=LISTA_destruir(&lsimpletron,liberar_memoria(&simpletron)))!=ST_OK)
	     	{
	  			if(fentrada!=NULL)
	  	   		{
	  	   			fclose(fentrada);
	  	   		}	
	  		   	if(fsalida!=NULL)
	 			{
   					fclose(fsalida);
   				} 				    	   					
				imprimir_error(st);
				return EXIT_FAILURE;
	     	}
	   		if(fentrada!=NULL)
	   		{
	   			fclose(fentrada);
	   		}
	   		if(fsalida!=NULL)
	 		{
   				fclose(fsalida);
   			}
	   		return EXIT_FAILURE;
	   	}   		
    }
    else if (argumentos.fmt_sal_bin==true)
   	{	
		if((st=LISTA_imprimir(lsimpletron, fsalida, imprimir_archivo_bin(simpletron,fsalida)))!=ST_OK)
	   	{
	   	   	imprimir_error(st);	
	   		if((st=LISTA_destruir(&lsimpletron,liberar_memoria(&simpletron)))!=ST_OK)
	     	{
	  			if(fentrada!=NULL)
	  	   		{
	  	   			fclose(fentrada);
	  	   		}	
	  		   	if(fsalida!=NULL)
	 			{
   					fclose(fsalida);
   				} 				    	   					
				imprimir_error(st);
				return EXIT_FAILURE;
	     	}
	   		if(fentrada!=NULL)
	   		{
	   			fclose(fentrada);
	   		}
	   		if(fsalida!=NULL)
	 		{
   				fclose(fsalida);
   			}
	   		return EXIT_FAILURE;
	   	}   		
    }
	if((st=LISTA_destruir(&lsimpletron,liberar_memoria(&simpletron)))!=ST_OK)
   	{
		if(fentrada!=NULL)
		{
   			fclose(fentrada);
   		}	
	   	if(fsalida!=NULL)
		{
			fclose(fsalida);
		} 				    	   					
		imprimir_error(st);
		return EXIT_FAILURE;
   	}	
	if(fentrada!=NULL)
        fclose(fentrada);
    if(fsalida!=NULL)
	   	fclose(fsalida);
 
    return EXIT_SUCCESS;
}

status_t validar_argumentos (int argc , char *argv[], parametros_t *argumentos, size_t *cant_palabras)
 /*recibe arc y argv para realizar las validaciones correspondientes a su cantidad y contenido;
 además recibe el puntero a cant_palabras (cantidad de instrucciones) para cargarle su contenido
 y los dobles punteros al archivo de entrada para abrirlo en caso de ser necesario,
 y al archivo de salida para crearlo en caso de así especificarlo.*/
{
	char *pc=NULL;
		
	if(!argv|| !cant_palabras || !argumentos)
	{
		return ST_ERROR_PTR_NULO;
	}

	if(argc==ARGC_MIN)
	{
		if(!(strcmp(argv[ARG_POS_H],ARG_H)))
			return ST_AYUDA;
	}

	if(strcmp(argv[ARG_POS_CANT_PALABRAS],ARG_CANT_PALABRAS))
	{
		*cant_palabras=CANT_PALABRAS_DEFAULT;
		if(strcmp(argv[ARG_POS_FSALIDA1],ARG_FSALIDA))
		{
			argumentos->fmt_sal_txt=true;
			argumentos->fmt_sal_bin=false;
			if (!(strcmp(argv[ARG_POS_FENTRADA1], ARG_STDIN)))
			{
				argumentos->fmt_ent_stdin=true;
				argumentos->nombre_arch=NOMBRE_SALIDA;
			}	
			else 
			{
				argumentos->fmt_ent_stdin=false;
				argumentos->inicio_arch=argv[ARG_POS_FENTRADA1];
			}	
			return ST_OK;
		}	
		else 
		{
			if (!(strcmp(argv[ARG_POS_FENTRADA2], ARG_STDIN)))
			{
				argumentos->fmt_ent_stdin=true;
				argumentos->nombre_arch=NOMBRE_SALIDA;
			}	
			else 
			{
				argumentos->fmt_ent_stdin=false;
				argumentos->inicio_arch=argv[ARG_POS_FENTRADA2];
			}	
			if(!(strcmp(argv[ARG_POS_FSALIDA1_TIPO],OPCION_BIN)))
			{
				argumentos->fmt_sal_txt=false;
				argumentos->fmt_sal_bin=true;
				return ST_OK;
			}	
			else if(!(strcmp(argv[ARG_POS_FSALIDA1_TIPO],OPCION_TXT)))
			{
				argumentos->fmt_sal_txt=true;
				argumentos->fmt_sal_bin=false;
				return ST_OK;
			}	
		}
	}	

	else 
	{
		*cant_palabras = strtol(argv[ARG_POS_CANT_PALABRAS_NUM], &pc, 10);
		if(*cant_palabras< MIN_CANT_PALABRA || *pc!='\0' || *cant_palabras> MAX_CANT_PALABRA)
			return ST_ERROR_CANT_PALABRAS;
		
		if(strcmp(argv[ARG_POS_FSALIDA2],ARG_FSALIDA))
		{
			argumentos->fmt_sal_txt=true;
			argumentos->fmt_sal_bin=false;
			if (!(strcmp(argv[ARG_POS_FENTRADA2], ARG_STDIN)))
			{
				argumentos->fmt_ent_stdin=true;
				argumentos->nombre_arch=NOMBRE_SALIDA;
			}	
			else {
				argumentos->fmt_ent_stdin=false;
				argumentos->inicio_arch=argv[ARG_POS_FENTRADA2];
			}	
			return ST_OK;
		}	
		else 
		{
			if(!(strcmp(argv[ARG_POS_FSALIDA2_TIPO],OPCION_BIN)))
			{
				argumentos->fmt_sal_txt=false;
				argumentos->fmt_sal_bin=true;
				if (!(strcmp(argv[ARG_POS_FENTRADA3], ARG_STDIN)))
				{
					argumentos->fmt_ent_stdin=true;
					argumentos->nombre_arch=NOMBRE_SALIDA;
				}	
				else 
				{
					argumentos->fmt_ent_stdin=false;
					argumentos->inicio_arch=argv[ARG_POS_FENTRADA3];
				}	
				return ST_OK;
			}	
			if(!(strcmp(argv[ARG_POS_FSALIDA2_TIPO],OPCION_TXT)))
			{
				argumentos->fmt_sal_txt=true;
				argumentos->fmt_sal_bin=false;				
				if (!(strcmp(argv[ARG_POS_FENTRADA3], ARG_STDIN)))
				{
					argumentos->fmt_ent_stdin=true;
					argumentos->nombre_arch=NOMBRE_SALIDA;
				}	
				else 
				{
					argumentos->fmt_ent_stdin=false;
					argumentos->inicio_arch=argv[ARG_POS_FENTRADA3];
				}	
				return ST_OK;
			}	
		}
	}
	return ST_OK;
}

status_t inicializar_simpletron (simpletron_t **simpletron, size_t cant_palabras)
/*Esta funcion recibe un doble puntero a la estructura simpletron para poder modificar su contenido, 
y un size_t de cant_palabras para darle la memoria dinamica necesaria al vector de palabras*/	
{
	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}	
	if(!cant_palabras)
	{
		return ST_ERROR_NADA_QUE_CARGAR;
	}	
	if((*simpletron = (simpletron_t *) calloc(1, sizeof(simpletron_t)))==NULL)
	{
		return ST_ERROR_NO_MEM;
	}	
	if(((*simpletron)->memoria=vector_crear(cant_palabras))==NULL)
	{
		liberar_memoria(simpletron);
		return ST_ERROR_NO_MEM;
	}
	(*simpletron)->acumulador=0;
	(*simpletron)->contador_programa=0;
	(*simpletron)->opcode=0;
	(*simpletron)->operando=0;

	return ST_OK;
}

status_t abrir_archivo_entrada (parametros_t * argumentos, FILE ** fentrada){
	
	char * aux;
	char * comienzo;
	char * fin;

	aux=argumentos->inicio_arch;
	for (comienzo = argumentos->inicio_arch; *comienzo!=DELIM_2PUNTOS; comienzo++)
	{}
   	if((fin=strrchr(aux,DELIM_2PUNTOS))!=NULL)
   	{
		*fin='\0';
		if(!(strcmp(aux,FMT_T))){
			argumentos->fmt_ent_txt=true;
			argumentos->fmt_ent_bin=false;
			if((*fentrada=fopen(argumentos->nombre_arch,"rt"))==NULL)
			{
				return ST_ERROR_APERTURA_ARCHIVO;
			}
		}	
		if(!(strcmp(aux,FMT_B)))
		{
			argumentos->fmt_ent_bin=true;
			argumentos->fmt_ent_txt=false;
			if((*fentrada=fopen(argumentos->nombre_arch,"rb"))==NULL)
			{
				return ST_ERROR_APERTURA_ARCHIVO;
			}
		}		
	}
	else
	{
		argumentos->nombre_arch=argumentos->inicio_arch;
		argumentos->fmt_ent_txt=true;
		argumentos->fmt_ent_bin=false;
		if((*fentrada=fopen(argumentos->nombre_arch,"rt"))==NULL)
		{
			return ST_ERROR_APERTURA_ARCHIVO;
		}	
	}
	return ST_OK;
}

status_t abrir_archivo_salida (parametros_t * argumentos, FILE ** fsalida){
	
	if(argumentos->fmt_sal_txt)
	{
		if((*fsalida=fopen(argumentos->nombre_arch,"wt"))==NULL)
		{	
			return ST_ERROR_APERTURA_ARCHIVO;
		}	
	}
	if(argumentos->fmt_sal_bin)
	{
		if((*fsalida=fopen(argumentos->nombre_arch,"wb"))==NULL)
		{	
			return ST_ERROR_APERTURA_ARCHIVO;
		}	
	}
	return ST_OK;
}


status_t leer_archivo_bin (simpletron_t ** simpletron, FILE *fentrada)
 /*recibe el puntero doble a la estructura de simpletron para cargar las instrucciones en el vector palabras, 
 para lo cual necesita la cantidad total de instrucciones (cant_palabras); ademas recibe el puntero
 al archivo de entrada para poder leer los datos*/
{
	size_t i;
	palabra_t instruccion;
	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
	i=0;
	instruccion = 0;
 	while(fread(&instruccion, sizeof(palabra_t),1,fentrada)==1)
 	{
 		if(i>(*simpletron)->memoria->pedido)
 		{
 			return ST_ERROR_LECTURA;
 		}
 		if(instruccion<MIN_PALABRA||instruccion>MAX_PALABRA)
 			return ST_ERROR_FUERA_DE_RANGO;

 		if(((instruccion&MASK_ORIENTACION1)>>SHIFT_ORIENTACION)>MAX_CANT_OPCODE)
	 			return ST_ERROR_FUERA_DE_RANGO;

	 	if((instruccion&MASK_ORIENTACION2)>MAX_CANT_OPERANDO)
	 			return ST_ERROR_FUERA_DE_RANGO;
 		
 		(*simpletron)->memoria->palabras[i]=instruccion;
 		i++;
 	}
	if (ferror(fentrada) || !feof(fentrada)) {
        return ST_ERROR_LECTURA;
    }

 	return ST_OK;
}

status_t leer_archivo_txt(simpletron_t ** simpletron, FILE *fentrada)
 /*Recibe el puntero doble a la estructura de simpletron para cargar las instrucciones en el vector palabras,
 la estructura de los argumentos para determinar desde donde se leeran los datos y el puntero al archivo de entrada.
 Tambien se necesita el valor de cant_palabras (cantidad de instrucciones).*/
{
	int i;
	char aux[MAX_CANT_PALABRA];
	long instruccion;
	char * comienzo;
	char * fin;

	instruccion = 0;
	i=0;

	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}

 	while(fgets(aux,MAX_CADENA,stdin)!=NULL)
 	{
 		if(i>(*simpletron)->memoria->pedido)
 		{
 			return ST_ERROR_LECTURA;
 		}
	   	if((fin=strrchr(aux,DELIM_COMA))!=NULL)
	   	{
 			*fin='\0';
 		}
 		for (comienzo = aux; isspace(*comienzo) && *comienzo!='\0'; comienzo++)
		{}
		if (*comienzo=='\0')
		{	
			*aux='\0';/*equivalente a  aux[0]='\0'*/
		}	
		for(fin = aux+strlen(aux)-1; isspace(*fin) && fin!=aux;fin--)
		{}
		*++fin='\0';
		if (memmove(aux,comienzo,fin-comienzo+1)=='\0')
		{
			continue;
		}
	    instruccion = strtol(aux,&fin,10); 
    	if(*fin!='\0'&& *fin!='\n')
    	{	
    		return ST_ERROR_NO_NUMERICO;
    	}	
    	if(instruccion==FIN)
    	{
    		break;
    	}	
 		if(instruccion<MIN_PALABRA||instruccion>MAX_PALABRA)
 		{
 			return ST_ERROR_FUERA_DE_RANGO;
 		}
 		if(((instruccion&MASK_ORIENTACION1)>>SHIFT_ORIENTACION)>MAX_CANT_OPCODE)
 		{
 			return ST_ERROR_FUERA_DE_RANGO;
 		}
 		if((instruccion&MASK_ORIENTACION2)>MAX_CANT_OPERANDO)\
 		{	
 			return ST_ERROR_FUERA_DE_RANGO;
 		}	
 		(*simpletron)->memoria->palabras[i]=instruccion;
 		i++;
	 	}
		return ST_OK;
	}
}

status_t leer_archivo_stdin(simpletron_t ** simpletron)
{
	int i;
	char aux[MAX_CANT_PALABRA];
	long instruccion;
	char * comienzo;
	char * fin;

	instruccion = 0;

	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}

 	printf("%s\n",MSJ_BIENVENIDA);	
	for(i=0; i<(*simpletron)->memoria->pedido;i++)
	{	
		printf("%2.i %s \n", i,PREGUNTA);
    	if(fgets(aux,MAX_CADENA,stdin)==NULL)
    	{
    		return ST_ERROR_FUERA_DE_RANGO;
    	}  	
	   	if((fin=strrchr(aux,DELIM_COMA))!=NULL)
	   	{
 			*fin='\0';
 		}
 		for (comienzo = aux; isspace(*comienzo) && *comienzo!='\0'; comienzo++)
		{}
		if (*comienzo=='\0')
		{	
			*aux='\0';/*equivalente a  aux[0]='\0'*/
		}	
		for(fin = aux+strlen(aux)-1; isspace(*fin) && fin!=aux;fin--)
		{}
		*++fin='\0';
		if (memmove(aux,comienzo,fin-comienzo+1)=='\0')
		{
			continue;
		}
	    instruccion = strtol(aux,&fin,10); 
    	if(*fin!='\0'&& *fin!='\n')
    	{	
    		return ST_ERROR_NO_NUMERICO;
    	}	
    	if(instruccion==FIN)
    	{
    		break;
    	}	
 		if(instruccion<MIN_PALABRA||instruccion>MAX_PALABRA)
 		{
 			return ST_ERROR_FUERA_DE_RANGO;
 		}
 		if(((instruccion&MASK_ORIENTACION1)>>SHIFT_ORIENTACION)>MAX_CANT_OPCODE)
 		{
 			return ST_ERROR_FUERA_DE_RANGO;
 		}
 		if((instruccion&MASK_ORIENTACION2)>MAX_CANT_OPERANDO)\
 		{	
 			return ST_ERROR_FUERA_DE_RANGO;
 		}	
 		(*simpletron)->memoria->palabras[i]=instruccion;
	}
	return ST_OK;
}

status_t imprimir_error(status_t st)
/*Imprime el error correspondiente*/
{
    fprintf(stderr, "%s\n", errmsg[st]);
	return ST_OK;
}


status_t imprimir_ayuda()
 /*Imprime la información de ayuda: tabla del orden de los argumentos y
 tabla de las operaciones validas*/
{
	printf("%s%s%s%s%s\n%s%s%s",MSJ_ACLARACION_AYUDA1, MSJ_ACLARACION_AYUDA2,TXT_AYUDA1,TXT_AYUDA2,TXT_AYUDA3,TXT_AYUDA4,TXT_AYUDA5,TXT_AYUDA6 );
	return ST_OK;
}


status_t imprimir_archivo_txt(simpletron_t *simpletron, FILE *fsalida)
 /*Recibe el puntero del archivo de salida y a la de simpletron para imprimir los datos guardados en el acumulador, 
 en el contador del programa, la ultima instruccion ejecutada, el ultimo opcode y operando, además de la lista de todas las palabras, en forma de matriz. 
 Esto se hara en un archivo txt o por stdout teniendo en cuenta lo guardado en la estructura de los argumentos*/
{
	int i,l;

	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
    
    fprintf(fsalida,"%s\n", MSJ_REGISTRO);
	fprintf(fsalida, "%25s: %6d\n",MSJ_ACUM, simpletron->acumulador );
	fprintf(fsalida, "%25s: %6lu\n",MSJ_CONT_PROG, simpletron->contador_programa );
	fprintf(fsalida, "%25s: %6d\n",MSJ_INST, simpletron->memoria->palabras[simpletron->contador_programa] );
	simpletron->opcode = simpletron->memoria->palabras[simpletron->contador_programa] /100;/*divido por 100 entonces como es un int borra los numeros despues de la coma y me queda el entero que quiero (ejemplo, si llega 2598 me queda 25.98 pero se guarda 25)*/
	simpletron->operando = simpletron->memoria->palabras[simpletron->contador_programa] - (simpletron->opcode*100);/*necesito los ultimos dos entonces al multiplicar opcode por 100 tengo 2500 del ejemplo entonces 2598-2500 da 98 que son los ultimos dos digitos que necesito*/
	fprintf(fsalida, "%25s: %6lu\n",MSJ_OPCODE, simpletron->opcode );
	fprintf(fsalida, "%25s: %6lu\n",MSJ_OPERANDO, simpletron->operando );
	fprintf(fsalida,"    ");
	for (l = 0; l < 10; l++)
		fprintf(fsalida,"  %i   ",l) ;
	for ( i = 0; i < simpletron->memoria->pedido ; i++)
	{ 
    	if ((i%10)==0)
    	{
	 		fprintf(fsalida,"\n%02i  ",i);
		}		  
		fprintf(fsalida,"%+05i ",simpletron->memoria->palabras[i] );
	}
    fprintf(fsalida,"\n");
    
    return ST_OK;
}

status_t imprimir_archivo_bin (simpletron_t *simpletron, FILE *fsalida)
 /*Recibe el puntero del archivo de salida y el de la estructura de la simpletron para imprimir los datos guardados en ella*/

{
	fwrite(simpletron, sizeof(simpletron_t),1, fsalida);
	return ST_OK;
}


status_t liberar_memoria(simpletron_t ** simpletron)
/*Recibe puntero al simpletron para liberar la memoria pedida*/
{	
	
	if (simpletron!=NULL && *simpletron!=NULL){
		if ((*simpletron)->memoria->palabras!=NULL)
		{	
			free((*simpletron)->memoria->palabras);
			(*simpletron)->memoria->palabras=NULL;
		}
		free((*simpletron)->memoria);
		(*simpletron)->memoria=NULL;
		(*simpletron)->acumulador=0;
		(*simpletron)->contador_programa=0;
		(*simpletron)->opcode=0;
		(*simpletron)->operando=0;
	}
	free(*simpletron);
	*simpletron=NULL;
	return ST_OK;
}

status_t ejecutar_simpletron (simpletron_t * simpletron)
 /*Recibe el puntero a la estructura de simpletron para hacer un análisis de las instrucciones que se encuentran
 en el vector palabras, y después se llama a una función que realiza la operación necesaria. 
 Ademas, se valida que el operando sea una posicion de memoria existente*/
{
	status_t st;
	st=ST_OK;

	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}

	while(st==ST_OK){
		if((simpletron->memoria->palabras)>0){	
			if(0<(simpletron->opcode=simpletron->memoria->palabras[simpletron->contador_programa]/10000) && simpletron->opcode<MAX_CANT_OPCODE){
				if(0<(simpletron->operando=(simpletron->memoria->palabras[simpletron->contador_programa])-(simpletron->opcode)*10000) && simpletron->operando<MAX_CANT_OPERANDO){	

					switch (simpletron->opcode){
						case (OP_LEER):
							st=x[F_op_leer](simpletron);
							simpletron->contador_programa++;
							break;
						case (OP_ESCRIBIR):
							st=x[F_op_escribir](simpletron);
							simpletron->contador_programa++;
							break;
						case (OP_CARGAR):
							st=x[F_op_cargar](simpletron);
							simpletron->contador_programa++;
							break;
						case (OP_GUARDAR):
							st=x[F_op_guardar](simpletron);
							simpletron->contador_programa++;
							break;
						case (OP_PCARGAR):
							st=x[F_op_pcargar](simpletron);
							simpletron->contador_programa++;
							break;
						case(OP_PGUARDAR):
							st=x[F_op_pguardar](simpletron);
							simpletron->contador_programa++;
							break;
						case(OP_SUMAR):
							st=x[F_op_sumar](simpletron);
							simpletron->contador_programa++;
							break;
						case(OP_RESTAR):
							st=x[F_op_restar](simpletron);
							simpletron->contador_programa++;
							break;
						case(OP_DIVIDIR):
							st=x[F_op_dividir](simpletron);
							simpletron->contador_programa++;
							break;
						case(OP_MULTIPLICAR):
							st=x[F_op_multiplicar](simpletron);
							simpletron->contador_programa++;
							break;
						case(OP_JMP):
							st=x[F_op_jmp](simpletron);
							break;
						case(OP_JMPNEG):
							if(simpletron->acumulador<0)
								st=x[F_op_jmp](simpletron);
							else
								simpletron->contador_programa++;
							break;
						case(OP_JMPZERO):
							if(simpletron->acumulador==0)
								st=x[F_op_jmp](simpletron);
							else
								simpletron->contador_programa++;
							break;
						case(OP_JNZ):
							if(simpletron->acumulador!=0)
								st=x[F_op_jmp](simpletron);
							else
							 	simpletron->contador_programa++;
							break;
						case(OP_DJNZ):
							st=x[F_op_jmp](simpletron);
							break;
						case (OP_HALT):
							st=ST_SALIR;
							break;
						default:
							simpletron->contador_programa++;
						break;
				}		
			}
			else
				imprimir_error(ST_ERROR_FUERA_DE_RANGO);
		}
		else
			imprimir_error(ST_ERROR_FUERA_DE_RANGO);
	}
	else 
		imprimir_error(ST_ERROR_FUERA_DE_RANGO);
	}

	if(st==ST_SALIR)
		st=ST_OK;
	return st;		
}


status_t op_leer (simpletron_t * simpletron)
 /*Lee una palabra por stdin a una posicion de memoria que está indicada por el operando (miembro de la estructura simpletron)*/
{
	long numero;
	char * pc, lectura[MAX_CADENA];

	if(!simpletron)
	{	
		return ST_ERROR_PTR_NULO;
	}
	printf("%s\n", MSJ_INGRESO_PALABRA);
	if ((fgets(lectura,MAX_CADENA,stdin))==NULL)
	{	
		return ST_ERROR_PALABRA_VACIA;
	}
	if((pc=strchr(lectura,'\n'))!=NULL)
	{	
		*pc='\0';
	}
	numero = strtol(lectura,&pc,10);
	if(*pc!='\0')
	{	
	    return ST_ERROR_NO_NUMERICO;  
	}
	if(numero<MIN_PALABRA||numero>MAX_PALABRA)
	{	
	 	return ST_ERROR_FUERA_DE_RANGO;
	}
	simpletron->memoria->palabras[simpletron->operando] = numero;
	return ST_OK;
}

status_t op_escribir(simpletron_t * simpletron)
 /*imprime por stdout el contenido de la posicion del operando (miembro de la estructura simpletron)*/
{
	if(!simpletron)
	{	
		return ST_ERROR_PTR_NULO;
	}	
	fprintf(stdout, "%s %lu : %i\n", MSJ_IMPRIMIR_PALABRA,simpletron->operando, simpletron->memoria->palabras[simpletron->operando]);
	return ST_OK;
}

status_t op_cargar (simpletron_t * simpletron)
/*Carga en el acumulador (miembro de la estructura simpletron) la posicion de memoria indicada 
por el operando(miembro de la estructura simpletron)*/
{
	if(!simpletron)
	{		
		return ST_ERROR_PTR_NULO;
	}	
	simpletron->acumulador = simpletron->memoria->palabras[simpletron->operando];
	return ST_OK;
}


status_t op_pcargar (simpletron_t * simpletron)
 /*Carga en el acumulador (miembro de la estructura simpletron) la posicion de memoria indicada 
 por la palabra a la que apunta el operando(miembro de la estructura simpletron)*/
{
	if(!simpletron)
	{	
		return ST_ERROR_PTR_NULO;
	}
	if(!simpletron->memoria->pedido)
	{
		return ST_ERROR_CANT_PALABRAS;
	}
	if(simpletron->memoria->palabras[simpletron->operando] > simpletron->memoria->pedido)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}

	simpletron->acumulador = simpletron->memoria->palabras[simpletron->memoria->palabras[simpletron->operando]];
	return ST_OK;
}

status_t op_guardar (simpletron_t * simpletron)
 /*guarda en la posicion de memoria indicada por el operando(miembro de la estructura simpletron)
  lo que está en el acumulador(miembro de la estructura simpletron)*/
{
	if(!simpletron)
	{	
		return ST_ERROR_PTR_NULO;
	}
	simpletron->memoria->palabras[simpletron->operando] = simpletron->acumulador ;
	return ST_OK;
}

status_t op_pguardar (simpletron_t * simpletron)
 /*guarda en la posicion de memoria indicada por la palabra a la que apunta el operando (miembro de la estructura simpletron) 
 lo que esta en el acumulador(miembro de la estructura simpletron)*/
{
	if(!simpletron)
	{	
		return ST_ERROR_PTR_NULO;
	}
	if(!simpletron->memoria->pedido)
	{
		return ST_ERROR_CANT_PALABRAS;
	}
	if(simpletron->memoria->palabras[simpletron->operando] > simpletron->memoria->pedido)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	simpletron->memoria->palabras[simpletron->memoria->palabras[simpletron->operando]] = simpletron->acumulador ;
	return ST_OK;
}

status_t op_sumar(simpletron_t * simpletron)
 /*suma al acumulador (miembro de la estructura simpletron) lo guardado en la posicion de memoria indcada 
 por el operando(miembro de la estructura simpletron)*/
{
	if(!simpletron)
	{	
		return ST_ERROR_PTR_NULO;
	}
	simpletron->acumulador += simpletron->memoria->palabras[simpletron->operando];
	if(simpletron->acumulador>MAX_PALABRA)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	return ST_OK;
}

status_t op_restar (simpletron_t * simpletron)
 /*resta al acumulador (miembro de la estructura simpletron) lo guardado en la posicion de memoria indcada 
 por el operando(miembro de la estructura simpletron)*/
{
	if(!simpletron)
	{	
		return ST_ERROR_PTR_NULO;
	}
	if(simpletron->acumulador>MAX_PALABRA)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	simpletron->acumulador -= simpletron->memoria->palabras[simpletron->operando];
	return ST_OK;
}

status_t op_dividir (simpletron_t * simpletron)
 /*divide al acumulador (miembro de la estructura simpletron) por lo guardado en la posicion de memoria indicada
  por el operando(miembro de la estructura simpletron)*/
{
	if(!simpletron)
	{	
		return ST_ERROR_PTR_NULO;
	}
	if(simpletron->acumulador>MAX_PALABRA)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	simpletron->acumulador /= simpletron->memoria->palabras[simpletron->operando];
	return ST_OK;
}

status_t op_multiplicar (simpletron_t * simpletron)
 /*multiplica al acumulador (miembro de la estructura simpletron)lo guardado en la posicion de memoria indicada por el operando(miembro de la estructura simpletron)*/
{
	if(!simpletron)
	{	
		return ST_ERROR_PTR_NULO;
	}
	simpletron->acumulador *= simpletron->memoria->palabras[simpletron->operando];
	if(simpletron->acumulador>MAX_PALABRA)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	return ST_OK;
}

status_t op_jmp (simpletron_t * simpletron)
/*salta a la posicion de memoria indicada por el operando(miembro de la estructura simpletron)*/
{
	if(!simpletron)
	{	
		return ST_ERROR_PTR_NULO;
	}
	simpletron->contador_programa = simpletron->operando;
	return ST_OK;
}

status_t op_djnz (simpletron_t * simpletron)
 /*decrementa en 1 el acumulador (miembro de la estructura simpletron) y salta a la posicion indicada 
 por el operando (miembro de la estructura simpletron) en el caso que el acumulador sea distinto de 0*/
{
	if(!simpletron)
	{	
		return ST_ERROR_PTR_NULO;
	}
	if(simpletron->acumulador>MAX_PALABRA)
	{
		return ST_ERROR_FUERA_DE_RANGO;
	}
	simpletron->acumulador--;
	if (simpletron->acumulador!=0)
	{	
		simpletron->contador_programa = simpletron->operando;
	}	
	else
	{
		simpletron->contador_programa++;
	}
	return ST_OK;
}