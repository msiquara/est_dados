#include <stdio.h>
#include <stdlib.h>

void merge(int 	*V, int inicio, int meio, int fim){
	int i = inicio;
	int j = meio;
	int *tmp;
	int pos = 0;

	tmp = (int *) malloc(sizeof(int) * (fim - inicio));

	while((i < meio) && (j < fim)){
		if (V[i] <= V[j]){
			tmp[pos] = V[i];
			i++;
		}

		else{
			tmp[pos] = V[j];
			j++;
		}

		pos++;
	}

	while (i < meio){
		tmp[pos] = V[i];
		i++;
		pos++;
	}

	while (j < fim){
		tmp[pos] = V[j];
		j++;
		pos++;
	}

	for (int k = 0; k < pos; k++){
		V[inicio + k] = tmp[k];
	}

	free(tmp);
}

void mergeSort(int *V, int inicio, int fim){
	if ((fim - inicio) > 1){
		int meio = (inicio + fim)/2;
		mergeSort(V, inicio, meio);
		mergeSort(V, meio, fim);
		merge(V, inicio, meio, fim);
	}
}

int main(int argc, char *argv[]){
	int *lista;

	lista = (int *) calloc(1,sizeof(int));
   	if (lista == NULL) {printf("ERRO--malloc\n"); return 2;}
   
   	int j = 0, x;

	while (scanf("%d", &x) == 1){
		lista[j] = x;
		j++;		
		lista = realloc(lista, sizeof(int) * (j+1));
	}

   	int linhas = j;

   	// printf("Lista original:\n");

   	// for (int i = 0; i < linhas; i++){
   	// 	printf("%d\n", lista[i]);
   	// }

   	int inicio = 0;

   	mergeSort(lista, inicio, linhas);

   	for (int i = 0; i < linhas; i++){
   		fprintf(stdout, "%d\n", lista[i]);
   	}

	free(lista);

	return 0;
}