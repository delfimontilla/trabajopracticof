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

#include "tipos.h"
#include "simpletron.h"
#include "errores.h"
#include "errores.c"
#include "prototipos.h"
#include "vector_puntero_funcion.c"
#include "tda_lista.h"
#include "tda_lista_rec.c"
#include "tda_vector.c"
#include "validar_arg.c"
#include "memoria.c"
#include "entrada.c"
#include "operaciones.c"
#include "salida.c"

int main(int argc, char *argv[])
{
	lista_t lsimpletron;
	simpletron_t * simpletron;
	size_t cant_palabras; /*la cantidad de palabras que han sido asignadas en memoria para las instrucciones*/
	parametros_t argumentos;
    status_t st;
    FILE *fentrada, *fsalida;

    status_t (*destructor_simpletron)(simpletron_t**)=liberar_memoria;
    status_t (*impresor_txt)(simpletron_t *, FILE *)=imprimir_archivo_txt;
    status_t (*impresor_bin)(simpletron_t *, FILE *)=imprimir_archivo_bin;
    status_t (*ejecutar)(simpletron_t *)=ejecutar_simpletron;
    
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
		   	if((st=LISTA_crear_nodo(&lsimpletron,simpletron))!=ST_OK)
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
		   	if((st=LISTA_crear_nodo(&lsimpletron,simpletron))!=ST_OK)
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
		   	}
		}   	
	   	argumentos.inicio_arch++;
	}
 	if((st=LISTA_recorrer(lsimpletron, ejecutar)!=ST_OK))
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
    return EXIT_SUCCESS;
}
