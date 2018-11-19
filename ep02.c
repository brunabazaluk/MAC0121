#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
	int * p[MAX];
	int topo; 
} pilha;

typedef pilha * Pilha;


void Desempilha(Pilha P);
void Empilha(Pilha P, int * x);
void DestroiPilha(Pilha P);
void lematriz(int i, int j, int ** mat);
Pilha CriaPilha();
void TopoDaPilha(Pilha P, int v[]);
int PilhaVazia(Pilha P);
int comeca_palavra(int **mat, int lin, int col);
void lepalavras(char **c, int v[], int n);
void print_matriz(char **c, int lin, int col);
int Tenta_inserir(int hor_ver, int **mat, char **char_mat, char c, int lin, int col);	


int main()
{
	int inseriu=0, c, n, i, j, k, lin, col, *tamanhos, **mat, index_palavra=0, atual[4];
	Pilha P;
	char **palavras, **mat_final;

	scanf("%d", &lin);
	scanf("%d", &col);
	
	mat_final=malloc(lin*sizeof(char *));
	for (i=0; i<lin; i++)
		mat_final[i]=malloc(col*sizeof(char));

	for (i=0;i<lin;i++)
	{	
		for(j=0;j<col;j++)
			mat_final[i][j]='*';
		mat_final[i][j+1]='\n';
	}

	mat=malloc(lin*sizeof(int *));
	for (i=0; i< lin;i++)
		mat[i]=malloc(col*sizeof(int));

	lematriz(lin, col, mat);

	scanf("%d", &n);

	palavras=malloc(n*sizeof(char *));
	for (i=0;i<n;i++)
		palavras[i]=malloc(MAX*sizeof(char));
	tamanhos=malloc(n*sizeof(int));

	lepalavras(palavras, tamanhos, n);

	P = CriaPilha();

	i=0;
	j=0;

	while(i<lin)
	{
		while(j<col)
		{
			print_matriz(mat_final, lin, col);printf("\n");
			if (comeca_palavra(mat, i, j))
			{
				for (k=0; k<n; k++)
				{
					printf("%s\n", palavras[k]);
					inseriu=0;
					if (tamanhos[k] <= lin) /*tenta horizontal*/
					{
						atual[0]=k;
						atual[1]=0;
						atual[2]=i;
						atual[3]=j;
						for(c=0; c<tamanhos[k]; c++)
						{

							if(mat[i][j]==0)
							{
								inseriu=Tenta_inserir(0, mat, mat_final, palavras[k][c], i, j);/*horizontal*/
								printf("%c %d\n", palavras[k][c], inseriu);
							}
							else if(mat_final[i][j] != palavras[k][c])
							{
								TopoDaPilha(P, atual);
								Desempilha(P); /* [#palavra, horizontal=0 vertical=1, i, j] */
								if (atual[1] == 1); /*foi tentada na horizontal*/
								{
									c=tamanhos[k]+2;
								}

							}
						}
						
						if (inseriu)
						{
							atual[0]=k;
							atual[1]=0;
							atual[2]=i;
							atual[3]=j;
							Empilha(P, atual);
							k=n+1;
							j++;
						}
					}


					if (tamanhos[k] <= col && !inseriu)
					{
						for(c=0; c<=tamanhos[k]; c++)
						{
							if(mat[i][j]==0)
								inseriu=Tenta_inserir(1, mat, mat_final, palavras[k][c], i, j);/*vertical*/
							else if(mat_final[i][j] != palavras[k][c])
							{
								TopoDaPilha(P, atual);
								Desempilha(P); /* [#palavra, horizontal=0 vertical=1,] */
								c=tamanhos[k]+2;
							}
						}
						if (inseriu)
						{
							atual[0]=k;
							atual[1]=0;
							atual[2]=i;
							atual[3]=j;
							Empilha(P, atual);
							k=n+1;
							j++;
						}
					}

				}
				
				if (!inseriu && !PilhaVazia(P))
				{
					i=atual[2];
					j=atual[3];
				}
				if(!inseriu && PilhaVazia(P))
				{
					printf("nao ha solucao\n");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	if (!inseriu)
		printf("nao ha solucao\n");
	else print_matriz(mat_final, lin, col);

	return(0);
}


Pilha CriaPilha()
{
	Pilha P;
	P = malloc(sizeof(pilha));
	P -> topo=0;

	return(P);
}

void DestroiPilha(Pilha P)
{
	free(P);
}

void Empilha(Pilha P, int * x)
{
	P -> p[P->topo] = malloc(5*sizeof(int));
	P -> topo ++;
	P -> p[P->topo] = x;
}

void Desempilha(Pilha P)
{
	P -> topo --;
}

void TopoDaPilha(Pilha P, int v[])
{
	v[0]=P -> topo-1;
	v[1]=P -> topo+1;
}

int PilhaVazia(Pilha P)
{
	if(P->topo == 0)
		return 1;
	else return 0;
}

void lematriz(int lin, int col, int ** mat)
{
	int i, j;


	for (i=0;i<lin; i++)
		for(j=0;j<col;j++)
			scanf("%d", &mat[i][j]);

}

int comeca_palavra(int **mat, int lin, int col)
{
	if (mat[lin][col]==-1)
		return (0);

	if (mat[lin+1][col]==-1 || mat[lin][col+1]==-1 || mat[lin][col-1]==-1)
		return (1);


	if (mat[lin+1][col]==-1 || mat[lin][col+1]==-1 || mat[lin-1][col]==-1)
		return (1);


	if (mat[lin+1][col]==-1 || mat[lin][col+1]==-1)
		return (1);

	if (mat[lin+1][col]==-1 || mat[lin][col+1]==-1 || mat[lin-1][col]==-1 || mat[lin][col-1]==-1)
		return (1);

	return(0);
}




void lepalavras(char **c, int tam[], int n)
{
	int i, j;
	char x;
	scanf("%c", &x);
	for(i=0;i<n;i++)
	{
		j=0;
		scanf("%c", &c[i][j]);
		while(c[i][j] != '\n')
		{
			scanf("%c", &c[i][j+1]);
			j++;
		}
		tam[i]=j;
	}	
}

void print_matriz(char **c, int lin, int col)
{
	int i, j;
	for(i=0;i<lin;i++)
	{
		for(j=0;j<col;j++)
			printf(" %c ", c[i][j]);
		printf("\n");
	}
}

int Tenta_inserir(int hor_ver, int **mat, char **char_mat, char c, int i, int j)
{
	if (mat[i][j] == 0  || char_mat[i][j] == c)
	{
		char_mat[i][j] = c;
		return 1;
	}

	return 0;
}