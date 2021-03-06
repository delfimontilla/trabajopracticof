#ifndef PROCESAMIENTO__C
#define PROCESAMIENTO__C 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "procesamiento.h"
#include "tipos.h"
#include "constantes.h"

#ifdef LENG_ESPANOL
#include "leng_espanol.h"

#elif defined (LENG_INGLES)
#include "leng_ingles.h"

#else
#include "leng_espanol.h"
#endif

status_t abrir_archivo_entrada (parametros_t * argumentos, FILE ** fentrada)
 /*Esta funcion recibe un puntero a la estructura de parametros para poder abrir los archivos pasados por linea de argumento,
 y un puntero doble a un archivo para poder abrir los diferentes archivos*/
{
	char aux1[MAX_CADENA];
	char aux2[MAX_CADENA];
	char * comienzo=NULL;
	char * fin=NULL;

	if((strcpy(aux1,argumentos->inicio_arch))==NULL)
	{
		return ST_ERROR_APERTURA_ARCHIVO;
	}
 	if(!(memcpy(aux2,argumentos->inicio_arch, MAX_FORMATO)))
 	{
		return ST_ERROR_APERTURA_ARCHIVO;
	}
 	if(!(strcmp(aux2,TT)) || !(strcmp(aux2, BB))){

		for (comienzo = argumentos->inicio_arch; *comienzo!=DELIM_2PUNTOS; comienzo++)
		{}
		comienzo++;
	   	if((fin=strrchr(aux1,DELIM_2PUNTOS))!=NULL)
	   	{
			*fin='\0';
			if(!(strcmp(aux1,FMT_T))){
				argumentos->fmt_ent_txt=true;
				argumentos->fmt_ent_bin=false;
				if((*fentrada=fopen(comienzo,"rt"))==NULL)
				{
					return ST_ERROR_APERTURA_ARCHIVO;
				}
			}
			else if(!(strcmp(aux1,FMT_B)))
			{
				argumentos->fmt_ent_bin=true;
				argumentos->fmt_ent_txt=false;
				if((*fentrada=fopen(comienzo,"rb"))==NULL)
				{
					return ST_ERROR_APERTURA_ARCHIVO;
				}
			}
		}
	}
	else
	{
		argumentos->fmt_ent_txt=true;
		argumentos->fmt_ent_bin=false;
		if((*fentrada=fopen(argumentos->inicio_arch,"rt"))==NULL)
		{
			return ST_ERROR_APERTURA_ARCHIVO;
		}
	}
	return ST_OK;
}

status_t leer_archivo_bin (simpletron_t ** simpletron, FILE *fentrada)
 /*recibe el puntero doble a la estructura de simpletron para cargar las instrucciones en el vector TDA palabras,
 ademas recibe el puntero al archivo de entrada para poder leer los datos*/
{
	size_t i;
	palabra_t instruccion;

	i=0;
	instruccion = 0;

	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}

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
 y el puntero al archivo de entrada.*/
{
	int i;
	char aux[MAX_CANT_PALABRA];
	long instruccion;
	char * comienzo=NULL;
	char * fin=NULL;

	instruccion = 0;
	i=0;

	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}

 	while(fgets(aux,MAX_CADENA,fentrada)!=NULL)
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
/*Recibe un puntero doble a la estructura simpletron para leer archivos desde stdin y guardar en el vector TDA palabras*/
{
	int i;
	char aux[MAX_CANT_PALABRA];
	long instruccion;
	char * comienzo=NULL;
	char * fin=NULL;

	i=0;
	instruccion = 0;

	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}
 	printf("%s\n",MSJ_BIENVENIDA);
	printf("%2.i %s \n", i,PREGUNTA);
	i++;
 	while(fgets(aux,MAX_CADENA,stdin)!=NULL)
 	{
 		if(i>(*simpletron)->memoria->pedido)
 		{puts("1");
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
    	if(*fin!='\0'&&  *fin!='\n')
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

status_t abrir_archivo_salida (parametros_t * argumentos, FILE ** fsalida)
 /*Esta funcion recibe un puntero simple a parametros para poder indicar el archivo a abrir. Y tambien un puntero doble a FILE
 para poder abrir el archivo de salida*/
{
	if(argumentos->fmt_sal_txt==true)
	{
		if((*fsalida=fopen(argumentos->nombre_arch_sal,"wt"))==NULL)
		{
			return ST_ERROR_APERTURA_ARCHIVO;
		}
	}
	else if(argumentos->fmt_sal_bin==true)
	{
		if((*fsalida=fopen(argumentos->nombre_arch_sal,"wb"))==NULL)
		{
			return ST_ERROR_APERTURA_ARCHIVO;
		}
	}
	return ST_OK;
}

status_t imprimir_archivo_txt(simpletron_t *simpletron, FILE *fsalida)
 /*Recibe el puntero del archivo de salida y a la de simpletron para imprimir los datos guardados en el acumulador,
 en el contador del programa, la ultima instruccion ejecutada, el ultimo opcode y operando,
 además de la lista de todas las palabras, en forma de matriz. Esto se hara en un archivo txt
 o por stdout teniendo en cuenta lo guardado en la estructura de los argumentos*/
{
	int i,l;

	if (!simpletron)
	{
		return ST_ERROR_PTR_NULO;
	}

  fprintf(fsalida,"%s\n", MSJ_REGISTRO);
	fprintf(fsalida, "%25s: %7X\n",MSJ_ACUM, simpletron->acumulador );
	fprintf(fsalida, "%25s: %7i\n",MSJ_CONT_PROG,(int) simpletron->contador_programa );
	fprintf(fsalida, "%25s: %+7d\n",MSJ_INST, simpletron->memoria->palabras[simpletron->contador_programa]);
	simpletron->opcode=(simpletron->memoria->palabras[simpletron->contador_programa]/10000);
	simpletron->operando=(simpletron->memoria->palabras[simpletron->contador_programa]-(simpletron->opcode)*10000);
	fprintf(fsalida, "%25s: %7i\n",MSJ_OPCODE, (int) simpletron->opcode );
	fprintf(fsalida, "%25s: %7i\n",MSJ_OPERANDO, (int) simpletron->operando);
	fprintf(fsalida,"    ");
	for (l = 0; l < 10; l++)
		fprintf(fsalida,"  %i   ",l) ;
	for ( i = 0; i < simpletron->memoria->pedido ; i++)
	{
    	if ((i%10)==0)
    	{
	 		fprintf(fsalida,"\n%03d  ",i);
		}
		fprintf(fsalida,"%05X ",simpletron->memoria->palabras[i] );
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



#endif
