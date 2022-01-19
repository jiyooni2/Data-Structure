#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_QUEUE_SIZE 10000

#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct QueueType
{
    int front, rear;
    int queue[MAX_QUEUE_SIZE];
} QueueType;

void init_queue(QueueType *Q)
{
    Q->front = Q->rear = 0;
}

int is_empty(QueueType *Q)
{
    return (Q->front == Q->rear);
}

void enqueue(QueueType *Q, int item)
{
    Q->rear = (Q->rear + 1) % MAX_QUEUE_SIZE;
    Q->queue[Q->rear] = item;
}

int dequeue(QueueType *Q)
{
    Q->front = (Q->front + 1) % MAX_QUEUE_SIZE;
    return Q->queue[Q->front];
}

typedef struct Graph
{
    int n;
    int *adj_mat[MAX_VERTICES];
} Graph;

void init_graph(Graph *G)
{
    G->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        G->adj_mat[i] = (int *)malloc(MAX_VERTICES * sizeof(int));
    }

    for (int r = 0; r < MAX_VERTICES; r++)
        for (int c = 0; c < MAX_VERTICES; c++)
            G->adj_mat[r][c] = 0;
}

void insert_vertex(Graph *G, int n)
{
    G->n = n;
}

void insert_edge(Graph *G, int v1, int v2)
{
    (G->adj_mat[v1][v2])++;
    (G->adj_mat[v2][v1])++;
}

void dfs_mat(Graph *G, int v)
{
    QueueType Q;
    init_queue(&Q);

    enqueue(&Q, v);
    printf("%d visited",v);
    visited[v]=TRUE;

    while (!is_empty(&Q))
    {
        v = dequeue(&Q);

        for (int w = 0; w < G->n; w++)
        {
            if (G->adj_mat[v][w] && visited[w] == FALSE)
            {
                
                visited[w] = TRUE;
                printf("%d visited ->", w);
                enqueue(&Q, w);
            }
        }
    }
}

int main()
{
    Graph G;
    init_graph(&G);
    insert_vertex(&G, 4);

    insert_edge(&G, 0, 1);
    insert_edge(&G, 0, 2);
    insert_edge(&G, 0, 3);
    insert_edge(&G, 1, 3);
    insert_edge(&G, 2, 3);

    dfs_mat(&G, 0);

    return 0;
}