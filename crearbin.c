#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	FILE *prueba;
	int instr[12]={100009,100010,200009,300010,210011,110011,450000,0,0,0,0,0};

	prueba = fopen("pruebabin", "wb");
	fwrite(&instr,sizeof(int),12,prueba);

	fclose(prueba);

	return 0;
}