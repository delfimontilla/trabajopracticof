#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define LENG_INGLES /*elección del idioma del programa*/

#ifdef LENG_ESPANOL
#include "leng_espanol.h"

#elif defined (LENG_INGLES)
#include "leng_ingles.h"

#else 
#include "leng_espanol.h"
#endif

#include "tipos.h"
#include "errores.c"
#include "constantes.h"
#include "main.h"
#include "tda_lista.h"
#include "tda_lista_rec.c"
#include "tda_vector.h"
#include "tda_vector.c"
#include "simpletron.h"
#include "simpletron.c"
#include "procesamiento.h"
#include "procesamiento.c"

int main(int argc, char *argv[])
{
	lista_t lsimpletron;
	simpletron_t * simpletron;
	size_t cant_palabras; /*la cantidad de palabras que han sido asignadas en memoria para las instrucciones*/
	parametros_t argumentos;
    status_t st;
    FILE *fentrada, *fsalida;

    size_t i,l;
    size_t posicion_arch; /*el numero de argc que le corresponde al primer archivo en la linea de comando*/

    status_t (*destructor_simpletron)(simpletron_t**)=liberar_memoria;
    status_t (*impresor_txt)(simpletron_t *, FILE *)=imprimir_archivo_txt;
    status_t (*impresor_bin)(simpletron_t *, FILE *)=imprimir_archivo_bin;
    status_t (*ejecutar)(simpletron_t *)=ejecutar_simpletron;
    
   	cant_palabras=0;
    simpletron=NULL;
    fentrada=NULL;
    fsalida=NULL;

    if((st=validar_argumentos(argc, argv, &argumentos, &cant_palabras, &posicion_arch))!=ST_OK)
    {
    	if (st==ST_AYUDA)
    	{
    		imprimir_ayuda();
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
   
	for(i=0; posicion_arch+i<argc; i++) /*lectura y cargar de archivos en una lista*/
	{
		l=strlen(argumentos.inicio_arch);
		if((st=inicializar_simpletron(&simpletron, cant_palabras))!=ST_OK)
		{
     		imprimir_error(st);
     		if((st=LISTA_destruir(&lsimpletron, destructor_simpletron))!=ST_OK)
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
		       	if((st=LISTA_destruir(&lsimpletron,destructor_simpletron))!=ST_OK)
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
		   	if((st=LISTA_insertar_al_final(&lsimpletron, simpletron))!=ST_OK)
		   	{
		   		imprimir_error(st);
		   		free(simpletron);
			   	simpletron=NULL;
		   		if((st=LISTA_destruir(&lsimpletron, destructor_simpletron))!=ST_OK)
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
		   	break;
		}	
	   	if (argumentos.fmt_ent_stdin==false)
	    {
	   		if((st=abrir_archivo_entrada(&argumentos, &fentrada))!=ST_OK)
	   		{
   	   			imprimir_error(st);
   	   			free(simpletron);
		       	simpletron=NULL;
     			if((st=LISTA_destruir(&lsimpletron,destructor_simpletron))!=ST_OK)
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
			     	if((st=LISTA_destruir(&lsimpletron, destructor_simpletron))!=ST_OK)
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
			       	if((st=LISTA_destruir(&lsimpletron,destructor_simpletron))!=ST_OK)
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
		   	if((st=LISTA_insertar_al_final(&lsimpletron, simpletron))!=ST_OK)
		   	{
		   		imprimir_error(st);
		   		free(simpletron);
			   	simpletron=NULL;
		   		if((st=LISTA_destruir(&lsimpletron, destructor_simpletron))!=ST_OK)
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
		}   
		argumentos.inicio_arch+=l+1;
	}

 	if((st=LISTA_recorrer(lsimpletron, ejecutar)!=ST_OK)) /*ejecucion de la simpletron de cada nodo de la lista*/
 	{
   		imprimir_error(st);
     	if((st=LISTA_destruir(&lsimpletron,destructor_simpletron))!=ST_OK)
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
   		if((st=LISTA_destruir(&lsimpletron,destructor_simpletron))!=ST_OK)
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
		if((st=LISTA_imprimir(lsimpletron, fsalida,impresor_txt))!=ST_OK)
	   	{
	   	   	imprimir_error(st);	
	   		if((st=LISTA_destruir(&lsimpletron,destructor_simpletron))!=ST_OK)
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
		if((st=LISTA_imprimir(lsimpletron, fsalida,impresor_bin))!=ST_OK)
	   	{
	   	   	imprimir_error(st);	
	   		if((st=LISTA_destruir(&lsimpletron,destructor_simpletron))!=ST_OK)
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
	if((st=LISTA_destruir(&lsimpletron,destructor_simpletron))!=ST_OK)/*liberacion de la memoria pedida*/
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
    return EXIT_SUCCESS;
}


status_t validar_argumentos (int argc , char *argv[], parametros_t *argumentos, size_t *cant_palabras, size_t *posicion_arch)
 /*recibe arc y argv para realizar las validaciones correspondientes a su cantidad y contenido;
 además recibe el puntero a la estructura de argumentos para cargarle el formato que fue indicado para la entrada y salida de
 datos, recibe el puntero a cant_palabras (cantidad de instrucciones) para cargarle su contenido
 y el puntero a posicion_arch para cargarle el numero de la posicion del primer archivo*/
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
	argumentos->nombre_arch_sal=NOMBRE_SALIDA;
	if(strcmp(argv[ARG_POS_CANT_PALABRAS],ARG_CANT_PALABRAS)) /*comprueba si se pasa la cantidad de palabras*/
	{
		*cant_palabras=CANT_PALABRAS_DEFAULT;
		if(strcmp(argv[ARG_POS_FSALIDA1],ARG_FSALIDA))/*comprueba si se especifica el formato de salida */
		{
			argumentos->fmt_sal_txt=true; 
			argumentos->fmt_sal_bin=false;
			if (!(strcmp(argv[ARG_POS_FENTRADA1], ARG_STDIN)))/*comprueba si la entrada es por stdin en caso de no pasar la cantidad palabras o formato de salida*/
			{
				argumentos->fmt_ent_stdin=true;
			}	
			else 
			{
				argumentos->fmt_ent_stdin=false;
				argumentos->inicio_arch=argv[ARG_POS_FENTRADA1];
				*posicion_arch=ARG_POS_FENTRADA1;
			}	
			return ST_OK;
		}	
		else 
		{
			if (!(strcmp(argv[ARG_POS_FENTRADA2], ARG_STDIN)))/*comprueba si la entrada es por stdin en caso de no pasar la cantidad palabras pero si el formato de salida*/
			{
				argumentos->fmt_ent_stdin=true;
			}	
			else 
			{
				argumentos->fmt_ent_stdin=false;
				argumentos->inicio_arch=argv[ARG_POS_FENTRADA2];
				*posicion_arch=ARG_POS_FENTRADA2;
			}	
			if(!(strcmp(argv[ARG_POS_FSALIDA1_TIPO],OPCION_BIN)))/*comprueba si el formato de salida es bin*/
			{
				argumentos->fmt_sal_txt=false;
				argumentos->fmt_sal_bin=true;
				argumentos->inicio_arch=argv[ARG_POS_FENTRADA2];
				*posicion_arch=ARG_POS_FENTRADA2;
				return ST_OK;
			}	
			else if(!(strcmp(argv[ARG_POS_FSALIDA1_TIPO],OPCION_TXT)))/*comprueba si el formato de salida es txt*/
			{
				argumentos->fmt_sal_txt=true;
				argumentos->fmt_sal_bin=false;
				argumentos->inicio_arch=argv[ARG_POS_FENTRADA2];
				*posicion_arch=ARG_POS_FENTRADA2;
				return ST_OK;
			}	
		}
	}	

	else /*caso de especificar la cantidad de palabras*/
	{
		*cant_palabras = strtol(argv[ARG_POS_CANT_PALABRAS_NUM], &pc, 10);
		if(*cant_palabras< MIN_CANT_PALABRA || *pc!='\0' || *cant_palabras> MAX_CANT_PALABRA)
		{
			return ST_ERROR_CANT_PALABRAS;
		}
			
		if(strcmp(argv[ARG_POS_FSALIDA2],ARG_FSALIDA))/*comprueba si se indica el formato de salida */
		{
			argumentos->fmt_sal_txt=true;
			argumentos->fmt_sal_bin=false;
			if (!(strcmp(argv[ARG_POS_FENTRADA2], ARG_STDIN)))
			{
				argumentos->fmt_ent_stdin=true;
			}	
			else {
				argumentos->fmt_ent_stdin=false;
				argumentos->inicio_arch=argv[ARG_POS_FENTRADA2];
			}	
			*posicion_arch=ARG_POS_FENTRADA2;
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
				}	
				else 
				{
					argumentos->fmt_ent_stdin=false;
					argumentos->inicio_arch=argv[ARG_POS_FENTRADA3];
					
				}	
				*posicion_arch=ARG_POS_FENTRADA3;
				return ST_OK;
			}	
			if(!(strcmp(argv[ARG_POS_FSALIDA2_TIPO],OPCION_TXT)))
			{
				argumentos->fmt_sal_txt=true;
				argumentos->fmt_sal_bin=false;				
				if (!(strcmp(argv[ARG_POS_FENTRADA3], ARG_STDIN)))
				{
					argumentos->fmt_ent_stdin=true;
				}	
				else 
				{
					argumentos->fmt_ent_stdin=false;
					argumentos->inicio_arch=argv[ARG_POS_FENTRADA3];
				

				}	
				*posicion_arch=ARG_POS_FENTRADA3;
				return ST_OK;
			}	
		}
	}
	return ST_OK;
}


status_t imprimir_error(status_t st)
/*Imprime el error correspondiente al status pasado*/
{
    fprintf(stderr, "%s\n", errmsg[st]);
	return ST_OK;
}


status_t imprimir_ayuda(void)
 /*Imprime la información de ayuda: tabla del orden de los argumentos y
 tabla de las operaciones validas*/
{
	printf("%s%s%s%s%s\n%s%s%s",MSJ_ACLARACION_AYUDA1, MSJ_ACLARACION_AYUDA2,TXT_AYUDA1,TXT_AYUDA2,TXT_AYUDA3,TXT_AYUDA4,TXT_AYUDA5,TXT_AYUDA6 );
	return ST_OK;
}
