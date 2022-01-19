#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 20000
#define INF 11 /* 무한대 (연결이 없는 경우) */

#define min(a, b) ((a < b) ? a : b)

int V, E, K;

typedef struct GraphType
{
    int n;
} GraphType;

int distance[MAX_VERTICES];
int visited[MAX_VERTICES];
int weight[MAX_VERTICES][MAX_VERTICES];

void init(GraphType *G)
{
    for (int i = 0; i < G->n; i++)
        for (int j = 0; j < G->n; j++)
            weight[i][j] = INF;
}
void insert_Vertex(GraphType *G, int n)
{
    G->n = n;
}

void insert_edge(int start, int end, int w)
{
    if (weight[start][end] > w)
    {
        weight[start][end] = w;
    }
}

int choose(int n)
{
    int i, min, minpos;
    min = INF;
    minpos = -1;
    for (i = 0; i < n; i++)
    {
        if (distance[i] < min && !visited[i])
        {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void shortest_path(GraphType *G, int start)
{
    int i, u, w;
    for (i = 0; i < G->n; i++)
    {
        distance[i] = weight[start][i];
        visited[i] = FALSE;
    }
    distance[start] = 0;
    visited[start] = TRUE;

    for (i = 0; i < G->n - 1; i++)
    {
        u = choose(G->n);
        if (u == -1)
        {
            return;
        }

        visited[u] = TRUE;
        for (w = 0; w < G->n; w++)
        {
            if (!visited[w])
            {
                if (distance[w] > weight[u][w] + distance[u])
                    distance[w] = weight[u][w] + distance[u];
            }
        }

        //     for (int i = 0; i < G->n; i++)
        //         printf("%d ", distance[i]);
        //     printf("\n");
    }
}

int main(void)
{

    scanf(" %d %d", &V, &E);
    scanf(" %d", &K);

    GraphType G;
    insert_Vertex(&G, V);
    init(&G);
    int u, v, w;
    for (int i = 0; i < E; i++)
    {
        scanf(" %d %d %d", &u, &v, &w);
        insert_edge(u - 1, v - 1, w);
    }

    shortest_path(&G, K - 1);
    for (int i = 0; i < G.n; i++)
    {
        if (distance[i] == INF)
            printf("INF\n");
        else
        {
            printf("%d\n", distance[i]);
        }
    }

    return 0;
}