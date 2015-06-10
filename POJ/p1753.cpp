#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;

const int MAXN = 8;
const int INF = 0x3f3f3f3f;

int fx[] = {-1, 0, 1, 0, 0};
int fy[] = {0, 1, 0, -1, 0};
char mat[MAXN][MAXN];

void flip(int x, int y) {
    static char t = 'w' ^ 'b';
    for(int i = 0; i < 5; ++i)
        mat[x + fx[i]][y + fy[i]] ^= t;
}

int dfs(int dep, int cnt) {
    if(dep == 16) {
        for(int i = 1; i <= 4; ++i)
            for(int j = 1; j <= 4; ++j)
                if(mat[i][j] != mat[1][1]) return INF;
        return cnt;
    } else {
        int res = INF, x = dep / 4 + 1, y = dep % 4 + 1;
        res = min(res, dfs(dep + 1, cnt));
        flip(x, y);
        res = min(res, dfs(dep + 1, cnt + 1));
        flip(x, y);
        return res;
    }
}

int main() {
    for(int i = 1; i <= 4; ++i) scanf("%s", mat[i] + 1);
    int res = dfs(0, 0);
    if(res != INF) printf("%d\n", dfs(0, 0));
    else puts("Impossible");
}
