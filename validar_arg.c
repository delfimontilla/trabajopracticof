#ifndef ERRORES__C
#define ERRORES__C 1

#include <stdio.h>

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
	argumentos->nombre_arch_sal=NOMBRE_SALIDA;
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
			}	
			else 
			{
				argumentos->fmt_ent_stdin=false;
			}	
			return ST_OK;
		}	
		else 
		{
			if (!(strcmp(argv[ARG_POS_FENTRADA2], ARG_STDIN)))
			{
				argumentos->fmt_ent_stdin=true;
			}	
			else 
			{
				argumentos->fmt_ent_stdin=false;
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

#endif