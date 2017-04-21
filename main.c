//--------------------------------------------------------------
// NOMES DOS RESPONSÁVEIS: Lucas Covre Delboni E blablabla
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <stdbool.h>

// ######### ESCREVA O NROUSP DO PRIMEIRO INTEGRANTE AQUI
char* nroUSP1() {
    return("8516006");
}

// ######### ESCREVA O NROUSP DO SEGUNDO INTEGRANTE AQUI (OU DEIXE COM ZERO)
char* nroUSP2() {
    return("0000000");
}


// elemento das listas de adjacência e de resposta
typedef struct estr {
        int v; // elemento
        int peso; // custo (não precisa ser usado na resposta)
        struct estr *prox;
} NO;

// vertices do grafo (salas) - use este tipo ao criar o grafo
typedef struct
{
       int flag; // para uso na busca em largura e profundidade, se necessario
       bool aberto; // vale true se a sala em questao esta aberta
       NO* inicio;
} VERTICE;


// funcao principal
//NO *caminho(int N, int *ijpeso, int *aberto, int inicio, int fim, int chave);


//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
colocaAbertos(VERTICE *g, int *abertos, int A){
    for(int i=1;i<=A;i++){
        if(abertos[i-1]==true){
            g[i].aberto = true;
        }
        else{
            g[i].aberto=false;
        }
    }
}

void insereVertices(int *arestas, VERTICE *g, int A, int *abertos){
	for(int i=1;i<=A*3;i=i+3){
		NO* novo = malloc(sizeof(NO));
		novo->v = arestas[i];
		novo->peso=arestas[i+1];
		novo->prox=NULL;
		if(g[i-1].inicio==NULL){
			g[i-1].inicio=novo;
		}
		else{
			NO *p = g[i-1].inicio;
			g[i-1].inicio = novo;
			g[i-1].inicio->prox=p;
		}
	}
	colocaAbertos(g, abertos, A);
}

buscaProfundidade(VERTICE *g, int inicio, int fim){
    g[inicio].flag=1;
    NO * p = g[inicio].inicio;
    while (p){
        if (g[p->v].flag==0){
            buscaProfundidade(g, p->v, fim);
        }
        p=p->prox;
    }
}

NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave)
{
	NO* resp;
	resp = NULL;

	// seu codigo AQUI
	VERTICE *g = malloc(sizeof(VERTICE)*(N));
	insereVertices(ijpeso,g,A, aberto);
	//...

	return resp;
}


/************************/
//fila

typedef struct estr {
        int valor;
        struct estr *prox;
} fila;

adicionaElementoFila(fila *i, int var){
	if (i->prox==NULL){
		fila *novo = malloc(sizeof(fila));
		novo->valor = var;
		novo->prox = NULL;
		i->prox = novo;	
	}	
	else{
		fila *f = i->prox;
    	while (f->prox != NULL){
			f = f->prox;
		}
		fila* novo = malloc(sizeof(fila));
		novo->valor = var;
		novo->prox = NULL;
		f->prox = novo;
	}
}

removeElementoFila(fila *i){
	if (i->valor==-1&&i->prox!=NULL){
		fila *f = i->prox;
		i->prox = f->prox;
	}
}

fila *inicializaFila(){
	fila *novo = malloc(sizeof(fila));
	novo->prox = NULL;
	novo->valor = -1;
	return novo;
}

/***************************/


//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {


	// aqui vc pode incluir codigo de teste

	// exemplo de teste trivial

	int N=3; // grafo de 3 vértices 1..3
	int aberto[] = {1,1,1}; // todos abertos
	int inicio=1;
	int fim=3;
	int chave=2;
	int A = 3;
	int ijpeso[]={1,2,10, 2,3,20, 3,1,10};

	// o EP sera testado com uma serie de chamadas como esta
	NO* teste = NULL;
	teste = caminho(N,A, ijpeso, aberto, inicio, fim, chave);
	printf("ok");
	return teste;

}

// por favor nao inclua nenhum código abaixo da função main()

