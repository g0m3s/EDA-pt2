#include <stdio.h>
#include<stdlib.h>


struct tipo_vizinho
{
    int vertice;
    struct tipo_vizinho *proximo_vizinho;

}typedef vizinho;

struct tipo_vetor
{
	int vertice;
	int cor;
	struct tipo_vetor *proximo_vertice;
	vizinho *proximo_vizinho;

}typedef vetor_vertices;






void criar_vetor(vetor_vertices *vetor, int n_vertice);
void ligar_vetor(vetor_vertices *vetor, int valor, int j, int linha);




int main()
{
	FILE *arquivo;
	vetor_vertices *vetor;
	int n_vertice, n_aresta, valor, j=1, linha=1;

	arquivo = fopen("arquivo.txt","r");

	if(arquivo != NULL)
	{
		fscanf(arquivo,"%d %d", &n_vertice, &n_aresta);
		criar_vetor(vetor, n_vertice);

		while(!feof(arquivo))
		{
			fscanf(arquivo,"%d", &valor);

			if(j>n_vertice*linha)
			{
				linha++;
			}

			ligar_vetor(vetor,valor,j,linha);
			j++;
		}



		colorir_vetor(vetor);
		imprimir_vetor(vetor);
	}
	else
	{
		printf("Arquivo Vazio!");
	}


	printf("RODOU\n");

	return 0;
}

void criar_vetor(vetor_vertices *vetor, int n_vertice)
{
	vetor_vertices *aux;
	int i;

    aux = vetor;

    while(aux->proximo_vertice != NULL)
    {
    	aux = aux->proximo_vertice;
    }


	for (i = 1; i <= n_vertice; i++)
	{
        aux -> proximo_vertice = (vetor_vertices*)malloc(sizeof(vetor_vertices));
        aux -> proximo_vertice = NULL;
        aux -> vertice = i;
        aux -> cor = NULL;
        aux -> proximo_vizinho = NULL;
    }
    printf("Ok Criar\n");
}


void ligar_vetor(vetor_vertices *vetor, int valor, int j, int linha)
{
	vetor_vertices *aux_vertice;
	vizinho *aux_vizinho;


    if(valor == 1)
    {

   		aux_vertice = vetor;
		while(aux_vertice->vertice != j)
	    {
	    	aux_vertice = aux_vertice->proximo_vertice;
	    }

		aux_vizinho = aux_vertice->proximo_vizinho;

	    while(aux_vizinho->proximo_vizinho != NULL)
	    {
	    	aux_vizinho = aux_vertice->proximo_vizinho;
	    }

		aux_vizinho -> proximo_vizinho = (vizinho*)malloc(sizeof(vizinho));
		aux_vizinho -> proximo_vizinho -> vertice = linha;
	}

	 printf("Ok ligar\n");
}

void colorir_vetor(vetor_vertices *vetor)
{
	int nova_cor=1;
	vetor_vertices *aux, *aux1;

	aux = vetor;

	while(aux->proximo_vertice != NULL)
	{
		aux1 = vetor;
		if(aux->proximo_vizinho != NULL)
		{
			while(aux1->proximo_vertice != NULL)
			{
				if(aux1->vertice == aux->vertice)
				{
					aux->cor = aux1->cor;
				}
				aux1 = aux1 ->proximo_vertice;
			}

			aux1 = vetor;

			while(aux1->proximo_vertice != NULL)
			{

				if(aux1->vertice == aux->vertice && aux1->vertice != aux->vertice)
				{
					nova_cor++;
				}
			}

			aux->cor = nova_cor;
		}

		aux = aux->proximo_vertice;
	}

	printf("Numero de cores utilizado foi de %d", nova_cor);
}


void imprimir_vetor(vetor_vertices *vetor)
{
	vetor_vertices *aux;
	vizinho *aux1;

	aux = vetor;

	while(aux->proximo_vertice != NULL)
	{
		aux1 = aux->proximo_vizinho;
		printf("\n%d -> ", aux->vertice);

		while(aux1->proximo_vizinho != NULL)
		{
			printf("%d  ", aux1->vertice);
		}
	}
}
