#include <stdio.h>
#include<stdlib.h>

typedef struct list {

    int vertex;
    struct list *prox;
    
} LIST;

LIST **createList (int amountVertex) {

    LIST **aux;
    aux = (LIST*)malloc(amountVertex * sizeof(LIST));

    for(int i = 0; i < amountVertex; i++){

        aux[i] = (LIST*)malloc(sizeof(LIST));
        aux[i] -> vertex = i + 1 ;
        aux[i] -> prox = NULL;

    }

    return aux;

}

LIST *searchEnd (LIST *adjacencyList) {

    LIST *aux = adjacencyList;

    while (aux -> prox != NULL)
        aux = aux -> prox;

    return aux;

}

void fillList(LIST **adjacencyList, int amountVertex, int value1, int value2) {

    LIST *aux1;

	for (int i = 0; i < amountVertex; i++) { 

        if(adjacencyList[i] -> vertex == value1) {

            aux1 = searchEnd(adjacencyList[i]);
            aux1 -> prox = (LIST*)malloc(sizeof(LIST));
            aux1 -> prox -> prox = NULL;
            aux1 -> prox -> vertex = value2;

        } else {
            
			if(adjacencyList[i] -> vertex == value2){

            	aux1 = searchEnd(adjacencyList[i]);
            	aux1 -> prox = (LIST*)malloc(sizeof(LIST));
            	aux1 -> prox -> prox = NULL;
            	aux1 -> prox -> vertex = value1;

			}
        }
    }
}

void printList (LIST **adjList, int amountVertex ) {

    LIST *aux;

    for(int i = 0; i < amountVertex; i++) {

        aux=adjList[i] -> prox;

        printf("\n%d -> ", adjList[i] -> vertex);

        while(aux != NULL) {

            if(aux -> prox != NULL)
                printf(" %d -> ",aux -> vertex);
            else
                printf(" %d",aux -> vertex);

            aux = aux -> prox;
        }

    }

}

// int** createMatrix (int value1, int value2) {

// 	int *matrix = (int)malloc(value1 * sizeof(int));

// 	for(int i = 0; i < value1; i++) {

// 		matrix[i] = (int)malloc(value2 * sizeof(int));

// 		for(int j = 0; j < value2; j++)

// 			matrix[i][j] = 0;
		
// 	}

// 	return matrix;
// }

void printMatrix(int **matriz, int n, int m){

	for(int i=0; i < n; i++) {

		for(int j=0; j < m; j++)

   			printf ("%d   \n\n", matriz[i][j]);
   	}
   	printf ("\n");
}

int main () {

    int position1[100] = {}, position2[100] = {};
    
    FILE *inputFile;
    LIST **adjacencyList;

	int amountVertex, amountEdge;
    int value1 = 0,
        value2 = 0,
        amount = 0;
    int **adjacencyMatrix,
        **incidenceMatrix;

    
    inputFile = fopen("Grafo.txt", "r" );

    if (inputFile != NULL){

        fscanf(inputFile, "%d %d", &amountVertex, &amountEdge);

        adjacencyList = createList( amountVertex );
        // adjacencyMatrix = createMatrix(amountVertex, amountEdge);
        // incidenceMatrix = createMatrix(amountVertex, amountEdge);

        while (!feof(inputFile)) {

            fscanf(inputFile, "%d", &value1);
            fscanf(inputFile, "%d", &value2);

            fillList(adjacencyList, amountVertex, value1, value2);

        }

        rewind(inputFile);

        while(!feof(inputFile)){

            fscanf(inputFile,"%d %d", &value1, &value2);
            fillList(adjacencyList, amountVertex, value1, value2);

	    }

        rewind(inputFile);
                            
        while(!feof(inputFile)) {

            fscanf(inputFile, "%d", &value1);
            fscanf(inputFile, "%d", &value2);

            int j = 0;

            for(int i = 0; i < amountVertex; i++) {

                if(i == (value1 - 1) || i == (value2 - 1))  
                    incidenceMatrix[i][j]= 1;
            }
            j++;
        }

        fclose(inputFile);

        printList(adjacencyList, amountVertex);
        printMatrix(adjacencyMatrix, amountVertex, amountEdge);
        printMatrix(incidenceMatrix, amountVertex, amountEdge);

    } else printf("\nErro na leitura do arquivo");

    return 0;

}

// Faça um algoritmo (na Linguagem C) para ler o arquivo de entrada “Grafo.txt” (que
// representa o grafo do Exercício 01) e construir as estruturas solicitadas no Exercício 01,
    // lista de adjacência;
    // matriz A de adjacência;
    // sua matriz B de incidência.
// imprimindo-as na tela em seguida.
