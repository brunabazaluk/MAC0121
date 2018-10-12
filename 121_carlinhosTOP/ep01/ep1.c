/* MAC 121 – Algoritmos e Estruturas de Dados I 		    */
/* EP01 Conjectura 3n + 1 – Entrega: 26 de agosto de 2018   */
/* Aluna: Bruna Bazaluk M. V. NUSP: 9797002 			    */
/* Declaro que este programa foi feito por mim e não copiei */
/* nada de ninguém! 										*/

#include <stdio.h>
#include <stdlib.h>


int atualiza_vetor(int *v, int *vtemp, int conttemp, int contv)
{
	int i;
	contv++;
	for(i=conttemp; i >= 0; i--)
		v[contv] = vtemp[i];
	return contv + conttemp -1;
}

int checa_vetor(int n, int *v, int index)
{
	int i;
	for(i=0; i<index ; i++)
		if(n == v[i])
			return i;
	return 0; 
}
int collatz(int n)
{
	if(n==1) return 1;
	else if(n%2==0) return n/2;
	else return 3*n + 1;
	return 0;
}


int main()
{
	int v[1000000], v_temporario[1000000];
	int pos, cont_f=0, cont_vtemp, fim, pos_vetor=0,i, f, n;

	printf("Digite o primeiro número do intervalo: ");
	scanf("%d", &i);
	printf("\nDigite o último número do intervalo: ");
	scanf("%d", &f);

	v[0] = 1;
	for(i; i <= f; i++)
	{
		n =i;
		cont_vtemp =0;
		while(n!=1)
		{
			pos_vetor += checa_vetor(n, v, pos_vetor);
			if(!pos_vetor)
			{
				v_temporario[cont_vtemp] = n;
				cont_vtemp ++;
				n = collatz(n);
				v_temporario[cont_vtemp] = n;
				cont_f++;
			}
			else if(!cont_vtemp) cont_f = pos_vetor	;
				else cont_f += atualiza_vetor(v, v_temporario, cont_vtemp, cont_f);

		}
		printf("%d\n", cont_f);
		pos_vetor=0;
		cont_f=0;
		atualiza_vetor(v, v_temporario, cont_vtemp, cont_f);
	}
	return 0;
}
