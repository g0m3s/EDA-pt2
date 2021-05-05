#include<stdio.h>
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
	struct tipo_vizinho *primeiro_vizinho;

}typedef vetor_vertices;

struct tipo_lista
{
	vetor_vertices *primeiro;
}typedef lista;



void criar_vetor(lista *vetor, int n_vertice);
void ligar_vetor(lista *vetor, int valor, int j, int linha, int n_vertice);
void colorir_vetor(lista *vetor);
void imprimir_vetor(lista *vetor);


int main()
{
	FILE *arquivo;
	lista vetor;
	int n_vertice, n_aresta, valor, j=1, linha=1;

	arquivo = fopen("arquivo.txt","r");

	if(arquivo != NULL)
	{
		fscanf(arquivo,"%d %d", &n_vertice, &n_aresta);

		criar_vetor(&vetor, n_vertice);


		while(!feof(arquivo))
		{
			fscanf(arquivo,"%d", &valor);

			if(j > (n_vertice*linha))
			{
				linha++;
			}

			ligar_vetor(&vetor,valor,j,linha, n_vertice);
			j++;
		}

		colorir_vetor(&vetor);
		imprimir_vetor(&vetor);
	}
	else
	{
		printf("Arquivo Vazio!");
	}

	return 0;
}

void criar_vetor(lista *vetor, int n_vertice)
{
	vetor_vertices *aux, *aux1;
	int i;

	vetor->primeiro = NULL;
	aux1 =vetor->primeiro;

	for (i = 0; i < n_vertice; i++)
	{
        aux = (vetor_vertices*)malloc(sizeof(vetor_vertices));
        aux -> proximo_vertice = NULL;
        aux -> vertice = (i+1);
        aux -> cor = NULL;
        aux -> primeiro_vizinho = NULL;

        if(vetor->primeiro == NULL)
		{
			vetor->primeiro = aux;
		}
		else
		{
			if(aux1 == NULL)
			{
				aux1 = vetor->primeiro;
			}

			aux1->proximo_vertice = aux;
			aux1 = aux1->proximo_vertice;
		}
    }
}

void ligar_vetor(lista *vetor, int valor, int j, int linha, int n_vertice)
{
	vetor_vertices *aux_vertice;
	vizinho *aux_vizinho1, *aux_vizinho2;

    if(valor == 1)
    {
		aux_vizinho2 = (vizinho*)malloc(sizeof(vizinho));
		aux_vizinho2 -> vertice = j-((linha-1)*n_vertice);
		aux_vizinho2 -> proximo_vizinho = NULL;

   		aux_vertice = vetor->primeiro;

		while(aux_vertice->vertice != linha)//ERRO
	    {
	    	aux_vertice = aux_vertice->proximo_vertice;
	    }


		aux_vizinho1 = aux_vertice->primeiro_vizinho;

		if(aux_vertice->primeiro_vizinho != NULL)
		{

			while(aux_vizinho1->proximo_vizinho != NULL)
		    {
		    	aux_vizinho1 = aux_vizinho1->proximo_vizinho;
		    	printf("ok");
		    }

		    aux_vizinho1->proximo_vizinho = aux_vizinho2;
		}
		else
		{
			aux_vizinho1 = aux_vizinho2;
		}
		printf("1\n");
	}
	else
	{
		printf("0\n");
	}
}

void colorir_vetor(lista *vetor)
{
	int nova_cor=1;
	vetor_vertices *aux, *aux1;

	aux = vetor;

	while(aux->proximo_vertice != NULL)
	{
		aux1 = vetor;
		if(aux->primeiro_vizinho != NULL)
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


void imprimir_vetor(lista *vetor)
{
	vetor_vertices *aux;
	vizinho *aux1;

	aux = vetor;

	while(aux->proximo_vertice != NULL)
	{
		aux1 = aux->primeiro_vizinho;
		printf("\n%d -> ", aux->vertice);

		while(aux1->proximo_vizinho != NULL)
		{
			printf("%d  ", aux1->vertice);
		}
	}
}

