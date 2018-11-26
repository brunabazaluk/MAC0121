#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elo{
	
	char * palavra;
	int quantidade;
	struct elo * prox;
	struct elo * anterior;

} elo;

typedef struct noh{
	char * palavra;
	int quantidade;
	struct noh * direita;
	struct noh * esquerda;
} noh;

typedef noh * Noh;

typedef elo * Elo;

int abb_compara(Noh x, Noh y);
int abb_vetor(Noh folha, Noh * v, int i);
void quicksort(char ** vetor, int * v_indices, int primeiro,int ultimo);
void print_alfab(Noh raiz);
void insere_abb(Noh raiz, char * palavra);
int busca_bin(char * palavra, char **v, int * v_indices, int n);
void lista_desordenada(FILE * texto, char * modo);
void v_ordenado(FILE * texto, char * modo);
int busca_vd(char * palavra, char ** v, int n);
char * le_palavra(FILE * texto);
void v_desordenado(FILE * texto, char * modo);
void lista_ordenada(FILE * texto, char * modo);
void abb(FILE * texto, char * modo);

int main(int argc, char ** argv)
{
	
	FILE * filetxt;
	
	setbuf(stdout,NULL);

	filetxt = fopen(argv[1], "r");

	if(strcmp(argv[2],"VD")==0)
		v_desordenado(filetxt, argv[3]);

	else if(strcmp(argv[2],"LD")==0)
		lista_desordenada(filetxt, argv[3]);

	else if(strcmp(argv[2],"VO")==0)
		v_ordenado(filetxt, argv[3]);

	else if(strcmp(argv[2],"LO")==0)
		lista_ordenada(filetxt, argv[3]);

	else if(strcmp(argv[2],"AB")==0)
		abb(filetxt, argv[3]);



	return(0);

}

void abb(FILE * texto, char * modo)
{
	noh *v;
	Noh raiz, folha;
	char * palavra;
	int n=0, i;	

	raiz=malloc(sizeof(Noh));
	raiz->palavra=malloc(30*sizeof(char));
	raiz->quantidade=1;
	raiz->direita=NULL;
	raiz->esquerda=NULL;

	palavra=le_palavra(texto);

	while(palavra!=NULL)
	{
		n+=1;
		folha=raiz;
		insere_abb(raiz, palavra);
		palavra=le_palavra(texto);
	}

	if(strcmp(modo, "A")==0)
	{
		print_alfab(raiz);
	}

	else
	{
		v=malloc(n*sizeof(noh));
		for(i=0; i<n; i++)
		{
			v[i].palavra=malloc(30*sizeof(char));
		}
		i=abb_vetor(raiz, v, n);
		qsort(v,n,sizeof(noh), abb_compara);

		for(i=0;i<n;i++) printf("%s %d\n", v[i].palavra, v[i].quantidade);

	}




void lista_ordenada(FILE * texto, char * modo)
{
	char * palavra;
	Elo comeco, lista, novo;

	comeco = malloc(sizeof(Elo));
	comeco->palavra=malloc(30*sizeof(char));
	comeco->prox=NULL;
	comeco->anterior=NULL;
	comeco->quantidade=1;
	
	palavra=le_palavra(texto);
	
	while(palavra!=NULL)
	{
		lista=comeco;
		while(lista->prox!=NULL && strcmp(lista->palavra,palavra)<0)
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
			novo->anterior=lista;
			lista->prox=novo;
		}
		else if(strcmp(lista->palavra,palavra)>0)
		{
			novo = malloc(sizeof(Elo));
			novo->palavra=malloc(30*sizeof(char));
			novo->palavra=palavra;
			novo->quantidade=1;
			novo->prox=lista;
			novo->anterior=lista->anterior;
			lista->anterior=novo;
			
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


void lista_desordenada(FILE * texto, char * modo)
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

void v_ordenado(FILE * texto, char * modo)
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
		if(i>=n)
		{
			n=2*n;
			v_chave=realloc(v_chave, n*sizeof(char *));
			v_valor=realloc(v_valor, n*sizeof(int));
		}
		busca = busca_bin(palavra,v_chave,v_valor,i);
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

	if(strcmp(modo, "A")){
		for(k=0;k<i;k++)
		{
			printf("%s %d\n", v_chave[k], v_valor[k]);
		}
	}
	else printf("fodase\n");

}

void v_desordenado(FILE * texto, char * modo)
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


	if(strcmp(modo, "A")==0)
	{
		quicksort(v_chave, v_valor, 0, i);
	}

	for(k=0;k<i;k++)
	{
		printf("%s %d\n", v_chave[k], v_valor[k]);
	}



}


char * le_palavra(FILE * texto)
{
	char * palavra;
	int i;

	palavra=malloc(30*sizeof(char));

	if (fscanf(texto, "%s", palavra)!=EOF)
	{
		if(32<=palavra[0] && palavra[0]<=64)
			for(i=0;i<30;i++)
				palavra[i]=palavra[i+1];
		
		else if(65<=palavra[0] && palavra[0]<=90)
			palavra[0]=palavra[0]+32;
		
		if(palavra!=" ")
			return (palavra);
	}
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
	int l=0, r=n-1, m=0;
	int cmp, i;

	while (l <= r) {
		int m = (l+r)/2;
		cmp = strcmp(palavra, v[m]);
		if (cmp == 0)
		{
			return m;
		}
		if (cmp < 0)
		{
			r = m-1;
		}
		else
		{
			l = m+1;
		}
	}
	if (cmp>0)
	{
		m++;
	}
	for (i=n-1;i>=m;i--)
	{
		v[i+1] = v[i];
		v_indices[i+1] = v_indices[i];
	}
	v[m] = palavra;
	v_indices[m] = 1;
	return(-1);
}


void insere_abb(Noh raiz, char * palavra)
{
	Noh folha;
	
	if(strcmp(raiz->palavra,palavra)==0)
	{
		raiz->quantidade+=1;
	}
	else if(strcmp(raiz->palavra,palavra)<0)
	{
		if(raiz->esquerda!=NULL)
		{
			raiz=raiz->esquerda;
			insere_abb(raiz, palavra);
	
		}
		else
		{	
			folha=malloc(sizeof(Noh));
			folha->palavra=malloc(30*sizeof(char));
			folha->esquerda=NULL;
			folha->direita=NULL;
			folha->palavra=palavra;
			folha->quantidade=1;
			raiz->esquerda=folha;
		}
	}
	else if(strcmp(raiz->palavra, palavra)>0)
	{
		if(raiz->direita!=NULL)
		{
			raiz=raiz->direita;
			insere_abb(raiz, palavra);
	
		}
		else
		{	
			folha=malloc(sizeof(Noh));
			folha->palavra=malloc(30*sizeof(char));
			folha->esquerda=NULL;
			folha->direita=NULL;
			folha->palavra=palavra;
			folha->quantidade=1;
			raiz->direita=folha;
		}
	
	}

}

void print_alfab(Noh raiz)
{
	if(raiz->direita!=NULL)
	{
		print_alfab(raiz->direita);
		if(raiz->palavra!="\s")
			printf("%s %d\n", raiz->palavra, raiz->quantidade);
		if(raiz->esquerda!=NULL)
			print_alfab(raiz->esquerda);
	}

	else
	{
		printf("%s %d\n", raiz->palavra, raiz->quantidade);
		if(raiz->esquerda!=NULL)
			print_alfab(raiz->esquerda);
	}
}
void quicksort(char ** vetor, int * v_indices, int primeiro,int ultimo)
{
	int i, j, pivot, n_aux;
	char * aux;
	
	if(primeiro<ultimo){
		pivot=primeiro;
		i=primeiro;
		j=ultimo;

	while(i<j)
	{
        	while(strcmp(vetor[i], vetor[pivot])<=0 && i<ultimo)
			i++;
        	while(strcmp(vetor[j], vetor[pivot])>0)
        		j--;
        	if(i<j)
		{
        		aux=vetor[i];
			n_aux=v_indices[i];
        		vetor[i]=vetor[j];
			v_indices[i]=v_indices[j];
        		vetor[j]=aux;
			v_indices[j]=n_aux;
		}
	}

	aux=vetor[pivot];
	n_aux=v_indices[pivot];
	vetor[pivot]=vetor[j];
	v_indices[pivot]=v_indices[j];
	vetor[j]=aux;
	v_indices[j]=n_aux;
	quicksort(vetor, v_indices,primeiro,j-1);
	quicksort(vetor, v_indices,j+1,ultimo);

   }
}

int abb_vetor(Noh folha, Noh * v, int i)
{
     if(folha == NULL)
          return i;


     v[i] = folha;
     i++;
     if(folha->esquerda != NULL)
          i = abb_vetor(folha->esquerda, v, i);
     if(folha->direita != NULL)
          i = abb_vetor(folha->direita, v, i);

     return i;
}

int abb_compara(Noh x, Noh y)
{
	if(x->quantidade<y->quantidade) return(-1);	
	if(x->quantidade>y->quantidade) return(1);
	else return(0);
}
