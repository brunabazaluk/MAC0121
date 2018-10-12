#define MAX 100000
#include <stdio.h>
#include <stdlib.h>

/*typedef int TipoDaPilha;*/

typedef struct {
	TipoDaPilha p[MAX];
	int topo; 
} pilha;




typedef pilha * Pilha; /* um ponteiro para uma pilha */



TipoDaPilha Topo(Pilha P);
void Desempilha(Pilha P);
void Empilha(Pilha P, TipoDaPilha x);
void DestroiPilha(Pilha P);
Pilha CriaPilha();


/*
int main()
{


	int x, y;


	Pilha P=CriaPilha();

	scanf("%d", &x);
	scanf("%d", &y);

	Empilha(P, x);
	Empilha(P, y);

	printf("%d\n", Topo(P));
	Desempilha(P);
	printf("%d\n", Topo(P));
	Desempilha(P);


}
*/

Pilha CriaPilha()
{
	Pilha P;
	P = malloc(sizeof(pilha));
	P -> topo=0;

}

void DestroiPilha(Pilha P)
{
	free(P);
}

void Empilha(Pilha P, TipoDaPilha x)
{
	P -> p[P -> topo]=x;
	P->topo ++;
}

void Desempilha(Pilha P)
{
	P -> topo --;
}

TipoDaPilha Topo(Pilha P)
{
	int * v;
	v=[P -> p[P->topo-1], 0];
	return(v);
}




