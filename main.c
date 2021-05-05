// Gabriel Gomes, Pedron Schaper, Filipe ..., Arthur ...
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
	vizinho *primeiro_vizinho;

}typedef vetor_vertices;

struct tipo_lista
{
	vetor_vertices *primeiro;
}typedef lista;



void criar_vetor(lista *vetor, int n_vertice);
void ligar_vetor(lista *vetor, int valor, int j, int linha, int n_vertice);
void colorir_vetor(lista *vetor);
void imprimir_vetor(lista *vetor);

int main() {
	
	FILE *arquivo;
	lista vetor;
	int n_vertice, n_aresta, valor, j=1, linha=1;

	arquivo = fopen("/Users/gabriel/Documents/IFF/EDA/trabalho-pt2/Arquivo.txt", "r");

	if(arquivo != NULL){

		fscanf(arquivo,"%d %d", &n_vertice, &n_aresta);

		criar_vetor(&vetor, n_vertice);

		while(!feof(arquivo))
		{
			fscanf(arquivo,"%d", &valor);

			if(j > (n_vertice*linha)) //é o numero do vertice na qual a linha da matriz se refere, sempre que pula de linha na matriz muda o vertice referente
			{
				linha++;
			}

			ligar_vetor(&vetor,valor,j,linha, n_vertice);//lendo um termo da matriz por vez e enviando para a função, junto do valor (0 ou 1), j (numero do termo)
			j++;						//e a linha (vertice referente na linha da matriz)
		}

		colorir_vetor(&vetor);
		imprimir_vetor(&vetor);
	}
	else
	{
		printf("Arquivo Vazio!");
	}

	fclose(arquivo);
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
        aux -> proximo_vertice = NULL; // n representa o vertice vizinho, é apenas a lista de vertices em ordem sequencial (aleatorio visualmente)
        aux -> vertice = (i+1);
        aux -> cor = 0;
        aux -> primeiro_vizinho = NULL; //vizinho inicialmente será Null pois n lemos a matriz de adjacencia ainda

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

void ligar_vetor(lista *vetor, int valor, int j, int linha, int n_vertice) {

	vetor_vertices *aux_vertice;
	vizinho *aux_vizinho1, *aux_vizinho2;

	//valor = 1 quer dizer q o vertice que a linha representa é vizinho do vertice que a coluna representa
    if(valor == 1) {

		aux_vizinho2 = (vizinho*)malloc(sizeof(vizinho));
		aux_vizinho2 -> vertice = j-((linha-1)*n_vertice); // para descobrir qual o vertice representado pela 'coluna é so pegar o valor de J e diminuir pelas linhas completas ja vistas anteriromente
		aux_vizinho2 -> proximo_vizinho = NULL;

   		aux_vertice = vetor->primeiro; // inicio da lista de de vertices

		while(aux_vertice->vertice != linha) //encontradando na lista de vertices aleatorio o termo com o vertice que representa o vertice da linha da matriz
	    	aux_vertice = aux_vertice->proximo_vertice;

		aux_vizinho1 = aux_vertice->primeiro_vizinho; // inicio da lista de vizinhos e nao de vertices

		if(aux_vizinho1 != NULL){

			while(aux_vizinho1->proximo_vizinho != NULL) //encontrando ultimo vizinho da lista dauqele vertice
		    	aux_vizinho1 = aux_vizinho1->proximo_vizinho;

		    aux_vizinho1->proximo_vizinho = aux_vizinho2; 
		}
		else{

			aux_vertice->primeiro_vizinho = aux_vizinho2; //lista de vizinho daquele vertice tava vazia, entao agr esse é o primeiro termo da lista
			
			
		}
		
	}
	
}

void colorir_vetor(lista *vetor) {

	int nova_cor=1;
	vetor_vertices *aux;
	vizinho *aux1;

	aux = vetor->primeiro;

	while(aux->proximo_vertice != NULL) {

		aux1 = vetor->primeiro;
		if(aux->primeiro_vizinho != NULL) {

			while(aux1->proximo_vertice != NULL) {

				if(aux1->vertice == aux->vertice)
					aux->cor = aux1->cor;

				aux1 = aux1 ->proximo_vertice;
			}

			aux1 = vetor;

			while(aux1->proximo_vertice != NULL) {

				if(aux1->vertice == aux->vertice && aux1->vertice != aux->vertice)
					nova_cor++;
			}

			aux->cor = nova_cor;
		}

		aux = aux->proximo_vertice;
	}

	printf("Numero de cores utilizado foi de %d", nova_cor);
}

void imprimir_vetor(lista *vetor) {
	
	vetor_vertices *aux;
	vizinho *aux1;

	aux = vetor->primeiro;
	aux1 = aux->primeiro_vizinho;

	while(aux != NULL){

		aux1 = aux->primeiro_vizinho;
		printf("\n%d -> ", aux->vertice);

		while(aux1 != NULL){

			printf("%d ", aux1->vertice);
			aux1 = aux1->proximo_vizinho;

		}

		aux = aux->proximo_vertice;
	}
}

