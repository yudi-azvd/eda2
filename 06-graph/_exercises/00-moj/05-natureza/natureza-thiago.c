#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX 7993

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

int main()
{
    int C, R;
    char criatura[30], criatura2[30];
    static int validas[5000], n = 0, pre[MAX];
    Graph G;
    Edge e;

    while (scanf("%d %d", &C, &R) == 2 && !(C == 0 && R == 0))
    {
        G = GRAPH(C, validas, n);
        n = 0;
        for (int i = 0; i < C; i++)
        {
            scanf("%s", criatura);
            validas[n++] = hash(criatura);
        }
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