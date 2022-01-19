#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */

typedef struct GraphType
{
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; /* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];    /* 방문한 정점 표시 */

// distance중에서 제일 작은것 choose
int choose(int n)
{
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++)
        if (distance[i] < min && !found[i])
        {
            //방문되지 않은 것중에서, 제일 짧은 것
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

void dijkstra(GraphType *G, int v)
{
    int n;
    for (int i = 0; i < G->n; i++)
    {
        distance[i] = G->weight[v][i]; // distance 시작점에서의 거리로 초기화
        found[i] = FALSE;
    }
    found[v] = TRUE;
    printf("%d choose\n", v);

    for (int i = 0; i < G->n - 1; i++)
    {
        n = choose(G->n);
        found[n] = TRUE;
        printf("%d choose\n", n);

        for (int j = 0; j < G->n; j++)
        {
            //방문되지 않은 것 중에서, distance update
            // n이 추가되었으니까, n을 통한 경로와 원래 distance와 비교
            if (!found[j] && distance[j] > distance[n] + G->weight[n][j])
                distance[j] = distance[n] + G->weight[n][j];
        }
    }
}

int main(void)
{
    GraphType g = {7,
                   {{0, 7, INF, INF, 3, 10, INF},
                    {7, 0, 4, 10, 2, 6, INF},
                    {INF, 4, 0, 2, INF, INF, INF},
                    {INF, 10, 2, 0, 11, 9, 4},
                    {3, 2, INF, 11, 0, INF, 5},
                    {10, 6, INF, 9, INF, 0, INF},
                    {INF, INF, INF, 4, 5, INF, 0}}};
    dijkstra(&g, 0);
    return 0;
}