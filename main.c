//--------------------------------------------------------------
// NOMES DOS RESPONSÁVEIS: Lucas Covre Delboni E Marcelo Toshiki Kozuma
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <stdbool.h>
#include <math.h>
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

void colocaAbertos(VERTICE *g, int *abertos, int N){
    for(int i=1;i<=N;i++){
        if(abertos[i-1]==1){
            g[i].aberto = 1;
        }
        else{
            g[i].aberto=0;
            printf("\n \n \n fecou a porta %d",i);
        }
    }
}

void abreTodos(VERTICE *g, int N){
    for(int i=1;i<=N;i++){
            g[i].aberto = true;
    }
}

void insereVertice(VERTICE *g, int i, int j, int p){
    printf("inicio do %d eh %d",i,g[i].inicio);

    NO *novo = (NO*) malloc(sizeof(NO));
	novo->v=j;
	novo->peso=p;
	novo->prox=g[i].inicio;
	g[i].inicio=novo;
	printf("teste:%d->%d:%d   %d\n",i,g[i].inicio->v,g[i].inicio->peso,novo->prox);

}

void insereVertices(int *arestas, VERTICE *g, int A,int N, int *abertos){
    //inicializa
    for(int i=1;i<=N;i++){
            printf("anulou o %d",i);
        g[i].inicio=NULL;
    }

    //INSERE NOS
	for(int i=1;i<=A*3;i=i+3){
	    //printf("%d - %d - %d \n",arestas[i-1],arestas[i],arestas[i+1]);
        insereVertice(g,arestas[i-1],arestas[i],arestas[i+1]);
    }
    colocaAbertos(g, abertos, N);


    //imprime grafo:
	for(int i=1;i<=N;i++){
        NO *p = g[i].inicio;
        printf("\n %d-> ",i);
        while (p){
                printf("a");
            printf("%d(%d) -", p->v,p->peso);
            p=p->prox;
        printf("foi prox");
        }
	}
	printf("inseriu certo");


}

NO*  menorCaminho(NO *a, NO* b){
    if(!b){
        printf("\n aux null \n");
        return a;
    }    int distA=0;
    while(a){

        distA=distA+a->peso;
        a=a->prox;
    }

    int distB =0;
    printf("aux: ");
    while(b){
            printf(" %d -", b->v);
        distB=distB+b->peso;
        b=b->prox;
    }
    printf("resp: %d   aux: %d \n", distA, distB);
    if(distA<=distB){
        return a;
    }
    return b;
}

int buscaProfundidade(VERTICE *g, int i, int fim, int chave, int N, int dist, NO *resp, NO *aux){
    if(i==chave){
        printf("abre posrtas");
        abreTodos(g, N);
    }
    printf("%d", i);
    if(i==fim){
        printf(" encontrou");
        printf("\n");
        resp = menorCaminho(resp, aux);
        aux = NULL;
        printf("distancia total: %d", dist);
        return dist;
    }

    printf("valor do aux %d", aux);
    g[i].flag=1;
    NO * p = g[i].inicio;

    while (p){
        if(g[p->v].aberto==1){
            if (g[p->v].flag==0){
                printf("-> ");
                dist=dist+p->peso;
                buscaProfundidade(g, p->v, fim, chave, N, dist, resp, aux);
            }
        }
        p=p->prox;
    }
    printf("\n");
    return 0;
}

void zeraFlags(VERTICE *g, int N){
    for(int i=1;i<=N;i++){
        g[i].flag=0;
    }
}

void buscaLargura(VERTICE *g, int inicio, int fim, int N, int chave, int A, NO* resp){
    int dist[N];
    for(int i=1;i<=N;i++){
        dist[i]=INFINITY;
    }
    dist[inicio]=0;

    FILA *f = inicializaFila();
    adicionaElementoFila(f, inicio);
    resp = g[inicio].inicio;


    int distancia = 0;
    printf(" busca em largura: \n %d",inicio);
    zeraFlags(g,N);

    g[inicio].flag=1;
    while(!f->inicio==NULL){
        int i = removeElementoFila(f);
        NO *p = g[i].inicio;
        if(i==chave){
            printf("\n abrindo todos \n");
            abreTodos(g,N);
        }
        NO* ant = NULL;
        while(p){
            if(g[p->v].aberto==true){
                if(p->v==fim/*&&((p->peso)<)*/){
                        distancia = distancia+ p->peso;
                    resp=p;
                    resp=resp->prox;
                    printf("encontrou o %d",p->v);

                    printf("\n peso %d totala: %d\n", p->peso,distancia);
                    dist[ant->v]=distancia;
                    //return;
                    g[p->v].flag=1;
                }
                if(g[p->v].flag==0){
                    distancia = distancia+ p->peso;
                    resp->prox=p;
                    resp=resp->prox;

                    printf(" -> %d", p->v);
                    adicionaElementoFila(f, p->v);
                    g[p->v].flag=1;
                    printf("\n peso %d totalb: %d", p->peso,distancia);
                }
            }
            printf("vai setar o ant");
            ant = p;
            printf("vai setar o prox");
            p=p->prox;
            printf("setou tudo %d",p->v);
        }
        g[i].flag=2;
    }

    //printf("\n peso total: %d", distancia);
    printf("\n distancias : ");
    for(int i=1;i<=N;i++){
        printf("- %d ",dist[i]);
    }
}

NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave)
{
	NO* resp;
	resp = NULL;

	// seu codigo AQUI
	NO* aux = NULL;

	VERTICE *g = (VERTICE*)malloc(sizeof(VERTICE)*(N+1));
	//FILA *f = (FILA*)malloc(sizeof(FILA));
	insereVertices(ijpeso,g,A,N, aberto);



    printf("\n busca produndidade \n");
	zeraFlags(g,N);
	int dist[N];
	for(int i=1;i<=N;i++){
        dist[i]=INFINITY;
        printf("disti %d", dist[i]);
	}

    NO *p= g[inicio].inicio;

	buscaProfundidade(g,inicio,fim, chave, N, 0, resp, aux);

    //buscaLargura(g,1,3,N, chave, A, resp);
	//...

	return resp;
}

//relax(int inicio, NO *p, int *dist){
 //   if(dist[p->v] > dist[inicio] + p->peso){
 //       dist[p->v]=dist[inicio] + p->peso;
 //       ant[p->v]=inicio;;
 //   }
//}

//extraiMin(int *aux){
//    NO *p = g[1].inicio;
//}
//
//void dj(int N, int inicio, int fim, VERTICE *g){
//    int dist[N];
//    int ant[N];
//    for(int i=1;i<=N;i++){
//        dist[i] = INFINITY;
//        ant[i]=-1;
//    }
//    dist[fim]=0;
//
//    S=NULL;
//    VERTICE *aux = g;
//    while(aux){
//        u = extraiMin(aux);
//        S = S união com u
//
//        NO *p=g[inicio].inicio;
//        while(p){
//            relax(inicio,p, dist);
//            p=p->prox;
//        }
//    }
//
//
//
//    for(int i=1;i<=N;i++){
//        NO* p= g[i].inicio;
//        int min = -1;
//        int minVal= INFINITY;
//        while(p){
//            if(g[p->v].flag==0 && p->peso<minVal){
//                minVal = p->peso;
//                min =p->v;
//            }
//            p=p->prox;
//        }
//
//        g[p->v].flag=1;
//        for(int i=1;)
//    }
//}



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
	int A = 4;
	int ijpeso[]={1,2,10, 2,3,20, 3,1,15, 1,3,55};

	// o EP sera testado com uma serie de chamadas como esta
	NO* teste = NULL;
	teste = caminho(N,A, ijpeso, aberto, inicio, fim, chave);
	printf("ok");
	return teste;
}

// por favor nao inclua nenhum código abaixo da função main()

