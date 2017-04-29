//--------------------------------------------------------------
// NOMES DOS RESPONSÁVEIS: Lucas Covre Delboni E Marcelo Toshiki Kozuma
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
    return("8598666");
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

typedef struct aux {
        int v;
        struct aux *prox;
}REGISTRO, *PONT;

typedef struct {
  PONT inicio;
  PONT fim;
} FILA;

// funcao principal
//NO *caminho(int N, int *ijpeso, int *aberto, int inicio, int fim, int chave);


//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
int removeElementoFila(FILA *f){
    //printf("tentando remover");
    int i= f->inicio->v;
    //printf("vai remover o %d ", i);
    PONT apagar = f->inicio;
    f->inicio=f->inicio->prox;
    free(apagar);
    if(f->inicio==NULL){
        f->fim=NULL;
    }
    return i;
}

FILA *inicializaFila(){
	FILA *f = (FILA*)malloc(sizeof(FILA));
	f->inicio=NULL;
	f->fim=NULL;
	return f;
}

void adicionaElementoFila(FILA *f, int var){
    REGISTRO *novo = (REGISTRO*)malloc(sizeof(REGISTRO));
    novo->prox=NULL;
    novo->v=var;
    if(f->inicio==NULL){
        f->inicio=novo;
    }
    else{
        f->fim->prox=novo;
    }
    f->fim=novo;
}

void colocaAbertos(VERTICE *g, int *abertos, int A){
    for(int i=1;i<=A;i++){
        if(abertos[i-1]==true){
            g[i].aberto = true;
        }
        else{
            g[i].aberto=false;
        }
    }
}

void insereVertice(VERTICE *g, int i, int j, int p){
    NO * novo = (NO*) malloc(sizeof(NO));
    if(g[i].inicio){
        printf("inicio:%d no elmento %d", g[i].inicio, i);
    }
	novo->v=j;
	novo->peso=p;
	novo->prox=NULL;
	g[i].inicio=novo;
//	printf("teste:%d->%d\n",i,g[i].inicio->v);
}

void insereVertices(int *arestas, VERTICE *g, int A,int N, int *abertos){
    //inicializa
    for(int i=1;i<=N;i++){
        g[i].inicio=NULL;
    }
	for(int i=0;i<A;i++){

        int k=i*3;
	    printf("%d - %d - %d \n",arestas[k],arestas[k+1],arestas[k+2]);
        insereVertice(g,arestas[k],arestas[k+1],arestas[k+2]);
    }
    //colocaAbertos(g, abertos, A);


    //imprime grafo:
	for(int i=1;i<=N;i++){
		NO *p = g[i].inicio;
		printf("\n%d ->", i);
		while(p){
			printf(" %d", p->v);
			p=p->prox;
			printf("p=%d",p);
		}
	}
	printf("inseriu certo");


}

void buscaProfundidade(VERTICE *g, int i, int fim){
    printf("%d", i);
    if(i==fim){
        printf(" encontrou");
        printf("\n");
        return;
    }
    g[i].flag=1;
    NO * p = g[i].inicio;
    while (p){
        if (g[p->v].flag==0){
            printf("-> ");
            buscaProfundidade(g, p->v, fim);
        }
        p=p->prox;
    }
    printf("\n");
}

void zeraFlags(VERTICE *g, int N){
    for(int i=1;i<=N;i++){
        g[i].flag=0;
    }
}

void buscaLargura(VERTICE *g, int inicio, int fim, int N){
    printf(" busca em largura: \n %d",inicio);
    zeraFlags(g,N);
    FILA *f = inicializaFila(inicio);
    adicionaElementoFila(f, inicio);
    g[inicio].flag=1;
    while(!f->inicio==NULL){
        int i = removeElementoFila(f);
        NO *p = g[i].inicio;
        if(p->v==fim){
            printf("encontrou o %d",p->v);
        }
        while(p){
            if(g[p->v].flag==0){
                printf(" -> %d", p->v);
                adicionaElementoFila(f, p->v);
                g[p->v].flag=1;
            }
            p=p->prox;
        }
        g[i].flag=2;
    }
}

NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave)
{
	NO* resp;
	resp = NULL;

	// seu codigo AQUI
	VERTICE *g = malloc(sizeof(VERTICE)*(N));
	insereVertices(ijpeso,g,A,N, aberto);
    printf("\n busca produndidade \n");
	zeraFlags(g,N);
	buscaProfundidade(g,1,3);

	buscaLargura(g,1,3,N);
	//...

	return resp;
}



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

