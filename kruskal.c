#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

void set_init(int n)
{
    //내 대가리를 다 나라고 지정
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

int set_find(int curr)
{
    //내 대가리가 누구인가 반환
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

//대가리 다르면 합친다, 특정 상황에서만 합칠거야
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
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

void graph_init(GraphType *G)
{
    G->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++)
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

void insert_edge(GraphType *G, int start, int end, int w)
{
    G->edges[G->n].start = start;
    G->edges[G->n].end = end;
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
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;

    set_init(G->vertex);
    qsort(G->edges, G->n, sizeof(struct Edge), compare);
    // G->edges에 다 정렬이 되어있음
    int i = 0;
    while (edge_accepted < (G->vertex - 1))
    {
        if (i >= G->n)
        {
            printf("no spanning tree");
            break;
        }

        e = G->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);
        //정점 u,v 집합

        if (uset != vset)
        {
            //대가리가 같으면, cycle이다!
            printf("edge (%d,%d) %d select\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
            //최단경로끼리 같은 집합에 쏘옥 쏙쏙
        }
        i++;
    }
}

int main(void)
{
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    graph_init(g);

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
