#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)
int count, N, arr[100][100], var[100];
// var[단지번호] = 단지 수

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

void dfs(int x, int y)
{
    var[count]++;
    arr[x][y] = 0;
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dx[i];
        int yy = y + dy[i];

        if (xx < 0 || xx >= N || yy < 0 || yy >= N || arr[xx][yy] == 0)
        {
            continue;
        }
        else if (arr[xx][yy] == 1)
        {
            dfs(xx, yy);
        }
    }
    return;
}

int main()
{
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%1d", &arr[i][j]);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (arr[i][j] == 1)
            {
                count++;
                dfs(i, j);
            }
        }
    }

    int tmp = 1, max = var[1];
    for (int i = 1; i <= count; i++)
    {
        if (max < var[i])
        {
            max = var[i];
            tmp = i;
        }
    }
    printf("%d\n", tmp);

    for (int i = 1; i <= count; i++)
    {
        printf("%d\n", var[i]);
    }

    return 0;
}