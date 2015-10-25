#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 105;

int fx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int fy[] = {-1, -1, -1, 0, 1, 1, 1, 0};

char mat[MAXN][MAXN];
int n, m, res;

void dfs(int x, int y) {
    mat[x][y] = 0;
    for(int f = 0; f < 8; ++f) {
        int newx = x + fx[f], newy = y + fy[f];
        if(mat[newx][newy] == 'W') dfs(newx, newy);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%s", mat[i] + 1);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            if(mat[i][j] != 'W') continue;
            res++;
            dfs(i, j);
        }
    printf("%d\n", res);
}
