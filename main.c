//--------------------------------------------------------------
// NOMES DOS RESPONSÁVEIS: Lucas Covre Delboni E Marcelo Toshiki Kozuma
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

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


void zeraFlags(VERTICE *g, int N){
    for(int i=1;i<=N;i++){
        g[i].flag=0;
    }
}



int menorDistanciaNaFila(int *dist,VERTICE *g, int N){
    int min =0;
    int retorno =0;

    for(int i=1;i<=N;i++){
        if(g[i].flag!=1){
            min = dist[i];
            retorno =i;
        }
    }

    for(int i=1;i<N;i++){
        if(g[i].flag!=1){
            if(dist[i]<min){
                retorno = i;
                min = dist[i];
            }
        }
    }
    return retorno;
}


void wikipedia(VERTICE *g, int inicio, int N, int *dist, int *prev, int *abertos){
    for(int i=1;i<=N;i++){
        dist[i]=INT_MAX;
        prev[i]=-1;
        if(abertos[i]==1){
            g[i].flag=0;
        }
        else{
            g[i].flag=1;
        }
    }
    dist[inicio] = 0;

    printf("\n");
    while(true){

        int u = menorDistanciaNaFila(dist, g, N);

        g[u].flag=1;

        printf("%d : ", u);
        NO *p = g[u].inicio;
        while (p){
            int alt = dist[u]+p->peso;
            if(alt < dist[p->v]){
                dist[p->v]=alt;
                prev[p->v]=u;
            }

            p=p->prox;
        }
        printf("\n");

        int cont=1;
        for(int i=1;i<=N;i++){
            if(g[i].flag==1){
                cont++;
            }
        }
        if(cont==N){
            break;
        }
    }
}



NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave)
{
	NO* resp;
	resp = NULL;

	// seu codigo AQUI
	//NO* aux = NULL;

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



	//buscaProfundidade(g,inicio,fim, chave, N, 0, resp, aux);

	printf("busca muito louca");
    //dj(N,inicio,fim,g,A);
    //lucas(N,inicio,fim,g);

    int prev[N+1];
    wikipedia(g,inicio,N, dist, prev, aberto);
    for(int i=1;i<=N;i++){
        printf("dist %d=%d\n",i,dist[i]);
    }
    for(int i=1;i<=N;i++){
        printf("prev i%d = %d \n", i, prev[i]);
	}

    int prevAux[N+1];
    zeraFlags(g,N);
    int distAux[N];
//	for(int i=1;i<=N;i++){
//        distAux[i]=INFINITY;
//        printf("disti %d", distAux[i]);
//	}
	zeraFlags(g,N);
	for(int i=0;i<N;i++){
        aberto[i]=1;
	}
    wikipedia(g,chave,N, distAux, prevAux, aberto);
    printf("cabou\n");
    for(int i=1;i<=N;i++){
        printf("distAux %d=%d\n",i,distAux[i]);
    }
    for(int i=1;i<=N;i++){
        printf("prevAux i%d = %d \n", i, prevAux[i]);
	}


    //buscaLargura(g,1,3,N, chave, A, resp);



    printf("prev:  %d  fim %d",prev[fim],fim);
    if(prev[fim]!=-1){
        if(dist[fim]>dist[chave]+distAux[fim] && prevAux[fim]!=-1){
            resp = (NO*) malloc(sizeof(NO));
            int aux=fim;
            resp->v=fim;
            resp->prox=NULL;
            while(aux!=chave){
                printf("\n aux: %d",aux);
                aux=prevAux[aux];
                NO *novo = (NO*)malloc(sizeof(NO));
                novo->v=aux;
                novo->prox = resp;
                resp=novo;
            }

            while(aux!=inicio){
                printf("\n aux: %d",aux);
                aux=prev[aux];
                NO *novo = (NO*)malloc(sizeof(NO));
                novo->v=aux;
                novo->prox = resp;
                resp=novo;
            }

            printf("\n passando pela chave eh melhor1");
        }
        else{
            resp = (NO*) malloc(sizeof(NO));
            int aux=fim;
            resp->v=fim;
            resp->prox=NULL;
            while(aux!=inicio){
                printf("\n aux: %d",aux);
                aux=prev[aux];
                NO *novo = (NO*)malloc(sizeof(NO));
                novo->v=aux;
                novo->prox = resp;
                resp=novo;
            }
            printf("\n passando sem chave eh melhor");
            return resp;
        }
    }
    else{
        if(prevAux[fim]==-1){
                printf("\n nao da pra chegar");
            return NULL;
        }
        resp = (NO*) malloc(sizeof(NO));
        int aux=fim;
        resp->v=fim;
        resp->prox=NULL;
        while(aux!=chave){
            printf("\n aux: %d",aux);
            aux=prevAux[aux];
            NO *novo = (NO*)malloc(sizeof(NO));
            novo->v=aux;
            novo->prox = resp;
            resp=novo;
        }

        while(aux!=inicio){
            printf("\n aux: %d",aux);
            aux=prev[aux];
            NO *novo = (NO*)malloc(sizeof(NO));
            novo->v=aux;
            novo->prox = resp;
            resp=novo;
        }
        printf("\n retorna passando pela chave2");
    }
	return resp;
}








//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {


	// aqui vc pode incluir codigo de teste
	// exemplo de teste trivial

	int N=3; // grafo de 3 vértices 1..3
	int aberto[] = {1,1,0}; // todos abertos
	int inicio=1;
	int fim=3;
	int chave=2;
	int A = 3;
	int ijpeso[]={1,2,10, 2,3,20, 3,1,15};

	// o EP sera testado com uma serie de chamadas como esta
	NO* teste = NULL;
	teste = caminho(N,A, ijpeso, aberto, inicio, fim, chave);
//    caminho(N,A, ijpeso, aberto, inicio, fim, chave);
	printf("ok");

    printf("\nresposta :\n");
	while(teste){
	    //printf("teste: %d",teste);
        printf("%d->",teste->v);
        teste=teste->prox;
	}
	return 0;
}

// por favor nao inclua nenhum código abaixo da função main()

