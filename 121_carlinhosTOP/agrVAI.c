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
int tenta_inserir_horizontal(int **mat, char **mat_final, char *s, int tam_s, int lin, int col, int m, int n);
int tenta_inserir_vertical(int **mat, char **mat_final, char *s, int tam_s, int lin, int col, int m, int n);	


int main()
{
	int inseriu=0, c, n, i, j, k, lin, col, *tamanhos, **mat, index_palavra=0, *atual;
	Pilha P;
	char **palavras, **mat_final;

	atual=malloc(4*sizeof(int));

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

	while(index_palavra<n)
	{
		inseriu=0;
		i=0;
		while(i<lin)
		{
			j=0;
			while(j<col)
			{
				if(comeca_palavra(mat, i,j))
				{
					if(tenta_inserir_horizontal(mat, mat_final, palavras[index_palavra], tamanhos[index_palavra], i, j, lin, col))
					{
						atual[0]=index_palavra;
						atual[1]=i;
						atual[2]=j;
						atual[3]=0;
						Empilha(P, atual);
						inseriu=1;
					}
					else
					{
						if(tenta_inserir_vertical(mat, mat_final, palavras[index_palavra], tamanhos[index_palavra], i, j, lin, col))
						{
							atual[0]=index_palavra;
							atual[1]=i;
							atual[2]=j;
							atual[3]=1;
							Empilha(P, atual);
							inseriu=1;

						}
						
					}
				}
				j++;

			}
			i++;
		}
		if (inseriu)
			index_palavra++;
		else
		{
			atual= P->p[P->topo];
			Desempilha(P);
			if(atual[3]==0)
			{
				if(tenta_inserir_vertical(mat, mat_final, palavras[index_palavra], tamanhos[index_palavra], i, j, lin, col))
					{
						atual[0]=index_palavra;
						atual[1]=i;
						atual[2]=j;
						atual[3]=1;
						Empilha(P, atual);
						inseriu=1;

					}
			}
			else
			{
				index_palavra=atual[0]+1;
			}

		}

	}

	if (inseriu)
	{
		print_matriz(mat_final, lin, col);
		return(0);
	}
	print_matriz(mat_final, lin, col);
	printf("nao ha solucao\n");
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

int tenta_inserir_vertical(int **mat, char **mat_final, char *s, int tam_s, int lin, int col, int m, int n)
{
	int i,k;
	
	for(i=0, k=lin;k<m && i<tam_s;i++, k++)	
	{
		if(mat[k][col] == -1)
			return(0);
		if (mat_final[k][col] != s[k] && mat_final[k][col] != '*')
			return(0);
	
	}
	if(k!=m) return(0);
	for(i=0, k=lin;k<m && i<tam_s;i++, k++)	
		mat_final[k][col] = s[i];
	return(1);
}

int tenta_inserir_horizontal(int **mat, char **mat_final, char *s, int tam_s, int lin, int col, int m, int n)
{
	
	int j,k;
	
	for(j=0, k=col;j<tam_s && k<n;j++, k++)
	{
		if(mat[lin][k] == -1)
		{
			return(0);
		}
		if(mat_final[lin][k] != s[k] && mat_final[lin][k] != '*')
		{
			return(0);
		}
		
	}
	if(k!=n) return(0);
	
	for(j=0, k=col;j<tam_s && k<n;j++, k++)
		mat_final[lin][k] = s[j];
	
	return(1);
}