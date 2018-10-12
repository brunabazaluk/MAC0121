#include <stdlib.h>
#include <stdio.h>

int main()
{
	int i, j, lin=2, col=2;
	char c[2][2];

	c[0][0]='a';
	c[0][1]='b';
	c[1][0]='a';
	c[1][1]='b';

	for(i=0;i<lin;i++)
	{
		for(j=0;j<col;j++)
			printf("%c", c[i][j]);
		printf("\n");
	}
}