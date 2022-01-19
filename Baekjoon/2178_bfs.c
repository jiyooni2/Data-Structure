#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10000

int arr[100][100], M, N, count = 0, min_dist = 10000;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

typedef struct element
{
    int x;
    int y;
    int level;
} element;

typedef struct Queue
{
    element item[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void init(Queue *Q)
{
    Q->front = Q->rear = 0;
}

int is_empty(Queue *Q)
{
    return (Q->front == Q->rear);
}

void enqueue(Queue *Q, int x, int y, int level)
{
    element *temp = (element *)malloc(sizeof(element));
    temp->x = x;
    temp->y = y;
    temp->level = level;

    Q->item[++(Q->rear)] = *temp;
}

element dequeue(Queue *Q)
{
    return (Q->item[++(Q->front)]);
}

Queue Q;

void bfs(int x, int y)
{
    arr[x][y] = 0;
    int level;
    enqueue(&Q, x, y, 1);

    element temp;
    while (!is_empty(&Q))
    {
        temp = dequeue(&Q);
        level = temp.level;
        for (int i = 0; i < 4; i++)
        {
            int xx = temp.x + dx[i];
            int yy = temp.y + dy[i];
            if (xx < 0 || xx >= M || yy < 0 || yy >= N || arr[xx][yy] == 0)
                continue;
            else if (xx == (M - 1) && yy == (N - 1))
            {
                printf("%d\n", level + 1);
                return;
            }
            else if (arr[xx][yy] == 1)
            {
                arr[xx][yy] = 0;
                enqueue(&Q, xx, yy, level + 1);
            }
        }
    }
}

void dfs(int x, int y)
{
    arr[x][y] = 0;

    for (int i = 0; i < 4; i++)
    {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx < 0 || xx >= M || yy < 0 || yy >= N || arr[xx][yy] == 0)
            continue;
        else if (xx == (M - 1) && yy == (N - 1))
        {
            if (min_dist > (count + 1))
            {
                min_dist = count + 1;
            }
            arr[xx][yy] = 1;
            return;
        }
        else if (arr[xx][yy] == 1)
        {
            ++count;
            dfs(xx, yy);
            arr[xx][yy] = 1;
            count--;
        }
    }
    return;
}

int main()
{
    init(&Q);
    scanf(" %d %d", &M, &N);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            scanf("%1d", &arr[i][j]);

    bfs(0, 0);

    return 0;
}