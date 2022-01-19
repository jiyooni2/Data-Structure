#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1002

int visited[MAX_VERTICES] = {0};
int bfs_visited[MAX_VERTICES] = {0};

#define MAX_QUEUE_SIZE 1002

typedef struct
{
    int queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

typedef struct Node
{
    int vertex;
    struct Node *link;
} Node;

typedef struct GraphType
{
    int n; // vertext 갯수
    Node *adj_list[MAX_VERTICES];
} GraphType;

void queue_init(QueueType *Q)
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
    // front는 비어있는 곳
}

void init(GraphType *G)
{
    G->n = 0;

    for (int v = 0; v < MAX_VERTICES; v++)
        G->adj_list[v] = NULL;
}

void insert_vertex(GraphType *G, int n)
{
    G->n = n;
}

void print_graph(GraphType *G)
{
    for (int i = 0; i < G->n; i++)
    {
        printf("vertex %d : ", i);
        for (Node *temp = G->adj_list[i]; temp != NULL; temp = temp->link)
            printf("%d ", temp->vertex);
        printf("\n");
    }
}

void insert_edge(GraphType *G, int v1, int v2)
{
    // v2 자리에 들어갈 것
    Node *p = (Node *)malloc(sizeof(Node));
    p->vertex = v1;

    if (G->adj_list[v2] == NULL)
    {
        p->link = NULL;
        G->adj_list[v2] = p;
    }
    else if (G->adj_list[v2]->link == NULL)
    {
        Node *pre = G->adj_list[v2];
        if (pre->vertex > v1)
        {
            p->link = pre;
            G->adj_list[v2] = p;
        }
        else
        {
            pre->link = p;
            p->link = NULL;
        }
    }
    else
    {

        Node *pre = G->adj_list[v2];
        if (pre->vertex >= v1)
        {
            p->link = pre;
            G->adj_list[v2] = p;
        }
        else
        {
            while ((pre->link != NULL) && (pre->link->vertex) < v1)
            {
                pre = pre->link;
            }

            p->link = pre->link;
            pre->link = p;
        }
    }

    Node *q = (Node *)malloc(sizeof(Node));
    q->vertex = v2;

    if (G->adj_list[v1] == NULL)
    {
        q->link = NULL;
        G->adj_list[v1] = q;
    }
    else if (G->adj_list[v1]->link == NULL)
    {
        Node *pre = G->adj_list[v1];
        if (pre->vertex > v2)
        {
            q->link = pre;
            G->adj_list[v1] = q;
        }
        else
        {
            pre->link = q;
            q->link = NULL;
        }
    }
    else
    {
        Node *pre = G->adj_list[v1];
        if (pre->vertex >= v2)
        {
            q->link = pre;
            G->adj_list[v1] = q;
        }
        else
        {
            while ((pre->link != NULL) && (pre->link->vertex) < v2)
            {
                pre = pre->link;
            }
            q->link = pre->link;
            pre->link = q;
        }
    }
}

void dfs(GraphType *G, int v)
{
    visited[v] = 1;
    printf("%d ", v + 1);

    for (Node *w = G->adj_list[v]; w != NULL; w = w->link)
    {
        if (!visited[w->vertex])
            dfs(G, w->vertex);
    }
}

void bfs(GraphType *G, int v)
{
    QueueType Q;
    queue_init(&Q);

    enqueue(&Q, v);
    bfs_visited[v] = 1;

    while (!is_empty(&Q))
    {
        v = dequeue(&Q);
        printf("%d ", v + 1);

        for (Node *w = G->adj_list[v]; w != NULL; w = w->link)
        {
            if (bfs_visited[w->vertex] == 0)
            {
                enqueue(&Q, w->vertex);
                bfs_visited[w->vertex] = 1;
            }
        }
    }
}

int main()
{

    GraphType G;
    init(&G);
    int N, M, V;
    scanf(" %d %d %d", &N, &M, &V);

    insert_vertex(&G, N);
    int a, b;
    for (int i = 0; i < M; i++)
    {
        scanf(" %d %d", &a, &b);
        insert_edge(&G, a - 1, b - 1);
    }

    dfs(&G, V - 1);
    printf("\n");
    bfs(&G, V - 1);
    printf("\n");

    return 0;
}