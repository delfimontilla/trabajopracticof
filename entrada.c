#ifndef ENTRADA__C
#define ENTRADA__C 1

#include <stdio.h>
#include "entrada.h"

status_t abrir_archivo_entrada (parametros_t * argumentos, FILE ** fentrada){
	
	char aux[MAX_CADENA];
	char * comienzo;
	char * fin;

	if((strcpy(aux,argumentos->inicio_arch))==NULL)
	{
		return ST_ERROR_APERTURA_ARCHIVO;
	}
	for (comienzo = argumentos->inicio_arch; *comienzo!=DELIM_2PUNTOS; comienzo++)
	{}
   	if((fin=strrchr(aux,DELIM_2PUNTOS))!=NULL)
   	{
		*fin='\0';
		if(!(strcmp(aux,FMT_T))){
			argumentos->fmt_ent_txt=true;
			argumentos->fmt_ent_bin=false;
			if((*fentrada=fopen(comienzo,"rt"))==NULL)
			{
				return ST_ERROR_APERTURA_ARCHIVO;
			}
		}	
		if(!(strcmp(aux,FMT_B)))
		{
			argumentos->fmt_ent_bin=true;
			argumentos->fmt_ent_txt=false;
			if((*fentrada=fopen(comienzo,"rb"))==NULL)
			{
				return ST_ERROR_APERTURA_ARCHIVO;
			}
		}		
	}
	else
	{
		argumentos->fmt_ent_txt=true;
		argumentos->fmt_ent_bin=false;
		if((*fentrada=fopen(comienzo,"rt"))==NULL)
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

status_t leer_archivo_stdin(simpletron_t ** simpletron)
{
	int i;
	char aux[MAX_CANT_PALABRA];
	long instruccion;
	char * comienzo;
	char * fin;

	i=0;
	instruccion = 0;

	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
 	printf("%s\n",MSJ_BIENVENIDA);	
 	while(fgets(aux,MAX_CADENA,stdin)!=NULL)
 	{
 		if(i>(*simpletron)->memoria->pedido)
 		{
 			return ST_ERROR_LECTURA;
 		}		
 		printf("%2.i %s \n", i,PREGUNTA);
 	
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


#endif