#include <stdio.h>
#include <stdlib.h>

#define min(a, b) ((a < b) ? a : b)

#define MAX_VERTICES 1002
#define INF 10000000

int M, N, K, res, min;
int parent[MAX_VERTICES];

void set_init(int n)
{
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

int set_find(int curr)
{
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

void set_union(int a, int b)
{
    int root1 = set_find(a);
    int root2 = set_find(b);

    if (root1 != root2)
        parent[root1] = root2;
}

typedef struct Edge
{
    int start, end, weight;
} Edge;

typedef struct GraphType
{
    int n;
    int vertex;
    // Edge *edges;
} GraphType;

Edge edges[10001];
GraphType G;

void graph_init(GraphType *G)
{
    min = min(10000, N * (N - 1) / 2);
    G->n = 0;
    G->vertex = 0;
    for (int i = 0; i < min; i++)
    {
        edges[i].start = 0;
        edges[i].end = 0;
        edges[i].weight = INF;
    }
}

void insert_vertex(GraphType *G, int n)
{
    G->vertex = n;
}

void insert_edge(GraphType *G, int start, int end, int w)
{
    edges[G->n].start = start;
    edges[G->n].end = end;
    edges[G->n].weight = w;
    G->n++;
}

void remove_edge(GraphType *G)
{
    edges[0].start = 0;
    edges[0].end = 0;
    edges[0].weight = INF;
}

int compare(const void *a, const void *b)
{
    Edge *x = (Edge *)a;
    Edge *y = (Edge *)b;
    return (x->weight - y->weight);
}

void kruskal(GraphType *G, int th)
{
    res = 0;
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;

    set_init(G->vertex);
    qsort(edges, G->n, sizeof(struct Edge), compare);
    if (th != 0)
        G->n--;

    int i = 0;
    while (edge_accepted < G->vertex - 1)
    {
        // printf("%dth turn %d\n", i, G->n);

        // for (int i = 0; i < G->n; i++)
        // {
        //     printf("%d ", parent[i]);
        // }
        // printf("\n");

        if (i >= G->n)
        {
            res = 0;
            return;
        }
        e = edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset)
        {
            // printf("%d edge (%d %d)\n", i, e.start, e.end);
            res += e.weight;
            set_union(uset, vset);
            edge_accepted++;
        }
        i++;
    }
}

int main()
{
    scanf("%d %d %d", &N, &M, &K);
    graph_init(&G);

    insert_vertex(&G, N);
    int start, end;
    for (int i = 0; i < M; i++)
    {
        scanf(" %d %d", &start, &end);
        insert_edge(&G, start - 1, end - 1, i + 1);
    }

    for (int i = 0; i < K; i++)
    {
        kruskal(&G, i);
        remove_edge(&G);
        printf("%d ", res);
    }
}