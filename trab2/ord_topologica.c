#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
	int chave;
	struct No *vt[7];
}tno;

tno *adj;

void checa_vert(tno *ptlista[], int num_v, int cont_grau[], int ordem[]){
	int pos = 0;
	for (int v = 1; v <= num_v; v++){
		if (cont_grau[v] == 0){
			ordem[pos] = v;
			pos++;
		}
	}

	//printf("%d\n", ordem[0]);

	int temp = 0;
	
	for (int v = 1; v <= num_v; v++){
		for (int i = 1; i <= num_v; i++){
			if (ptlista[ordem[temp]]->vt[i]){
				//printf("nó %d e seu vertice %d na pos = %d\n", ptlista[ordem[temp]]->chave, ptlista[ordem[temp]]->vt[i]->chave, i);
				
				cont_grau[ptlista[ordem[pos-1]]->vt[i]->chave]--;

				if (cont_grau[ptlista[i]->chave] == 0){
					ordem[pos] = ptlista[i]->chave;
					pos++;	
				}
			}	
		}
		temp++;
	}
}

void insere_prox(tno *ptlista[], int x, int aponta){
	ptlista[x]->vt[aponta] = ptlista[aponta];	
	//printf("prox x:%d\n", ptlista[x]->vt[aponta]->chave);
}

void init(tno *ptlista[], int num_v){
	for (int i = 1; i <= num_v; i++){
		tno *novo = NULL; 
		novo = calloc(1,sizeof(struct No));
		if (novo == NULL) {printf("ERRO--malloc\n");}

		novo->chave = i;
		ptlista[i] = novo;	

		//printf("%d\n", ptlista[i]->chave);		
	}
}

int main(){
   	int num_v, arestas;   	
   	size_t tamLinha = 0;
	
	scanf("%d %d\n", &num_v, &arestas);


	adj =  malloc(sizeof(struct No)*num_v);
   	if (adj == NULL) {printf("ERRO--malloc\n"); return 2;}

   	init(&adj, num_v);

	int cont_grau[num_v + 1], ordem[num_v];
	memset(cont_grau, 0, sizeof cont_grau);
	memset(ordem, 0, sizeof ordem);		
		
	char *linha=NULL;

  	for(int i = 1; i <= num_v; i++){
		getline(&linha, &tamLinha, stdin);
	    int j = 0;
	    int numLido = 0;
	    int numChars;
	    
	    while (sscanf(&linha[j], " %d %n", &numLido, &numChars) > 0) {
			j += numChars;

			if(strlen(linha) != 0){
				cont_grau[numLido]++;
				//printf(" insere em adj [ %d ] o vertice %d\n",i, numLido);     
			 	insere_prox(&adj, i, numLido);
			}
    	}
  	}	
  
  	checa_vert(&adj, num_v, cont_grau, ordem);

	// while (pos != num_v){
	// 	for (int v = 1; v <= num_v; v++){
	// 		if (*(adj+1)->prox+2){
	// 			printf("a\n");
	// 		}

	// 		cont_grau[v]--;

	// 		if (cont_grau[v] == 0){
	// 			ordem[pos] = v;
	// 			pos++;
	// 		}
	// 	}

	// }

	for (int i = 0; i < num_v; i++){
		fprintf(stdout, "%d ", ordem[i]);
	}

	free(adj);

	//free(ch);
	//free(linha);
	// free(cont_grau);
	// free(ordem);

	return 0;
}
