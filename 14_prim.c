#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType
{
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertex(int n)
{
    int v;
    for (int i = 0; i < n; i++)
    {
        if (!selected[i])
        {
            v = i;
            break;
        }
    } //이걸 하는 이유는, 방문된 애의 distance를 잡을 수는 없으니까
    for (int i = 0; i < n; i++)
        if (!selected[i] && (distance[i] < distance[v]))
            v = i;
    //결국 v는 방문안된 노드들 중에서 distance가 제일 작은 node
    return v;
}

void prim(GraphType *G, int v)
{
    for (int i = 0; i < G->n; i++)
        distance[i] = INF;

    distance[v] = 0; //방문되었으면 distacne = 0

    for (int i = 0; i < G->n; i++)
    {
        int u = get_min_vertex(G->n); //방문되지 않은 노드 중 distance min.인 node

        selected[u] = TRUE;
        printf("%d selected\n", u);

        // distance update
        for (int j = 0; j < G->n; j++)
        {
            //원래 길과 u를 통해서 가는 길과 비교, 짧은 것을 distance로 채택
            if ((!selected[j]) && (G->weight[u][j] < distance[j]))
                distance[j] = G->weight[u][j];
        }
    }
}

int main(void)
{
    GraphType g = {7,
                   {{0, 29, INF, INF, INF, 10, INF},
                    {29, 0, 16, INF, INF, INF, 15},
                    {INF, 16, 0, 12, INF, INF, INF},
                    {INF, INF, 12, 0, 22, INF, 18},
                    {INF, INF, INF, 22, 0, 27, 25},
                    {10, INF, INF, INF, 27, 0, INF},
                    {INF, 15, INF, 18, 25, INF, 0}}};
    prim(&g, 0);
    return 0;
}