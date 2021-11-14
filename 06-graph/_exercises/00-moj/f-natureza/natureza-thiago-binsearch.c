#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX 7993

typedef char Item;


void merge(Item v[5000][31], Item aux[5000][31], int lo, int mid, int hi) {
  int k = 0, i = lo, j = mid+1;
    
  while (i <= mid && j <= hi) {
    // if (less(v[i], v[j])) // less(v[i], v[j])
    if (strncmp(v[i], v[j], 30) < 0)
      strncmp(aux[k++], v[i++], 30);
      // aux[k++] = v[i++];
    else
      strncmp(aux[k++], v[j++], 30);
      // aux[k++] = v[j++];
  }

  while (i <= mid) {
    strncmp(aux[k++], v[i++], 30);
    // aux[k++] = v[i++];
  }

  while (j <= hi) {
    strncmp(aux[k++], v[j++], 30);
    // aux[k++] = v[j++];
  }

  // copiar para o vetor original
  k = 0;
  for (i = lo; i <= hi; ++i)
    strncmp(v[i], aux[k++], 30);
    // v[i] = aux[k++];
}


void mergesort(Item v[5000][31], Item aux[5000][31], int lo, int hi) {
  if (lo >= hi) return;

  int mid = (lo+hi)/2;

  mergesort(v, aux, lo, mid);
  mergesort(v, aux, mid+1, hi);
  merge(v, aux, lo, mid, hi);
}



typedef struct edge
{
    int v;
    int w;
} Edge;

struct graph
{
    int V;
    int E;
    char adj[MAX][MAX];
};

typedef struct graph *Graph;
static struct graph g;

Edge EDGE(int v, int w)
{
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

Graph GRAPH(int v, int *validas, int n)
{
    int t, w;
    g.V = v;
    g.E = 0;
    for(int i = 0; i < n; i++){
        t = validas[i];
        for(int j = 0; j < n; j++){
            w = validas[j];
            g.adj[t][w] = 0;
        }
    }
    return &g;
}

void GRAPH_insert(Graph G, Edge e)
{
    int v = e.v, w = e.w;
    if (G->adj[v][w] == 0)
        G->E++;
    G->adj[v][w] = 1;
    G->adj[w][v] = 1;
}

void dfsR(Graph G, Edge e, int *pre, int *count, int *validas, int n)
{
    int t, w = e.w, v;
    pre[w] = (*count)++;
    for (t = 0; t < n; t++)
    {
        v = validas[t];
        if (G->adj[w][v] != 0)
        {
            if (pre[v] == -1)
            {
                dfsR(G, EDGE(w, v), pre, count, validas, n);
            }
        }
    }
}

int GRAPH_maior_nucleos(Graph G, int *validas, int n, int *pre)
{
    int count = 0, t, quantidade = 0, v;
    int maior = 0;

    for(int i = 0; i < MAX; i++)
        pre[i] = -1;

    for (int i = 0; i < n; i++)
    {
        v = validas[i];
        if (pre[v] == -1)
        {
            t = count;
            dfsR(G, EDGE(v, v), pre, &count, validas, n);
            quantidade = count - t;
            if (quantidade > maior)
            {
                maior = quantidade;
            }
        }
    }
    return maior;
}

int hash(char *key)
{
    int a = 31415, b = 27183, h = 0;
    for (; *key != '\0'; key++)
    {
        a = (a * b) % (MAX - 1);
        h = (a * (unsigned)h + *key) % MAX;
    }
    return h;
}

int cmp_criatura(const void* c1, const void * c2) {
  // const char* cri1 = *(const char** ) c1;
  // const char* cri2 = *(const char** ) c2;
  const char* cri1;
  const char* cri2;
  strcmp(cri1,  *(const char** ) c1);
  strcmp(cri2,  *(const char** ) c2);

  return strncmp(cri1, cri2, 30);
}

int main()
{
    int C, R;
    char criatura[31], criatura2[31];
    static int validas[5000], n = 0, pre[MAX];
    char criaturas[5000][31], aux[5000][31];
    Graph G;
    Edge e;

    while (scanf("%d %d", &C, &R) == 2 && !(C == 0 && R == 0))
    {
        G = GRAPH(C, validas, n);
        n = 0;
        for (int i = 0; i < C; i++)
        {
            scanf("%s", criatura);
            strncpy(criaturas[n], criatura, 30);
            validas[n++] = hash(criatura);
        }
        
        mergesort(criaturas, aux, 0, n-1);
        // qsort(criaturas, n, sizeof(char*), cmp_criatura);

        for (int i = 0; i < R; i++)
        {
            scanf("%s %s", criatura, criatura2);
            GRAPH_insert(G, EDGE(hash(criatura), hash(criatura2)));
        }
        int maior = GRAPH_maior_nucleos(G, validas, n, pre);
        printf("%d\n", maior);
    }
    return 0;
}