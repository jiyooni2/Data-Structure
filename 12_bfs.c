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

typedef struct Queue
{
    int front, rear;
    int queue[MAX_VERTICES];
} Queue;

void init_queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = 0;
}

void error(char *msg)
{
    fprintf(stderr, msg);
    exit(-1);
}

int is_empty(Queue *Q)
{
    return (Q->front == Q->rear);
}

int is_full(Queue *Q)
{
    return ((Q->rear + 1) % MAX_VERTICES == (Q->front));
}

void enqueue(Queue *Q, int item)
{
    if (is_full(Q))
        error("full");

    Q->rear = (Q->rear + 1) % MAX_VERTICES;
    Q->queue[Q->rear] = item;
}

int dequeue(Queue *Q)
{
    if (is_empty(Q))
        error("Empty");
    Q->front = (Q->front + 1) % MAX_VERTICES;

    return (Q->queue[Q->front]);
}

void print_queue(Queue *Q)
{
    if (is_empty(Q))
        return;
    printf("\nqueue :");
    for (int i = Q->front + 1; i != Q->rear; i = (i + 1) % MAX_VERTICES)
        printf("%d ", Q->queue[i]);
    printf("%d ", Q->queue[Q->rear]);
    printf("\n");
}

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

void bfs_mat(GraphType *G, int v)
{
    Queue Q;
    int w;
    init_queue(&Q);

    enqueue(&Q, v);
    visited[v] = TRUE;
    printf("%d visited -> ", v);

    while (!is_empty(&Q))
    {
        w = dequeue(&Q);

        for (int i = 0; i < G->n; i++)
        {
            if ((!visited[i]) && (G->adj_ver[w][i] != 0))
            {

                enqueue(&Q, i);
                visited[i] = TRUE; //밖에서 visited 처리해주면, 중복되어서 안됨
                //이 루프 돌 때, 다음 루프에서 이미 방문했음에도 불구하고 다시
                printf("%d visited ->", i);
            }
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

    bfs_mat(&G, 0);
    return 0;
}
