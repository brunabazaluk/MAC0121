#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int busca_bin(char * palavra, char **v, int * v_indices, int n);
void lista_desordenada(FILE * texto);
void v_ordenado(FILE * texto);
int busca_vd(char * palavra, char ** v, int n);
char * le_palavra(FILE * texto);
void v_desordenado(FILE * texto);
void lista_ordenada(FILE * texto);

typedef struct elo{
	
	char * palavra;
	int quantidade;
	struct elo * prox;

} elo;

typedef elo * Elo;

int main(int argc, char ** argv)
{
	
	FILE * filetxt;
	
	setbuf(stdout,NULL);

	filetxt = fopen(argv[1], "r");

	if(strcmp(argv[2],"VD")==0)
		v_desordenado(filetxt);

	else if(strcmp(argv[2],"LD")==0)
		lista_desordenada(filetxt);

	else if(strcmp(argv[2],"VO")==0)
		v_ordenado(filetxt);

	else if(strcmp(argv[2],"LO")==0)
		lista_ordenada(filetxt);


	return(0);

}

void lista_ordenada(FILE * texto)
{
	char * palavra;
	Elo comeco, lista, novo;

	comeco = malloc(sizeof(Elo));
	comeco->palavra=malloc(30*sizeof(char));
	comeco->prox=NULL;
	comeco->quantidade=1;
	
	palavra=le_palavra(texto);
	
	while(palavra!=NULL)
	{
		lista=comeco;
		while(lista->prox!=NULL && strcmp(lista->palavra,palavra)!=0)
		{
			lista=lista->prox;
		}
		
		if(strcmp(lista->palavra,palavra)==0)
		{
			lista=lista->prox;
			lista->quantidade+=1;
		}
		else if(lista->prox==NULL)
		{
			novo = malloc(sizeof(Elo));
			novo->palavra=malloc(30*sizeof(char));
			novo->palavra=palavra;
			novo->quantidade=1;
			novo->prox=NULL;
			lista->prox=novo;
		}
		palavra=le_palavra(texto);

	}
	
	lista=comeco;

	while(lista->prox!=NULL)
	{
		printf("%s %d\n", lista->palavra, lista->quantidade);
		lista=lista->prox;
	}

}


void lista_desordenada(FILE * texto)
{
	char * palavra;
	Elo comeco, lista, novo;

	comeco = malloc(sizeof(Elo));
	comeco->palavra=malloc(30*sizeof(char));
	comeco->prox=NULL;
	comeco->quantidade=1;
	
	palavra=le_palavra(texto);
	
	while(palavra!=NULL)
	{
		lista=comeco;
		while(lista->prox!=NULL && strcmp(lista->palavra,palavra)!=0)
		{
			lista=lista->prox;
		}
		
		if(strcmp(lista->palavra,palavra)==0)
		{
			lista=lista->prox;
			lista->quantidade+=1;
		}
		else if(lista->prox==NULL)
		{
			novo = malloc(sizeof(Elo));
			novo->palavra=malloc(30*sizeof(char));
			novo->palavra=palavra;
			novo->quantidade=1;
			novo->prox=NULL;
			lista->prox=novo;
		}
		palavra=le_palavra(texto);

	}
	
	lista=comeco;

	while(lista->prox!=NULL)
	{
		printf("%s %d\n", lista->palavra, lista->quantidade);
		lista=lista->prox;
	}

}

void v_ordenado(FILE * texto)
{	
	char *palavra, **v_chave;
	int *v_valor, busca;
	int i=0,k, j=0, tamanho=0, fim, n=100;

	v_chave = malloc(n*sizeof(char*));
	v_valor = malloc(n*sizeof(int));
	for(k=0;k<n;k++)
	{
		v_chave[k]=malloc(30*sizeof(char));
	}
		
	palavra = le_palavra(texto);
	while (palavra != NULL)
	{	
		j++;
		printf("%d",j);
		if(i>=n)
		{
			n=2*n;
			v_chave=realloc(v_chave, n*sizeof(char *));
			v_valor=realloc(v_valor, n*sizeof(int));
		}
		busca = busca_bin(palavra,v_chave,v_valor,n);
		if(busca==-1)
		{	
			i++;
		}
		else
		{
			v_valor[busca]+=1;
		}
	
		palavra=le_palavra(texto);
	}

	for(k=0;k<i;k++)
	{
		printf("%s %d\n", v_chave[k], v_valor[k]);
	}


}

void v_desordenado(FILE * texto)
{
	char *palavra, **v_chave;
	int *v_valor, busca;
	int i=0,k, j, tamanho=0, fim, n=100;

	v_chave = malloc(n*sizeof(char*));
	v_valor = malloc(n*sizeof(int));
	for(k=0;k<n;k++)
	{
		v_chave[k]=malloc(30*sizeof(char));
	}
	
	palavra = le_palavra(texto);
	while (palavra != NULL)
	{	
		if(i>=n)
		{
			n=2*n;
			v_chave=realloc(v_chave, n*sizeof(char *));
			v_valor=realloc(v_valor, n*sizeof(int));
		}
		busca = busca_vd(palavra,v_chave,n);
		if(busca==-1)
		{	
			v_chave[i]=palavra;
			v_valor[i]=1;
			i++;
			palavra=le_palavra(texto);

		}
		else
		{
			v_valor[busca]+=1;
			palavra=le_palavra(texto);
		}
	}

	for(k=0;k<i;k++)
	{
		printf("%s %d\n", v_chave[k], v_valor[k]);
	}



}


char * le_palavra(FILE * texto)
{
	char * palavra;

	palavra=malloc(30*sizeof(char));

	if (fscanf(texto, "%s", palavra)!=EOF)
		return (palavra);
	
	return(NULL);

}

int busca_vd(char * palavra, char ** v, int n)
{
	int i=0;
	while(i<n)
	{
		if(strcmp(palavra, v[i])==0)
			return(i);
		i++;
	}
	return(-1);
}

int busca_bin(char * palavra, char **v, int * v_indices, int n)
{
	int k,esquerda=-1, direita=n, meio;

	while(esquerda<direita-1)
	{
		meio=(esquerda+direita)/2;
		if (strcmp(v[meio],palavra)<0)
			esquerda = meio;
		else direita = meio;
	}
	if (direita!=n && strcmp(palavra, v[direita])==0) 
	{
		printf("palavra igual\n");
		return(direita);
	}
	else 
	{
		for(k=n;k>=direita;k--)
		{
			v[k]=v[k-1];
			v_indices[k]=v_indices[k-1];
		}
		n++;
		v[direita-1]=palavra;
		return(-1);
	}

}
