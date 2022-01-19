#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 50

int visited[MAX_VERTICES];

typedef struct Vertex
{
    int no;
    int w;
    struct Vertex *next;
} Vertex;

typedef struct
{
    int vCount;
    Vertex *v[MAX_VERTICES];
} Graph;

void init(Graph *G)
{
    G->vCount = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        G->v[i] = NULL;
}

void makeVertex(Graph *G)
{
    G->vCount++;
}

void insertEdge(Graph *G, int w, int v1, int v2)
{

    if (v1 == v2)
    {
        Vertex *k = (Vertex *)malloc(sizeof(Vertex));
        k->w = w;
        k->no = v1;
        k->next = G->v[v1]; // insert가 마지막에 되는게 아님 처음에 됨 주의!!!
        G->v[v1] = k;
        //최근에 insert된게 head list가 됨
        return;
    }
    // v1은 v2에 붙힘
    Vertex *q = (Vertex *)malloc(sizeof(Vertex));
    q->w = w;
    q->no = v1;
    q->next = G->v[v2];
    G->v[v2] = q;

    // v2는 v1에 붙힘
    Vertex *p = (Vertex *)malloc(sizeof(Vertex));
    p->w = w;
    p->no = v2;
    p->next = G->v[v1];
    G->v[v1] = p;
}

void dfs_list(Graph *G, int v)
{
    visited[v] = TRUE;
    printf("%d visited -> ", v);
    for (Vertex *w = G->v[v]; w != NULL; w = w->next)
    {
        if (!visited[w->no])
        {
            dfs_list(G, w->no);
        }
    }
}

int main()
{
    Graph G;
    init(&G);
    for (int i = 0; i < 4; i++)
        makeVertex(&G);

    insertEdge(&G, 1, 0, 1);
    insertEdge(&G, 1, 0, 2);
    insertEdge(&G, 1, 0, 3);
    insertEdge(&G, 1, 1, 2);
    insertEdge(&G, 1, 2, 3);

    dfs_list(&G, 0);
    return 0;
}