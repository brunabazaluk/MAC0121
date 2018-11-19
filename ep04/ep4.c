#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
	
	FILE * filetxt;

	filetxt = fopen(argv[1], "r");

	if (fgets(texto, filetxt)==NULL)
		printf("\nerror reading file\n");

}

int v_desordenado(char ** texto)
{
	char ** v;
	int i=0, j;
	
	while (texto[i]!= EOF)
	{
			
	}



}

