#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lista_desordenada(FILE * texto);
void v_ordenado(FILE * texto);
int busca_vd(char * palavra, char ** v, int n);
char * le_palavra(FILE * texto);
void v_desordenado(FILE * texto);

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

	return(0);

}

void lista_desordenada(FILE * texto)
{
	char * palavra;
	Elo comeco, lista, novo;

	comeco = malloc(sizeof(Elo));
	comeco->palavra=malloc(30*sizeof(char));
	comeco->prox=NULL;
	
	palavra=le_palavra(texto);
	
	while(palavra!=NULL)
	{
		lista=comeco;
		printf("while palavra nao nula\n");
		while(lista->prox!=NULL && strcmp(lista->prox->palavra,palavra)!=0)
		{
			printf("percorre ate achar ou acabar\n");
			lista=lista->prox;
		}
		
		if(lista->prox->palavra==palavra)
		{
			lista=lista->prox;
			lista->quantidade+=1;
		}
		else if(lista->prox==NULL)
		{
		8	
			novo = malloc(sizeof(Elo));
			novo->palavra=malloc(30*sizeof(char));
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
	int i=0,k, j, tamanho=0, fim, n=100;
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


