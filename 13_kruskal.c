#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

typedef struct Edge
{
    int start, end, weight;
} Edge;

typedef struct GraphType
{
    int n;      // edge갯수
    int vertex; // vertex갯수
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

void set_init(int n)
{
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

int union_find(int curr)
{
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

void set_union(int a, int b)
{
    int root1 = union_find(a);
    int root2 = union_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

void init(GraphType *G)
{
    G->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        G->edges[i].start = 0;
        G->edges[i].end = 0;
        G->edges[i].weight = INF;
    }
}

void insert_vertex(GraphType *G)
{
    G->vertex++;
}

void insert_edge(GraphType *G, int v1, int v2, int w)
{
    G->edges[G->n].start = v1;
    G->edges[G->n].end = v2;
    G->edges[G->n].weight = w;
    G->n++;
}

int compare(const void *a, const void *b)
{
    Edge *x = (Edge *)a;
    Edge *y = (Edge *)b;
    return (x->weight - y->weight);
}

void kruskal(GraphType *G)
{
    Edge e;
    int uset, vset;
    int edge_accepted = 0;
    set_init(G->vertex);

    qsort(G->edges, G->n, sizeof(struct Edge), compare);

    int i = 0;
    while (edge_accepted < ((G->vertex) - 1))
    {
        if (i >= G->n)
        {
            printf("No MST");
            break;
        }
        e = G->edges[i];
        uset = union_find(e.start);
        vset = union_find(e.end);

        if (vset != uset)
        { //대가리가 다르면, 다른 집합에 속해있는 거니까
            set_union(uset, vset);
            edge_accepted++;
            printf("edge %d(%d,%d) selected\n", e.weight, e.end, e.start);
        }
        i++;
    }
}

int main(void)
{
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    init(g);

    for (int i = 0; i < 7; i++)
    {
        insert_vertex(g);
    }

    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);

    kruskal(g);
    free(g);
    return 0;
}
