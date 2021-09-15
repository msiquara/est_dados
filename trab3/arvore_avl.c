#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALT(pt) ((pt != NULL)? (pt)->alt : 0)
#define MAX(x, y) ((x) > (y)? (x) : (y))

struct No{
	int chave;
	int alt;
	struct No *dir;
	struct No *esq;
};

struct No *tree = NULL;
int cont = 0;


struct No* rotacaoEsq(struct No *ptraiz){
	struct No *ptb = ptraiz->dir;
	struct No *T2 = ptb->esq;
	ptb->esq = ptraiz;
	ptraiz->dir = T2;

	ptraiz->alt = MAX(ALT(ptraiz->esq), ALT(ptraiz->dir)) + 1;
	ptb->alt = MAX(ALT(ptb->esq), ALT(ptb->dir)) + 1;

	return ptb;
}

struct No* rotacaoDir(struct No *ptb){
	struct No *ptraiz = ptb->esq;
	struct No *T2 = ptraiz->dir;
	ptraiz->dir = ptb;
	ptb->esq = T2;

	ptraiz->alt = MAX(ALT(ptraiz->esq), ALT(ptraiz->dir)) + 1;
	ptb->alt = MAX(ALT(ptb->esq), ALT(ptb->dir)) + 1;

	return ptraiz;
}

struct No* registraAlt(struct No *ptraiz, int x){
	int reg = ALT(ptraiz->esq) - ALT(ptraiz->dir);

	//rotacao esquerda
	if (reg < -1 && x > ptraiz->dir->chave){
		ptraiz = rotacaoEsq(ptraiz);
	} 

	//rotacao direita esquerda
	if (reg < -1 && x < ptraiz->dir->chave){
		ptraiz->dir = rotacaoDir(ptraiz->dir);
		ptraiz = rotacaoEsq(ptraiz);
	}

	// else{
	// 	ptraiz->alt = MAX(ALT(ptraiz->esq), ALT(ptraiz->dir)) + 1;
	// }
	return ptraiz;
}

void imprime(struct No *ptraiz){
	if (ptraiz != NULL){
		fprintf(stdout, "%d(%d) ", ptraiz->chave, ptraiz->alt);
		imprime(ptraiz->esq);
		imprime(ptraiz->dir);
	}
}

struct No* insereAVL(struct No *ptraiz, int x){
	if (ptraiz == NULL){
		struct No *novo = (struct No*) malloc(sizeof(struct No));
   		if (novo == NULL) {printf("ERRO--malloc\n");}

   		novo->chave = x;
   		novo->esq = NULL;
   		novo->dir = NULL;
   		novo->alt = 1;
   		ptraiz = novo;

   		return ptraiz;
	}

	if (x < ptraiz->chave){
		ptraiz->esq = insereAVL(ptraiz->esq, x);
	}

	else{
		ptraiz->dir = insereAVL(ptraiz->dir, x);
	}

	ptraiz->alt = MAX(ALT(ptraiz->esq), ALT(ptraiz->dir)) + 1;

	ptraiz = registraAlt(ptraiz, x);

	return ptraiz;
}

int main(int argc, char * argv[]){
	char *linha = NULL;
	size_t tamLinha = 0;
	char separator[] = "\n ";
	int j = 0, num;

	// tree = malloc(sizeof(struct No));
 //   	if (tree == NULL) {printf("ERRO--malloc\n"); return 2;}

	while (getline(&linha, &tamLinha, stdin) != -1){
	    char *val = strtok(linha, separator);

	    while (val != NULL){
	    	

	    	if (strcmp(val, "i") == 0){
	    		val = strtok(NULL, separator);	    		
	    		num = atoi(val);

	    		tree = insereAVL(tree, num);

	    		j++;
	    		tree = realloc(tree, sizeof(struct No) * j);
	    	}

	    	else{
	    		imprime(tree);
	    		fprintf(stdout, "\n");
	    	}

	    	val = strtok(NULL, separator);
	    }
  	}	

  	fflush(stdout);

  	free(tree);

	return 0;
}
