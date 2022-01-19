#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 101

#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct Node
{
    int vertex;
    struct Node *link;
} Node;

typedef struct GraphType
{
    int n;
    Node *adj_ver[MAX_VERTICES];
} GraphType;

void init(GraphType *G)
{
    G->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        G->adj_ver[i] = NULL;
}

void insert_vertex(GraphType *G, int n)
{
    G->n = n;
}

void insert_edge(GraphType *G, int v1, int v2)
{
    Node *p = (Node *)malloc(sizeof(Node *));
    p->vertex = v1;

    Node *q = (Node *)malloc(sizeof(Node *));
    q->vertex = v2;

    q->link = G->adj_ver[v1];
    G->adj_ver[v1] = q;

    p->link = G->adj_ver[v2];
    G->adj_ver[v2] = p;
}

void print_graph(GraphType *G)
{
    for (int i = 0; i < G->n; i++)
    {
        printf("vertex %d : ", i);
        for (Node *temp = G->adj_ver[i]; temp != NULL; temp = temp->link)
            printf("%d ", temp->vertex);
        printf("\n");
    }
}

void dfs(GraphType *G, int v)
{
    visited[v] = TRUE;

    for (Node *tmp = G->adj_ver[v]; tmp != NULL; tmp = tmp->link)
    {
        if (visited[tmp->vertex] == FALSE)
        {
            dfs(G, tmp->vertex);
        }
    }
}

int main()
{
    GraphType G;
    init(&G);

    int computer, edge, a, b;
    scanf(" %d", &computer);
    scanf(" %d", &edge);

    insert_vertex(&G, computer);

    for (int i = 0; i < edge; i++)
    {
        scanf(" %d %d", &a, &b);
        insert_edge(&G, a - 1, b - 1);
    }
    dfs(&G, 0);
    int count = 0;
    for (int i = 0; i < G.n; i++)
    {
        if (visited[i] == TRUE)
            count++;
    }
    printf("%d\n", count - 1);
    return 0;
}