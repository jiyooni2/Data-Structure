#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int visited[MAX_VERTICES];
#define TRUE 1
#define FALSE 0

typedef struct GraphType
{
    int n;
    int adj_ver[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void init(GraphType *G)
{
    G->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        for (int j = 0; j < MAX_VERTICES; j++)
            G->adj_ver[i][j] = 0;
    }
}

void insert_vertex(GraphType *G)
{
    G->n++;
}

void insert_edge(GraphType *G, int v1, int v2)
{
    G->adj_ver[v1][v2]++;
    G->adj_ver[v2][v1]++;
}

void dfs_mat(GraphType *G, int v)
{
    visited[v] = TRUE;
    printf("%d visited -> ", v);

    for (int i = 0; i < G->n; i++)
    {
        if ((G->adj_ver[v][i] != 0) && !visited[i])
        {
            dfs_mat(G, i);
        }
    }
}

int main()
{
    GraphType G;
    init(&G);
    for (int i = 0; i < 6; i++)
        insert_vertex(&G);

    insert_edge(&G, 0, 1);
    insert_edge(&G, 0, 5);
    insert_edge(&G, 1, 2);
    insert_edge(&G, 1, 4);
    insert_edge(&G, 2, 3);
    dfs_mat(&G, 0);
}