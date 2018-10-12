#include <stdlib.h>
#include <stdio.h>


int main()
{
	int * tam, n, i, j;
	char **c;

	scanf("%d", &n);

	for(i=0;i<n;i++)
	{
		j=0;
		scanf("%c", &c[i][j]);
		while(c[i][j] != '\n')
		{
			scanf("%c", &c[i][j]);
			j++;
		}
		tam[i]=j;
	}
	for (i=0; i<n;i++)
		printf("%s\n", c[i]);

}