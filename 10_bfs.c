#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_QUEUE_SIZE 10

typedef struct
{
    int queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void queue_init(QueueType *Q)
{
    Q->front = Q->rear = 0;
}

int is_empty(QueueType *Q)
{
    return (Q->front == Q->rear);
}

int is_full(QueueType *Q)
{
    return ((Q->rear + 1) % MAX_QUEUE_SIZE == Q->front);
}

void enqueue(QueueType *Q, int item)
{
    if (is_full(Q))
        error("full");
    Q->rear = (Q->rear + 1) % MAX_QUEUE_SIZE;
    Q->queue[Q->rear] = item;
}

int dequeue(QueueType *Q)
{
    if (is_empty(Q))
        error("empty");
    Q->front = (Q->front + 1) % MAX_QUEUE_SIZE;
    return Q->queue[Q->front];
    // front는 비어있는 곳
}

#define MAX_VERTICES 50

typedef struct GraphType
{
    int n;
    //노드가 총 몇개 있는지
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

void graph_init(GraphType *G)
{
    G->n = 0;
    for (int r = 0; r < MAX_VERTICES; r++)
        for (int c = 0; c < MAX_VERTICES; c++)
            G->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType *G, int v)
{
    //여기서 v는 vertex의 이름인데, 여기서는 필요 없겠지
    // int형이 아니라 vertex에도 여러 정보가 있다면 사용
    if (((G->n) + 1) > MAX_VERTICES)
    {
        fprintf(stderr, "input error");
        return;
    }
    G->n++;
}

void insert_edge(GraphType *G, int start, int end)
{
    if (start >= G->n || end >= G->n)
    {
        fprintf(stderr, "input error");
        return;
    }
    G->adj_mat[start][end]++;
    G->adj_mat[end][start]++;
}

void bfs_mat(GraphType *G, int v)
{
    // v는 시작점
    int w, u;
    QueueType Q;
    queue_init(&Q);

    // visited[v] = TRUE;
    // printf("%d visited ->", v);
    // // visited가 실행된 순간 방문된 것
    enqueue(&Q, v);
    visited[v]=TRUE;

    while (!is_empty(&Q))
    {
        v = dequeue(&Q);
        printf("%d visited-> ", v);
        for (int w = 0; w < G->n; w++)
        {
            // w의 인접정점 중에서, 방문되지 않은 것 enqueue
            if (G->adj_mat[v][w] && !visited[w])
            {
                enqueue(&Q, w);
                visited[w]=TRUE;
                //queue에 넣는 순간 TRUE 가 되어야만 함
            }
        }
    }
}

int main()
{
    GraphType G;
    graph_init(&G);

    for (int i = 0; i < 4; i++)
    {
        insert_vertex(&G, i);
    }

    insert_edge(&G, 0, 1);
    insert_edge(&G, 0, 2);
    insert_edge(&G, 0, 3);
    insert_edge(&G, 1, 2);
    insert_edge(&G, 2, 3);
    bfs_mat(&G, 0);
    printf("\n");
}