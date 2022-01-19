#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

int arr[100][100], M, N, count = 0, min_dist = 10000;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

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
    scanf(" %d %d", &M, &N);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            scanf("%1d", &arr[i][j]);
    count++;
    dfs(0, 0);

    printf("%d\n", min_dist);

    return 0;
}